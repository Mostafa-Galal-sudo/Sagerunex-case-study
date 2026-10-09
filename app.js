const functions = [
  {id:'MainEntry',name:'MalwareMainEntry',group:'entry',role:'Exported entry point',summary:'Builds the temporary log path, gates optional token impersonation, decodes the in-memory region, and enters the beacon loop.',confidence:'high'},
  {id:'FUN_1800061bc',name:'DecodeXorChainedBuffer',group:'config',role:'In-memory decoder',summary:'Processes a 0x760-byte region in reverse using chained XOR, then XORs the first byte with 0xAD.',confidence:'high'},
  {id:'FUN_180003208',name:'FindExplorerProcessHandle',group:'entry',role:'Process discovery',summary:'Enumerates processes, compares names with explorer.exe, and delegates process opening.',confidence:'high'},
  {id:'FUN_1800031a0',name:'OpenProcessByPid_DynamicApi',group:'entry',role:'Dynamic API wrapper',summary:'Decodes the OpenProcess name, resolves it from Kernel32.dll, and invokes the resulting pointer.',confidence:'high'},
  {id:'FUN_180003294',name:'ImpersonateExplorerToken',group:'entry',role:'Token impersonation',summary:'Calls OpenProcessToken, DuplicateToken with SecurityImpersonation, and SetThreadToken.',confidence:'high'},
  {id:'FUN_18000208c',name:'TimestompFileTo2011',group:'config',role:'Timestamp helper',summary:'Sets the SYSTEMTIME year to 2011 and applies one FILETIME to creation, access, and write fields.',confidence:'high'},
  {id:'FUN_180002e64',name:'DiscoverDnsAndRunIcmpTrace',group:'network',role:'Network discovery',summary:'Uses GetNetworkParams, the 8.8.8.8 fallback, and bounded IcmpSendEcho probes.',confidence:'high'},
  {id:'FUN_180002884',name:'C2BeaconLoop',group:'network',role:'Beacon controller',summary:'Checks work hours, rotates endpoint slots, applies retry waits, and accounts elapsed loop time.',confidence:'high'},
  {id:'FUN_1800027c0',name:'LoadOrInitializeSessionConfig',group:'config',role:'Session initialization',summary:'Loads or copies the 0x640-byte configuration and validates work-hour fields.',confidence:'high'},
  {id:'FUN_180004194',name:'ReadAndDecryptConfigFile',group:'config',role:'Configuration reader',summary:'Reads 0x640 bytes from the AppData artifact and invokes the RC4-like transform wrapper.',confidence:'high'},
  {id:'FUN_180004288',name:'EncryptAndSaveConfigFile',group:'config',role:'Configuration writer',summary:'Transforms a temporary copy, writes it to disk, and invokes the timestamp helper.',confidence:'high'},
  {id:'FUN_1800090a4',name:'TransformConfigRC4',group:'config',role:'Cipher wrapper',summary:'Calls state initialization and the PRGA-shaped configuration transform.',confidence:'high'},
  {id:'FUN_180002624',name:'InitializeRC4State',group:'config',role:'State setup',summary:'Initializes a 256-byte identity state and performs the key-scheduling swap loop used by the RC4-shaped transform.',confidence:'high'},
  {id:'FUN_1800026cc',name:'RC4TransformBuffer',group:'config',role:'Stream transform',summary:'Performs a swap/XOR keystream operation over the 0x640-byte buffer.',confidence:'high'},
  {id:'FUN_1800040cc',name:'BuildAppDataConfigFilePath',group:'config',role:'Path construction',summary:'Resolves CSIDL_APPDATA and builds the Microsoft\\Protect\\Windows\\DMI%X.DAT pattern.',confidence:'high'},
  {id:'FUN_18000339c',name:'ResetBuffersAndConnectC2',group:'network',role:'Connection setup',summary:'Clears connection-related buffers and delegates proxy-aware transport setup.',confidence:'moderate'},
  {id:'FUN_1800033dc',name:'ConnectC2WithProxyFallback',group:'network',role:'Transport strategy',summary:'Attempts configured, WPAD, IE, Firefox, automatic, and preconfigured routes.',confidence:'high'},
  {id:'FUN_180003c40',name:'HandleC2SessionAndCommands',group:'control',role:'Session dispatcher',summary:'Logs registration status and dispatches recovered numeric command identifiers.',confidence:'high'},
  {id:'FUN_180005628',name:'ExecuteRemoteShellOrDllCommand',group:'control',role:'Remote execution',summary:'Handles runexe and rundll prefixes, otherwise constructing a cmd.exe /c fallback.',confidence:'high'},
  {id:'FUN_1800068ac',name:'OpenUserIEProxyRegistryKey',group:'network',role:'IE proxy discovery',summary:'Enumerates S-1-5-21 user hives and opens the Internet Settings subkey.',confidence:'high'},
  {id:'FUN_180006d10',name:'ReadFirefoxHttpsProxySettings',group:'network',role:'Firefox proxy discovery',summary:'Resolves a profile from profiles.ini and parses proxy preferences from prefs.js.',confidence:'high'},
  {id:'FUN_180006130',name:'BuildAndSendRegistration',group:'control',role:'Registration',summary:'Clears a 0xC800-byte workspace, selects registration material, prepares a 16-byte value, and delegates the registration send path. Caller and callee disagree on the recovered return type.',confidence:'moderate'},
  {id:'FUN_180003a2c',name:'ReceiveAndValidateC2Command',group:'control',role:'Command receive',summary:'Reads and decrypts a framed response, validates its checksum and 0x1C-byte identity field, then returns the recovered command identifier and payload.',confidence:'high'},
  {id:'FUN_180003e70',name:'BuildEncryptAndSendC2Packet',group:'control',role:'Packet send',summary:'Builds a bounded message, calculates integrity data, encrypts header and payload components, selects key material, and submits the framed packet through the transport helper.',confidence:'high'},
  {id:'FUN_180002148',name:'LogMessageAnsi',group:'support',role:'ANSI logging',summary:'Formats a local timestamp and ANSI message, transforms the buffer, and appends it to the configured log when logging is enabled.',confidence:'high'},
  {id:'FUN_180002394',name:'LogMessageWide',group:'support',role:'Wide logging',summary:'Formats a wide-character message, converts it to a multibyte buffer, transforms the data, and appends it to the configured log.',confidence:'high'},
  {id:'FUN_18000210c',name:'ConfigureLogPath',group:'support',role:'Log setup',summary:'Converts the supplied wide-character path into the global ANSI log-path buffer.',confidence:'high'},
  {id:'FUN_180002780',name:'InitializeSessionState',group:'support',role:'Session lifecycle',summary:'Initializes two embedded state regions and clears the session field at offset 0xD7C0.',confidence:'moderate'},
  {id:'FUN_1800027b4',name:'CleanupSessionState',group:'support',role:'Session lifecycle',summary:'Delegates cleanup of the embedded transport/session state at offset 0xD098.',confidence:'moderate'},
  {id:'FUN_18001cfc0',name:'CopyMemoryBuffer',group:'support',role:'Memory helper',summary:'Implements an overlap-aware, vectorized memory-copy routine with forward and reverse paths.',confidence:'high'},
  {id:'FUN_18001cca0',name:'FillMemoryBuffer',group:'support',role:'Memory helper',summary:'Implements an optimized byte-fill routine with scalar and vectorized paths.',confidence:'high'}
];

