bool FUN_180004288(longlong param_1)

{
  HANDLE hFile;
  undefined8 *puVar1;
  bool bVar2;
  DWORD local_res10 [2];
  byte local_648 [1600];
  
  hFile = CreateFileA(&DAT_1800414f0,0x40000000,1,(LPSECURITY_ATTRIBUTES)0x0,4,0,(HANDLE)0x0);
  if (hFile == (HANDLE)0xffffffffffffffff) {
    bVar2 = false;
  }
  else {
    local_res10[0] = 0;
    local_648[0] = 0;
    local_648[1] = 0;
    local_648[2] = 0;
    local_648[3] = 0;
    local_648[4] = 0;
    local_648[5] = 0;
    local_648[6] = 0;
    local_648[7] = 0;
    local_648[8] = 0;
    local_648[9] = 0;
    local_648[10] = 0;
    local_648[0xb] = 0;
    local_648[0xc] = 0;
    local_648[0xd] = 0;
    local_648[0xe] = 0;
    local_648[0xf] = 0;
    FUN_18001cca0((undefined1 (*) [16])(local_648 + 0x10),0,0x630);
    puVar1 = (undefined8 *)(param_1 + 0xc848);
    FUN_18001cfc0((undefined8 *)local_648,puVar1,0x640);
    FUN_1800090a4(local_648,puVar1,param_1 + 0xd4b8);
    WriteFile(hFile,local_648,0x640,local_res10,(LPOVERLAPPED)0x0);
    FUN_18000208c(hFile);
    CloseHandle(hFile);
    bVar2 = local_res10[0] == 0x640;
  }
  return bVar2;
}
