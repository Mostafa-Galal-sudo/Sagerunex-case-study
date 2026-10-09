bool FUN_180005628(ulonglong param_1,char *param_2,int param_3,int param_4,char *param_5,
                  uint *param_6)

{
  uint *puVar1;
  int iVar2;
  BOOL BVar3;
  DWORD DVar4;
  size_t sVar5;
  undefined1 (*pauVar6) [16];
  HMODULE hModule;
  FARPROC pFVar7;
  size_t sVar8;
  uint uVar9;
  char *pcVar10;
  char *_Format;
  char *pcVar11;
  ulonglong local_res8 [2];
  int local_res18;
  int local_res20;
  undefined8 in_stack_fffffffffffffab8;
  undefined4 uVar12;
  HANDLE local_518;
  HANDLE local_510;
  _PROCESS_INFORMATION local_508;
  _SECURITY_ATTRIBUTES local_4f0;
  undefined4 local_4d8;
  undefined1 local_4d4 [44];
  _STARTUPINFOA local_4a8;
  char local_438;
  undefined1 local_437 [1023];
  
  uVar12 = (undefined4)((ulonglong)in_stack_fffffffffffffab8 >> 0x20);
  local_438 = '\0';
  local_res8[0] = param_1;
  local_res18 = param_3;
  local_res20 = param_4;
  FUN_18001cca0((undefined1 (*) [16])local_437,0,0x3ff);
  puVar1 = param_6;
  sprintf_s(param_5,(ulonglong)*param_6,"\r\n[%s]\r\n");
  iVar2 = strncmp(param_2,"runexe ",7);
  if (iVar2 == 0) {
    strcpy_s(&local_438,0x400,param_2 + 7);
    iVar2 = strcmp(&local_438,"/?");
    if (iVar2 != 0) {
LAB_180005966:
      local_510 = (HANDLE)0x0;
      local_518 = (HANDLE)0x0;
      local_4f0.nLength = 0x18;
      local_4f0.lpSecurityDescriptor = (LPVOID)0x0;
      local_4f0.bInheritHandle = 1;
      BVar3 = CreatePipe(&local_518,&local_510,&local_4f0,0);
      if (BVar3 == 0) {
        DVar4 = GetLastError();
        sVar5 = strlen(param_5);
        uVar9 = *puVar1;
        sVar8 = strlen(param_5);
        sprintf_s(param_5 + sVar8,uVar9 - sVar5,"open pipe error: 0x%x\r\n\r\n",(ulonglong)DVar4);
        sVar5 = strlen(param_5);
        *puVar1 = (uint)sVar5;
        return false;
      }
      FUN_18001cca0((undefined1 (*) [16])&local_4a8.lpReserved,0,0x60);
      local_508.hProcess = (HANDLE)0x0;
      local_508.hThread = (HANDLE)0x0;
      local_508.dwProcessId = 0;
      local_508.dwThreadId = 0;
      local_4a8.hStdError = local_510;
      local_4a8.hStdOutput = local_510;
      local_4a8.wShowWindow = 0;
      local_4a8.cb = 0x68;
      local_4a8.dwFlags = 0x101;
      BVar3 = CreateProcessA((LPCSTR)0x0,&local_438,(LPSECURITY_ATTRIBUTES)0x0,
                             (LPSECURITY_ATTRIBUTES)0x0,1,0,(LPVOID)0x0,(LPCSTR)0x0,&local_4a8,
                             &local_508);
      if ((BVar3 != 0) && (param_3 != 0)) {
        WaitForSingleObject(local_508.hThread,param_4 * 1000);
        local_res8[0] = local_res8[0] & 0xffffffff00000000;
        param_6._0_4_ = 0;
        sVar5 = strlen(param_5);
        uVar9 = (uint)sVar5;
        if (uVar9 < *puVar1) {
          do {
            uVar9 = (uint)sVar5;
            BVar3 = PeekNamedPipe(local_518,(LPVOID)0x0,0,(LPDWORD)0x0,(LPDWORD)&param_6,
                                  (LPDWORD)0x0);
            if ((((BVar3 == 0) || ((int)param_6 == 0)) ||
                (BVar3 = ReadFile(local_518,param_5 + (sVar5 & 0xffffffff),*puVar1 - uVar9,
                                  (LPDWORD)local_res8,(LPOVERLAPPED)0x0), BVar3 == 0)) ||
               ((int)local_res8[0] == 0)) break;
            uVar9 = uVar9 + (int)local_res8[0];
            sVar5 = (size_t)uVar9;
            param_6._0_4_ = 0;
            WaitForSingleObject(local_508.hThread,1000);
          } while (uVar9 < *puVar1);
        }
        FUN_18001cca0((undefined1 (*) [16])(param_5 + uVar9),0,(ulonglong)(*puVar1 - uVar9));
        *puVar1 = uVar9;
        CloseHandle(local_508.hThread);
        CloseHandle(local_508.hProcess);
      }
      CloseHandle(local_518);
      CloseHandle(local_510);
      return local_508.hProcess != (HANDLE)0x0;
    }
    strcat_s(param_5,(ulonglong)*puVar1,"usage:\r\n  runexe 1.exe\r\n\r\n");
    goto LAB_1800056f2;
  }
  iVar2 = strncmp(param_2,"rundll ",7);
  if (iVar2 != 0) {
    GetSystemDirectoryA(&local_438,0x400);
    strcat_s(&local_438,0x400,"\\cmd.exe");
    local_4d8 = 0;
    FUN_18001cca0((undefined1 (*) [16])local_4d4,0,0x20);
    BVar3 = GetFileAttributesExA(&local_438,GetFileExInfoStandard,&local_4d8);
    if (BVar3 == -1) {
      DVar4 = GetLastError();
      sVar5 = strlen(param_5);
      uVar9 = *puVar1;
      sVar8 = strlen(param_5);
      sprintf_s(param_5 + sVar8,uVar9 - sVar5,"%s not exist: 0x%x\r\n\r\n",&local_438,
                CONCAT44(uVar12,DVar4));
      sVar5 = strlen(param_5);
      *puVar1 = (uint)sVar5;
      param_4 = local_res20;
      param_3 = local_res18;
    }
    strcat_s(&local_438,0x400," /c ");
    strcat_s(&local_438,0x400,param_2);
    goto LAB_180005966;
  }
  sVar5 = strlen(param_2);
  if (sVar5 < 9) {
LAB_18000572f:
    pcVar10 = "illegal command\r\n\r\n";
  }
  else {
    strcpy_s(&local_438,0x400,param_2 + 7);
    iVar2 = strcmp(&local_438,"/?");
    if (iVar2 != 0) {
      pauVar6 = FUN_18001e668((undefined1 (*) [16])&local_438,(undefined1 (*) [16])&DAT_180035b0c);
      if (pauVar6 == (undefined1 (*) [16])0x0) goto LAB_18000572f;
      (*pauVar6)[0] = 0;
      pcVar10 = *pauVar6 + 1;
      hModule = LoadLibraryA(&local_438);
      if (hModule == (HMODULE)0x0) {
        DVar4 = GetLastError();
        sVar5 = strlen(param_5);
        uVar9 = *puVar1;
        sVar8 = strlen(param_5);
        sprintf_s(param_5 + sVar8,uVar9 - sVar5,"error:0x%x\r\n\r\n",(ulonglong)DVar4);
        goto LAB_1800056f2;
      }
      iVar2 = strcmp(pcVar10,"DllMain");
      if (iVar2 == 0) {
LAB_180005844:
        sVar5 = strlen(param_5);
        sVar5 = *puVar1 - sVar5;
        sVar8 = strlen(param_5);
        pcVar11 = &local_438;
        _Format = "load %s[%s] ok.\r\n\r\n";
      }
      else {
        pFVar7 = GetProcAddress(hModule,pcVar10);
        if (pFVar7 != (FARPROC)0x0) {
          (*pFVar7)();
          goto LAB_180005844;
        }
        DVar4 = GetLastError();
        sVar5 = strlen(param_5);
        sVar5 = *puVar1 - sVar5;
        sVar8 = strlen(param_5);
        _Format = "find %s error:0x%x\r\n\r\n";
        pcVar11 = pcVar10;
        pcVar10 = (char *)CONCAT44(uVar12,DVar4);
      }
      sprintf_s(param_5 + sVar8,sVar5,_Format,pcVar11,pcVar10);
      goto LAB_1800056f2;
    }
    pcVar10 = "usage:\r\n  rundll 1.dll,DllMain\r\n\r\n";
  }
  strcat_s(param_5,(ulonglong)*puVar1,pcVar10);
LAB_1800056f2:
  sVar5 = strlen(param_5);
  *puVar1 = (uint)sVar5;
  return true;
}