const flowGroups = [
  {id:'entry',label:'Entry and identity',note:'export → process discovery → token path',order:['MainEntry','FUN_180003208','FUN_1800031a0','FUN_180003294']},
  {id:'config',label:'Decode and configuration',note:'memory decode → load → transform → save',order:['FUN_1800061bc','FUN_1800027c0','FUN_1800040cc','FUN_180004194','FUN_1800090a4','FUN_180002624','FUN_1800026cc','FUN_180004288','FUN_18000208c']},
  {id:'network',label:'Beacon and route',note:'schedule → discovery → proxy-aware connection',order:['FUN_180002884','FUN_180002e64','FUN_18000339c','FUN_1800033dc','FUN_1800068ac','FUN_180006d10']},
  {id:'control',label:'C2 control plane',note:'session → registration → receive → execute / send',order:['FUN_180003c40','FUN_180006130','FUN_180003a2c','FUN_180005628','FUN_180003e70']},
  {id:'support',label:'Shared support',note:'log path → logging → state → memory primitives',order:['FUN_18000210c','FUN_180002148','FUN_180002394','FUN_180002780','FUN_1800027b4','FUN_18001cfc0','FUN_18001cca0']}
];

const functionTrace = ['MainEntry','FUN_18000210c','FUN_180003294','FUN_1800061bc','FUN_1800027c0','FUN_180004194','FUN_1800090a4','FUN_180002884','FUN_18000339c','FUN_1800033dc','FUN_180003c40','FUN_180006130','FUN_180003a2c','FUN_180005628','FUN_180003e70'];

