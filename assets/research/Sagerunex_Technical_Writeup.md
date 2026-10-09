# Sagerunex: Reverse Engineering a Proxy-Aware Windows Backdoor

**A Complete Static Malware Analysis and Command-and-Control Investigation**

**Author:** Mostafa Galal  
**Challenge:** MalOps — Sagerunex  
**Category:** Malware Analysis / Reverse Engineering  
**Difficulty:** Medium  
**Challenge Score:** 260 / 260  
**Analysis Environment:** Ghidra, Windows x64 PE Analysis  
**Methodology:** Static Reverse Engineering and Control-Flow Reconstruction

---

# Abstract

Sagerunex is a Windows backdoor whose implementation incorporates several mechanisms for evading casual inspection, managing configuration data, communicating through restricted networks, and executing commands supplied by a remote controller.

This investigation examines a 64-bit DLL sample associated with the MalOps Sagerunex challenge. Using Ghidra, we reconstructed the relationships between the sample's initialization routine, data-decoding functions, access-token manipulation, configuration management, C2 communication loop, proxy discovery routines, command dispatcher, and file-transfer implementation.

The analysis identified a 1,888-byte XOR-processed memory region, a separate 1,600-byte RC4-like protected configuration, five configurable C2 server slots, operating-hour restrictions, and a retry mechanism with five-minute and thirty-minute delays. The sample also contains logic for impersonating an `explorer.exe` security token, manipulating file timestamps, discovering network proxy configurations, executing remote commands, and transmitting files in 48 KiB chunks.

A defining characteristic of the sample is its support for multiple proxy discovery mechanisms, including registry-based Windows proxy settings, Firefox configuration files, WPAD, and automatic proxy selection. These capabilities make the malware particularly relevant to enterprise network environments where direct external connections may be restricted.

The investigation also highlights an important distinction between challenge-accepted answers and independently interpreted binary behavior. One configuration offset accepted by the challenge does not align cleanly with the apparent start/end semantics of the decompiled work-hour comparison.

**Scope and evidence limitations:** This report uses the PE metadata, assembly, and Ghidra decompilation collected during the investigation. The original sample was not available for independent re-execution in this reporting session. No real C2 hostname or IP address, sample hash, complete decoded configuration, or confirmed autostart mechanism was recovered. These details are deliberately not fabricated.

---

# 1. Investigation Background

The scenario begins with a suspicious email concerning an invoice update. The email contains a password-protected ZIP archive whose password is `infected`.

After interaction with the attachment, a Windows workstation reportedly begins generating background HTTPS activity even though the employee is not actively browsing the Internet.

This behavior creates several investigative possibilities: a malicious process could be maintaining an outbound C2 session, a loader could have introduced a persistent implant, or a legitimate process could have been abused as part of the execution chain.

The supplied executable was therefore examined to answer four central questions:

1. How does the malicious code initialize and establish its execution context?
2. How does it process configuration and select C2 infrastructure?
3. What remote capabilities does the backdoor expose?
4. What artifacts and behaviors can be recovered for detection and further investigation?

The analysis focuses on the code that was actually recovered rather than assuming that every scenario detail can be demonstrated from the DLL alone.

## 1.1 Sample profile

| Property | Observation |
|---|---|
| Malware | Sagerunex |
| File format | Windows PE32+ DLL |
| Architecture | AMD64 / x86-64 |
| PE machine identifier | `0x8664` |
| Exported module name | `MainDLL.dll` |
| Exported routine | `MainEntry` |
| Main routine address | `0x1800064C8` |
| Reported PE timestamp | March 15, 2021, 09:44:36 UTC |
| Primary analysis tool | Ghidra |
| SHA-256 | Not recovered |
| Actual C2 addresses | Not recovered |

## 1.2 Reconstructed execution architecture

The functions examined during the investigation suggest the following high-level execution architecture:

```text
Reported phishing attachment
          |
          v
64-bit Windows DLL
          |
          v
MainEntry
          |
          +-- Initialize temporary logging
          |
          +-- Evaluate magic value 0xC91F3B
          |       |
          |       +-- Locate explorer.exe
          |       +-- Open and duplicate token
          |       +-- Impersonate token
          |
          +-- Decode embedded data using XOR
          |
          v
Main Beacon Routine
FUN_180002884
          |
          +-- Construct APPDATA config path
          +-- Load or initialize configuration
          +-- Transform RC4-like config data
          +-- Validate work-hour restrictions
          +-- Select one of five C2 slots
          |
          v
C2 Connection Routine
FUN_1800033dc
          |
          +-- Configured proxy
          +-- WPAD proxy
          +-- IE proxy
          +-- Firefox proxy
          +-- Automatic proxy
          +-- Preconfigured connection
          |
          v
C2 Session / Command Dispatcher
FUN_180003c40
          |
          +-- Registration
          +-- Remote process execution
          +-- DLL execution
          +-- Windows shell commands
          +-- File transfer
          |
          v
Retry / Beacon Scheduling
```

This diagram represents function relationships and apparent behavioral flow. It is not a complete dynamically observed execution trace.

---

# 2. Finding 01 — PE Compilation Timestamp

**Question:** What is the compilation timestamp of the malware?

**Answer:** `2021-03-15 09:44:36`

**Ghidra location:** PE File Header, near `0x180000100`

The first step in the investigation was examining the Portable Executable metadata.

The PE header contains a timestamp field named `TimeDateStamp`, stored inside the `IMAGE_FILE_HEADER` structure.

The recovered value was:

```c
TimeDateStamp = 0x604F2C84;
```

Interpreted as a Unix-style timestamp, this value corresponds to March 15, 2021, at 09:44:36 UTC.

The PE header also identifies the machine type as AMD64, consistent with the 64-bit code addresses and pointer arithmetic observed later in the investigation.

## Technical interpretation

The timestamp is useful for organizing samples and performing timeline analysis. It can help determine whether multiple binaries plausibly belong to the same build period.

However, compilation timestamps cannot be considered authoritative. Attackers, packers, build systems, and binary modification tools may alter the `TimeDateStamp` field.

Consequently, the correct interpretation is that the binary **reports** a timestamp of March 15, 2021, not that its actual compilation date has been independently proven.

**Screenshot 01:** Ghidra PE File Header showing `Machine = 0x8664` and `TimeDateStamp = 0x604F2C84`.

---

# 3. Finding 02 — Malware Log Filename

**Question:** What log filename is created by the malware?

**Answer:** `TS_FB56.tmp`

**Ghidra function:** `MainEntry`

During initialization, the malware retrieves the current temporary directory using the Windows API:

```c
GetTempPathW(...);
```

It then appends a fixed filename using a wide-character string operation:

```c
wcscat_s(..., L"\\TS_FB56.tmp");
```

The constructed path follows the pattern:

```text
%TEMP%\TS_FB56.tmp
```

The resulting string is passed into the logging initialization routine associated with `FUN_18000210c`.

Additional diagnostic strings in the sample include:

```text
0x00, ST.
0x00, SM.
0x01, RC success.
0x01, RC failed.
0x01, CN failed.
```

