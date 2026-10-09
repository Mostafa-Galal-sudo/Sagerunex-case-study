undefined1 (*) [16] FUN_1800033dc(undefined4 *param_1,int param_2)

{
  LPWSTR lpWideCharStr;
  bool bVar1;
  int iVar2;
  longlong lVar3;
  undefined1 (*pauVar4) [16];
  undefined1 (*pauVar5) [16];
  undefined8 uVar6;
  undefined7 extraout_var;
  undefined7 extraout_var_00;
  ulonglong uVar7;
  undefined7 extraout_var_01;
  undefined7 extraout_var_02;
  wchar_t *pwVar8;
  wchar_t *pwVar9;
  wchar_t *pwVar10;
  wchar_t *pwVar11;
  rsize_t _MaxCount;
  undefined4 *puVar12;
  LPCSTR lpMultiByteStr;
  undefined1 (*_Src) [16];
  ulonglong _MaxCount_00;
  DWORD local_res10 [2];
  WCHAR local_288;
  undefined1 local_286 [110];
  wchar_t local_218;
  undefined1 local_216 [110];
  wchar_t local_1a8;
  undefined1 local_1a6 [110];
  undefined1 local_138;
  undefined1 local_137 [271];
  
  local_288 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_286,0,0x62);
  local_1a8 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_1a6,0,0x62);
  local_218 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_216,0,0x62);
  uVar6 = 0x32;
  lpMultiByteStr = (LPCSTR)((longlong)param_1 + (longlong)param_2 * 0x32 + 0xc858);
  MultiByteToWideChar(0,0,lpMultiByteStr,0x32,&local_288,0x32);
  FUN_180002394(L"0x01, %s.",&local_288,lpMultiByteStr,uVar6);
  wcscpy_s(&local_1a8,0x32,&local_288);
  wcscpy_s(&local_218,0x32,&local_288);
  local_res10[0] = 0;
  local_138 = 0;
  FUN_18001cca0((undefined1 (*) [16])local_137,0,0x103);
  UrlMkGetSessionOption(0x10000001,&local_138,0x400,local_res10,0);
  _MaxCount_00 = (ulonglong)local_res10[0];
  lpWideCharStr = (LPWSTR)(param_1 + 0x343f);
  _Src = (undefined1 (*) [16])&local_138;
  MultiByteToWideChar(0,0,(LPCSTR)_Src,local_res10[0],lpWideCharStr,0x400);
  lVar3 = FUN_18001d570(lpWideCharStr);
  if (lVar3 == 0) {
    FUN_18001e010((longlong)lpWideCharStr,L"Mozilla/5.0 (compatible; MSIE 7.0; Win32)");
  }
  pauVar4 = FUN_18001e02c((undefined1 (*) [16])&local_288,(undefined1 (*) [16])L"http://");
  if (((pauVar4 == (undefined1 (*) [16])0x0) &&
      (pauVar4 = FUN_18001e02c((undefined1 (*) [16])&local_288,(undefined1 (*) [16])L"https://"),
      pauVar4 == (undefined1 (*) [16])0x0)) &&
     (pauVar4 = FUN_18001e02c((undefined1 (*) [16])&local_288,(undefined1 (*) [16])&DAT_18003558c),
     pauVar4 != (undefined1 (*) [16])0x0)) {
    pauVar5 = FUN_18001e02c((undefined1 (*) [16])&local_288,(undefined1 (*) [16])&DAT_180035590);
    if (pauVar5 != (undefined1 (*) [16])0x0) {
      _MaxCount = (rsize_t)((int)((longlong)pauVar4 - (longlong)&local_288 >> 1) + 1);
      wcsncpy_s(&local_1a8,0x32,&local_288,_MaxCount);
      wcscpy_s(&local_218,0x32,&local_1a8);
      lVar3 = FUN_18001d570(&local_1a8);
      iVar2 = (int)lVar3;
      lVar3 = (longlong)pauVar5 - (longlong)&local_288 >> 1;
      _MaxCount_00 = lVar3 - _MaxCount;
      wcsncpy_s((wchar_t *)(local_1a6 + (longlong)iVar2 * 2 + -2),(longlong)(0x32 - iVar2),
                (wchar_t *)(local_286 + _MaxCount * 2 + -2),_MaxCount_00);
      _Src = (undefined1 (*) [16])(local_286 + lVar3 * 2);
      wcscpy_s((wchar_t *)(local_216 + (longlong)iVar2 * 2 + -2),(longlong)(0x32 - iVar2),
               (wchar_t *)_Src);
    }
  }
  pwVar9 = (wchar_t *)0x32;
  pwVar10 = L"http://";
  pauVar4 = FUN_18001e02c((undefined1 (*) [16])&local_218,(undefined1 (*) [16])L"http://");
  if (pauVar4 == (undefined1 (*) [16])0x0) {
    _Src = (undefined1 (*) [16])&local_218;
    pauVar5 = (undefined1 (*) [16])0x1;
    pwVar10 = &local_218;
    wcscpy_s((wchar_t *)(param_1 + 0x3610),0x32,(wchar_t *)_Src);
    pwVar11 = L"https://";
    pauVar4 = FUN_18001e02c((undefined1 (*) [16])&local_218,(undefined1 (*) [16])L"https://");
    if (pauVar4 != (undefined1 (*) [16])0x0) {
      lVar3 = FUN_18001d570(L"https://");
      pwVar10 = (wchar_t *)(local_216 + lVar3 * 2 + -2);
    }
    param_1[0x3211] = 1;
    FUN_180002394(L"0x01, try httpsviaconfigproxy.",pwVar11,_Src,_MaxCount_00);
    _MaxCount_00 = 1;
    pwVar11 = pwVar10;
    uVar6 = FUN_1800038fc(param_1,pwVar10,_Src,1);
    if ((int)uVar6 == 0) {
      pauVar4 = (undefined1 (*) [16])(param_1 + 0x3426);
      FUN_180006834((longlong)pauVar4);
      param_1[0x3211] = 2;
      FUN_180002394(L"0x01, try httpswpadproxy.",pwVar11,_Src,_MaxCount_00);
      pwVar11 = pwVar10;
      bVar1 = FUN_1800076ec((longlong)pauVar4,pwVar10);
      if ((int)CONCAT71(extraout_var,bVar1) != 0) {
        puVar12 = param_1 + 0x35f7;
        for (pwVar8 = pwVar9; pwVar8 != (wchar_t *)0x0; pwVar8 = (wchar_t *)((longlong)pwVar8 + -1))
        {
          *(undefined2 *)puVar12 = 0;
          puVar12 = (undefined4 *)((longlong)puVar12 + 2);
        }
        uVar6 = FUN_180003c40(param_1,pwVar11,_Src,_MaxCount_00);
        if ((int)uVar6 != 0) goto LAB_1800038d9;
        FUN_180006834((longlong)pauVar4);
      }
      param_1[0x3211] = 3;
      FUN_180002394(L"0x01, try httpsviaiexproxy.",pwVar11,_Src,_MaxCount_00);
      pwVar11 = pwVar10;
      _Src = pauVar5;
      bVar1 = FUN_18000761c((wchar_t *)pauVar4,pwVar10,1);
      if ((int)CONCAT71(extraout_var_00,bVar1) == 0) {
LAB_180003783:
        param_1[0x3211] = 4;
        FUN_180002394(L"0x01, try httpsviafirefoxproxy.",pwVar11,_Src,_MaxCount_00);
        _Src = (undefined1 (*) [16])0x1;
        pwVar11 = pwVar10;
        bVar1 = FUN_180007680((wchar_t *)pauVar4,pwVar10,1);
        if ((int)CONCAT71(extraout_var_01,bVar1) == 0) {
LAB_1800037e7:
          param_1[0x3211] = 5;
          FUN_180002394(L"0x01, try httpsviaautoproxy.",pwVar11,_Src,_MaxCount_00);
          pwVar11 = pwVar10;
          bVar1 = FUN_18000786c(pauVar4,pwVar10);
          if ((int)CONCAT71(extraout_var_02,bVar1) == 0) {
LAB_180003848:
            param_1[0x3211] = 6;
            FUN_180002394(L"0x01, try httpspreconfig.",pwVar11,_Src,_MaxCount_00);
            iVar2 = FUN_1800075d0((longlong)pauVar4,pwVar10);
            if (iVar2 != 0) {
              puVar12 = param_1 + 0x35f7;
              for (; pwVar9 != (wchar_t *)0x0; pwVar9 = (wchar_t *)((longlong)pwVar9 + -1)) {
                *(undefined2 *)puVar12 = 0;
                puVar12 = (undefined4 *)((longlong)puVar12 + 2);
              }
              uVar6 = FUN_180003c40(param_1,pwVar10,_Src,_MaxCount_00);
              if ((int)uVar6 != 0) goto LAB_1800038d9;
              FUN_180006834((longlong)pauVar4);
            }
            param_1[0x3211] = 0;
            goto LAB_18000389d;
          }
          uVar7 = FUN_18001d570((short *)pauVar4);
          if (uVar7 < 0x33) {
            pwVar11 = pwVar9;
            _Src = pauVar4;
            wcscpy_s((wchar_t *)(param_1 + 0x35f7),0x32,(wchar_t *)pauVar4);
            uVar6 = FUN_180003c40(param_1,pwVar11,_Src,_MaxCount_00);
            if ((int)uVar6 == 0) {
              FUN_180006834((longlong)pauVar4);
              goto LAB_180003848;
            }
          }
        }
        else {
          uVar7 = FUN_18001d570((short *)pauVar4);
          if (uVar7 < 0x33) {
            pwVar11 = pwVar9;
            _Src = pauVar4;
            wcscpy_s((wchar_t *)(param_1 + 0x35f7),0x32,(wchar_t *)pauVar4);
            uVar6 = FUN_180003c40(param_1,pwVar11,_Src,_MaxCount_00);
            if ((int)uVar6 == 0) {
              FUN_180006834((longlong)pauVar4);
              goto LAB_1800037e7;
            }
          }
        }
      }
      else {
        uVar7 = FUN_18001d570((short *)pauVar4);
        if (uVar7 < 0x33) {
          pwVar11 = pwVar9;
          _Src = pauVar4;
          wcscpy_s((wchar_t *)(param_1 + 0x35f7),0x32,(wchar_t *)pauVar4);
          uVar6 = FUN_180003c40(param_1,pwVar11,_Src,_MaxCount_00);
          if ((int)uVar6 == 0) {
            FUN_180006834((longlong)pauVar4);
            goto LAB_180003783;
          }
        }
      }
    }
LAB_1800038d9:
    FUN_180002394(L"0x01, %s ok.",
                  *(undefined8 *)(&DAT_180035c90 + (longlong)(int)param_1[0x3211] * 8),_Src,
                  _MaxCount_00);
  }
  else {
LAB_18000389d:
    pauVar5 = (undefined1 (*) [16])0x0;
    FUN_180002394(L"0x01, CN failed.",pwVar10,_Src,_MaxCount_00);
  }
  FUN_180006834((longlong)(param_1 + 0x3426));
  return pauVar5;
}