const findings = [
  {
    n:1, group:'PE METADATA', title:'A timestamp, not a timeline',
    question:'What is the compilation timestamp of the Sagerunex sample?',
    answer:'2021-03-15 09:44:36 UTC', answerNote:'PE TimeDateStamp 0x604F2C84',
    funcs:['MainEntry'], location:'PE header near image offset 0x100',
    facts:[['Machine','0x8664 / AMD64'],['Format','PE32+ DLL'],['Timestamp','0x604F2C84']],
    analysis:['The COFF header stores 0x604F2C84 in the TimeDateStamp field. Interpreted as a Unix epoch value, it resolves to 15 March 2021 at 09:44:36 UTC. The same header identifies the image as AMD64, which agrees with the 0x180000000-style virtual addresses used throughout the decompilation.','This is a build-time claim about the file header—not proof of when the intrusion began, when the DLL reached a victim, or when the operator used it. PE timestamps are writable metadata and can be altered deliberately or incidentally by a build pipeline.'],
    significance:'Useful for sample clustering and chronology only when corroborated by signer data, linker artifacts, file-system timestamps, or related samples.',
    evidence:'Screenshot 01: PE header showing 0x604F2C84 and machine value 0x8664.', caveat:'Treat the time as reported metadata, not an independently verified event.'
  },
  {
    n:2, group:'INITIALIZATION', title:'The first disk clue',
    question:'What temporary log filename does the malware construct?',
    answer:'TS_FB56.tmp', answerNote:'Resolved beneath the process temporary directory',
    funcs:['MainEntry','FUN_18000210c'], location:'MainEntry log-initialization path',
    facts:[['Directory API','GetTempPathW'],['Append operation','wcscat_s'],['Result','%TEMP%\\TS_FB56.tmp']],
    analysis:['MainEntry asks Windows for the current temporary directory with GetTempPathW, appends the literal filename TS_FB56.tmp, and passes the resulting wide-character path to FUN_18000210c. That helper converts the path into the global ANSI log-path buffer.','The supplied ANSI and wide logging functions open that configured path with CreateFileA, format a local timestamp and message, transform the buffer, and append it with WriteFile when logging is enabled. This establishes a real logging path in the code, while runtime file creation still depends on configuration and API success.'],
    significance:'The filename is a practical host-search pivot. Analysts should combine it with path context and adjacent Sagerunex artifacts to reduce false positives.',
    evidence:'Screenshot 02: GetTempPathW, filename append, and the call to FUN_18000210c in one frame.', caveat:'Path construction proves intent; a successful file write is not yet demonstrated.'
  },
  {
    n:3, group:'INITIALIZATION', title:'A conditional identity gate',
    question:'Which magic value controls the optional impersonation branch?',
    answer:'0xC91F3B', answerNote:'Compared before FUN_180003294 is reached',
    funcs:['MainEntry','FUN_180003294'], location:'MainEntry conditional branch',
    facts:[['Constant','0xC91F3B'],['Branch target','Token path'],['Data lineage','Unresolved']],
    analysis:['MainEntry compares a recovered value against 0xC91F3B. When the condition is satisfied, control reaches the explorer.exe discovery and token-impersonation chain; the branch is therefore a gate for optional identity manipulation rather than an unconditional startup step.','The origin and semantics of the compared local value are not fully recovered in the supplied text. Calling this an authentication token, campaign identifier, or anti-analysis marker would go beyond the evidence. Its defensible role is a literal branch discriminator.'],
    significance:'Conditional execution helps explain why two runs of the same binary may exhibit different process-access behavior.',
    evidence:'Screenshot 03: comparison with 0xC91F3B plus the taken/not-taken targets.', caveat:'The constant is exact; its higher-level meaning is not.'
  },
  {
    n:4, group:'DECODING', title:'1,888 bytes unwound backward',
    question:'How many bytes does the chained-XOR decoder process?',
    answer:'1,888 bytes', answerNote:'0x760 bytes',
    funcs:['FUN_1800061bc','MainEntry'], location:'Decode call from MainEntry',
    facts:[['Length','0x760'],['Direction','End to beginning'],['First-byte key','0xAD']],
    analysis:['FUN_1800061bc walks the buffer in reverse, combining each byte with the preceding stored byte, then treats the first byte separately with XOR 0xAD. MainEntry supplies a length of 0x760, which is 1,888 decimal bytes.','Traversal order is part of the algorithm, not an implementation detail: a forward in-place loop would consume already-modified bytes and produce a different result. This routine is also separate from the RC4-shaped transform used for the persisted 0x640-byte configuration.'],
    significance:'The recovered transform can support static decoding and memory-region validation without executing the sample.',
    evidence:'Screenshot 04: reverse loop, 0x760 argument, and the 0xAD first-byte operation.', caveat:'The decoded content itself should remain undescribed until the complete buffer is recovered.'
  },
  {
    n:5, group:'IDENTITY', title:'Borrowing the desktop user',
    question:'Which process does Sagerunex target for token impersonation?',
    answer:'explorer.exe', answerNote:'Located through a Toolhelp process snapshot',
    funcs:['FUN_180003208','FUN_1800031a0','FUN_180003294'], location:'Process discovery and token helper chain',
    facts:[['Enumeration','Process32FirstW / Process32NextW'],['Process access','0x1F0FFF'],['Token level','SecurityImpersonation']],
    analysis:['FUN_180003208 enumerates running processes using the Toolhelp snapshot APIs and compares executable names with explorer.exe. FUN_1800031a0 dynamically resolves OpenProcess from Kernel32.dll, and FUN_180003294 proceeds through OpenProcessToken, DuplicateToken, and SetThreadToken.','The sequence is consistent with adopting the interactive user context for later filesystem, registry, or proxy access. It is token impersonation, not proof of privilege escalation: the duplicated token cannot grant privileges the selected source token does not possess.'],
    significance:'Process access followed by thread-token assignment is a high-value behavioral chain for detection, especially when paired with the sample paths.',
    evidence:'Screenshot 05: explorer.exe comparison and the OpenProcessToken → DuplicateToken → SetThreadToken sequence.', caveat:'Static code establishes an attempt, not that a suitable process or usable token was obtained.'
  },
  {
    n:6, group:'ANTI-FORENSICS', title:'The calendar is pushed back',
    question:'To which year does the malware backdate its file?',
    answer:'2011', answerNote:'SYSTEMTIME.wYear = 0x7DB',
    funcs:['FUN_18000208c','FUN_180004288'], location:'Timestamp helper called after configuration save',
    facts:[['Year','0x7DB / 2011'],['Conversion','SystemTimeToFileTime'],['Applied fields','Creation, access, write']],
    analysis:['FUN_18000208c obtains local time, replaces the year field with 2011, converts the modified SYSTEMTIME to FILETIME, opens the target, and supplies the same value for creation, last-access, and last-write time through SetFileTime.','Because the remaining calendar fields are inherited from the current local time, the routine does not assign a single universal timestamp. It creates a 2011 date that preserves the run month, day, and time before Windows performs the conversion.'],
    significance:'Uniform backdating across all three timestamp fields can frustrate naive sorting while also creating a detectable temporal inconsistency.',
    evidence:'Screenshot 06: 0x7DB assignment, conversion, and three SetFileTime arguments.', caveat:'The exact displayed UTC value depends on local-time conversion and run date.'
  },
  {
    n:7, group:'NETWORK DISCOVERY', title:'A public resolver as fallback',
    question:'Which hardcoded DNS server is used when local discovery fails?',
    answer:'8.8.8.8', answerNote:'Fallback after GetNetworkParams',
    funcs:['FUN_180002e64'], location:'DNS discovery branch',
    facts:[['Primary source','GetNetworkParams'],['Fallback','8.8.8.8'],['Ownership','Google Public DNS']],
    analysis:['FUN_180002e64 first uses GetNetworkParams to obtain network configuration. If it cannot recover a usable local DNS value, it substitutes the literal IPv4 address 8.8.8.8 and continues into its route-diagnostic logic.','The address is legitimate shared infrastructure. Its presence describes resilience and a reference destination; it does not identify the operator or a command-and-control server. Network telemetry must show suspicious context before the address becomes meaningful.'],
    significance:'The branch reveals that the malware attempts to function even when host DNS discovery is incomplete.',
    evidence:'Screenshot 07: GetNetworkParams outcome feeding the 8.8.8.8 fallback.', caveat:'Never block or label 8.8.8.8 as malicious solely from this sample.'
  },
  {
    n:8, group:'NETWORK DISCOVERY', title:'A ten-hop route probe',
    question:'Which string marks completion of the ICMP trace routine?',
    answer:'Trace complete.', answerNote:'Emitted after bounded TTL probing',
    funcs:['FUN_180002e64'], location:'ICMP route-diagnostic routine',
    facts:[['Handle','IcmpCreateFile'],['Probe','IcmpSendEcho'],['Iterations','Up to 10 TTL values']],
    analysis:['The routine opens an ICMP handle, sends echo requests while varying the TTL from the first hop through a bounded set of up to ten iterations, logs each returned hop, and reaches “Trace complete.” when a reply address equals the destination.','A separate address-classification helper can cause the routine to copy a returned address into session state and exit early; that helper is not in the supplied set. The visible routine is traceroute-like discovery, not proof of a C2 session.'],
    significance:'Repeated ICMP echo requests with incrementing TTL can be hunted as a host reconnaissance pattern.',
    evidence:'Screenshot 08: ICMP API calls, TTL progression, loop bound, and completion string.', caveat:'The text indicates routine completion, not successful reachability of a malicious server.'
  },
  {
    n:9, group:'BEACON CONTROL', title:'A twelve-hour accounting ceiling',
    question:'After how many accounted minutes does the beacon loop stop?',
    answer:'720 minutes', answerNote:'0x2D0 / twelve hours',
    funcs:['FUN_180002884'], location:'C2 loop time-accounting branch',
    facts:[['Threshold','0x2D0'],['Decimal','720 minutes'],['Mechanism','Accumulated delay counter']],
    analysis:['Within FUN_180002884, an accumulator is increased by a delay-related value and compared against 0x2D0. The terminating condition appears as the equivalent of “if 0x2CF < counter,” making 720 the first value beyond the allowed range.','This is accounted loop time, not necessarily twelve hours of wall-clock runtime. Work performed between waits, early branch changes, event-triggered wakeups, and scheduling delays can make observed elapsed time differ from the counter.'],
    significance:'The limit bounds a session phase and may constrain sandbox observation windows or explain self-termination after prolonged failure.',
    evidence:'Screenshot 09: accumulator update and comparison against 0x2D0.', caveat:'Describe it as a counter threshold unless runtime tracing confirms wall-clock behavior.'
  },
  {
    n:10, group:'C2 CONFIGURATION', title:'Five places to call home',
    question:'How many C2 server slots are present in configuration?',
    answer:'5', answerNote:'Five fixed 0x32-byte entries',
    funcs:['FUN_180002884','FUN_1800033dc'], location:'Session structure beginning at +0xC858',
    facts:[['Slot size','0x32 / 50 bytes'],['First slot','+0xC858'],['Total capacity','0xFA / 250 bytes']],
    analysis:['The beacon selector indexes a table with the expression session + 0xC858 + index × 0x32 and rotates the index modulo five. The resulting slot offsets are +0xC858, +0xC88A, +0xC8BC, +0xC8EE, and +0xC920.','These locations prove five configured storage slots, not five recovered live servers. The supplied material does not contain the actual hostnames, addresses, ports, or a decrypted campaign configuration, so infrastructure attribution remains open.'],
    significance:'A multi-endpoint design improves availability and supports operator-controlled failover.',
    evidence:'Screenshot 10: modulo-five selection and the 0xC858 + index × 0x32 address calculation.', caveat:'Offsets are structure locations; they are not network indicators.'
  },
  {
    n:11, group:'BEACON CONTROL', title:'Retry pressure changes over time',
    question:'What is the initial retry interval after a failed connection?',
    answer:'5 minutes', answerNote:'300,000 milliseconds before later 30-minute fallback',
    funcs:['FUN_180002884'], location:'Failure and wait branches',
    facts:[['Initial wait','5 × 60,000 ms'],['Short phase','10 failed rounds'],['Later wait','30 × 60,000 ms']],
    analysis:['The failure path initializes a counter to ten. Each failed five-endpoint round decrements it; values above zero select a five-minute wait, while zero selects thirty minutes and resets the counter to ten.','The supplied body therefore confirms ten short-delay rounds between thirty-minute backoff events. The challenge asks for the initial retry interval, which remains five minutes.'],
    significance:'Two-stage retry timing balances responsiveness with reduced sustained network noise.',
    evidence:'Screenshot 11: counter initialization at 10, decrement/reset logic, five-minute selection, and thirty-minute branch.', caveat:'The counter advances per failed endpoint-rotation round, not per individual server attempt.'
  },
  {
    n:12, group:'COMMAND EXECUTION', title:'Three routes to execution',
    question:'Which command-execution paths are supported?',
    answer:'runexe, rundll, and cmd.exe /c', answerNote:'Two explicit prefixes plus one constructed fallback',
    funcs:['FUN_180005628'], location:'Remote execution dispatcher',
    facts:[['runexe','CreateProcessA with pipes'],['rundll','LoadLibraryA + GetProcAddress'],['fallback','SystemDirectory\\cmd.exe /c']],
    analysis:['FUN_180005628 recognizes runexe and copies the remainder into a process command line before CreateProcessA. The rundll branch splits a library and export, loads the module, resolves the requested export, and includes special handling around DllMain-like cases.','Other accepted input is routed through an internally constructed Windows command processor path ending in cmd.exe /c. That shell string is a fallback execution mechanism, not a third wire-level prefix alongside runexe and rundll.'],
    significance:'The handler supports native process launch, in-process DLL invocation, and general shell command execution—broad remote-control capability.',
    evidence:'Screenshot 12: prefix comparisons and each resulting execution path.', caveat:'No supplied traffic or runtime trace proves that an operator issued any command.'
  },
  {
    n:13, group:'COMMAND EXECUTION', title:'The parser says no',
    question:'Which message is produced for malformed command syntax?',
    answer:'illegal command', answerNote:'Recovered with trailing CRLF formatting',
    funcs:['FUN_180005628'], location:'Command-validation failure branch',
    facts:[['Core text','illegal command'],['Formatting','\\r\\n\\r\\n'],['Context','Parser rejection']],
    analysis:['A validation failure in FUN_180005628 reaches a literal containing “illegal command” followed by carriage-return and line-feed formatting. The branch is particularly relevant to malformed DLL syntax and other inputs that cannot satisfy the dispatch parser.','The challenge answer is the semantic message rather than its transport framing. Any byte count can vary depending on whether a reviewer includes the null terminator or the two CRLF pairs, so the literal should be shown explicitly in evidence.'],
    significance:'Error strings help reconstruct operator protocol behavior and can anchor string-based static triage.',
    evidence:'Screenshot 13: rejected branch and the complete literal including control characters.', caveat:'Keep the message text separate from length calculations and packet framing.'
  },
  {
    n:14, group:'FILE TRANSFER', title:'A 48 KiB transfer unit',
    question:'What is the maximum file-read chunk size?',
    answer:'49,152 bytes', answerNote:'0xC000 / 48 KiB',
    funcs:['FUN_180003e70'], location:'Transfer loop near 0x180004F8F',
    facts:[['Requested bytes','0xC000'],['Decimal','49,152'],['Binary size','48 KiB']],
    analysis:['The transfer routine supplies 0xC000 as the requested length to ReadFile. A successful full read therefore places at most 49,152 bytes of source data into a single iteration before the buffer is passed toward the send helper.','ReadFile returns the number of bytes actually read, so the last chunk—or any short read—can be smaller. The constant is a maximum request size, not a guarantee that every network message carries 49,152 bytes.'],
    significance:'The chunk size helps characterize memory use, approximate transfer cadence, and expected telemetry during large file movement.',
    evidence:'Screenshot 14: ReadFile call with 0xC000 and the returned-byte variable.', caveat:'The packet helper is supplied, but the distinct 0xC000 ReadFile controller body is not part of this 31-function paste.'
  },
  {
    n:15, group:'FILE TRANSFER', title:'Three chances per chunk',
    question:'How many total send attempts are allowed for a file chunk?',
    answer:'3 attempts', answerNote:'Initial attempt included in the total',
    funcs:['FUN_180003e70'], location:'Bounded chunk-send retry loop',
    facts:[['Message type','0x0D'],['Failure log','0x01, SSD failed %d.'],['Bound','counter < 3']],
    analysis:['Each prepared chunk is submitted through FUN_180003e70 with message identifier 0x0D. Failure increments a counter and can emit “0x01, SSD failed %d.” while the loop remains below three. Assuming the observed zero initialization, valid attempts are numbered zero, one, and two.','This means three total tries, not an initial send followed by three additional retries. A successful return exits early, so many chunks may be sent only once.'],
    significance:'A tight retry bound avoids indefinite blocking while providing limited resilience against transient transport failure.',
    evidence:'Screenshot 15: counter initialization, send call, failure increment, and comparison with three.', caveat:'FUN_180003e70 is now supplied; the separate caller that enforces the three-attempt bound is still absent.'
  },
  {
    n:16, group:'PROXY DISCOVERY', title:'Internet Explorer settings, per user',
    question:'Which registry subkey is inspected for Windows proxy settings?',
    answer:'\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings', answerNote:'Opened beneath selected HKEY_USERS hives',
    funcs:['FUN_1800068ac'], location:'IE proxy-discovery routine',
    facts:[['Root','HKEY_USERS'],['Enumeration','RegEnumKeyW'],['Open','RegOpenKeyExW']],
    analysis:['FUN_1800068ac enumerates HKEY_USERS subkeys, selects user-SID-shaped entries, and appends the Internet Settings subkey before opening it. This targets proxy configuration stored in each user profile rather than only the current process identity.','The behavior complements token impersonation: a service-context implant may need access to an interactive user hive or its effective proxy settings to communicate through an enterprise network.'],
    significance:'Registry access to per-user Internet Settings from an unexpected process is a useful proxy-discovery signal.',
    evidence:'Screenshot 16: exact subkey literal and the surrounding registry enumeration/open calls.', caveat:'The specific proxy values read from the key are not present in the supplied report.'
  },
  {
    n:17, group:'PROXY DISCOVERY', title:'Finding real user hives',
    question:'Which SID prefix is used to select user registry hives?',
    answer:'S-1-5-21', answerNote:'Compared across the first eight wide characters',
    funcs:['FUN_1800068ac'], location:'HKEY_USERS enumeration filter',
    facts:[['Prefix','S-1-5-21'],['Comparison','wcsncmp length 8'],['Purpose','Domain/local user SID filtering']],
    analysis:['During registry enumeration, the routine compares candidate subkey names with the first eight characters of S-1-5-21. That prefix is characteristic of Windows account SIDs and separates user-profile hives from entries such as .DEFAULT or short well-known identifiers.','Adjacent logic also needs to avoid Classes subkeys that do not represent the root profile hive. The filter is therefore a practical way to search for user-specific Internet Settings across loaded profiles.'],
    significance:'The SID filter shows deliberate adaptation to multi-user Windows environments rather than a single hardcoded account.',
    evidence:'Screenshot 17: S-1-5-21 literal, wcsncmp length, and Classes exclusion logic.', caveat:'Prefix matching identifies candidate hive names; it does not validate account activity.'
  },
  {
    n:18, group:'PROXY DISCOVERY', title:'Following Firefox to prefs.js',
    question:'Which Firefox file is parsed for proxy configuration?',
    answer:'prefs.js', answerNote:'Located through profiles.ini',
    funcs:['FUN_180006d10'], location:'Firefox profile-discovery routine',
    facts:[['Base folder','CSIDL_APPDATA / 0x1A'],['Profile index','profiles.ini'],['Preference file','prefs.js']],
    analysis:['FUN_180006d10 resolves the roaming AppData directory, locates Firefox profiles.ini, extracts a profile Path entry, and joins that profile location with prefs.js. It then scans the preference text rather than relying on a browser API.','The two-step lookup matters because Firefox profiles may use generated directory names. Resolving profiles.ini makes the routine portable across user installations and supports relative profile paths.'],
    significance:'This expands proxy awareness beyond Windows/IE settings and improves operation on hosts where Firefox has independent network configuration.',
    evidence:'Screenshot 18: AppData resolution, profiles.ini Path parsing, and prefs.js construction.', caveat:'Finding the file does not prove Firefox is installed, active, or configured with a proxy.'
  },
  {
    n:19, group:'PROXY DISCOVERY', title:'The HTTPS proxy preference',
    question:'Which Firefox preference names the HTTPS proxy host?',
    answer:'network.proxy.ssl', answerNote:'Paired with network.proxy.ssl_port',
    funcs:['FUN_180006d10'], location:'Firefox preference parser',
    facts:[['Host key','network.proxy.ssl'],['Port key','network.proxy.ssl_port'],['Source','prefs.js']],
    analysis:['After opening prefs.js, the parser searches for network.proxy.ssl to recover the secure-proxy host and network.proxy.ssl_port for its companion port. The names align with Firefox user preference syntax and provide an alternate route when system-wide proxy discovery is insufficient.','The strings establish what the parser seeks; they do not show a concrete host or port from a victim. A valid setting must still be parsed, normalized, and successfully used by downstream connection logic.'],
    significance:'Browser-specific proxy discovery is evidence of deliberate network-environment adaptation.',
    evidence:'Screenshot 19: both Firefox preference strings and the extraction branch.', caveat:'Do not report an actual proxy endpoint until a configuration artifact supplies one.'
  },
  {
    n:20, group:'C2 SESSION', title:'Registration accepted',
    question:'Which log string indicates successful C2 registration?',
    answer:'0x01, RC success.', answerNote:'Selected when FUN_180006130 returns nonzero',
    funcs:['FUN_180003c40','FUN_180006130'], location:'Session-registration result branch',
    facts:[['Success','0x01, RC success.'],['Failure','0x01, RC failed.'],['Predicate','Nonzero helper return']],
    analysis:['FUN_180003c40 invokes FUN_180006130 and chooses between paired registration log messages. A nonzero caller-observed result reaches “0x01, RC success.” while zero reaches the failure variant.','The supplied callee clears a 0xC800-byte workspace, selects 16-byte registration material, derives another 16-byte value, and delegates two lower-level helpers. Ghidra decompiles the callee as void even though the caller consumes a return value, so the exact success contract and wire protocol remain unresolved.'],
    significance:'The paired messages provide a precise pivot for runtime logging and clarify where command dispatch becomes available.',
    evidence:'Screenshot 20: registration call, return test, both RC strings, and the callee’s conflicting recovered prototype.', caveat:'“Success” is the caller’s interpretation; the supplied caller/callee return types conflict and no traffic validates the event.'
  },
  {
    n:21, group:'CONFIGURATION', title:'Where configuration begins',
    question:'What is the session-structure offset of the configuration base?',
    answer:'0xC848', answerNote:'Accepted base used by FUN_1800027c0',
    funcs:['FUN_1800027c0','FUN_180002884'], location:'Session initialization and configuration copy',
    facts:[['Config base','+0xC848'],['Copy length','0x640'],['First server','+0xC858']],
    analysis:['FUN_1800027c0 operates on a 0x640-byte configuration associated with session offset 0xC848. That base precedes the first recovered server-string slot, which begins sixteen bytes later at +0xC858.','The distinction prevents a common off-by-structure error: 0xC848 identifies the broader configuration base accepted by the challenge, while 0xC858 is the location of the first 50-byte endpoint field inside the runtime layout.'],
    significance:'Correct structure coordinates are essential when mapping future decompiled field accesses or carving configuration from memory.',
    evidence:'Screenshot 21: base pointer arithmetic and 0x640-byte configuration copy.', caveat:'Do not relabel 0xC848 as the first server address.'
  },
  {
    n:22, group:'SCHEDULING', title:'The ambiguous second hour',
    question:'Which offset does the challenge identify for the work-hour field?',
    answer:'0xCC50', answerNote:'Accepted answer; branch semantics suggest the upper/end bound',
    funcs:['FUN_180002884'], location:'Local-hour scheduling checks',
    facts:[['First field','+0xCC4C'],['Second field','+0xCC50'],['Relative offsets','0x404 / 0x408']],
    analysis:['The beacon loop reads adjacent 32-bit fields at runtime session offsets 0xCC4C and 0xCC50. Relative to the 0xC848 configuration base they are 0x404 and 0x408; viewed as undefined4 indices they appear as 0x3313 and 0x3314. These are three coordinate systems for the same pair.','The challenge accepts 0xCC50. However, comparisons against local hour indicate that 0xCC4C behaves like the lower/start boundary and 0xCC50 like the upper/end boundary. The site preserves both the expected answer and the semantic warning instead of silently flattening them.'],
    significance:'This ambiguity is exactly where screenshots of the complete branch matter: field names should follow behavior, not answer-key wording.',
    evidence:'Screenshot 22: both field accesses and all comparisons forming the work-hour window.', caveat:'0xCC50 is accepted; calling it the start time remains unverified.'
  },
  {
    n:23, group:'NETWORK DISCOVERY', title:'Three seconds per ICMP probe',
    question:'What timeout is passed to each ICMP echo request?',
    answer:'3,000 milliseconds', answerNote:'Three seconds',
    funcs:['FUN_180002e64'], location:'IcmpSendEcho call site',
    facts:[['Timeout','3000 ms'],['API','IcmpSendEcho'],['Scope','Per probe']],
    analysis:['FUN_180002e64 passes the decimal value 3000 to the timeout parameter of IcmpSendEcho. Because the route loop can attempt multiple TTL values, total diagnostic duration can exceed three seconds even though each individual call is bounded.','The API context matters. The value is not a WinHTTP timeout, beacon delay, or generic socket timeout; assigning it to those behaviors would mischaracterize both network timing and detection expectations.'],
    significance:'A bounded timeout prevents an unreachable route probe from stalling the broader network setup indefinitely.',
    evidence:'Screenshot 23: IcmpSendEcho arguments with 3000 in the timeout position.', caveat:'Actual return time may be shorter than the configured maximum.'
  },
  {
    n:24, group:'SCHEDULING', title:'Five minutes outside the window',
    question:'How long does the malware wait when the local time is outside configured work hours?',
    answer:'300,000 milliseconds', answerNote:'Five minutes',
    funcs:['FUN_180002884'], location:'Out-of-hours branch',
    facts:[['Wait value','300000 ms'],['Equivalent','5 minutes'],['API','WaitForSingleObject']],
    analysis:['When the local-hour test fails, the beacon controller calls WaitForSingleObject with 300,000 milliseconds before looping back to reevaluate the schedule. The use of a waitable object means the sleep can potentially end early if the object becomes signaled.','This interval is distinct from the connection-failure backoff even though the early retry value is also five minutes. One enforces an operating window; the other controls repeated network attempts after failure.'],
    significance:'Periodic rechecking lets the implant remain dormant outside its configured window without terminating the session state.',
    evidence:'Screenshot 24: out-of-hours branch leading to WaitForSingleObject with 300000.', caveat:'It is a maximum wait per iteration when the handle can signal early.'
  },
  {
    n:25, group:'SCHEDULING', title:'The host clock controls the beacon',
    question:'Which API supplies the hour used for work-window checks?',
    answer:'GetLocalTime', answerNote:'Uses the host’s local hour',
    funcs:['FUN_180002884'], location:'Beginning of the scheduling decision',
    facts:[['API','GetLocalTime'],['Field','SYSTEMTIME.wHour'],['Validation','Bounds below 24 and non-equal']],
    analysis:['FUN_180002884 obtains a SYSTEMTIME through GetLocalTime and compares wHour with the two configured boundaries. Initialization logic checks that both hours are below 24 and are not equal; the branch layout also accounts for windows that cross midnight.','Using local rather than UTC time lets one configuration align activity with the victim’s apparent working day across time zones. It also means timezone changes, daylight-saving transitions, or a manipulated system clock can shift observed beacon periods.'],
    significance:'Local-time gating can reduce conspicuous overnight traffic and complicate short sandbox runs.',
    evidence:'Screenshot 25: GetLocalTime, wHour load, and both normal/cross-midnight comparisons.', caveat:'The configured hour values are not supplied, so the actual active window is unknown.'
  },
  {
    n:26, group:'CONFIGURATION', title:'Roaming AppData hides the state file',
    question:'Which API call and folder identifier locate the configuration directory?',
    answer:'SHGetSpecialFolderPathA with 26', answerNote:'26 / 0x1A is CSIDL_APPDATA',
    funcs:['FUN_1800040cc','FUN_180004194','FUN_180004288'], location:'Configuration-path construction',
    facts:[['API variant','SHGetSpecialFolderPathA'],['CSIDL','26 / 0x1A'],['Path','%APPDATA%\\Microsoft\\Protect\\Windows\\DMI%X.DAT']],
    analysis:['FUN_1800040cc calls the ANSI SHGetSpecialFolderPathA variant with folder identifier 26, the legacy CSIDL_APPDATA value for roaming application data. It appends Microsoft\\Protect\\Windows and a DMI%X.DAT filename pattern used by the configuration read/write path.','The path deliberately resembles Microsoft protection storage, but the analyzed behavior is a data/configuration artifact. Nothing in the supplied static evidence registers this file for automatic execution at boot or logon, so describing it as persistence would be inaccurate.'],
    significance:'The directory and filename pattern form the strongest sample-specific disk IOC when correlated with the 0x640-byte transformed content and 2011 timestamps.',
    evidence:'Screenshot 26: SHGetSpecialFolderPathA, argument 0x1A, and complete appended path pattern.', caveat:'A similar-looking path alone is not enough to convict a host; validate content and provenance.'
  }
];