These log messages suggest that the malware maintains internal operational reporting for initialization and communication stages.

## Security significance

A fixed log filename creates a potentially useful forensic artifact. Investigators can search for the filename and correlate its existence with suspicious processes, file creation events, and other malware behavior.

The filename alone should not be treated as definitive evidence of infection, and the presence of a string-construction routine does not prove that the file was successfully written on every execution.

The evidence does establish that the sample is programmed to construct and use this path.

**Screenshot 02:** `MainEntry`, highlighting `GetTempPathW`, the `TS_FB56.tmp` string, and the logging setup call.

---

# 4. Finding 03 — Magic Value Controlling Token Impersonation

**Question:** What magic value controls the token impersonation path?

**Answer:** `0xC91F3B`

**Ghidra function:** `MainEntry`

The main routine compares a local value with a specific constant before invoking a token-related helper.

A simplified representation of the observed control flow is:

```c
if (local_e274 == 0xC91F3B) {
    FUN_180003294(...);
}
```

The comparison is important because the token impersonation behavior is conditional.

It is not simply executed unconditionally during every invocation of the exported routine.

## Technical analysis

The constant acts as a control value for an execution branch.

Such checks are common in malware initialization code and may depend on configuration, loader-supplied arguments, decoded data, or execution state.

In this sample, the branch leads to a routine that attempts to obtain and impersonate another process's security token.

The precise origin of `local_e274` needs complete data-flow reconstruction before labeling the constant as an authentication token, configuration signature, or anti-analysis trigger.

The supported conclusion is narrower: `0xC91F3B` gates the observed impersonation path.

## Security significance

Conditional execution can complicate sandbox analysis because a behavior may not appear unless its controlling value is present.

This also demonstrates why branch analysis is important. Identifying a sensitive API call does not automatically establish that the API executes along every program path.

**Screenshot 03:** `MainEntry`, with `0xC91F3B`, the conditional branch, and the call to `FUN_180003294` highlighted.

---

# 5. Finding 04 — XOR Configuration Data Size

**Question:** How many bytes are processed by the XOR routine?

**Answer:** `1888`

**Hexadecimal:** `0x760`

**Ghidra function:** `FUN_1800061bc`

The main routine invokes an in-memory data transformation:

```c
FUN_1800061bc(abStack_e7c0, 0x760);
```

The second argument represents the size of the buffer being processed.

The conversion is:

```text
0x760 = 1888 decimal
```

## Reverse engineering the algorithm

Inspection of the function revealed a reverse-order XOR operation.

A simplified reconstruction of the observed behavior is:

```c
void decode_xor_chain(uint8_t *buffer, size_t size)
{
    if (size == 0)
        return;

    for (size_t i = size - 1; i > 0; --i) {
        buffer[i] ^= buffer[i - 1];
    }

    buffer[0] ^= 0xAD;
}
```

The last statement applies an XOR operation to the first byte using the constant:

```text
0xAD
```

The remaining bytes are decoded using the previous stored byte.

## Why reverse iteration matters

The routine processes the data from the end toward the beginning.

This preserves the previous source byte until it has been used for the current XOR operation.

Reversing the iteration direction in an in-place decoder could alter the decoded output because already transformed bytes would then be reused.

## Security significance

This is an obfuscation mechanism. It obscures a data region from straightforward plaintext inspection without providing the security properties of modern authenticated encryption.

The transformation should not be confused with the separate RC4-like encryption used for the saved configuration file.

**Screenshot 04:** `MainEntry` showing the `0x760` argument, followed by `FUN_1800061bc` showing reverse traversal and the `0xAD` XOR constant.

---

# 6. Finding 05 — Process Targeted for Token Impersonation

**Question:** Which process does the malware target for token impersonation?

**Answer:** `explorer.exe`

**Ghidra functions:**

- `FUN_180003208`
- `FUN_1800031a0`
- `FUN_180003294`

The malware contains a process-enumeration routine that searches for `explorer.exe`.

The relevant Windows APIs include:

```c
CreateToolhelp32Snapshot(...);
Process32FirstW(...);
Process32NextW(...);
```

The process name is compared against:

```c
L"explorer.exe"
```

Once a matching process is identified, the code attempts to open it.

## Dynamic API resolution

A helper at `FUN_1800031a0` reconstructs the string `OpenProcess` and resolves it at runtime.

The resolution sequence involves:

```c
GetModuleHandleA("Kernel32.dll");
GetProcAddress(...);
```

The resulting function pointer is then used to open the target process.

The analyzed code contains an access mask of:

```text
0x1F0FFF
```

Dynamic API resolution can reduce the visibility of an API name in the ordinary import table, although the API may still be recoverable through static or dynamic analysis.

## Token manipulation

The function `FUN_180003294` includes calls to:

```c
OpenProcessToken(...);
DuplicateToken(...);
SetThreadToken(...);
```

The recovered `DuplicateToken` call uses the `SecurityImpersonation` level.

The intended control flow is:

```text
Enumerate processes
      |
Find explorer.exe
      |
Open process handle
      |
OpenProcessToken
      |
DuplicateToken
      |
SetThreadToken
```

This gives the executing thread a mechanism to adopt an impersonation token derived from the target process.

## Security significance

Access-token impersonation can change the security context used by subsequent thread operations.

Its practical impact depends on the original token, access rights, and system security policy.

The observed code establishes an impersonation attempt. It does not independently demonstrate successful privilege escalation to SYSTEM or administrator.

**Screenshot 05:** `FUN_180003208`, `FUN_1800031a0`, and `FUN_180003294`, highlighting process enumeration, dynamic API resolution, and token duplication.

---

# 7. Finding 06 — File Timestomping Year

**Question:** To which year does the malware backdate file timestamps?

**Answer:** `2011`

**Hexadecimal:** `0x7DB`

**Ghidra function:** `FUN_18000208c`

The malware contains a dedicated routine for changing file metadata timestamps.

The routine retrieves the current local time:

```c
GetLocalTime(&systemTime);
```

It then modifies the year field:

```c
systemTime.wYear = 0x7DB;
```

Because:

```text
0x7DB = 2011
```

the resulting timestamp is intended to appear to originate from the year 2011.

The modified value is processed using:

```c
SystemTimeToFileTime(...);
```

and applied through:

```c
SetFileTime(...);
```

The observed call sets creation, access, and modification timestamp fields.

## Technical significance

Changing all three timestamps can make a recently created configuration file appear older.

This may interfere with basic forensic techniques that rely on file creation or modification dates to establish recent activity.

The conversion path begins with local time, so the exact resulting timestamp should be verified before stating its UTC equivalent.

The code is sufficient to identify deliberate timestomping behavior.

**Screenshot 06:** `FUN_18000208c`, highlighting `wYear = 0x7DB`, `SystemTimeToFileTime`, and `SetFileTime`.

---

# 8. Finding 07 — Fallback DNS Server

**Question:** What fallback DNS address is used by the malware?

**Answer:** `8.8.8.8`

**Ghidra function:** `FUN_180002e64`

The sample retrieves the system's network configuration through:

```c
GetNetworkParams(...);
```

It examines DNS-related information and uses a hardcoded fallback when the expected value is missing or unsuitable.

The fallback is:

```text
8.8.8.8
```

This address belongs to Google's public DNS service.

## Technical interpretation

The routine demonstrates that the malware does not exclusively rely on the host's existing DNS configuration.

It can use a predefined resolver address during its network-related operations.

This may help when system configuration is incomplete or differs from what the malware expects.

However, successful communication with a public resolver still depends on the network allowing the relevant traffic.

## IOC consideration

`8.8.8.8` is legitimate public infrastructure.

It must not be labeled as the malware's C2 server solely because it appears in the code.

A detection rule that treats all communication to this DNS address as malicious would produce substantial false positives.

The value is more useful as supporting context when correlated with the malware process and surrounding activity.

**Screenshot 07:** `FUN_180002e64`, showing `GetNetworkParams` and the fallback address.

---

# 9. Finding 08 — Traceroute Completion Message

**Question:** What message indicates completion of the traceroute routine?

**Answer:** `Trace complete.`

**Ghidra function:** `FUN_180002e64`

The same network-discovery function contains code consistent with an ICMP-based traceroute.

The relevant API family includes:

```c
IcmpCreateFile(...);
IcmpSendEcho(...);
IcmpCloseHandle(...);
```

The routine varies the outgoing IP time-to-live value across successive requests.

The observed implementation starts with a low TTL and performs a bounded number of iterations, with a limit of ten attempts in the examined loop.

A TTL-limited probe can help infer the sequence of routers or hops toward a destination.

On reaching its completion condition, the function emits:

```text
Trace complete.
```

## Security significance

Route probing can provide environmental information about the victim network.

A backdoor may use such information for connectivity diagnostics or to understand whether an intended destination is reachable.

The presence of traceroute code does not prove that the routine ran successfully or that a full route was recovered in the affected environment.

It establishes a network reconnaissance or diagnostic capability within the binary.

**Screenshot 08:** `FUN_180002e64`, highlighting the TTL loop, ICMP APIs, and `Trace complete.` string.

---

# 10. Finding 09 — Maximum Beacon Time Counter

**Question:** What is the accumulated beacon time threshold?

**Answer:** `720` minutes

**Hexadecimal:** `0x2D0`

**Ghidra function:** `FUN_180002884`

The central beacon routine maintains a counter associated with its operational loop.

The recovered control flow includes:

```c
iVar22 += uVar6;

if (0x2CF < iVar22) {
    return 1;
}
```

In the corresponding assembly, the comparison uses:

```asm
CMP R15D, 0x2D0
```

The threshold is therefore:

```text
0x2D0 = 720 minutes
```

or twelve hours.

## Technical interpretation

This value limits the counter maintained by the loop.

It is tempting to describe the result as a strict twelve-hour lifetime, but the code does not justify that stronger claim.

The counter increases according to the routine's own delay-accounting logic.

Working-hour waits, event signaling, elapsed execution time, and control-flow branches may cause the actual wall-clock duration to differ.

## Security significance

A bounded beacon loop can reduce indefinite retry behavior and may allow the malware to relinquish control after a configured operational period.

It also affects how an investigator interprets a sample that stops communicating after repeated failures.

**Screenshot 09:** `FUN_180002884`, highlighting the counter increment and comparison against `0x2D0`.

---

# 11. Finding 10 — Number of Configurable C2 Servers

**Question:** How many C2 servers can the malware select from?

**Answer:** `5`

**Ghidra functions:**

- `FUN_180002884`
- `FUN_1800033dc`

The beacon loop contains logic that cycles through five configured server slots.

The connection routine accesses the selected entry through:

```c
lpMultiByteStr = (LPCSTR)(
    (longlong)param_1 +
    (longlong)param_2 * 0x32 +
    0xC858
);
```

This expression reveals two important structural details.

First, the C2 server list begins at:

```text
Session + 0xC858
```

Second, every entry is separated by:

```text
0x32 bytes = 50 bytes
```

## Reconstructed layout

| Slot | Session-relative offset |
|---|---|
| Server 1 | `0xC858` |
| Server 2 | `0xC88A` |
| Server 3 | `0xC8BC` |
| Server 4 | `0xC8EE` |
| Server 5 | `0xC920` |

The total storage occupied by these five slots is:

```text
5 × 0x32 = 0xFA bytes
```

The broader configuration block begins at `0xC848`, sixteen bytes before the first server entry.

## Security significance

Multiple configured C2 entries provide alternatives when a destination is unreachable.

A single failed or blocked server therefore does not necessarily prevent the malware from attempting additional endpoints.

The actual contents of the five slots were not recovered during the supplied analysis.

Consequently, we can identify the configuration capacity and its addressing logic, but cannot provide verified C2 domains or IP addresses.

**Screenshot 10:** `FUN_180002884` showing five-slot rotation and `FUN_1800033dc` showing the `0xC858 + index * 0x32` expression.

---

# 12. Finding 11 — Initial C2 Retry Interval

**Question:** How long does the malware initially wait before retrying a failed C2 connection?

**Answer:** `5` minutes

**Ghidra function:** `FUN_180002884`

When C2 connection attempts fail, the beacon loop enters a delay-controlled retry path.

The code maintains a countdown initialized around ten attempts.

The observed logic selects a five-minute delay while the countdown remains positive and can switch to a thirty-minute delay when the shorter retry phase expires.

A simplified reconstruction is:

```c
retry_count--;

if (retry_count > 0) {
    delay_minutes = 5;
} else {
    delay_minutes = 30;
}

WaitForSingleObject(
    stop_event,
    delay_minutes * 60000
);
```

The expression:

```text
5 × 60000 = 300000 milliseconds
```

corresponds to five minutes.

The longer fallback interval is:

```text
30 × 60000 = 1800000 milliseconds
```

## Technical significance

The retry mechanism introduces a controlled delay between connection attempts.

This can reduce the frequency of repeated failed connections and alter the timing characteristics visible in network telemetry.

The precise number of short-delay iterations depends on the countdown's initialization and update path.

The confirmed answer for the initial retry interval is five minutes.

**Screenshot 11:** `FUN_180002884`, highlighting the failure countdown, five-minute value, thirty-minute fallback, and `WaitForSingleObject`.

---

# 13. Finding 12 — Supported Remote Command Execution Forms

**Question:** Which command execution forms are supported by the malware?

**Answer:** `runexe, rundll, cmd.exe /c`

**Ghidra function:** `FUN_180005628`

One of the most security-relevant functions in the sample is the remote command execution handler.

It interprets received command strings and chooses an execution path based on their structure.

## 13.1 Executable execution: runexe

The `runexe` command form directs the malware to launch an executable using the Windows process-creation API:

```c
CreateProcessA(...);
```

The routine prepares the supplied command line and contains pipe-related logic for collecting process output.

This indicates support for executing commands and potentially reporting their output to the surrounding C2 command-handling subsystem.

## 13.2 DLL execution: rundll

The `rundll` command form causes the function to parse a library name and an exported routine.

