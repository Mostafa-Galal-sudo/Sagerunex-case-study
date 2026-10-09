undefined8 FUN_180002884(undefined4 *param_1,longlong param_2,HANDLE param_3,undefined8 param_4)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 *puVar5;
  uint uVar6;
  int iVar7;
  DWORD DVar8;
  uint uVar9;
  undefined8 *puVar10;
  __time64_t _Var11;
  size_t sVar12;
  undefined8 *puVar13;
  longlong lVar14;
  ulonglong uVar15;
  int iVar16;
  undefined8 *puVar17;
  int iVar18;
  undefined8 uVar19;
  ulonglong uVar20;
  int iVar21;
  int iVar22;
  __time64_t local_res10;
  _SYSTEMTIME local_688;
  undefined8 local_678 [200];
  
  FUN_18001cca0((undefined1 (*) [16])(param_1 + 4),0,0x14);
  FUN_18001cca0((undefined1 (*) [16])(param_1 + 0x3209),0,0x1c);
  FUN_18001cca0((undefined1 (*) [16])(param_1 + 0x3212),0,0x640);
  puVar13 = (undefined8 *)(param_1 + 0x352e);
  uVar19 = 0x100;
  FUN_18001cfc0(puVar13,(undefined8 *)(param_2 + 0x28),0x100);
  FUN_1800040cc(puVar13,*(uint *)(param_2 + 0x574));
  lVar14 = 0xc;
  puVar13 = local_678;
  puVar5 = (undefined8 *)(param_2 + 0x148);
  do {
    puVar17 = puVar5;
    puVar10 = puVar13;
    uVar1 = puVar17[1];
    uVar2 = puVar17[2];
    uVar3 = puVar17[3];
    *puVar10 = *puVar17;
    puVar10[1] = uVar1;
    uVar1 = puVar17[4];
    uVar4 = puVar17[5];
    puVar10[2] = uVar2;
    puVar10[3] = uVar3;
    uVar2 = puVar17[6];
    uVar3 = puVar17[7];
    puVar10[4] = uVar1;
    puVar10[5] = uVar4;
    uVar1 = puVar17[8];
    uVar4 = puVar17[9];
    puVar10[6] = uVar2;
    puVar10[7] = uVar3;
    uVar2 = puVar17[10];
    uVar3 = puVar17[0xb];
    puVar10[8] = uVar1;
    puVar10[9] = uVar4;
    uVar1 = puVar17[0xc];
    uVar4 = puVar17[0xd];
    puVar10[10] = uVar2;
    puVar10[0xb] = uVar3;
    uVar2 = puVar17[0xe];
    uVar3 = puVar17[0xf];
    puVar10[0xc] = uVar1;
    puVar10[0xd] = uVar4;
    puVar10[0xe] = uVar2;
    puVar10[0xf] = uVar3;
    lVar14 = lVar14 + -1;
    puVar13 = puVar10 + 0x10;
    puVar5 = puVar17 + 0x10;
  } while (lVar14 != 0);
  uVar1 = puVar17[0x11];
  uVar2 = puVar17[0x12];
  uVar3 = puVar17[0x13];
  puVar10[0x10] = puVar17[0x10];
  puVar10[0x11] = uVar1;
  uVar1 = puVar17[0x14];
  uVar4 = puVar17[0x15];
  puVar10[0x12] = uVar2;
  puVar10[0x13] = uVar3;
  uVar2 = puVar17[0x16];
  uVar3 = puVar17[0x17];
  puVar10[0x14] = uVar1;
  puVar10[0x15] = uVar4;
  puVar10[0x16] = uVar2;
  puVar10[0x17] = uVar3;
  FUN_1800027c0((longlong)param_1,local_678,uVar19,param_4);
  uVar20 = 0x1c;
  *param_1 = param_1[0x3310];
  FUN_18001cfc0((undefined8 *)(param_1 + 0x3209),(undefined8 *)(param_1 + 0x3319),0x1c);
  FUN_180002148("0x00, %d",(ulonglong)(uint)param_1[0x320d],uVar20,param_4);
  iVar21 = 10;
  iVar22 = 0;
  do {
    if (param_1[0x3313] != 0) {
      local_688.wYear = 0;
      local_688.wMonth = 0;
      local_688.wDayOfWeek = 0;
      local_688.wDay = 0;
      local_688.wHour = 0;
      local_688.wMinute = 0;
      local_688.wSecond = 0;
      local_688.wMilliseconds = 0;
      GetLocalTime(&local_688);
      uVar20 = (ulonglong)(uint)param_1[0x3314];
      FUN_180002148("0x00, %02d-%02d.",(ulonglong)(uint)param_1[0x3313],uVar20,param_4);
      if ((int)param_1[0x3313] < (int)param_1[0x3314]) {
        while (((int)param_1[0x3314] <= (int)(uint)local_688.wHour ||
               ((int)(uint)local_688.wHour < (int)param_1[0x3313]))) {
          GetLocalTime(&local_688);
          WaitForSingleObject(param_3,300000);
        }
      }
      else {
        uVar6 = (uint)local_688.wHour;
        if ((int)param_1[0x3314] <= (int)(uint)local_688.wHour) {
          do {
            if ((int)param_1[0x3313] <= (int)uVar6) break;
            GetLocalTime(&local_688);
            WaitForSingleObject(param_3,300000);
            uVar6 = (uint)local_688.wHour;
          } while ((int)param_1[0x3314] <= (int)uVar6);
        }
      }
    }
    _Var11 = _time64(&local_res10);
    FUN_18001df50((ulong)_Var11);
    uVar6 = FUN_18001df24();
    *(undefined8 *)(param_1 + 0x3210) = 1;
    iVar16 = (int)uVar6 % 5;
    iVar18 = iVar16 + 5;
    iVar7 = iVar16 - iVar18;
    while (SBORROW4(iVar16,iVar18) != iVar7 < 0) {
      uVar6 = iVar16 % 5;
      sVar12 = strlen((char *)((longlong)param_1 + (longlong)(int)uVar6 * 0x32 + 0xc858));
      if ((sVar12 != 0) &&
         (sVar12 = strlen((char *)((longlong)param_1 + (longlong)(int)uVar6 * 0x32 + 0xc858)),
         sVar12 < 0x32)) {
        DAT_1800414ec = 1;
        DAT_1800414e8 = 0;
        FUN_180002148("0x00, %d.",(ulonglong)uVar6,uVar20,param_4);
        uVar15 = (ulonglong)uVar6;
        iVar7 = FUN_18000339c(param_1,uVar6);
        if (iVar7 != 0) {
          DVar8 = GetTickCount();
          FUN_18001df50(DVar8);
          iVar18 = param_1[0x3311] * 0x3c;
          uVar6 = FUN_18001df24();
          uVar9 = FUN_18001df24();
          uVar6 = iVar18 + (int)(uVar6 * uVar9) %
                           ((int)(((longlong)iVar18 / 3 + ((longlong)iVar18 >> 0x3f) & 0xffffffffU)
                                 >> 0x1f) + iVar18 / 3 + (iVar18 >> 0x1f));
          FUN_180002148("0x06, DT %d.",(ulonglong)uVar6,uVar20,param_4);
          WaitForSingleObject(param_3,uVar6 * 1000);
          uVar6 = (int)uVar6 % 0x3c;
          goto LAB_180002c10;
        }
        FUN_180002148("0x00, LG failed.",uVar15,uVar20,param_4);
      }
      iVar16 = iVar16 + 1;
      iVar7 = iVar16 - iVar18;
    }
    iVar21 = iVar21 + -1;
    uVar6 = 0x1e;
    if (0 < iVar21) {
      uVar6 = 5;
    }
    if (iVar21 == 0) {
      iVar21 = 10;
    }
    FUN_180002148("0x00, OL failed, s %d.",(ulonglong)uVar6,uVar20,param_4);
    WaitForSingleObject(param_3,uVar6 * 60000);
LAB_180002c10:
    iVar22 = iVar22 + uVar6;
    if (0x2cf < iVar22) {
      return 1;
    }
  } while( true );
}