const evidence = [
  ['PE Header','Timestamp 0x604F2C84 and AMD64 architecture'],['MainEntry','Temporary log construction with GetTempPathW and TS_FB56.tmp'],['MainEntry','Magic-value branch at 0xC91F3B'],['FUN_1800061bc','Reverse XOR decoder, 0x760 size, and 0xAD constant'],['FUN_180003208 / FUN_180003294','explorer.exe enumeration and token impersonation'],['FUN_18000208c','2011 timestomping through SetFileTime'],['FUN_180002e64','GetNetworkParams and 8.8.8.8 fallback'],['FUN_180002e64','TTL loop, ICMP APIs, and Trace complete.'],['FUN_180002884','720-minute counter and 0x2D0 comparison'],['FUN_1800033dc','Five C2 slots and 0xC858 + index × 0x32'],['FUN_180002884','Short retry countdown, five-minute delay, thirty-minute fallback'],['FUN_180005628','runexe, rundll, and constructed cmd.exe /c paths'],['FUN_180005628','Invalid-command branch and illegal command string'],['Transfer routine','0xC000 / 48 KiB ReadFile chunk'],['Transfer routine','Three total send attempts and FUN_180003e70'],['FUN_1800068ac','IE proxy registry subkey'],['FUN_1800068ac','S-1-5-21 SID filtering'],['FUN_180006d10','Firefox profile lookup and prefs.js'],['FUN_180006d10','network.proxy.ssl and network.proxy.ssl_port'],['FUN_180003c40','0x01, RC success. registration response'],['FUN_1800027c0','Configuration base at session +0xC848'],['FUN_180002884','0xCC4C / 0xCC50 work-hour fields'],['FUN_180002e64','3,000 ms IcmpSendEcho timeout'],['FUN_180002884','300,000 ms out-of-hours wait'],['FUN_180002884','GetLocalTime work-hour checks'],['FUN_1800040cc','SHGetSpecialFolderPathA, 0x1A, and AppData path']
];