The implementation uses:

```c
LoadLibraryA(...);
GetProcAddress(...);
```

This allows the routine to load a DLL and identify a function by its exported name.

The code also contains handling associated with the `DllMain` name.

The exact argument-passing and invocation details require the complete DLL execution branch for a full protocol-level reconstruction.

## 13.3 Windows command shell

Commands not handled by the specialized forms can be wrapped in a Windows command-interpreter invocation.

The malware constructs a command line containing:

```text
cmd.exe /c
```

and launches it with `CreateProcessA`.

This distinction matters: `cmd.exe /c` is an execution string constructed internally rather than necessarily being a third literal prefix tested against the incoming command.

## Security significance

These three mechanisms collectively provide several remote execution capabilities:

- Launching executable programs.
- Loading and invoking DLL exports.
- Executing Windows shell commands.

The recovered code demonstrates execution capability. The investigation did not include an observed live C2 operator issuing these commands.

**Screenshot 12:** `FUN_180005628`, highlighting `runexe`, `rundll`, the constructed `cmd.exe /c` string, and their associated Windows APIs.

---

# 14. Finding 13 — Invalid Command Error Message

**Question:** What error message is returned for an illegal command?

**Answer:** `illegal command`

**Ghidra function:** `FUN_180005628`

The command-execution function validates specialized input formats.

In the DLL execution path, malformed or unsupported syntax can produce the following message:

```text
illegal command\r\n\r\n
```

The challenge accepted the message without the carriage-return and newline characters:

```text
illegal command
```

## Technical interpretation

This validation step demonstrates that the command handler does not blindly interpret every string in the same way.

The function contains at least some format checking before attempting certain execution operations.

The error is associated with the command parser, particularly the handling of DLL execution syntax.

The presence of this error string is also useful for tracing the function's relationships to response-generation code.

**Screenshot 13:** `FUN_180005628`, highlighting the invalid-command branch and error string.

---

# 15. Finding 14 — File Transfer Chunk Size

**Question:** What chunk size does the malware use for file transfers?

**Answer:** `49152` bytes

**Hexadecimal:** `0xC000`

**Size:** 48 KiB

**Ghidra location:** File-transfer routine containing a `ReadFile` call around `0x180004F8F`

The transfer code initializes a read length using:

```c
local_res8[0] = 0xC000;
```

The resulting value is passed to:

```c
ReadFile(
    hFile,
    lpBuffer,
    local_res8[0],
    ...
);
```

The conversion is:

```text
0xC000 = 49152 bytes
```

or:

```text
49152 / 1024 = 48 KiB
```

## Technical interpretation

The code reads file contents into a buffer in bounded blocks.

Chunk-based transfer is useful when a file may be larger than an individual message buffer or network payload.

The final block of a file may contain fewer bytes than the configured maximum read size.

Therefore, 49,152 bytes is the configured maximum requested read length in the examined routine, not proof that every transmitted block is exactly that size.

## Security significance

A fixed chunk size can help reverse engineers identify related data-processing and transmission functions.

It may also help correlate file reads with outbound message construction in a controlled execution trace.

**Screenshot 14:** The enclosing transfer function near `0x180004F8F`, highlighting `0xC000` and `ReadFile`.

---

# 16. Finding 15 — File Transfer Retry Count

**Question:** How many attempts are made when a chunk transfer fails?

**Answer:** `3`

**Ghidra functions:**

- Enclosing file-transfer routine
- `FUN_180003e70`, involved in the sending path

The transfer implementation contains a retry counter.

The relevant comparison is equivalent to:

```c
local_res20 < 3
```

The send routine is called with a command or message identifier of:

```text
0x0D
```

Failed attempts can produce:

```text
0x01, SSD failed %d.
```

## Technical interpretation

The observed loop allows up to three total attempts, assuming the counter is initialized to zero and incremented once for each attempt.

In that interpretation, the retry policy consists of:

1. Initial transmission attempt.
2. First repeat after failure.
3. Second repeat after failure.

This is more precise than saying there are three retries in addition to an initial attempt.

## Security significance

Bounded retry behavior can preserve operational stability when a transfer fails.

It also means that a failed transmission is not necessarily abandoned after the first error.

The available code establishes an intended transfer-and-retry mechanism. It does not prove that any specific file was successfully transmitted during the analyzed scenario.

**Screenshot 15:** Transfer loop showing the call to `FUN_180003e70`, the failure message, and the comparison against three attempts.

---

# 17. Finding 16 — Internet Explorer Proxy Registry Path

**Question:** Which registry subkey does the malware inspect for Internet Explorer proxy settings?

**Answer:**

`\Software\Microsoft\Windows\CurrentVersion\Internet Settings`

**Ghidra function:** `FUN_1800068ac`

The malware attempts to discover proxy configuration through Windows registry data.

The relevant code enumerates user profiles beneath:

```text
HKEY_USERS
```

It then constructs or opens a subkey matching:

```text
HKEY_USERS\<User SID>\Software\Microsoft\Windows\CurrentVersion\Internet Settings
```

The main APIs include:

```c
RegEnumKeyW(...);
RegOpenKeyExW(...);
```

## Technical significance

Windows maintains Internet-related configuration beneath user-specific registry hives.

By enumerating multiple user SID entries rather than relying exclusively on the current process's user context, the malware can discover proxy-related settings associated with different profiles.

This can be valuable when the currently executing thread has an unusual security context or when the network environment uses browser-related proxy configuration.

The examined routine establishes access to the relevant registry path; the precise proxy-value parsing should be verified in its downstream consumers.

**Screenshot 16:** `FUN_1800068ac`, highlighting `RegEnumKeyW`, `RegOpenKeyExW`, and the Internet Settings subkey.

---

# 18. Finding 17 — SID Prefix Used for Registry Filtering

**Question:** What SID prefix is used when enumerating user registry hives?

**Answer:** `S-1-5-21`

**Ghidra function:** `FUN_1800068ac`

During enumeration of `HKEY_USERS`, the malware compares the beginning of each subkey name against:

```text
S-1-5-21
```

The code uses a prefix comparison resembling:

```c
wcsncmp(..., L"S-1-5-21", 8);
```

The prefix is associated with Windows account and domain SID structures.

The implementation also contains checks related to `Classes` subkeys.

## Technical interpretation

Filtering subkeys by their SID prefix helps the routine distinguish likely user profile hives from unrelated registry entries.

This is useful when locating per-user Internet proxy settings.

The behavior also indicates an awareness of Windows registry organization rather than a simple hardcoded lookup against one user.

**Screenshot 17:** `FUN_1800068ac`, highlighting the `S-1-5-21` comparison and associated filtering logic.

---

# 19. Finding 18 — Firefox Configuration Filename

**Question:** Which Firefox configuration file is inspected for proxy settings?

**Answer:** `prefs.js`

**Ghidra function:** `FUN_180006d10`

The malware contains a routine dedicated to discovering Firefox configuration.

The routine first identifies the user's roaming AppData directory through:

```c
SHGetSpecialFolderPathW(..., 0x1A, ...);
```

