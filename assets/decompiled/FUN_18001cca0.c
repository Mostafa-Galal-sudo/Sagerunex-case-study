undefined1 (*) [16] FUN_18001cca0(undefined1 (*param_1) [16],byte param_2,ulonglong param_3)

{
  uint uVar1;
  undefined1 (*pauVar2) [16];
  undefined1 (*pauVar3) [16];
  undefined1 uVar4;
  ulonglong uVar7;
  longlong lVar8;
  ulonglong uVar9;
  ulonglong uVar10;
  undefined1 auVar11 [16];
  undefined2 uVar5;
  undefined4 uVar6;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 uVar19;
  
  if (0xf < param_3) {
    pauVar2 = param_1;
    if ((DAT_18003fc98 >> 1 & 1) == 0) {
      uVar7 = (ulonglong)param_2 * 0x101010101010101;
      uVar4 = (undefined1)uVar7;
      if ((DAT_18003fc98 >> 2 & 1) != 0) {
        uVar19 = (undefined1)(uVar7 >> 0x38);
        auVar18._8_6_ = 0;
        auVar18._0_8_ = uVar7;
        auVar18[0xe] = uVar19;
        auVar18[0xf] = uVar19;
        uVar19 = (undefined1)(uVar7 >> 0x30);
        auVar17._14_2_ = auVar18._14_2_;
        auVar17._8_5_ = 0;
        auVar17._0_8_ = uVar7;
        auVar17[0xd] = uVar19;
        auVar16._13_3_ = auVar17._13_3_;
        auVar16._8_4_ = 0;
        auVar16._0_8_ = uVar7;
        auVar16[0xc] = uVar19;
        uVar19 = (undefined1)(uVar7 >> 0x28);
        auVar15._12_4_ = auVar16._12_4_;
        auVar15._8_3_ = 0;
        auVar15._0_8_ = uVar7;
        auVar15[0xb] = uVar19;
        auVar14._11_5_ = auVar15._11_5_;
        auVar14._8_2_ = 0;
        auVar14._0_8_ = uVar7;
        auVar14[10] = uVar19;
        uVar19 = (undefined1)(uVar7 >> 0x20);
        auVar13._10_6_ = auVar14._10_6_;
        auVar13[8] = 0;
        auVar13._0_8_ = uVar7;
        auVar13[9] = uVar19;
        auVar12._9_7_ = auVar13._9_7_;
        auVar12[8] = uVar19;
        auVar12._0_8_ = uVar7;
        uVar19 = (undefined1)(uVar7 >> 0x18);
        auVar11._8_8_ = auVar12._8_8_;
        auVar11[7] = uVar19;
        auVar11[6] = uVar19;
        uVar19 = (undefined1)(uVar7 >> 0x10);
        auVar11[5] = uVar19;
        auVar11[4] = uVar19;
        uVar19 = (undefined1)(uVar7 >> 8);
        auVar11[3] = uVar19;
        auVar11[2] = uVar19;
        auVar11[1] = uVar4;
        auVar11[0] = uVar4;
        if (((ulonglong)param_1 & 0xf) != 0) {
          *param_1 = auVar11;
          pauVar2 = (undefined1 (*) [16])((longlong)param_1 + (0x10 - ((ulonglong)param_1 & 0xf)));
          param_3 = (((ulonglong)param_1 & 0xf) - 0x10) + param_3;
        }
        uVar7 = param_3 >> 7;
        pauVar3 = pauVar2;
        if (uVar7 != 0) {
          do {
            *pauVar2 = auVar11;
            pauVar2[1] = auVar11;
            pauVar3 = pauVar2 + 8;
            pauVar2[2] = auVar11;
            pauVar2[3] = auVar11;
            uVar7 = uVar7 - 1;
            pauVar2[4] = auVar11;
            pauVar2[5] = auVar11;
            pauVar2[6] = auVar11;
            pauVar2[7] = auVar11;
            pauVar2 = pauVar3;
          } while (uVar7 != 0);
          param_3 = param_3 & 0x7f;
        }
        for (uVar7 = param_3 >> 4; uVar7 != 0; uVar7 = uVar7 - 1) {
          *pauVar3 = auVar11;
          pauVar3 = pauVar3 + 1;
        }
        if ((param_3 & 0xf) != 0) {
          *(undefined1 (*) [16])(pauVar3[-1] + (param_3 & 0xf)) = auVar11;
        }
        return param_1;
      }
      if (0x3f < param_3) {
        uVar1 = -(int)param_1 & 7;
        uVar9 = param_3;
        if (uVar1 != 0) {
          uVar9 = param_3 - uVar1;
          *(ulonglong *)*param_1 = uVar7;
        }
        param_3 = uVar9 & 0x3f;
        pauVar2 = (undefined1 (*) [16])(*param_1 + uVar1);
        for (uVar9 = uVar9 >> 6; uVar9 != 0; uVar9 = uVar9 - 1) {
          *(ulonglong *)*pauVar2 = uVar7;
          *(ulonglong *)(*pauVar2 + 8) = uVar7;
          *(ulonglong *)pauVar2[1] = uVar7;
          *(ulonglong *)(pauVar2[1] + 8) = uVar7;
          *(ulonglong *)pauVar2[2] = uVar7;
          *(ulonglong *)(pauVar2[2] + 8) = uVar7;
          *(ulonglong *)pauVar2[3] = uVar7;
          *(ulonglong *)(pauVar2[3] + 8) = uVar7;
          pauVar2 = pauVar2 + 4;
        }
      }
      uVar10 = param_3 & 7;
      for (uVar9 = param_3 >> 3; uVar9 != 0; uVar9 = uVar9 - 1) {
        *(ulonglong *)*pauVar2 = uVar7;
        pauVar2 = (undefined1 (*) [16])(*pauVar2 + 8);
      }
      for (; uVar10 != 0; uVar10 = uVar10 - 1) {
        (*pauVar2)[0] = uVar4;
        pauVar2 = (undefined1 (*) [16])(*pauVar2 + 1);
      }
    }
    else {
      for (; param_3 != 0; param_3 = param_3 - 1) {
        (*pauVar2)[0] = param_2;
        pauVar2 = (undefined1 (*) [16])(*pauVar2 + 1);
      }
    }
    return param_1;
  }
  lVar8 = (ulonglong)param_2 * 0x101010101010101;
  uVar4 = (undefined1)lVar8;
  uVar5 = (undefined2)lVar8;
  uVar6 = (undefined4)lVar8;
  switch(param_3) {
  case 0:
    return param_1;
  case 1:
    goto switchD_18001ce32_caseD_1;
  case 8:
    *(longlong *)(param_1[-1] + param_3 + 8) = lVar8;
    return param_1;
  case 9:
    *(longlong *)(param_1[-1] + param_3 + 7) = lVar8;
    param_1[-1][param_3 + 0xf] = uVar4;
    return param_1;
  case 10:
    *(longlong *)(param_1[-1] + param_3 + 6) = lVar8;
    *(undefined2 *)(param_1[-1] + param_3 + 0xe) = uVar5;
    return param_1;
  case 0xb:
    *(longlong *)(param_1[-1] + param_3 + 5) = lVar8;
    break;
  case 0xc:
    *(longlong *)(param_1[-1] + param_3 + 4) = lVar8;
  case 4:
    *(undefined4 *)(param_1[-1] + param_3 + 0xc) = uVar6;
    return param_1;
  case 0xd:
    *(longlong *)(param_1[-1] + param_3 + 3) = lVar8;
  case 5:
    *(undefined4 *)(param_1[-1] + param_3 + 0xb) = uVar6;
    param_1[-1][param_3 + 0xf] = uVar4;
    return param_1;
  case 0xe:
    *(longlong *)(param_1[-1] + param_3 + 2) = lVar8;
  case 6:
    *(undefined4 *)(param_1[-1] + param_3 + 10) = uVar6;
  case 2:
    *(undefined2 *)(param_1[-1] + param_3 + 0xe) = uVar5;
    return param_1;
  case 0xf:
    *(longlong *)(param_1[-1] + param_3 + 1) = lVar8;
  case 7:
    *(undefined4 *)(param_1[-1] + param_3 + 9) = uVar6;
  }
  *(undefined2 *)(param_1[-1] + param_3 + 0xd) = uVar5;
switchD_18001ce32_caseD_1:
  param_1[-1][param_3 + 0xf] = uVar4;
  return param_1;
}