const answers = [
  [1,'2021-03-15 09:44:36 UTC','PE timestamp 0x604F2C84; modifiable metadata','caveat'],[2,'TS_FB56.tmp','Constructed in MainEntry','direct'],[3,'0xC91F3B','Conditional gate; full lineage unresolved','caveat'],[4,'1888','0x760-byte decode call','direct'],[5,'explorer.exe','Process enumeration target','direct'],[6,'2011','SYSTEMTIME.wYear = 0x7DB','direct'],[7,'8.8.8.8','DNS fallback; benign, not C2','caveat'],[8,'Trace complete.','Recovered completion string','direct'],[9,'720','Accounted loop minutes, not exact wall time','caveat'],[10,'5','Endpoint index modulo five','direct'],[11,'5','Initial retry interval in minutes','direct'],[12,'runexe, rundll, cmd.exe /c','Shell path is constructed fallback, not a third prefix','caveat'],[13,'illegal command','Accepted answer; placeholder counts differed','caveat'],[14,'49152','0xC000-byte ReadFile','direct'],[15,'3','At most three total send attempts','direct'],[16,'\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings','Per-user proxy key','direct'],[17,'S-1-5-21','User SID prefix','direct'],[18,'prefs.js','Firefox preference source','direct'],[19,'network.proxy.ssl','Firefox HTTPS proxy key','direct'],[20,'0x01, RC success.','Logged on nonzero registration return','direct'],[21,'0xC848','Config base; first server string is +0xC858','caveat'],[22,'0xCC50','Accepted by platform; code suggests end-time field','caveat'],[23,'3000','IcmpSendEcho timeout, not WinHTTP','caveat'],[24,'300000','Outside-hours wait interval','direct'],[25,'GetLocalTime','Time source for work-hour check','direct'],[26,'SHGetSpecialFolderPathA, 26','CSIDL_APPDATA path construction','direct']
];