It then constructs a path associated with:

```text
Mozilla\Firefox\profiles.ini
```

The `profiles.ini` file contains profile metadata, including path information.

The malware uses that metadata to locate a Firefox profile directory.

It then constructs the path to:

```text
prefs.js
```

## Technical significance

Firefox stores numerous user preferences in `prefs.js`, including network proxy settings.

By parsing this file, malware can discover proxy configuration without relying exclusively on Windows Internet Settings.

This supports the broader observation that Sagerunex attempts several possible outbound connectivity methods.

**Screenshot 18:** `FUN_180006d10`, showing the roaming AppData lookup, `profiles.ini`, profile path handling, and `prefs.js`.

---

# 20. Finding 19 — Firefox HTTPS Proxy Preference

**Question:** Which Firefox preference identifies the HTTPS proxy host?

**Answer:** `network.proxy.ssl`

**Ghidra function:** `FUN_180006d10`

After locating the Firefox profile configuration, the malware searches for proxy-related preference strings.

One of the recovered keys is:

```text
network.proxy.ssl
```

The implementation also references:

```text
network.proxy.ssl_port
```

These settings can describe an HTTPS proxy hostname and its associated port.

## Technical interpretation

Firefox proxy preferences may differ from the settings used by Windows components.

By inspecting both Firefox and Windows Internet proxy configuration, the malware increases the number of potential network paths available to its connection logic.

This behavior is particularly notable in environments where applications use different proxy settings.

The code establishes the ability to identify these configuration fields; it does not prove that a valid Firefox proxy was configured on the challenge machine.

**Screenshot 19:** `FUN_180006d10`, highlighting `network.proxy.ssl` and `network.proxy.ssl_port`.

---

# 21. Finding 20 — Successful C2 Registration Message

**Question:** What message indicates successful C2 registration?

**Answer:** `0x01, RC success.`

**Ghidra function:** `FUN_180003c40`

The malware contains a communication routine that invokes another function associated with registration or session initialization:

```text
FUN_180006130
```

The return value determines which diagnostic message is emitted.

A nonzero result leads to:

```text
0x01, RC success.
```

A zero result leads to:

```text
0x01, RC failed.
```

## Technical interpretation

This establishes that the code distinguishes between successful and failed communication initialization.

The function is also connected to command dispatch logic.

During the investigation, command identifiers including `0`, `6`, `7`, `8`, `9`, `11`, `15`, `17`, and `18` were observed in the surrounding dispatch structure.

Different branches invoke different handlers.

## Important limitation

The exact registration packet format was not reconstructed from these log strings alone.

To establish the protocol, the complete body of `FUN_180006130` and the relevant transport helpers would need to be examined.

Likewise, numeric command IDs should not be assigned definitive meanings without tracing their corresponding handlers.

**Screenshot 20:** `FUN_180003c40`, highlighting the `FUN_180006130` call and the success/failure messages.

---

# 22. Finding 21 — Configuration Base Offset

**Question:** What is the offset of the configuration block containing the C2 information?

**Answer:** `0xC848`

**Ghidra function:** `FUN_1800027c0`

The function copies or initializes a configuration buffer at:

```text
Session + 0xC848
```

The block size is:

```text
0x640 bytes
```

The first C2 server string begins at:

```text
Session + 0xC858
```

This distinction is important.

## Configuration base versus server array

The configuration base is:

```text
0xC848
```

The first server entry is sixteen bytes later:

```text
0xC848 + 0x10 = 0xC858
```

The first sixteen bytes may contain other configuration fields or header-like data, but their exact semantics were not fully established in the supplied code.

The connection routine directly indexes server strings from `0xC858`.

The challenge accepted `0xC848`, identifying the broader configuration block rather than the first string's immediate location.

## Data flow

The local configuration can be loaded from disk or copied from supplied/default configuration data.

The read and initialization paths ultimately make the configuration available inside the main session structure.

This is the same structure accessed by the C2 beacon loop and connection routines.

**Screenshot 21:** `FUN_1800027c0`, highlighting the `0x640` copy to `+0xC848`, with the first server access at `+0xC858` shown separately.

---

# 23. Finding 22 — Work-Hour Configuration Offset

**Question:** What is the offset of the work-hour start time in the configuration?

**Challenge-accepted answer:** `0xCC50`

**Ghidra functions:**

- `FUN_180002884`
- `FUN_1800027c0`

This was the most ambiguous question in the investigation.

The sample accesses two adjacent configuration fields:

```text
Session + 0xCC4C
Session + 0xCC50
```

The code validates that the values represent acceptable hour numbers.

In particular, the values are expected to be less than 24 and not equal to each other.

## Ghidra pointer-arithmetic detail

The decompiler represents the session pointer as an `undefined4 *` in parts of the code.

Therefore, array indexing is scaled by four bytes.

For example:

```c
param_1[0x3313]
```

corresponds to:

```text
0x3313 × 4 = 0xCC4C
```

Similarly:

```c
param_1[0x3314]
```

corresponds to:

```text
0x3314 × 4 = 0xCC50
```

These are not raw byte offsets equal to the displayed array indices.

## Work-hour logic

The function uses:

```c
GetLocalTime(...);
```

to obtain the current system hour.

It then compares the hour against the two configured bounds.

When the current hour falls outside the permitted interval, it waits and checks again.

The observed comparisons suggest that `0xCC4C` behaves as the lower/start bound while `0xCC50` behaves as the upper/end bound.

However, the challenge accepted:

```text
0xCC50
```

for the work-hour start question.

## Analytical conclusion

Both observations should be preserved:

**Challenge answer:** `0xCC50`

**Code-level interpretation:** The visible branch comparisons suggest `0xCC50` is the upper/end bound.

This may reflect ambiguous challenge terminology, an interpretation error in the challenge's expected answer, or an unresolved nuance elsewhere in the configuration handling.

It should not be presented as definitively resolved without inspecting the complete original structure and its consumers.

**Screenshot 22:** `FUN_180002884`, highlighting both offsets, the work-hour comparison branches, and `GetLocalTime`.

---

# 24. Finding 23 — ICMP Timeout

**Question:** What timeout value is used in the network-probing routine?

**Answer:** `3000` milliseconds

**Ghidra function:** `FUN_180002e64`

The network discovery function calls:

```c
IcmpSendEcho(..., 3000);
```

The final argument supplies a timeout of 3,000 milliseconds.

This equals three seconds.

## Technical interpretation

The timeout bounds how long the routine waits for an individual ICMP echo operation.

This is relevant to the traceroute-like behavior identified earlier.

The routine uses time-to-live variation together with ICMP responses to infer network reachability or intermediate hops.

## Challenge terminology discrepancy

The challenge question described the value as a WinHTTP timeout.

However, the supplied code evidence associates `3000` specifically with:

```c
IcmpSendEcho
```

not a demonstrated WinHTTP call.

Therefore, the code-supported description is **ICMP echo timeout**.

The numerical answer remains `3000`.

**Screenshot 23:** `FUN_180002e64`, highlighting `IcmpSendEcho` and the timeout argument.

---

