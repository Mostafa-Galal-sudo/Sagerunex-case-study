HKEY FUN_1800068ac(HKEY param_1,DWORD *param_2)

{
  DWORD dwIndex;
  LSTATUS LVar1;
  int iVar2;
  undefined1 (*pauVar3) [16];
  HKEY local_res8;
  WCHAR local_428;
  undefined1 local_426 [526];
  wchar_t local_218;
  undefined1 local_216 [526];
  
  local_428 = L'\0';
  local_res8 = param_1;
  FUN_18001cca0((undefined1 (*) [16])local_426,0,0x206);
  do {
    dwIndex = *param_2;
    *param_2 = dwIndex + 1;
    LVar1 = RegEnumKeyW((HKEY)0xffffffff80000003,dwIndex,&local_428,0x104);
    if (LVar1 != 0) {
      return (HKEY)0x0;
    }
    iVar2 = wcsncmp(L"S-1-5-21",&local_428,8);
  } while ((iVar2 != 0) ||
          (pauVar3 = FUN_18001e02c((undefined1 (*) [16])&local_428,(undefined1 (*) [16])L"Classes"),
          pauVar3 != (undefined1 (*) [16])0x0));
  local_res8 = (HKEY)0x0;
  local_218 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_216,0,0x206);
  wcscpy_s(&local_218,0x104,&local_428);
  wcscat_s(&local_218,0x104,L"\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings");
  LVar1 = RegOpenKeyExW((HKEY)0xffffffff80000003,&local_218,0,0x20019,&local_res8);
  if (LVar1 != 0) {
    local_res8 = (HKEY)0x0;
  }
  return local_res8;
}
