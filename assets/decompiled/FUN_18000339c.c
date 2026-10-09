void FUN_18000339c(undefined4 *param_1,int param_2)

{
  longlong lVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1 + 0x3610;
  for (lVar1 = 0x32; lVar1 != 0; lVar1 = lVar1 + -1) {
    *(undefined2 *)puVar2 = 0;
    puVar2 = (undefined4 *)((longlong)puVar2 + 2);
  }
  puVar2 = param_1 + 0x35f7;
  for (lVar1 = 0x32; lVar1 != 0; lVar1 = lVar1 + -1) {
    *(undefined2 *)puVar2 = 0;
    puVar2 = (undefined4 *)((longlong)puVar2 + 2);
  }
  FUN_1800033dc(param_1,param_2);
  return;
}
