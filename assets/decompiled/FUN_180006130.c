void FUN_180006130(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  undefined8 uVar4;
  
  FUN_18001cca0((undefined1 (*) [16])(param_1 + 0x24),0,0xc800);
  uVar4 = 0x10;
  *(undefined2 *)(param_1 + 0x2e) = 1;
  puVar2 = (undefined8 *)(param_1 + 0xcc54);
  if (*(char *)(param_1 + 0xcc48) != '\0') {
    puVar2 = (undefined8 *)(param_1 + 0xcc64);
  }
  FUN_18001cfc0((undefined8 *)(param_1 + 0x30),puVar2,0x10);
  puVar2 = (undefined8 *)(param_1 + 0x40);
  FUN_18001cfc0(puVar2,(undefined8 *)(param_1 + 0xcc54),0x10);
  puVar3 = (undefined8 *)(param_1 + 0x50);
  FUN_1800011ac(puVar2,puVar3);
  uVar1 = FUN_180005dd4(param_1,puVar3,(int)uVar4);
  if ((int)uVar1 != 0) {
    FUN_180005f84(param_1,(byte *)(param_1 + 0x50),uVar4,param_4);
  }
  return;
}
