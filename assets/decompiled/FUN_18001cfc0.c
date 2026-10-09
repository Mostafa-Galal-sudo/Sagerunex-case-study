undefined8 * FUN_18001cfc0(undefined8 *param_1,undefined8 *param_2,ulonglong param_3) 
 
{ 
  undefined4 *puVar1; 
  undefined8 *puVar2; 
  undefined8 *puVar3; 
  undefined8 uVar4; 
  undefined8 uVar5; 
  undefined8 uVar6; 
  undefined8 *puVar7; 
  undefined8 *puVar8; 
  undefined4 *puVar9; 
  undefined4 *puVar10; 
  longlong lVar11; 
  ulonglong uVar12; 
  ulonglong uVar13; 
  undefined4 uVar14; 
  undefined4 uVar15; 
  undefined4 uVar16; 
  undefined4 uVar17; 
   
  if (0x10 < param_3) { 
    lVar11 = (longlong)param_2 - (longlong)param_1; 
    if ((param_2 < param_1) && ((longlong)param_1 < (longlong)((longlong)param_2 + param_3))) { 
      if ((DAT_18003fc98 >> 2 & 1) != 0) { 
        if (0x20 < param_3) { 
          uVar12 = (longlong)param_1 + param_3; 
          if ((uVar12 & 0xf) == 0) { 
            puVar9 = (undefined4 *)(uVar12 - 0x10); 
            puVar10 = (undefined4 *)(lVar11 + (longlong)puVar9); 
            uVar14 = *puVar10; 
            uVar15 = puVar10[1]; 
            uVar16 = puVar10[2]; 
            uVar17 = puVar10[3]; 
            uVar12 = param_3 - 0x10; 
          } 
          else { 
            puVar7 = (undefined8 *)(uVar12 - 0x10); 
            uVar4 = ((undefined8 *)(lVar11 + (longlong)puVar7))[1]; 
            puVar9 = (undefined4 *)((ulonglong)puVar7 & 0xfffffffffffffff0); 
            puVar10 = (undefined4 *)(lVar11 + (longlong)puVar9); 
            uVar14 = *puVar10; 
            uVar15 = puVar10[1]; 
            uVar16 = puVar10[2]; 
            uVar17 = puVar10[3]; 
            *puVar7 = *(undefined8 *)(lVar11 + (longlong)puVar7); 
            *(undefined8 *)(uVar12 - 8) = uVar4; 
            uVar12 = (longlong)puVar9 - (longlong)param_1; 
          } 
          uVar13 = uVar12 >> 7; 
          if (uVar13 != 0) { 
            *puVar9 = uVar14; 
            puVar9[1] = uVar15; 
            puVar9[2] = uVar16; 
            puVar9[3] = uVar17; 
            puVar10 = puVar9; 
            while( true ) { 
              puVar7 = (undefined8 *)(lVar11 + -0x10 + (longlong)puVar10); 
              uVar4 = puVar7[1]; 
              puVar8 = (undefined8 *)(lVar11 + -0x20 + (longlong)puVar10); 
              uVar5 = *puVar8; 
              uVar6 = puVar8[1]; 
              puVar9 = puVar10 + -0x20; 
              *(undefined8 *)(puVar10 + -4) = *puVar7; 
              *(undefined8 *)(puVar10 + -2) = uVar4; 
              *(undefined8 *)(puVar10 + -8) = uVar5; 
              *(undefined8 *)(puVar10 + -6) = uVar6; 
              puVar7 = (undefined8 *)(lVar11 + 0x50 + (longlong)puVar9); 
              uVar4 = puVar7[1]; 
              puVar8 = (undefined8 *)(lVar11 + 0x40 + (longlong)puVar9); 
              uVar5 = *puVar8; 
              uVar6 = puVar8[1]; 
              uVar13 = uVar13 - 1; 
              *(undefined8 *)(puVar10 + -0xc) = *puVar7; 
              *(undefined8 *)(puVar10 + -10) = uVar4; 
              *(undefined8 *)(puVar10 + -0x10) = uVar5; 
              *(undefined8 *)(puVar10 + -0xe) = uVar6; 
              puVar7 = (undefined8 *)(lVar11 + 0x30 + (longlong)puVar9); 
              uVar4 = puVar7[1]; 
              puVar8 = (undefined8 *)(lVar11 + 0x20 + (longlong)puVar9); 
              uVar5 = *puVar8; 
              uVar6 = puVar8[1]; 
              *(undefined8 *)(puVar10 + -0x14) = *puVar7; 
              *(undefined8 *)(puVar10 + -0x12) = uVar4; 
              *(undefined8 *)(puVar10 + -0x18) = uVar5; 
              *(undefined8 *)(puVar10 + -0x16) = uVar6; 
              puVar7 = (undefined8 *)(lVar11 + 0x10 + (longlong)puVar9); 
              uVar4 = *puVar7; 
              uVar5 = puVar7[1]; 
              puVar1 = (undefined4 *)(lVar11 + (longlong)puVar9); 
              uVar14 = *puVar1; 
              uVar15 = puVar1[1]; 
              uVar16 = puVar1[2]; 
              uVar17 = puVar1[3]; 
              if (uVar13 == 0) break; 
              *(undefined8 *)(puVar10 + -0x1c) = uVar4; 
              *(undefined8 *)(puVar10 + -0x1a) = uVar5; 
              *puVar9 = uVar14; 
              puVar10[-0x1f] = uVar15; 
              puVar10[-0x1e] = uVar16; 
              puVar10[-0x1d] = uVar17; 
              puVar10 = puVar9; 
            } 
            *(undefined8 *)(puVar10 + -0x1c) = uVar4; 
            *(undefined8 *)(puVar10 + -0x1a) = uVar5; 
            uVar12 = uVar12 & 0x7f; 
          } 
          for (uVar13 = uVar12 >> 4; uVar13 != 0; uVar13 = uVar13 - 1) { 
            *puVar9 = uVar14; 
            puVar9[1] = uVar15; 
            puVar9[2] = uVar16; 
            puVar9[3] = uVar17; 
            puVar9 = puVar9 + -4; 
            puVar10 = (undefined4 *)(lVar11 + (longlong)puVar9); 
            uVar14 = *puVar10; 
            uVar15 = puVar10[1]; 
            uVar16 = puVar10[2]; 
            uVar17 = puVar10[3]; 
          } 
          if ((uVar12 & 0xf) != 0) { 
            uVar4 = param_2[1]; 
            *param_1 = *param_2; 
            param_1[1] = uVar4; 
          } 
          *puVar9 = uVar14; 
          puVar9[1] = uVar15; 
          puVar9[2] = uVar16; 
          puVar9[3] = uVar17; 
          return param_1; 
        } 
LAB_18001d350: 
        uVar4 = param_2[1]; 
        puVar7 = (undefined8 *)((param_3 - 0x10) + (longlong)param_1); 
        uVar5 = *(undefined8 *)(lVar11 + (longlong)puVar7); 
        uVar6 = ((undefined8 *)(lVar11 + (longlong)puVar7))[1]; 
        *param_1 = *param_2; 
        param_1[1] = uVar4; 
        *puVar7 = uVar5; 
        puVar7[1] = uVar6; 
        return param_1; 
      } 
      puVar7 = (undefined8 *)((longlong)param_1 + param_3); 
      if (((ulonglong)puVar7 & 7) != 0) { 
        if (((ulonglong)puVar7 & 1) != 0) { 
          puVar7 = (undefined8 *)((longlong)puVar7 + -1); 
          param_3 = param_3 - 1; 
          *(undefined1 *)puVar7 = *(undefined1 *)(lVar11 + (longlong)puVar7); 
        } 
        if (((ulonglong)puVar7 & 2) != 0) { 
          puVar7 = (undefined8 *)((longlong)puVar7 + -2); 
          param_3 = param_3 - 2; 
          *(undefined2 *)puVar7 = *(undefined2 *)(lVar11 + (longlong)puVar7); 
        } 
        if (((ulonglong)puVar7 & 4) != 0) { 
          puVar7 = (undefined8 *)((longlong)puVar7 + -4); 
          param_3 = param_3 - 4; 
          *(undefined4 *)puVar7 = *(undefined4 *)(lVar11 + (longlong)puVar7); 
        } 
      } 
      uVar12 = param_3 >> 5; 
      puVar8 = puVar7; 
      if (uVar12 != 0) { 
        do { 
          uVar4 = *(undefined8 *)(lVar11 + -0x10 + (longlong)puVar8); 
          puVar7 = puVar8 + -4; 
          puVar8[-1] = *(undefined8 *)(lVar11 + -8 + (longlong)puVar8); 
          puVar8[-2] = uVar4; 
          uVar4 = *(undefined8 *)(lVar11 + (longlong)puVar7); 
          uVar12 = uVar12 - 1; 
          puVar8[-3] = *(undefined8 *)(lVar11 + 8 + (longlong)puVar7); 
          *puVar7 = uVar4; 
          puVar8 = puVar7; 
        } while (uVar12 != 0); 
        param_3 = param_3 & 0x1f; 
      } 
      uVar12 = param_3 >> 3; 
      if (uVar12 != 0) { 
        do { 
          puVar7 = puVar7 + -1; 
          uVar12 = uVar12 - 1; 
          *puVar7 = *(undefined8 *)(lVar11 + (longlong)puVar7); 
        } while (uVar12 != 0); 
        param_3 = param_3 & 7; 
      } 
      if (param_3 == 0) { 
        return param_1; 
      } 
      param_1 = (undefined8 *)((longlong)puVar7 - param_3); 
      param_2 = (undefined8 *)(lVar11 + (longlong)param_1); 
    } 
    else { 
      puVar7 = param_1; 
      if ((DAT_18003fc98 >> 1 & 1) != 0) { 
        for (; param_3 != 0; param_3 = param_3 - 1) { 
          *(undefined1 *)puVar7 = *(undefined1 *)param_2; 
          param_2 = (undefined8 *)((longlong)param_2 + 1); 
          puVar7 = (undefined8 *)((longlong)puVar7 + 1); 
        } 
        return param_1; 
      } 
      if ((DAT_18003fc98 >> 2 & 1) != 0) { 
        if (0x20 < param_3) { 
          if (((ulonglong)param_1 & 0xf) == 0) { 
            puVar10 = (undefined4 *)(lVar11 + (longlong)param_1); 
            uVar14 = *puVar10; 
            uVar15 = puVar10[1]; 
            uVar16 = puVar10[2]; 
            uVar17 = puVar10[3]; 
            puVar7 = param_1 + 2; 
            uVar12 = param_3 - 0x10; 
          } 
          else { 
            uVar4 = ((undefined8 *)(lVar11 + (longlong)param_1))[1]; 
            puVar7 = (undefined8 *)((ulonglong)(param_1 + 4) & 0xfffffffffffffff0); 
            puVar10 = (undefined4 *)(lVar11 + -0x10 + (longlong)puVar7); 
            uVar14 = *puVar10; 
            uVar15 = puVar10[1]; 
            uVar16 = puVar10[2]; 
            uVar17 = puVar10[3]; 
            *param_1 = *(undefined8 *)(lVar11 + (longlong)param_1); 
            param_1[1] = uVar4; 
            uVar12 = param_3 - ((longlong)puVar7 - (longlong)param_1); 
          } 
          uVar13 = uVar12 >> 7; 
          if (uVar13 != 0) { 
            *(undefined4 *)(puVar7 + -2) = uVar14; 
            *(undefined4 *)((longlong)puVar7 + -0xc) = uVar15; 
            *(undefined4 *)(puVar7 + -1) = uVar16; 
            *(undefined4 *)((longlong)puVar7 + -4) = uVar17; 
            puVar8 = puVar7; 
            while( true ) { 
              uVar4 = ((undefined8 *)(lVar11 + (longlong)puVar8))[1]; 
              puVar7 = (undefined8 *)(lVar11 + 0x10 + (longlong)puVar8); 
              uVar5 = *puVar7; 
              uVar6 = puVar7[1]; 
              puVar7 = puVar8 + 0x10; 
              *puVar8 = *(undefined8 *)(lVar11 + (longlong)puVar8); 
              puVar8[1] = uVar4; 
              puVar8[2] = uVar5; 
              puVar8[3] = uVar6; 
              puVar2 = (undefined8 *)(lVar11 + -0x60 + (longlong)puVar7); 
              uVar4 = puVar2[1]; 
              puVar3 = (undefined8 *)(lVar11 + -0x50 + (longlong)puVar7); 
              uVar5 = *puVar3; 
              uVar6 = puVar3[1]; 
              uVar13 = uVar13 - 1; 
              puVar8[4] = *puVar2; 
              puVar8[5] = uVar4; 
              puVar8[6] = uVar5; 
              puVar8[7] = uVar6; 
              puVar2 = (undefined8 *)(lVar11 + -0x40 + (longlong)puVar7); 
              uVar4 = puVar2[1]; 
              puVar3 = (undefined8 *)(lVar11 + -0x30 + (longlong)puVar7); 
              uVar5 = *puVar3; 
              uVar6 = puVar3[1]; 
              puVar8[8] = *puVar2; 
              puVar8[9] = uVar4; 
              puVar8[10] = uVar5; 
              puVar8[0xb] = uVar6; 
              puVar2 = (undefined8 *)(lVar11 + -0x20 + (longlong)puVar7); 
              uVar4 = *puVar2; 
              uVar5 = puVar2[1]; 
              puVar10 = (undefined4 *)(lVar11 + -0x10 + (longlong)puVar7); 
              uVar14 = *puVar10; 
              uVar15 = puVar10[1]; 
              uVar16 = puVar10[2]; 
              uVar17 = puVar10[3]; 
              if (uVar13 == 0) break; 
              puVar8[0xc] = uVar4; 
              puVar8[0xd] = uVar5; 
              *(undefined4 *)(puVar8 + 0xe) = uVar14; 
              *(undefined4 *)((longlong)puVar8 + 0x74) = uVar15; 
              *(undefined4 *)(puVar8 + 0xf) = uVar16; 
              *(undefined4 *)((longlong)puVar8 + 0x7c) = uVar17; 
              puVar8 = puVar7; 
            } 
            puVar8[0xc] = uVar4; 
            puVar8[0xd] = uVar5; 
            uVar12 = uVar12 & 0x7f; 
          } 
          for (uVar13 = uVar12 >> 4; uVar13 != 0; uVar13 = uVar13 - 1) { 
            *(undefined4 *)(puVar7 + -2) = uVar14; 
            *(undefined4 *)((longlong)puVar7 + -0xc) = uVar15; 
            *(undefined4 *)(puVar7 + -1) = uVar16; 
            *(undefined4 *)((longlong)puVar7 + -4) = uVar17; 
            puVar10 = (undefined4 *)(lVar11 + (longlong)puVar7); 
            uVar14 = *puVar10; 
            uVar15 = puVar10[1]; 
            uVar16 = puVar10[2]; 
            uVar17 = puVar10[3]; 
            puVar7 = puVar7 + 2; 
          } 
          uVar12 = uVar12 & 0xf; 
          if (uVar12 != 0) { 
            puVar8 = (undefined8 *)((longlong)puVar7 + lVar11 + -0x10 + uVar12); 
            uVar4 = puVar8[1]; 
            *(undefined8 *)((longlong)puVar7 + (uVar12 - 0x10)) = *puVar8; 
            *(undefined8 *)((longlong)puVar7 + (uVar12 - 8)) = uVar4; 
          } 
          *(undefined4 *)(puVar7 + -2) = uVar14; 
          *(undefined4 *)((longlong)puVar7 + -0xc) = uVar15; 
          *(undefined4 *)(puVar7 + -1) = uVar16; 
          *(undefined4 *)((longlong)puVar7 + -4) = uVar17; 
          return param_1; 
        } 
        goto LAB_18001d350; 
      } 
      if (((ulonglong)param_1 & 7) != 0) { 
        if (((ulonglong)param_1 & 1) != 0) { 
          param_3 = param_3 - 1; 
          *(undefined1 *)param_1 = *(undefined1 *)(lVar11 + (longlong)param_1); 
          puVar7 = (undefined8 *)((longlong)param_1 + 1); 
        } 
        if (((ulonglong)puVar7 & 2) != 0) { 
          param_3 = param_3 - 2; 
          *(undefined2 *)puVar7 = *(undefined2 *)(lVar11 + (longlong)puVar7); 
          puVar7 = (undefined8 *)((longlong)puVar7 + 2); 
        } 
        if (((ulonglong)puVar7 & 4) != 0) { 
          param_3 = param_3 - 4; 
          *(undefined4 *)puVar7 = *(undefined4 *)(lVar11 + (longlong)puVar7); 
          puVar7 = (undefined8 *)((longlong)puVar7 + 4); 
        } 
      } 
      uVar12 = param_3 >> 5; 
      puVar8 = puVar7; 
      if (uVar12 != 0) { 
        do { 
          uVar4 = *(undefined8 *)(lVar11 + 8 + (longlong)puVar8); 
          puVar7 = puVar8 + 4; 
          *puVar8 = *(undefined8 *)(lVar11 + (longlong)puVar8); 
          puVar8[1] = uVar4; 
          uVar4 = *(undefined8 *)(lVar11 + -8 + (longlong)puVar7); 
          uVar12 = uVar12 - 1; 
          puVar8[2] = *(undefined8 *)(lVar11 + -0x10 + (longlong)puVar7); 
          puVar8[3] = uVar4; 
          puVar8 = puVar7; 
        } while (uVar12 != 0); 
        param_3 = param_3 & 0x1f; 
      } 
      uVar12 = param_3 >> 3; 
      if (uVar12 != 0) { 
        do { 
          *puVar7 = *(undefined8 *)(lVar11 + (longlong)puVar7); 
          puVar7 = puVar7 + 1; 
          uVar12 = uVar12 - 1; 
        } while (uVar12 != 0); 
        param_3 = param_3 & 7; 
      } 
      if (param_3 == 0) { 
        return param_1; 
      } 
      param_2 = (undefined8 *)(lVar11 + (longlong)puVar7); 
      param_1 = puVar7; 
    } 
  } 
                    /* WARNING: Could not recover jumptable at 0x00018001d09e. Too many branches */ 
                    /* WARNING: Treating indirect jump as call */ 
  puVar7 = (undefined8 *) 
           (*(code *)((ulonglong)*(uint *)(&DAT_18001d0a0 + param_3 * 4) + 0x180000000)) 
                     (param_1,param_2); 
  return puVar7; 
}
