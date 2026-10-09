/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined8 FUN_180003a2c(longlong param_1,undefined8 *param_2,uint *param_3,ulonglong param_4)

{
  uint uVar1;
  int iVar2;
  longlong lVar3;
  wchar_t *pwVar4;
  longlong lVar5;
  byte *_Buf2;
  ulonglong uVar6;
  ulonglong uVar7;
  undefined1 (*pauVar8) [16];
  uint local_res8 [2];
  undefined4 local_cc28;
  ushort local_cc24;
  uint local_cc22;
  byte local_c828 [4];
  undefined1 local_c824 [28];
  ushort local_c808;
  undefined1 local_c7e8 [51128];
  undefined8 uStack_30;
  
  uStack_30 = 0x180003a50;
  local_cc28 = local_cc28 & 0xffffff00;
  FUN_18001cca0((undefined1 (*) [16])((longlong)&local_cc28 + 1),0,0x3ff);
  local_c828[0] = 0;
  FUN_18001cca0((undefined1 (*) [16])(local_c828 + 1),0,0xc7ff);
  lVar5 = param_1 + 0xd098;
  pauVar8 = (undefined1 (*) [16])0x40;
  lVar3 = lVar5;
  uVar1 = FUN_180008dcc(lVar5,(longlong)local_c828,0x40);
  uVar6 = (ulonglong)(int)uVar1;
  if ((int)uVar1 < 0x40) {
    pwVar4 = L"0x04, RED not enough, %d.";
LAB_180003ab9:
    FUN_180002394(pwVar4,uVar6 & 0xffffffff,pauVar8,param_4);
  }
  else {
    local_res8[0] = 0;
    pauVar8 = (undefined1 (*) [16])local_c828;
    param_4 = (ulonglong)uVar1;
    _Buf2 = (byte *)0x1;
    iVar2 = FUN_180001880(lVar3,1,pauVar8,uVar1,(undefined8 *)&local_cc28,(int *)local_res8,
                          (undefined8 *)(param_1 + 0xd498));
    if (iVar2 == 0) {
      if (local_res8[0] < 10) {
LAB_180003b23:
        pwVar4 = L"0x04, RPD not enough, %d.";
        goto LAB_180003ab9;
      }
      uVar1 = FUN_180008dcc(lVar5,(longlong)(local_c828 + uVar6),(uint)local_cc24);
      uVar6 = (ulonglong)uVar1;
      if (uVar1 != local_cc24) {
        FUN_180002394(L"0x04, RD not enough, %d, .",(ulonglong)uVar1,(ulonglong)local_cc24,param_4);
        return 0;
      }
      local_res8[0] = 0;
      pauVar8 = (undefined1 (*) [16])local_c7e8;
      param_4 = (ulonglong)uVar1;
      _Buf2 = (byte *)0x1;
      iVar2 = FUN_180001880(lVar5,1,pauVar8,uVar1,(undefined8 *)local_c828,(int *)local_res8,
                            (undefined8 *)(param_1 + 0xd498));
      if (iVar2 != 0) goto LAB_180003b08;
      uVar7 = (ulonglong)(int)local_res8[0];
      if ((int)local_res8[0] < (int)(uint)local_c808) goto LAB_180003b23;
      _Buf2 = local_c828;
      pauVar8 = (undefined1 (*) [16])(ulonglong)local_res8[0];
      uVar1 = FUN_1800010c4(lVar5,_Buf2,local_res8[0]);
      if (local_cc22 == uVar1) {
        _Buf2 = (byte *)(param_1 + 0xcc64);
        pauVar8 = (undefined1 (*) [16])0x1c;
        iVar2 = memcmp(local_c824,_Buf2,0x1c);
        if (iVar2 == 0) {
          *param_3 = local_cc28;
          FUN_18001cfc0(param_2,(undefined8 *)local_c828,uVar7);
          return 1;
        }
        pwVar4 = L"0x04, CM failed.";
      }
      else {
        pwVar4 = L"0x04, CC failed.";
      }
    }
    else {
LAB_180003b08:
      pwVar4 = L"0x04, DPH failed.";
    }
    FUN_180002394(pwVar4,_Buf2,pauVar8,param_4);
  }
  return 0;
}