const entrySteps = [
  ['STEP 01 / EXPORTED ENTRY','MainEntry establishes the case’s execution spine.','The export belongs to MainDLL.dll. An export-directory reference is not itself a direct internal call.','MainEntry'],
  ['STEP 02 / LOG SETUP','A temporary artifact is named before network activity begins.','GetTempPathW constructs TS_FB56.tmp; the path helper converts it to the global ANSI log path used by the supplied write routines.','FUN_18000210c'],
  ['STEP 03 / CONDITIONAL GATE','The value 0xC91F3B controls the impersonation branch.','The comparison is literal. Its complete data lineage is not available, so it should not be called an authenticated signature.','MainEntry'],
  ['STEP 04 / TOKEN PATH','The routine attempts to impersonate explorer.exe.','Process discovery, OpenProcessToken, DuplicateToken, and SetThreadToken establish the attempt—not its runtime success.','FUN_180003294'],
  ['STEP 05 / MEMORY TRANSFORM','A 1,888-byte region is decoded in place.','This chained XOR routine is distinct from the RC4-like transform used for persisted configuration.','FUN_1800061bc'],
  ['STEP 06 / BEACON CONTROLLER','Execution moves into the long-running selection loop.','Work-hour checks, endpoint rotation, connection setup, and retry accounting converge in FUN_180002884.','FUN_180002884']
];

const routeCopy = {
  config:['ROUTE / CONFIG','The function first considers proxy information carried by configuration. Concrete proxy values were not supplied.'],
  wpad:['ROUTE / WPAD','A Web Proxy Auto-Discovery path is attempted. The host-specific discovery result is not established.'],
  ie:['ROUTE / IE','Per-user HKEY_USERS S-1-5-21 hives are inspected for Internet Settings.'],
  firefox:['ROUTE / FIREFOX','profiles.ini is used to locate a profile, then prefs.js is parsed for network.proxy.ssl and its port.'],
  auto:['ROUTE / AUTO','Automatic proxy resolution is another fallback. The negotiated proxy or result is unknown.'],
  preconfig:['ROUTE / PRECONFIG','A preconfigured system route is attempted after other strategies. The endpoint remains absent.']
};

const provenanceCopy = {
  observed:'Observed evidence includes the PE machine value, export, API calls, exact strings, offsets, and branch constants reported in the supplied analysis.',
  establishes:'Code establishes attempted behavior such as reading a configuration file, duplicating a token, rotating endpoint slots, or launching a process.',
  scenario:'The password-protected invoice ZIP and employee HTTPS traffic belong to the challenge narrative, not independent forensic collection.',
  unknown:'No supplied artifact proves successful command execution, data theft, a real C2 address, propagation, or attribution.'
};

const commandFlows = {
  runexe:[['PARSE','copy remainder to command line'],['ATTEMPT','CreateProcessA'],['OUTPUT','collect through pipes']],
  rundll:[['PARSE','split library from export'],['LOAD','LoadLibraryA + GetProcAddress'],['INVOKE','non-DllMain export']],
  other:[['BUILD','SystemDirectory\\cmd.exe /c'],['ATTEMPT','CreateProcessA'],['OUTPUT','collect through pipes']]
};

const qs = s => document.querySelector(s);
const qsa = s => [...document.querySelectorAll(s)];