# 25. Finding 24 — Sleep Duration Outside Working Hours

**Question:** How many milliseconds does the malware wait when the current time falls outside its configured working hours?

**Answer:** `300000`

**Ghidra function:** `FUN_180002884`

When the current local hour is outside the permitted operating interval, the malware calls:

```c
WaitForSingleObject(
    stop_event,
    300000
);
```

The timeout is:

```text
300000 milliseconds
```

or five minutes.

After the wait, the function reevaluates the current hour.

## Technical interpretation

The use of `WaitForSingleObject` is significant.

Unlike a simple unconditional delay, waiting on a handle may allow the thread to resume earlier if the associated object becomes signaled.

Therefore, the value represents the maximum wait timeout for that call, not an unconditional guarantee that execution always pauses for exactly five minutes.

## Security significance

Working-hour restrictions can influence when the sample attempts communications.

Such behavior may reduce traffic outside periods the author considers useful or desirable.

The routine's local-time dependency also means that host timezone and clock configuration can affect scheduling behavior.

**Screenshot 24:** `FUN_180002884`, showing the out-of-hours branch and `WaitForSingleObject(..., 300000)`.

---

# 26. Finding 25 — API Used to Check Local Working Hours

**Question:** Which Windows API is used to obtain the local time for working-hour checks?

**Answer:** `GetLocalTime`

**Ghidra function:** `FUN_180002884`

The malware obtains local date and time information using:

```c
GetLocalTime(&systemTime);
```

It then examines the hour component for comparison with the configured operating window.

The time checks occur repeatedly while the malware waits for its permitted interval.

## Technical interpretation

`GetLocalTime` provides the system's current local date and time.

This differs from obtaining a UTC timestamp and applying an independent timezone conversion.

The malware's behavior is therefore tied to the local time configured on the host.

This is relevant to analyzing execution in a sandbox whose timezone differs from the original victim environment.

A sample may delay communications simply because the sandbox's local clock falls outside the configured hours.

**Screenshot 25:** `FUN_180002884`, highlighting the `GetLocalTime` call and subsequent hour comparisons.

---

# 27. Finding 26 — API Used for AppData Path Construction

**Question:** Which API is used to retrieve the application data directory, and which CSIDL value is supplied?

**Answer:** `SHGetSpecialFolderPathA, 26`

**Ghidra function:** `FUN_1800040cc`

The configuration-path construction routine uses:

```c
SHGetSpecialFolderPathA(
    ...,
    0x1A,
    ...
);
```

The CSIDL value is:

```text
0x1A = 26 decimal
```

This corresponds to:

```text
CSIDL_APPDATA
```

The routine then constructs a configuration path beneath the user's roaming application-data directory.

The recovered pattern is:

```text
%APPDATA%\Microsoft\Protect\Windows\DMI%X.DAT
```

The code also attempts to create intermediate directory components when needed.

## ANSI versus Unicode distinction

The configuration-path builder uses the ANSI version:

```c
SHGetSpecialFolderPathA
```

The separate Firefox configuration-discovery function uses:

```c
SHGetSpecialFolderPathW
```

These are different entry points and should not be confused when answering the challenge.

## Security significance

Storing configuration in AppData provides a user-writable location commonly used by legitimate applications.

A malware author may choose such a path because it is accessible without requiring administrative privileges and may be less conspicuous than an unusual directory at the root of a drive.

The path is evidence of configuration storage, not by itself evidence of automatic execution after login or reboot.

**Screenshot 26:** `FUN_1800040cc`, highlighting `SHGetSpecialFolderPathA`, `0x1A`, the path construction, and directory creation.

---

# 28. Deeper Analysis — C2 Proxy Fallback Architecture

The individual challenge questions reveal many implementation details, but the complete C2 connection function provides additional insight into the design.

The central function is:

`FUN_1800033dc`

It receives a pointer to the session structure and an index selecting a C2 server entry.

The function obtains the server string using:

```c
lpMultiByteStr = (LPCSTR)(
    (longlong)param_1 +
    (longlong)param_2 * 0x32 +
    0xC858
);
```

It then converts the selected value to a wide-character representation:

```c
MultiByteToWideChar(
    0,
    0,
    lpMultiByteStr,
    0x32,
    &local_288,
    0x32
);
```

The function also initializes or retrieves an HTTP user-agent string.

When the expected value is unavailable, the code uses:

```text
Mozilla/5.0 (compatible; MSIE 7.0; Win32)
```

The routine parses URL-related strings, including checks for:

```text
http://
https://
```

The remaining connection logic evaluates a series of possible transport configurations.

## Observed fallback strategies

| Mode | Log string | Interpretation |
|---|---|---|
| 1 | `httpsviaconfigproxy` | Configured proxy route |
| 2 | `httpswpadproxy` | WPAD-related proxy route |
| 3 | `httpsviaiexproxy` | Internet Explorer proxy settings |
| 4 | `httpsviafirefoxproxy` | Firefox proxy settings |
| 5 | `httpsviaautoproxy` | Automatic proxy discovery |
| 6 | `httpspreconfig` | Preconfigured connection settings |

A session field indexed as `param_1[0x3211]` records values corresponding to these modes.

The function invokes a series of helper routines:

`FUN_1800038fc`, `FUN_1800076ec`, `FUN_18000761c`, `FUN_180007680`, `FUN_18000786c`, and `FUN_1800075d0`.

Their observed placement matches the respective connection branches, although their complete implementations must be reviewed before assigning definitive protocol-level semantics.

On successful completion, the routine emits a success message selected from an internal string table.

On total failure, it emits:

```text
0x01, CN failed.
```

## Architectural significance

This design allows the malware to attempt different connection configurations without requiring every target environment to expose the same networking setup.

For example, a workstation might have access to an automatically configured HTTP proxy while direct Internet access is restricted.

A sample with only direct outbound connectivity could fail in such an environment.

Sagerunex instead contains multiple methods for locating and selecting available proxy configurations.

The recovered architecture is therefore consistent with malware designed to tolerate heterogeneous enterprise networking environments.

However, the investigation does not establish which specific method succeeded during the reported infection.

---

# 29. Deeper Analysis — Configuration Lifecycle

The investigation recovered three related configuration operations:

**Path construction:** `FUN_1800040cc`

**Configuration loading:** `FUN_180004194`

**Configuration saving:** `FUN_180004288`

The main session initialization routine is `FUN_1800027c0`.

Together, these functions define a configuration lifecycle.

```text
Initialize session
       |
       v
Construct APPDATA path
       |
       v
Attempt to load configuration file
       |
       +-- Existing file
       |       |
       |       v
       |   Read 0x640 bytes
       |       |
       |       v
       |   Apply RC4-like transform
       |
       +-- Missing/unusable file
               |
               v
          Use supplied/default config
               |
               v
          Save configuration
       |
       v
Validate configuration fields
       |
       v
Use configuration for C2 activity
```

The initialization function copies configuration data into the session starting at `0xC848`.

The saved file contains a 1,600-byte configuration block.

The encryption wrapper operates on this data using the recovered RC4-like routines.

