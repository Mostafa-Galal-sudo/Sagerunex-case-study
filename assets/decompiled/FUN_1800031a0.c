void FUN_1800031a0(undefined8 param_1,uint param_2)

{
  HMODULE hModule;
  FARPROC pFVar1;
  byte local_18 [16];
  
  hModule = GetModuleHandleA("Kernel32.dll");
  local_18[0] = 0xe2;
  local_18[1] = 0x92;
  local_18[2] = 0xf7;
  local_18[3] = 0x99;
  local_18[4] = 0xc9;
  local_18[5] = 0xbb;
  local_18[6] = 0xd4;
  local_18[7] = 0xb7;
  local_18[8] = 0xd2;
  local_18[9] = 0xa1;
  local_18[10] = 0xd2;
  local_18[0xb] = 0xd2;
  FUN_1800061bc(local_18,0xc);
  pFVar1 = GetProcAddress(hModule,(LPCSTR)local_18);
  (*pFVar1)(0x1f0fff,0,(ulonglong)param_2);
  return;
}