function renderFindings(){
  const list=qs('#findingsList'),jump=qs('#findingsJump');
  if(!list||!jump)return;
  findings.forEach(f=>{
    const number=String(f.n).padStart(2,'0');
    const link=document.createElement('a');link.href=`#finding-${number}`;link.textContent=number;link.setAttribute('aria-label',`Jump to finding ${number}: ${f.title}`);jump.appendChild(link);

    const article=document.createElement('article');article.className='finding-lead';article.id=`finding-${number}`;article.dataset.group=f.group;
    const rail=document.createElement('div');rail.className='finding-rail';
    const label=document.createElement('span');label.textContent=`LEAD ${number} / 26`;
    const numeral=document.createElement('strong');numeral.textContent=number;
    const group=document.createElement('small');group.textContent=f.group;
    rail.append(label,numeral,group);

    const body=document.createElement('div');body.className='finding-body';
    const q=document.createElement('p');q.className='finding-question';q.textContent=f.question;
    const title=document.createElement('h4');title.textContent=f.title;
    const answer=document.createElement('div');answer.className='finding-answer';
    const answerLabel=document.createElement('span');answerLabel.textContent='DIRECT ANSWER';
    const answerValue=document.createElement('b');answerValue.textContent=f.answer;
    const answerNote=document.createElement('small');answerNote.textContent=f.answerNote;
    answer.append(answerLabel,answerValue,answerNote);

    const meta=document.createElement('div');meta.className='finding-meta';
    const loc=document.createElement('div');loc.innerHTML='<span>CODE LOCATION</span>';const locText=document.createElement('p');locText.textContent=f.location;loc.appendChild(locText);
    const fnWrap=document.createElement('div');fnWrap.innerHTML='<span>FUNCTION RECORDS</span>';const fnButtons=document.createElement('p');
    f.funcs.forEach(id=>{const b=document.createElement('button');b.type='button';b.dataset.function=id;b.textContent=id;fnButtons.appendChild(b)});fnWrap.appendChild(fnButtons);meta.append(loc,fnWrap);

    const facts=document.createElement('dl');facts.className='finding-facts';f.facts.forEach(([k,v])=>{const row=document.createElement('div'),dt=document.createElement('dt'),dd=document.createElement('dd');dt.textContent=k;dd.textContent=v;row.append(dt,dd);facts.appendChild(row)});
    const analysis=document.createElement('div');analysis.className='finding-analysis';
    const analysisLabel=document.createElement('span');analysisLabel.textContent='TECHNICAL ANALYSIS';analysis.appendChild(analysisLabel);
    f.analysis.forEach(copy=>{const p=document.createElement('p');p.textContent=copy;analysis.appendChild(p)});

    const impact=document.createElement('div');impact.className='finding-impact';
    [['WHY IT MATTERS',f.significance],['EVIDENCE TARGET',f.evidence],['BOUNDARY / CAVEAT',f.caveat]].forEach(([k,v])=>{const d=document.createElement('div'),s=document.createElement('span'),p=document.createElement('p');s.textContent=k;p.textContent=v;d.append(s,p);impact.appendChild(d)});
    body.append(q,title,answer,meta,facts,analysis,impact);article.append(rail,body);list.appendChild(article);
  });
}
renderFindings();

const enter = qs('#enterCase');
enter.addEventListener('click',()=>{enter.disabled=true;qs('#prelude').classList.add('departed');document.body.classList.remove('prelude-active');setTimeout(()=>qs('#prelude').hidden=true,1200)});
qs('.skip').addEventListener('click',()=>{qs('#prelude').hidden=true;document.body.classList.remove('prelude-active')});

const index=qs('#caseIndex'),indexToggle=qs('#indexToggle');
function setIndex(open){index.classList.toggle('open',open);indexToggle.setAttribute('aria-expanded',String(open))}
indexToggle.addEventListener('click',()=>setIndex(!index.classList.contains('open')));qs('.index-close').addEventListener('click',()=>setIndex(false));qsa('.case-index a').forEach(a=>a.addEventListener('click',()=>setIndex(false)));

addEventListener('scroll',()=>{const max=document.documentElement.scrollHeight-innerHeight;qs('#caseProgress').style.width=`${max?Math.min(100,scrollY/max*100):0}%`},{passive:true});

qsa('[data-provenance]').forEach(b=>b.addEventListener('click',()=>{qsa('[data-provenance]').forEach(x=>x.classList.remove('active'));b.classList.add('active');qs('#provenanceReadout').textContent=provenanceCopy[b.dataset.provenance]}));

qsa('[data-step]').forEach(b=>b.addEventListener('click',()=>{qsa('[data-step]').forEach(x=>x.classList.remove('active'));b.classList.add('active');const [label,title,copy,fn]=entrySteps[Number(b.dataset.step)];const panel=qs('#entryReadout');panel.replaceChildren();const p1=document.createElement('p');p1.textContent=label;const h=document.createElement('h4');h.textContent=title;const p2=document.createElement('p');p2.textContent=copy;const btn=document.createElement('button');btn.type='button';btn.dataset.function=fn;btn.textContent='Inspect function record';panel.append(p1,h,p2,btn)}));

for(let i=0;i<32;i++){const el=document.createElement('i');qs('#xorRibbon').appendChild(el)}
qs('#runXor').addEventListener('click',()=>{const cells=qsa('#xorRibbon i');cells.forEach(c=>c.classList.remove('hot'));cells.reverse().forEach((c,i)=>setTimeout(()=>c.classList.add('hot'),i*28))});
qs('#runRc4').addEventListener('click',()=>{const w=qs('#stateWheel');w.classList.remove('spin');void w.offsetWidth;w.classList.add('spin')});

function selectServer(n){qsa('[data-server]').forEach(b=>b.classList.toggle('active',Number(b.dataset.server)===n));qs('#serverReadout').textContent=String(n).padStart(2,'0')}
qsa('[data-server]').forEach(b=>b.addEventListener('click',()=>selectServer(Number(b.dataset.server))));
let cycleRunning=false;qs('#runCycle').addEventListener('click',()=>{if(cycleRunning)return;cycleRunning=true;const items=qsa('#cycleTrace li');let i=0;items.forEach(x=>x.classList.remove('active'));qs('#cycleStatus').textContent='SIMULATION / LOCAL VISUAL ONLY';const tick=()=>{items.forEach(x=>x.classList.remove('active'));items[i].classList.add('active');if(i===2)selectServer((Number(qs('#serverReadout').textContent)%5)+1);i++;if(i<items.length)setTimeout(tick,480);else setTimeout(()=>{cycleRunning=false;qs('#cycleStatus').textContent='CYCLE COMPLETE / NO NETWORK ACTION'},480)};tick()});

qsa('[data-route]').forEach(b=>b.addEventListener('click',()=>{qsa('[data-route]').forEach(x=>x.classList.remove('active'));b.classList.add('active');const [label,copy]=routeCopy[b.dataset.route];qs('#routeReadout span').textContent=label;qs('#routeReadout p').textContent=copy}));
qs('#traceRoute').addEventListener('click',()=>{const wires=qsa('.route-wire');wires.forEach(w=>w.classList.remove('tracing'));void qs('#routePulse').offsetWidth;wires.forEach(w=>w.classList.add('tracing'))});

function renderCommand(type){const wrap=qs('#dispatchFlow');wrap.replaceChildren();commandFlows[type].forEach((item,i)=>{const d=document.createElement('div'),s=document.createElement('span'),b=document.createElement('b');s.textContent=item[0];b.textContent=item[1];d.append(s,b);wrap.appendChild(d);if(i<2)wrap.appendChild(document.createElement('i'))})}
qsa('[data-command]').forEach(b=>b.addEventListener('click',()=>{qsa('[data-command]').forEach(x=>x.setAttribute('aria-selected','false'));b.setAttribute('aria-selected','true');renderCommand(b.dataset.command)}));
let sending=false;qs('#sendChunk').addEventListener('click',()=>{if(sending)return;sending=true;const strip=qs('#packetStrip');let n=0;const attempt=()=>{n++;qs('#attemptReadout').textContent=`${n} / 3`;strip.classList.remove('sending');void strip.offsetWidth;strip.classList.add('sending');if(n<3)setTimeout(attempt,1050);else setTimeout(()=>{sending=false;strip.classList.remove('sending')},1100)};attempt()});

