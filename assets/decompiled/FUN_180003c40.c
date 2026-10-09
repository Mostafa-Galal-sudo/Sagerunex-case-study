/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Type propagation algorithm not settling */

undefined8
FUN_180003c40(undefined4 *param_1,undefined8 param_2,undefined8 param_3,ulonglong param_4)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  undefined7 extraout_var_01;
  undefined7 extraout_var_02;
  undefined7 extraout_var_03;
  undefined8 uVar4;
  undefined7 extraout_var_04;
  undefined7 extraout_var_05;
  undefined7 extraout_var_06;
  undefined7 extraout_var_07;
  char *pcVar5;
  undefined8 *puVar6;
  ulonglong uVar7;
  uint *puVar8;
  uint local_res8 [2];
  undefined8 local_c808;
  undefined8 uStack_10;
  
  uStack_10 = 0x180003c61;
  puVar8 = (uint *)0xc7ff;
  uVar4 = 0;
  local_c808._0_1_ = 0;
  FUN_18001cca0((undefined1 (*) [16])((longlong)&local_c808 + 1),0,0xc7ff);
  iVar3 = Ordinal_11(param_1 + 4);
  if ((iVar3 + 1U & 0xfffffffe) == 0) {
    FUN_180002e64((longlong)param_1,uVar4,puVar8,param_4);
  }
  puVar6 = (undefined8 *)(param_1 + 4);
  FUN_180002148("0x04, %s.",puVar6,puVar8,param_4);
  if (DAT_1800414e8 == 0) {
    iVar3 = FUN_180006130((longlong)param_1,puVar6,puVar8,param_4);
    if (iVar3 == 0) {
      pcVar5 = "0x01, RC failed.";
      goto LAB_180003cc3;
    }
    FUN_180002148("0x01, RC success.",puVar6,puVar8,param_4);
  }
  if (*(char *)(param_1 + 0x3312) == '\0') {
    bVar2 = FUN_180004674(param_1);
    if ((int)CONCAT71(extraout_var,bVar2) == 0) {
      return 0;
    }
    *(undefined1 *)(param_1 + 0x3312) = 1;
    bVar2 = FUN_180004288((longlong)param_1);
    if ((int)CONCAT71(extraout_var_00,bVar2) == 0) {
      FUN_180002394(L"0x04, RFO failed.",puVar6,puVar8,param_4);
    }
    FUN_180002394(L"0x04, FO.",puVar6,puVar8,param_4);
  }
  if (DAT_1800414ec == 1) {
    bVar2 = FUN_1800044f8((longlong)param_1);
    if ((int)CONCAT71(extraout_var_01,bVar2) != 0) {
LAB_180003d4e:
      uVar7 = 0;
      do {
        puVar8 = local_res8;
        puVar6 = &local_c808;
        FUN_180003a2c((longlong)param_1,puVar6,puVar8,param_4);
        uVar1 = local_res8[0];
        if (local_res8[0] != 0x11) {
          puVar6 = (undefined8 *)(ulonglong)local_res8[0];
          FUN_180002148("0x01, R %d.",puVar6,puVar8,param_4);
        }
        if ((uVar1 == 0) || (uVar1 == 6)) {
          return 1;
        }
        if (uVar1 == 7) {
          bVar2 = FUN_1800046f8((longlong)param_1,(undefined4 *)&local_c808,7);
          iVar3 = (int)CONCAT71(extraout_var_07,bVar2);
        }
        else if (uVar1 == 8) {
          iVar3 = FUN_180004904((longlong)param_1,(undefined4 *)&local_c808);
        }
        else if (uVar1 == 9) {
          bVar2 = FUN_180005bb4((longlong)param_1,(undefined4 *)&local_c808);
          iVar3 = (int)CONCAT71(extraout_var_06,bVar2);
        }
        else if (uVar1 == 0xb) {
          bVar2 = FUN_180004d08((longlong)param_1,(undefined4 *)&local_c808);
          iVar3 = (int)CONCAT71(extraout_var_05,bVar2);
        }
        else if (uVar1 == 0xf) {
          bVar2 = FUN_180005124((longlong)param_1,(undefined4 *)&local_c808);
          iVar3 = (int)CONCAT71(extraout_var_04,bVar2);
          uVar7 = 0;
        }
        else if (uVar1 == 0x11) {
          uVar4 = FUN_180005324((longlong)param_1,(longlong)&local_c808);
          iVar3 = (int)uVar4;
          uVar7 = (ulonglong)((int)uVar7 + 1);
        }
        else {
          if (uVar1 != 0x12) {
            FUN_18000437c((longlong)param_1);
            pcVar5 = "0x04, RU.";
            goto LAB_180003cc3;
          }
          bVar2 = FUN_18000550c((longlong)param_1,(undefined4 *)&local_c808,puVar8,param_4);
          iVar3 = (int)CONCAT71(extraout_var_03,bVar2);
          if (0 < (int)uVar7) {
            FUN_180002148("0x01, R %d*%d times.",0x12,uVar7,param_4);
            uVar7 = 0;
          }
        }
        if (iVar3 == 0) {
          return 0;
        }
      } while( true );
    }
    pcVar5 = "0x01, SOM failed";
  }
  else {
    bVar2 = FUN_18000437c((longlong)param_1);
    if ((int)CONCAT71(extraout_var_02,bVar2) != 0) goto LAB_180003d4e;
    pcVar5 = "0x01, SIM failed";
  }
LAB_180003cc3:
  FUN_180002148(pcVar5,puVar6,puVar8,param_4);
  return 0;
}
