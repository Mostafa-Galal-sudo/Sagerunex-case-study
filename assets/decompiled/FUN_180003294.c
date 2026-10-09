undefined8 FUN_180003294(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  BOOL BVar1;
  DWORD DVar2;
  HANDLE ProcessHandle;
  PHANDLE ppvVar3;
  PHANDLE ppvVar4;
  undefined8 uVar5;
  HANDLE local_res10;
  HANDLE local_res18;
  
  local_res10 = (HANDLE)0x0;
  ProcessHandle = (HANDLE)FUN_180003208();
  if (ProcessHandle != (HANDLE)0x0) {
    ppvVar3 = &local_res10;
    BVar1 = OpenProcessToken(ProcessHandle,0xf01ff,ppvVar3);
    if (BVar1 == 0) {
      DVar2 = GetLastError();
      FUN_180002148("0x02, GA failed 0x%x.",(ulonglong)DVar2,ppvVar3,param_4);
    }
    else {
      ppvVar3 = (PHANDLE)(param_1 + 0xd7c8);
      ppvVar4 = ppvVar3;
      BVar1 = DuplicateToken(local_res10,SecurityImpersonation,ppvVar3);
      if (BVar1 != 0) {
        local_res18 = GetCurrentThread();
        ppvVar4 = (PHANDLE)(param_1 + 0xd7d0);
        uVar5 = 0;
        OpenThreadToken(local_res18,0xf01ff,0,ppvVar4);
        BVar1 = SetThreadToken(&local_res18,*ppvVar3);
        if (BVar1 == 0) {
          DVar2 = GetLastError();
          FUN_180002148("0x02, SA failed 0x%x.",(ulonglong)DVar2,uVar5,ppvVar4);
          return 0;
        }
        return 1;
      }
      DVar2 = GetLastError();
      FUN_180002148("0x02, DA failed 0x%x.",(ulonglong)DVar2,ppvVar4,param_4);
      CloseHandle(ProcessHandle);
      ProcessHandle = local_res10;
    }
    CloseHandle(ProcessHandle);
  }
  return 0;
}
