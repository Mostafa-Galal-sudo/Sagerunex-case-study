void FUN_1800061bc(byte *param_1,int param_2)

{
  uint uVar1;
  byte *pbVar2;
  
  if (param_1 != (byte *)0x0) {
    uVar1 = param_2 - 1;
    if (uVar1 != 0) {
      pbVar2 = param_1 + uVar1;
      do {
        *pbVar2 = *pbVar2 ^ pbVar2[-1];
        pbVar2 = pbVar2 + -1;
        uVar1 = uVar1 - 1;
      } while (uVar1 != 0);
    }
    *param_1 = *param_1 ^ 0xad;
  }
  return;
}
