void FUN_1800040cc(undefined8 param_1,uint param_2)

{
  size_t sVar1;
  size_t sVar2;
  
  FUN_18001cca0((undefined1 (*) [16])&DAT_1800414f0,0,0x104);
  SHGetSpecialFolderPathA((HWND)0x0,&DAT_1800414f0,0x1a,0);
  strcat_s(&DAT_1800414f0,0x104,"\\Microsoft");
  CreateDirectoryA(&DAT_1800414f0,(LPSECURITY_ATTRIBUTES)0x0);
  strcat_s(&DAT_1800414f0,0x104,"\\Protect");
  CreateDirectoryA(&DAT_1800414f0,(LPSECURITY_ATTRIBUTES)0x0);
  strcat_s(&DAT_1800414f0,0x104,"\\Windows\\");
  CreateDirectoryA(&DAT_1800414f0,(LPSECURITY_ATTRIBUTES)0x0);
  sVar1 = strlen(&DAT_1800414f0);
  sVar2 = strlen(&DAT_1800414f0);
  sprintf_s(&DAT_1800414f0 + sVar2,0x104 - sVar1,"DMI%X.DAT",(ulonglong)param_2);
  return;
}
