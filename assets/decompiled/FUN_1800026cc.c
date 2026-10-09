/* WARNING: Removing unreachable block (ram,0x00018000271c) */
/* WARNING: Removing unreachable block (ram,0x0001800026fa) */
/* WARNING: Removing unreachable block (ram,0x000180002748) */

void FUN_1800026cc(byte *param_1,undefined8 param_2,longlong param_3)

{
  byte bVar1;
  uint uVar2;
  ulonglong uVar3;
  uint uVar4;
  longlong lVar5;
  
  uVar2 = (uint)*(byte *)(param_3 + 0x100);
  uVar4 = (uint)*(byte *)(param_3 + 0x101);
  lVar5 = 0x640;
  do {
    uVar2 = uVar2 + 1 & 0x800000ff;
    uVar3 = (ulonglong)uVar2;
    bVar1 = *(byte *)(uVar3 + param_3);
    uVar4 = uVar4 + bVar1 & 0x800000ff;
    *(undefined1 *)(uVar3 + param_3) = *(undefined1 *)((ulonglong)uVar4 + param_3);
    *(byte *)((ulonglong)uVar4 + param_3) = bVar1;
    *param_1 = *param_1 ^
               *(byte *)((ulonglong)((uint)*(byte *)(uVar3 + param_3) + (uint)bVar1 & 0x800000ff) +
                        param_3);
    param_1 = param_1 + 1;
    lVar5 = lVar5 + -1;
  } while (lVar5 != 0);
  *(char *)(param_3 + 0x100) = (char)uVar2;
  *(char *)(param_3 + 0x101) = (char)uVar4;
  return;
}