const atlas=qs('#functionAtlas');
function makeFunctionNode(f){const b=document.createElement('button');b.type='button';b.className=`function-card flow-node ${f.confidence==='review'?'unverified':f.confidence==='moderate'?'moderate':''}`;b.dataset.function=f.id;b.dataset.group=f.group;const state=document.createElement('span');state.textContent=f.confidence==='review'?'REVIEW REQUIRED':f.confidence==='moderate'?'MODERATE':'CODE-BACKED';const id=document.createElement('b');id.textContent=f.id;const name=document.createElement('small');name.textContent=f.name;const role=document.createElement('em');role.textContent=f.role;b.append(state,id,name,role);return b}
function renderFunctions(filter='all',query=''){atlas.replaceChildren();const needle=query.trim().toLowerCase();let visible=0;flowGroups.forEach(group=>{if(filter!=='all'&&filter!==group.id)return;const matches=group.order.map(id=>functions.find(f=>f.id===id)).filter(f=>f&&(!needle||`${f.id} ${f.name} ${f.role}`.toLowerCase().includes(needle)));if(!matches.length)return;const lane=document.createElement('section');lane.className='flow-lane';lane.dataset.flowGroup=group.id;const head=document.createElement('header');const index=document.createElement('span');index.textContent=String(flowGroups.indexOf(group)+1).padStart(2,'0');const copy=document.createElement('div');const h=document.createElement('h4');h.textContent=group.label;const p=document.createElement('p');p.textContent=group.note;copy.append(h,p);head.append(index,copy);const track=document.createElement('div');track.className='flow-track';track.setAttribute('role','list');matches.forEach((f,i)=>{const wrap=document.createElement('div');wrap.className='flow-stop';wrap.setAttribute('role','listitem');wrap.appendChild(makeFunctionNode(f));track.appendChild(wrap);if(i<matches.length-1){const edge=document.createElement('i');edge.className='flow-edge';edge.setAttribute('aria-hidden','true');track.appendChild(edge)}});lane.append(head,track);atlas.appendChild(lane);visible+=matches.length});qs('#graphStatus').textContent=`${visible} node${visible===1?'':'s'} / ${filter==='all'?'full graph':filter}`}
renderFunctions();let currentFilter='all';qsa('[data-function-filter]').forEach(b=>b.addEventListener('click',()=>{currentFilter=b.dataset.functionFilter;qsa('[data-function-filter]').forEach(x=>x.classList.remove('active'));b.classList.add('active');renderFunctions(currentFilter,qs('#functionSearch').value)}));qs('#functionSearch').addEventListener('input',e=>renderFunctions(currentFilter,e.target.value));
let graphTracing=false;qs('#runFunctionTrace').addEventListener('click',()=>{if(graphTracing)return;graphTracing=true;currentFilter='all';qs('#functionSearch').value='';qsa('[data-function-filter]').forEach(x=>x.classList.toggle('active',x.dataset.functionFilter==='all'));renderFunctions();const button=qs('#runFunctionTrace');button.classList.add('running');qs('#graphStatus').textContent='signal entering / local visualization';let i=0;const tick=()=>{qsa('.flow-node.trace-hot').forEach(n=>n.classList.remove('trace-hot'));const node=qs(`.flow-node[data-function="${functionTrace[i]}"]`);if(node){node.classList.add('trace-hot');node.scrollIntoView({behavior:'smooth',block:'nearest',inline:'center'})}i++;if(i<functionTrace.length)setTimeout(tick,260);else setTimeout(()=>{qsa('.flow-node.trace-hot').forEach(n=>n.classList.remove('trace-hot'));button.classList.remove('running');qs('#graphStatus').textContent='31 nodes / trace complete';graphTracing=false},520)};tick()});

const dialog=qs('#functionDialog');
function closeFunction(){dialog.removeAttribute('open');dialog.classList.remove('manual-open')}
async function openFunction(id){const f=functions.find(x=>x.id===id);if(!f)return;qs('#functionGroup').textContent=`${f.group.toUpperCase()} / ${f.role.toUpperCase()}`;qs('#functionTitle').textContent=f.name;qs('#functionName').textContent=f.id;const summary=qs('#functionSummary');summary.replaceChildren();const confidence=f.confidence==='review'?'Requires verification':f.confidence==='moderate'?'Moderate':'High';[['Role',f.role],['Confidence',confidence],['Evidence basis',f.summary]].forEach(([k,v])=>{const d=document.createElement('div'),b=document.createElement('b'),s=document.createElement('span');b.textContent=k;s.textContent=v;d.append(b,s);summary.appendChild(d)});const code=qs('#functionCode');code.textContent='Loading supplied function text…';qs('#codeState').textContent='LOADING';dialog.setAttribute('open','');dialog.classList.add('manual-open');try{const res=await fetch(`assets/decompiled/${id}.c`,{cache:'no-store'});if(!res.ok)throw new Error();code.textContent=await res.text();qs('#codeState').textContent=code.textContent.includes('AWAITING_DECOMPILE')?'STAGED / AWAITING EXPORT':'SUPPLIED / INERT TEXT'}catch{code.textContent=`AWAITING_DECOMPILE: ${id}\n\nThe site is open from the local filesystem, so browser fetch access is unavailable. Serve the folder over HTTP to load staged source files. No code is executed.`;qs('#codeState').textContent='LOCAL FILE MODE / STAGED'}}
document.addEventListener('click',e=>{const trigger=e.target.closest('[data-function]');if(trigger)openFunction(trigger.dataset.function)});qs('#closeFunction').addEventListener('click',closeFunction);

const evidenceGrid=qs('#evidenceGrid');evidence.forEach((item,i)=>{const art=document.createElement('article');art.className='evidence-slot';const num=document.createElement('span');num.textContent=`SHOT ${String(i+1).padStart(2,'0')} / 26`;const h=document.createElement('h4');h.textContent=item[0];const p=document.createElement('p');p.textContent=`Highlight: ${item[1]}`;const foot=document.createElement('footer');const left=document.createElement('span');left.textContent='GHIDRA CAPTURE';const right=document.createElement('b');right.textContent='AWAITING';foot.append(left,right);art.append(num,h,p,foot);evidenceGrid.appendChild(art)});

const ledgerBody=qs('#ledgerBody');function renderLedger(filter='all'){ledgerBody.replaceChildren();answers.filter(a=>filter==='all'||a[3]===filter).forEach(a=>{const tr=document.createElement('tr');tr.dataset.type=a[3];[String(a[0]).padStart(2,'0'),a[1],a[2],a[3].toUpperCase()].forEach(v=>{const td=document.createElement('td');td.textContent=v;tr.appendChild(td)});ledgerBody.appendChild(tr)})}renderLedger();qsa('[data-ledger]').forEach(b=>b.addEventListener('click',()=>{qsa('[data-ledger]').forEach(x=>x.classList.remove('active'));b.classList.add('active');renderLedger(b.dataset.ledger)}));

const reducedMotion=matchMedia('(prefers-reduced-motion: reduce)').matches;
if(!reducedMotion&&'IntersectionObserver' in window){document.body.classList.add('motion-ready');const revealObserver=new IntersectionObserver(entries=>entries.forEach(entry=>{if(entry.isIntersecting){entry.target.classList.add('in-view');revealObserver.unobserve(entry.target)}}),{rootMargin:'0px 0px -8% 0px',threshold:.08});qsa('.chapter,.findings-head,.finding-lead,.artifacts-head,.artifact-columns,.atlas-head,.atlas-toolbar,.function-graph,.evidence-head,.evidence-grid,.ledger-head,.ledger-wrap,.verdict>*,.case-closed').forEach(el=>revealObserver.observe(el))}

document.addEventListener('keydown',e=>{if(e.key==='Escape'){if(dialog.open)closeFunction();setIndex(false)}});
