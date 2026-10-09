/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_180002148(char *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  int iVar1;
  size_t sVar2;
  HANDLE hFile;
  undefined8 uVar3;
  HANDLE pvVar4;
  size_t _SizeInBytes;
  undefined8 local_res10;
  undefined8 local_res18;
  undefined8 local_res20;
  undefined8 in_stack_ffffffffffffbf88;
  undefined4 uVar5;
  undefined8 in_stack_ffffffffffffbf90;
  undefined4 uVar6;
  undefined8 in_stack_ffffffffffffbf98;
  undefined4 uVar7;
  int local_4048;
  int local_4044;
  _SYSTEMTIME local_4040;
  DWORD local_4030 [2];
  char local_4028 [8192];
  byte local_2028;
  undefined1 local_2027 [8183];
  undefined8 uStack_30;
  
  uVar5 = (undefined4)((ulonglong)in_stack_ffffffffffffbf88 >> 0x20);
  uVar6 = (undefined4)((ulonglong)in_stack_ffffffffffffbf90 >> 0x20);
  uVar7 = (undefined4)((ulonglong)in_stack_ffffffffffffbf98 >> 0x20);
  uStack_30 = 0x180002172;
  if (DAT_1800414e4 != 0) {
    local_4040.wYear = 0;
    local_4040.wMonth = 0;
    local_4040.wDayOfWeek = 0;
    local_4040.wDay = 0;
    local_4040.wHour = 0;
    local_4040.wMinute = 0;
    local_4040.wSecond = 0;
    local_4040.wMilliseconds = 0;
    local_4028[0] = '\0';
    local_res10 = param_2;
    local_res18 = param_3;
    local_res20 = param_4;
    FUN_18001cca0((undefined1 (*) [16])(local_4028 + 1),0,0x1fff);
    local_2028 = 0;
    FUN_18001cca0((undefined1 (*) [16])local_2027,0,0x1fff);
    GetLocalTime(&local_4040);
    sprintf_s(local_4028,0x2000,"%d/%02d/%02d %02d:%02d:%02d - ",(ulonglong)local_4040.wYear,
              CONCAT44(uVar5,(uint)local_4040.wMonth),CONCAT44(uVar6,(uint)local_4040.wDay),
              CONCAT44(uVar7,(uint)local_4040.wHour),local_4040._10_4_ & 0xffff,
              (uint)local_4040._10_4_ >> 0x10);
    sVar2 = strlen(local_4028);
    _SizeInBytes = (size_t)(0x2000 - (int)sVar2);
    _vsnprintf_s(local_4028 + (int)sVar2,_SizeInBytes,_SizeInBytes,param_1,(va_list)&local_res10);
    hFile = CreateFileA(&DAT_1800413e0,0x40000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
    if (hFile != (HANDLE)0xffffffffffffffff) {
      sVar2 = strlen(local_4028);
      local_4030[0] = GetFileSize(hFile,(LPDWORD)0x0);
      pvVar4 = hFile;
      if (DAT_18003e6c4 < local_4030[0]) {
        SetEndOfFile(hFile);
      }
      else {
        SetFilePointer(hFile,0,(PLONG)0x0,2);
      }
      local_4044 = 0;
      iVar1 = FUN_180001880(pvVar4,0,(undefined1 (*) [16])local_4028,(int)sVar2,
                            (undefined8 *)&local_2028,&local_4044,(undefined8 *)&DAT_18003e6c8);
      if (iVar1 == 0) {
        FUN_18001cca0((undefined1 (*) [16])local_4028,0,0x2000);
        local_4048 = 0x2000;
        uVar3 = FUN_180001ee0(&local_2028,local_4044,(undefined1 (*) [16])local_4028,&local_4048);
        if (((int)uVar3 != 0) && (0 < local_4048)) {
          strcat_s(local_4028,0x2000,"\r\n");
          sVar2 = strlen(local_4028);
          WriteFile(hFile,local_4028,(DWORD)sVar2,local_4030,(LPOVERLAPPED)0x0);
          CloseHandle(hFile);
        }
      }
    }
  }
  return;
}
