/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_180002394(wchar_t *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  longlong lVar2;
  HANDLE hFile;
  undefined8 uVar3;
  size_t sVar4;
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  int local_8048;
  int local_8044;
  _SYSTEMTIME local_8040;
  DWORD local_8030 [2];
  CHAR local_8028;
  undefined1 local_8027 [8191];
  byte local_6028;
  undefined1 local_6027 [8191];
  wchar_t local_4028;
  undefined1 local_4026 [16382];
  undefined8 uStack_28;
  
  uStack_28 = 0x1800023bc;
  if (DAT_1800414e4 != 0) {
    local_8040.wYear = 0;
    local_4028 = L'\0';
    local_8040.wMonth = 0;
    local_8040.wDayOfWeek = 0;
    local_8040.wDay = 0;
    local_8040.wHour = 0;
    local_8040.wMinute = 0;
    local_8040.wSecond = 0;
    local_8040.wMilliseconds = 0;
    local_res10 = param_2;
    local_res18 = param_3;
    local_res20 = param_4;
    FUN_18001cca0((undefined1 (*) [16])local_4026,0,0x3ffe);
    local_6028 = 0;
    FUN_18001cca0((undefined1 (*) [16])local_6027,0,0x1fff);
    GetLocalTime(&local_8040);
    FUN_18001d8d8(&local_4028,0x2000,L"%d/%02d/%02d %02d:%02d:%02d - ",(ulonglong)local_8040.wYear);
    lVar2 = FUN_18001d570(&local_4028);
    sVar4 = (size_t)(0x2000 - (int)lVar2);
    _vsnwprintf_s((wchar_t *)(local_4026 + (longlong)(int)lVar2 * 2 + -2),sVar4,sVar4,param_1,
                  (va_list)&local_res10);
    hFile = CreateFileA(&DAT_1800413e0,0x40000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
    if (hFile != (HANDLE)0xffffffffffffffff) {
      local_8028 = '\0';
      FUN_18001cca0((undefined1 (*) [16])local_8027,0,0x1fff);
      local_8030[0] = GetFileSize(hFile,(LPDWORD)0x0);
      if (DAT_18003e6c4 < local_8030[0]) {
        SetEndOfFile(hFile);
      }
      else {
        SetFilePointer(hFile,0,(PLONG)0x0,2);
      }
      WideCharToMultiByte(0,0,&local_4028,-1,&local_8028,0x2000,(LPCSTR)0x0,(LPBOOL)0x0);
      sVar4 = strlen(&local_8028);
      local_8048 = 0;
      iVar1 = FUN_180001880(&local_6028,0,(undefined1 (*) [16])&local_8028,(int)sVar4,
                            (undefined8 *)&local_6028,&local_8048,(undefined8 *)&DAT_18003e6c8);
      if (iVar1 == 0) {
        FUN_18001cca0((undefined1 (*) [16])&local_8028,0,0x2000);
        local_8044 = 0x2000;
        uVar3 = FUN_180001ee0(&local_6028,local_8048,(undefined1 (*) [16])&local_8028,&local_8044);
        if (((int)uVar3 != 0) && (0 < local_8044)) {
          strcat_s(&local_8028,0x2000,"\r\n");
          sVar4 = strlen(&local_8028);
          WriteFile(hFile,&local_8028,(DWORD)sVar4,local_8030,(LPOVERLAPPED)0x0);
          CloseHandle(hFile);
        }
      }
    }
  }
  return;
}
