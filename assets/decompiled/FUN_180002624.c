/* WARNING: Removing unreachable block (ram,0x000180002682) */
/* WARNING: Removing unreachable block (ram,0x0001800026a7) */

void FUN_180002624(longlong param_1,undefined8 param_2,byte *param_3)

{
  byte bVar1;
  short sVar2;
  ulonglong uVar3;
  ulonglong uVar4;
  byte *pbVar5;
  longlong lVar6;
  
  uVar4 = 0;
  uVar3 = 0;
  sVar2 = 0;
  lVar6 = 0x100;
  pbVar5 = param_3;
  do {
    *pbVar5 = (byte)sVar2;
    sVar2 = sVar2 + 1;
    pbVar5 = pbVar5 + 1;
  } while (sVar2 < 0x100);
  param_3[0x100] = 0;
  param_3[0x101] = 0;
  pbVar5 = param_3;
  do {
    bVar1 = *pbVar5;
    uVar3 = (ulonglong)((int)uVar3 + (uint)*(byte *)(uVar4 + param_1) + (uint)bVar1 & 0x800000ff);
    *pbVar5 = param_3[uVar3];
    param_3[uVar3] = bVar1;
    pbVar5 = pbVar5 + 1;
    uVar4 = (ulonglong)(byte)((char)uVar4 + 1);
    lVar6 = lVar6 + -1;
  } while (lVar6 != 0);
  return;
}