The save path additionally modifies file timestamps.

## Key distinction: two data transformations

The analysis identified two separate transformation mechanisms.

| Property | XOR transform | RC4-like configuration transform |
|---|---|---|
| Main routine | `FUN_1800061bc` | `FUN_1800090a4` and helpers |
| Processed size | `0x760` bytes | `0x640` bytes |
| Decimal size | 1,888 | 1,600 |
| Technique | Reverse chained XOR | RC4-style stream cipher |
| Primary context | In-memory decoded data | Saved configuration |

Treating these operations as one encryption routine would incorrectly combine two separate stages of the sample's architecture.

---

# 30. Deeper Analysis — Work-Hour Fields and Session Offsets

The work-hour question deserves a separate technical explanation because it involved several plausible but rejected offset interpretations.

The two observed runtime fields are:

```text
0xCC4C
0xCC50
```

The challenge accepted `0xCC50`.

The configuration block begins at:

```text
0xC848
```

Consequently, relative to the saved configuration block, the two fields would be located at:

```text
0xCC4C - 0xC848 = 0x404
0xCC50 - 0xC848 = 0x408
```

This yields three different ways of discussing the same fields:

| Representation | First field | Second field |
|---|---|---|
| Runtime session offset | `0xCC4C` | `0xCC50` |
| Saved-config-relative offset | `0x404` | `0x408` |
| Ghidra `undefined4 *` array index | `0x3313` | `0x3314` |

These representations are not interchangeable.

A configuration-relative offset and a session-relative offset describe different coordinate systems.

Likewise, a typed C pointer index is scaled according to the size of the pointed-to type.

## Why the accepted answer is still ambiguous

The work-hour checks suggest that the first runtime field acts as the lower interval boundary and the second as the upper interval boundary.

The platform nevertheless accepts the second field for the start-time question.

A rigorous malware report should preserve that discrepancy until the original configuration structure and all relevant writers/readers are reconciled.

This is a useful methodological lesson: challenge-answer validation and binary semantic validation are separate forms of evidence.

---

# 31. Indicators of Compromise and Forensic Artifacts

The static analysis recovered the following potential investigation artifacts.

