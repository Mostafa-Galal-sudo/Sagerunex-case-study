undefined8 FUN_180004194(longlong param_1)

{
  byte *lpBuffer;
  int iVar1;
  HANDLE hFile;
  byte *pbVar2;
  DWORD local_res10 [2];
  
  hFile = CreateFileA(&DAT_1800414f0,0x80000000,1,(LPSECURITY_ATTRIBUTES)0x0,3,0,(HANDLE)0x0);
  if (hFile != (HANDLE)0xffffffffffffffff) {
    local_res10[0] = 0;
    lpBuffer = (byte *)(param_1 + 0xc848);
    pbVar2 = lpBuffer;
    ReadFile(hFile,lpBuffer,0x640,local_res10,(LPOVERLAPPED)0x0);
    CloseHandle(hFile);
    if (local_res10[0] == 0x640) {
      FUN_1800090a4(lpBuffer,pbVar2,param_1 + 0xd4b8);
      if (*(char *)(param_1 + 0xcc48) == '\0') {
        DeleteFileA(&DAT_1800414f0);
      }
      else {
        iVar1 = *(int *)(param_1 + 0xcc74);
        if ((((iVar1 == 0xaa9abb) || (iVar1 == 0xb9dcfb)) || (iVar1 == 0xc91f3b)) ||
           ((iVar1 == 0xd8617b || (iVar1 == 0xe7a3bb)))) {
          return 1;
        }
      }
    }
  }
  return 0;
}
