/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint FUN_180003e70(longlong param_1,uint param_2,int param_3)

{
  undefined8 *puVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined8 *puVar5;
  wchar_t *pwVar6;
  longlong lVar7;
  char *pcVar8;
  undefined1 (*pauVar9) [16];
  undefined1 (*pauVar10) [16];
  ulonglong uVar11;
  undefined8 uVar12;
  int local_res18 [2];
  int local_res20 [2];
  byte local_c838;
  undefined8 local_c837 [2];
  undefined8 local_c827 [6396];
  undefined8 uStack_40;
  
  uStack_40 = 0x180003e92;
  if (param_3 < 1) {
LAB_1800040ab:
    uVar2 = 1;
  }
  else {
    local_c838 = 0;
    if (0xc800 < param_3) {
      param_3 = 0xc800;
    }
    FUN_18001cca0((undefined1 (*) [16])local_c837,0,0xc7ff);
    pauVar10 = (undefined1 (*) [16])(param_1 + 0x24);
    puVar5 = (undefined8 *)(param_1 + 0x32);
    FUN_18001cfc0(puVar5,(undefined8 *)(param_1 + 0xcc64),0x1c);
    *(short *)(param_1 + 0x4e) = (short)param_3 + -10;
    *(uint *)*pauVar10 = param_2;
    uVar2 = FUN_1800010c4(puVar5,(byte *)(param_1 + 0x2e),param_3 - 10);
    local_res18[0] = 0;
    puVar1 = (undefined8 *)(param_1 + 0xd498);
    *(uint *)(param_1 + 0x2a) = uVar2;
    uVar11 = 10;
    uVar12 = 0;
    pauVar9 = pauVar10;
    iVar3 = FUN_180001880(puVar5,0,pauVar10,10,(undefined8 *)&local_c838,local_res18,puVar1);
    if (iVar3 == 0) {
      local_res20[0] = 0;
      FUN_18001cca0((undefined1 (*) [16])&local_c838,0,0xc800);
      uVar11 = (ulonglong)(param_3 - 10U);
      pauVar9 = (undefined1 (*) [16])(param_1 + 0x2e);
      lVar7 = (longlong)local_c827 + (longlong)local_res18[0];
      uVar12 = 0;
      iVar4 = FUN_180001880(lVar7,0,pauVar9,param_3 - 10U,(undefined8 *)lVar7,local_res20,puVar1);
      iVar3 = local_res20[0];
      if (iVar4 == 0) {
        local_res18[0] = 0;
        uVar11 = 10;
        uVar12 = 0;
        *(short *)(param_1 + 0x28) = (short)local_res20[0];
        iVar4 = FUN_180001880(lVar7,0,pauVar10,10,local_c827,local_res18,puVar1);
        pauVar9 = pauVar10;
        if (iVar4 == 0) {
          uVar2 = FUN_18001df24();
          local_c838 = (char)uVar2 +
                       (((char)((int)uVar2 / 0x7e) + (char)((int)uVar2 >> 0x1f)) -
                       (char)((longlong)(int)uVar2 * 0x82082083 >> 0x3f)) * -0x7e + 0x81;
          puVar5 = (undefined8 *)(param_1 + 0xcc54);
          if (param_2 != 3) {
            puVar5 = (undefined8 *)(param_1 + 0xcc64);
          }
          FUN_18001cfc0(local_c837,puVar5,0x10);
          iVar3 = local_res18[0] + iVar3;
          if (iVar3 < 0x801) {
            uVar11 = (ulonglong)(iVar3 + 0x11U);
            uVar12 = 0;
            uVar2 = FUN_180008984((short *)(param_1 + 0xd098),&local_c838,iVar3 + 0x11U,0);
            if (uVar2 != 1) {
              pcVar8 = "0x01, GS %d failed.";
              goto LAB_180004071;
            }
          }
          else {
            uVar11 = (ulonglong)(iVar3 + 0x11U);
            uVar12 = 1;
            uVar2 = FUN_180008984((short *)(param_1 + 0xd098),&local_c838,iVar3 + 0x11U,1);
            if (uVar2 != 1) {
              pcVar8 = "0x01, PS %d failed.";
LAB_180004071:
              FUN_180002148(pcVar8,(ulonglong)param_2,uVar11,uVar12);
              return uVar2;
            }
          }
          if (param_2 != 0xd) {
            FUN_180002148("0x01, S %d success.",(ulonglong)param_2,uVar11,uVar12);
          }
          goto LAB_1800040ab;
        }
      }
      pwVar6 = L"0x04, EPH failed.";
    }
    else {
      pwVar6 = L"0x04, CEPHL failed.";
    }
    FUN_180002394(pwVar6,uVar12,pauVar9,uVar11);
    uVar2 = 0;
  }
  return uVar2;
}
