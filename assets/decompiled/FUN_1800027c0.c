undefined8 FUN_1800027c0(longlong param_1,undefined8 *param_2,undefined8 param_3,undefined8 param_4)

{
  uint uVar1;
  bool bVar2;
  undefined8 uVar3;
  longlong lVar4;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  undefined8 *puVar5;
  
  puVar5 = param_2;
  uVar3 = FUN_180004194(param_1);
  if ((int)uVar3 == 0) {
    param_3 = 0x640;
    FUN_18001cfc0((undefined8 *)(param_1 + 0xc848),param_2,0x640);
    uVar1 = 2;
    if (2 < (int)*(uint *)(param_1 + 0xcc44)) {
      uVar1 = *(uint *)(param_1 + 0xcc44);
    }
    *(uint *)(param_1 + 0xcc44) = uVar1;
    puVar5 = param_2;
    if (*(longlong *)(param_1 + 0xcc78) == 0) {
      lVar4 = FUN_180002d0c((ulonglong)uVar1);
      *(longlong *)(param_1 + 0xcc78) = lVar4;
      puVar5 = param_2;
    }
    bVar2 = FUN_180004288(param_1);
    if ((int)CONCAT71(extraout_var,bVar2) == 0) {
      FUN_180002148("0x00, SC failed.",puVar5,param_3,param_4);
    }
  }
  if (*(uint *)(param_1 + 0xcc50) < 0x18) {
    uVar1 = *(uint *)(param_1 + 0xcc4c);
    puVar5 = (undefined8 *)(ulonglong)uVar1;
    if ((uVar1 < 0x18) && (*(uint *)(param_1 + 0xcc50) != uVar1)) {
      return 1;
    }
  }
  *(undefined4 *)(param_1 + 0xcc4c) = 0;
  *(undefined4 *)(param_1 + 0xcc50) = 0;
  bVar2 = FUN_180004288(param_1);
  if ((int)CONCAT71(extraout_var_00,bVar2) == 0) {
    FUN_180002148("0x00, SC failed.",puVar5,param_3,param_4);
  }
  return 1;
}
