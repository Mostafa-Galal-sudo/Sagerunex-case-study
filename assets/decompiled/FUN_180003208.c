undefined8 FUN_180003208(void)

{
  int iVar1;
  HANDLE hObject;
  undefined8 uVar2;
  undefined4 local_248;
  undefined1 local_244 [4];
  uint local_240;
  wchar_t local_21c [266];
  
  hObject = (HANDLE)CreateToolhelp32Snapshot(2);
  if (hObject != (HANDLE)0xffffffffffffffff) {
    local_248 = 0x238;
    FUN_18001cca0((undefined1 (*) [16])local_244,0,0x234);
    iVar1 = Process32FirstW(hObject,&local_248);
    while (iVar1 != 0) {
      iVar1 = wcscmp(local_21c,L"explorer.exe");
      if (iVar1 == 0) {
        CloseHandle(hObject);
        uVar2 = FUN_1800031a0(hObject,local_240);
        return uVar2;
      }
      iVar1 = Process32NextW(hObject,&local_248);
    }
  }
  return 0;
}