| Category | Artifact | Evidence |
|---|---|---|
| Log filename | `TS_FB56.tmp` | MainEntry path construction |
| Log location | `%TEMP%` | `GetTempPathW` |
| Configuration location | `%APPDATA%\Microsoft\Protect\Windows\` | Configuration path builder |
| Configuration naming pattern | `DMI%X.DAT` | Formatted filename |
| Target process | `explorer.exe` | Process enumeration |
| DNS fallback | `8.8.8.8` | Network helper |
| Firefox profile metadata | `profiles.ini` | Firefox discovery routine |
| Firefox preferences | `prefs.js` | Proxy parsing routine |
| Firefox HTTPS proxy key | `network.proxy.ssl` | Preference string |
| Firefox HTTPS port key | `network.proxy.ssl_port` | Preference string |
| Windows proxy subkey | `Software\Microsoft\Windows\CurrentVersion\Internet Settings` | Registry enumeration |
| User SID prefix | `S-1-5-21` | Registry filtering |
| Default HTTP user-agent | `Mozilla/5.0 (compatible; MSIE 7.0; Win32)` | Connection routine |

## Unresolved indicators

The following values were not established from the available evidence:

- SHA-256 of the analyzed DLL.
- Actual C2 hostname or IP strings.
- C2 destination ports and URI paths.
- Exact contents of the saved configuration file.
- Specific victim files transferred to a remote server.
- A confirmed Windows autostart persistence artifact.

These omissions matter. A reliable IOC section should contain recovered evidence, not values inferred from an unrelated sample of the same malware family.

---

# 32. MITRE ATT&CK Mapping

The observed implementation supports several ATT&CK-aligned classifications.

| Behavior | Technique | ATT&CK ID | Evidence |
|---|---|---|---|
| Phishing attachment delivery | Spearphishing Attachment | T1566.001 | Challenge scenario |
| Token impersonation | Access Token Manipulation | T1134 | `DuplicateToken`, `SetThreadToken` |
| File timestamp alteration | Timestomp | T1070.006 | `SetFileTime`, year 2011 |
| Windows shell execution | Windows Command Shell | T1059.003 | `cmd.exe /c` |
| Proxy-assisted communications | Proxy | T1090 | Proxy discovery and connection branches |
| Web-based C2 | Web Protocols | T1071.001 | HTTPS transport handling |
| File transfer through C2 | Exfiltration Over C2 Channel | T1041 | File read and send routine |

These mappings describe supported capabilities or scenario elements.

They should not all be interpreted as dynamically confirmed actions in the victim environment.

---

# 33. Ghidra Function Renaming Reference

The following names are proposed for improving readability during continued reverse engineering.

A rename should be applied only after confirming that the relevant Ghidra symbol is located at the expected function entry.

| Original name | Proposed name | Confidence |
|---|---|---|
| `MainEntry` | `MalwareMainEntry` | High |
| `FUN_1800061bc` | `DecodeXorChainedBuffer` | High |
| `FUN_180003208` | `FindExplorerProcessHandle` | High |
| `FUN_1800031a0` | `OpenProcessByPid_DynamicApi` | High |
| `FUN_180003294` | `ImpersonateExplorerToken` | High |
| `FUN_18000208c` | `TimestompFileTo2011` | High |
| `FUN_180002e64` | `DiscoverDnsAndRunIcmpTrace` | High |
| `FUN_180002884` | `C2BeaconLoop` | High |
| `FUN_1800027c0` | `LoadOrInitializeSessionConfig` | High |
| `FUN_180004194` | `ReadAndDecryptConfigFile` | High |
| `FUN_180004288` | `EncryptAndSaveConfigFile` | High |
| `FUN_1800090a4` | `TransformConfigRC4` | High |
| `FUN_180002624` | `InitializeRC4State` | Requires verification |
| `FUN_1800026cc` | `RC4TransformBuffer` | High |
| `FUN_1800040cc` | `BuildAppDataConfigFilePath` | High |
| `FUN_18000339c` | `ResetBuffersAndConnectC2` | Moderate |
| `FUN_1800033dc` | `ConnectC2WithProxyFallback` | High |
| `FUN_180003c40` | `HandleC2SessionAndCommands` | High |
| `FUN_180005628` | `ExecuteRemoteShellOrDllCommand` | High |
| `FUN_1800068ac` | `OpenUserIEProxyRegistryKey` | High |
| `FUN_180006d10` | `ReadFirefoxHttpsProxySettings` | High |
| `FUN_180006130` | `PerformC2Registration` | Requires verification |
| `FUN_180003a2c` | `ReceiveC2Command` | Requires verification |
| `FUN_180003e70` | `SendC2Chunk` | Requires verification |
| `FUN_180002148` | `LogMessageAnsi` | Requires verification |
| `FUN_180002394` | `LogMessageWide` | Requires verification |
| `FUN_18000210c` | `ConfigureLogPath` | Requires verification |
| `FUN_180002780` | `InitializeSessionState` | Requires verification |
| `FUN_1800027b4` | `CleanupSessionState` | Requires verification |
| `FUN_18001cfc0` | `CopyMemoryBuffer` | Requires verification |
| `FUN_18001cca0` | `FillMemoryBuffer` | Requires verification |

Function renaming is a readability improvement. It must not modify the binary's instructions, data, calling conventions, or runtime behavior.

---

# 34. Screenshot Collection Plan

For a fully illustrated publication, the Ghidra screenshots should be collected from the actual analysis project.

Each image should show the relevant function name or address, with the important instructions, constants, strings, or calls highlighted.

| Figure | Location | Evidence |
|---|---|---|
| 01 | PE Header | Timestamp and architecture |
| 02 | `MainEntry` | Temporary log construction |
| 03 | `MainEntry` | Magic-value branch |
| 04 | `FUN_1800061bc` | XOR decoder |
| 05 | `FUN_180003208` / `FUN_180003294` | Explorer token impersonation |
| 06 | `FUN_18000208c` | Timestomping |
| 07 | `FUN_180002e64` | DNS fallback |
| 08 | `FUN_180002e64` | Traceroute |
| 09 | `FUN_180002884` | 720-minute counter |
| 10 | `FUN_1800033dc` | C2 server slots |
| 11 | `FUN_180002884` | Retry timing |
| 12 | `FUN_180005628` | Execution methods |
| 13 | `FUN_180005628` | Invalid command |
| 14 | Transfer routine | 48 KiB chunk |
| 15 | Transfer routine | Three attempts |
| 16 | `FUN_1800068ac` | IE proxy registry |
| 17 | `FUN_1800068ac` | SID filtering |
| 18 | `FUN_180006d10` | Firefox profile lookup |
| 19 | `FUN_180006d10` | HTTPS proxy preference |
| 20 | `FUN_180003c40` | Registration response |
| 21 | `FUN_1800027c0` | Configuration base |
| 22 | `FUN_180002884` | Work-hour field offsets |
| 23 | `FUN_180002e64` | ICMP timeout |
| 24 | `FUN_180002884` | Out-of-hours wait |
| 25 | `FUN_180002884` | Local time checks |
| 26 | `FUN_1800040cc` | AppData path lookup |

Additional supporting images should include the export table, configuration load/save functions, RC4 transformation, and the complete proxy fallback sequence.

Screenshots should be captured from Ghidra with consistent zoom and formatting. No synthetic screenshot should be represented as evidence from the original binary.

---

# 35. Complete Challenge Answer Reference

| Question | Answer | Primary evidence |
|---|---|---|
| Q01 | `2021-03-15 09:44:36` | PE Header |
| Q02 | `TS_FB56.tmp` | `MainEntry` |
| Q03 | `0xC91F3B` | `MainEntry` |
| Q04 | `1888` | `FUN_1800061bc` |
| Q05 | `explorer.exe` | `FUN_180003208` |
| Q06 | `2011` | `FUN_18000208c` |
| Q07 | `8.8.8.8` | `FUN_180002e64` |
| Q08 | `Trace complete.` | `FUN_180002e64` |
| Q09 | `720` | `FUN_180002884` |
| Q10 | `5` | `FUN_180002884` |
| Q11 | `5` | `FUN_180002884` |
| Q12 | `runexe, rundll, cmd.exe /c` | `FUN_180005628` |
| Q13 | `illegal command` | `FUN_180005628` |
| Q14 | `49152` | File-transfer routine |
| Q15 | `3` | File-transfer retry loop |
| Q16 | `\Software\Microsoft\Windows\CurrentVersion\Internet Settings` | `FUN_1800068ac` |
| Q17 | `S-1-5-21` | `FUN_1800068ac` |
| Q18 | `prefs.js` | `FUN_180006d10` |
| Q19 | `network.proxy.ssl` | `FUN_180006d10` |
| Q20 | `0x01, RC success.` | `FUN_180003c40` |
| Q21 | `0xC848` | `FUN_1800027c0` |
| Q22 | `0xCC50` | Challenge-accepted value; semantic ambiguity |
| Q23 | `3000` | `IcmpSendEcho` call |
| Q24 | `300000` | Work-hour wait |
| Q25 | `GetLocalTime` | `FUN_180002884` |
| Q26 | `SHGetSpecialFolderPathA, 26` | `FUN_1800040cc` |

---

# 36. Research Limitations and Further Investigation

Several important components remain outside the scope of the recovered evidence.

## Complete configuration decoding

The available analysis identifies the configuration buffers, their sizes, the storage location, and the transformation routines.

However, it does not include a complete recovered plaintext configuration.

A full configuration analysis could establish the exact C2 server strings, connection parameters, and additional operational settings.

## Full C2 protocol

The registration and command-processing routines were identified, but the entire message format was not reconstructed.

This includes request and response serialization, command payload structures, and any cryptographic protection applied to communications.

## Autostart persistence

The code saves configuration data to disk.

A Windows autostart mechanism was not independently identified in the examined snippets.

The report therefore does not claim that a Run key, scheduled task, Windows service, or startup-folder mechanism was confirmed.

## Command handler coverage

Several numeric command identifiers are visible in the dispatcher.

Their exact capabilities require analysis of the corresponding handler implementations.

Assigning meanings based only on command numbers would be speculative.

## Dynamic observations

No controlled execution trace or packet capture was available in the supplied evidence.

Consequently, the report does not claim observed network connections to specific malicious endpoints, successful token impersonation, or completed file exfiltration.

These remain implementation capabilities identified from code.

---

# 37. Final Conclusion

The Sagerunex investigation demonstrates how static reverse engineering can reveal the internal design of a Windows backdoor even when its actual network infrastructure and runtime execution traces are unavailable.

The analyzed DLL contains an exported initialization routine, conditional access-token impersonation, an XOR-based data decoder, RC4-like protected local configuration, file timestomping, configurable C2 server selection, time-based communication restrictions, and multiple network proxy fallback mechanisms.

Its command-handling subsystem supports executable launching, DLL invocation, Windows command shell execution, and chunked file transfer with bounded retries.

The strongest architectural finding is the communication subsystem. The sample does not rely on a single straightforward connection strategy. Instead, it contains mechanisms for extracting network settings from the host and attempting several routes to external infrastructure.

The analysis also illustrates a broader reverse engineering principle: identifying an API, configuration value, or code branch is not the same as proving that the behavior executed successfully in a particular environment.

This distinction is especially important for the work-hour configuration offsets, the unspecified C2 infrastructure, and the difference between persistent configuration storage and confirmed autostart persistence.

The reconstructed function relationships, memory offsets, Windows API usage, diagnostic messages, and file artifacts provide a strong foundation for continued investigation and defensive detection engineering.

**The result is a detailed technical reconstruction of Sagerunex's observable architecture, with its remaining uncertainties explicitly documented rather than concealed.**

---

**Analysis and writeup by Mostafa Galal**

**Tools:** Ghidra  
**Focus:** Windows Malware Reverse Engineering, C2 Analysis, Configuration Recovery, and Backdoor Capabilities

*End of technical report.*