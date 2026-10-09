int FUN_180006d10(wchar_t *param_1)

{
  BOOL BVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  longlong lVar5;
  FILE *_File;
  short *psVar6;
  undefined1 (*pauVar7) [16];
  ulonglong uVar8;
  undefined1 (*pauVar9) [16];
  LPWSTR lpReturnedString;
  wchar_t *pwVar10;
  undefined1 (*pauVar11) [16];
  ulonglong uVar12;
  wchar_t local_a58;
  undefined1 local_a56 [46];
  wchar_t local_a28 [32];
  undefined8 local_9e8;
  undefined2 local_9e0;
  wchar_t local_9d8 [32];
  undefined8 local_998;
  undefined4 local_990;
  wchar_t local_988 [40];
  wchar_t local_938 [32];
  undefined4 local_8f8;
  wchar_t local_8e8;
  undefined1 local_8e6 [110];
  wchar_t local_878;
  undefined1 local_876 [526];
  wchar_t local_668;
  undefined1 local_666 [526];
  WCHAR local_458;
  undefined1 local_456 [526];
  WCHAR local_248;
  undefined1 local_246 [526];
  
  local_a58 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_a56,0,0x26);
  local_458 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_456,0,0x206);
  local_668 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_666,0,0x206);
  local_248 = L'\0';
  FUN_18001cca0((undefined1 (*) [16])local_246,0,0x206);
  BVar1 = SHGetSpecialFolderPathW((HWND)0x0,&local_458,0x1a,1);
  if (BVar1 != 0) {
    wcscat_s(&local_458,0x104,L"\\Mozilla\\Firefox\\");
    wcscpy_s(&local_668,0x104,&local_458);
    wcscat_s(&local_458,0x104,L"profiles.ini");
    FUN_18001d8d8(&local_a58,0x14,L"Profile%d",0);
    lpReturnedString = &local_248;
    GetPrivateProfileStringW(&local_a58,L"Path",(LPCWSTR)0x0,lpReturnedString,0x104,&local_458);
    wcscat_s(&local_668,0x104,&local_248);
    wcscat_s(&local_668,0x104,L"\\prefs.js");
    lVar5 = FUN_18001d570(&local_668);
    iVar2 = (int)lVar5 + -1;
    lVar5 = (longlong)iVar2;
    if (0 < iVar2) {
      do {
        if (*(short *)(local_666 + lVar5 * 2 + -2) == 0x2f) {
          *(undefined2 *)(local_666 + lVar5 * 2 + -2) = 0x5c;
        }
        lVar5 = lVar5 + -1;
      } while (0 < lVar5);
    }
    iVar2 = 0;
    uVar12 = 0;
    local_8e8 = L'\0';
    FUN_18001cca0((undefined1 (*) [16])local_8e6,0,0x62);
    local_878 = L'\0';
    FUN_18001cca0((undefined1 (*) [16])local_876,0,0x206);
    local_8f8 = 0x22;
    builtin_wcsncpy(local_938,L"user_pref(\"network.proxy.http\", ",0x20);
    local_990 = 0x20;
    builtin_wcsncpy(local_988,L"user_pref(\"network.proxy.ssl\", \"",0x21);
    builtin_wcsncpy(local_9d8,L"user_pref(\"network.proxy.http_po",0x20);
    local_9e0 = 0;
    local_998 = 0x2c002200740072;
    builtin_wcsncpy(local_a28,L"user_pref(\"network.proxy.ssl_por",0x20);
    local_9e8 = 0x20002c00220074;
    iVar3 = wcscmp(L"HTTPS",L"HTTP");
    if (iVar3 == 0) {
      pauVar11 = (undefined1 (*) [16])local_938;
      pauVar9 = (undefined1 (*) [16])local_9d8;
    }
    else {
      iVar3 = wcscmp(L"HTTPS",L"HTTPS");
      if (iVar3 != 0) {
        return 0;
      }
      pauVar11 = (undefined1 (*) [16])local_988;
      pauVar9 = (undefined1 (*) [16])local_a28;
    }
    _File = (FILE *)FUN_18001ecc4(&local_668,L"r");
    if (_File != (FILE *)0x0) {
      uVar4 = FUN_18001edb0((longlong)_File);
      while (uVar4 == 0) {
        iVar3 = 0;
        psVar6 = FUN_18001ee00(&local_8e8,0x32,_File);
        if (psVar6 == (short *)0x0) break;
        pauVar7 = FUN_18001e02c((undefined1 (*) [16])&local_8e8,pauVar11);
        if (pauVar7 == (undefined1 (*) [16])0x0) {
          pauVar7 = FUN_18001e02c((undefined1 (*) [16])&local_8e8,pauVar9);
          if (pauVar7 != (undefined1 (*) [16])0x0) {
            lVar5 = FUN_18001d570((short *)pauVar9);
            uVar4 = FUN_18001eec8((wchar_t *)(local_8e6 + lVar5 * 2 + -2));
            uVar12 = (ulonglong)uVar4;
          }
        }
        else {
          lVar5 = FUN_18001d570((short *)pauVar11);
          wcscpy_s(&local_878,0x104,(wchar_t *)(local_8e6 + lVar5 * 2 + -2));
          iVar2 = 1;
          lVar5 = FUN_18001d570(&local_878);
          if (0 < (int)lVar5) {
            pwVar10 = &local_878;
            do {
              if (*pwVar10 == L'\"') {
                *pwVar10 = L'\0';
              }
              iVar3 = iVar3 + 1;
              pwVar10 = pwVar10 + 1;
              lVar5 = FUN_18001d570(&local_878);
            } while (iVar3 < (int)lVar5);
          }
        }
        uVar4 = FUN_18001edb0((longlong)_File);
      }
      fclose(_File);
      if (iVar2 == 0) {
        return 0;
      }
      uVar8 = FUN_18001d570(&local_878);
      if (uVar8 < 0x29) {
        pwVar10 = L"HTTPS";
        FUN_18001d8d8(param_1,0x32,L"%s=%s://%s:%d",L"HTTPS");
        FUN_180002394(L"0x03, P %s:%d",&local_878,uVar12,pwVar10);
        return iVar2;
      }
      FUN_180002394(L"0x04, firefox proxy %s:%d too long",&local_878,uVar12,lpReturnedString);
    }
  }
  return 0;
}
