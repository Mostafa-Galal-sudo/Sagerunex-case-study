void FUN_180002e64(longlong param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *puVar1;
  bool bVar2;
  int iVar3;
  IPAddr DestinationAddress;
  DWORD DVar4;
  longlong lVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  HGLOBAL hMem;
  size_t sVar8;
  HANDLE IcmpHandle;
  undefined8 uVar9;
  undefined8 *puVar10;
  char *pcVar11;
  undefined1 *puVar12;
  char *_Src;
  undefined8 uVar13;
  uint local_res8 [2];
  undefined4 local_res10 [2];
  char local_378 [16];
  undefined1 local_368 [9];
  undefined8 local_35f;
  undefined2 local_357;
  undefined1 local_355;
  ip_option_information local_350;
  undefined1 local_340 [40];
  IPAddr local_318 [20];
  undefined1 local_2c8 [256];
  undefined1 local_1c8 [416];
  
  puVar1 = (undefined8 *)(param_1 + 0x10);
  iVar3 = Ordinal_11(puVar1);
  if ((iVar3 + 1U & 0xfffffffe) != 0) {
    return;
  }
  Ordinal_57(local_2c8,0x100);
  lVar5 = Ordinal_52(local_2c8);
  if ((undefined8 *)**(undefined8 **)(lVar5 + 0x18) == (undefined8 *)0x0) {
    return;
  }
  FUN_18001cfc0((undefined8 *)local_res10,(undefined8 *)**(undefined8 **)(lVar5 + 0x18),
                (longlong)*(short *)(lVar5 + 0x12));
  puVar6 = (undefined8 *)Ordinal_12(local_res10[0]);
  uVar9 = 0x14;
  puVar10 = puVar1;
  FUN_18001cfc0(puVar1,puVar6,0x14);
  uVar7 = FUN_180002de4(puVar10,puVar1);
  if ((int)uVar7 != 0) {
    return;
  }
  local_res8[0] = 0;
  local_378[0] = '\0';
  local_378[1] = '\0';
  local_378[2] = '\0';
  local_378[3] = '\0';
  local_378[4] = '\0';
  local_378[5] = '\0';
  local_378[6] = '\0';
  local_378[7] = '\0';
  local_378[8] = '\0';
  local_378[9] = '\0';
  local_378[10] = '\0';
  local_378[0xb] = '\0';
  local_378[0xc] = '\0';
  local_378[0xd] = '\0';
  local_378[0xe] = '\0';
  local_378[0xf] = '\0';
  hMem = GlobalAlloc(0x40,600);
  local_res8[0] = 600;
  iVar3 = GetNetworkParams(hMem,local_res8);
  if (iVar3 == 0x6f) {
    GlobalFree(hMem);
    hMem = GlobalAlloc(0x40,(ulonglong)local_res8[0]);
  }
  iVar3 = GetNetworkParams(hMem,local_res8);
  if (iVar3 != 0) {
    FUN_180002148("0x02, GetNetworkParams failed:%08x",(ulonglong)(iVar3 != 0),uVar9,param_4);
  }
  else {
    _Src = (char *)((longlong)hMem + 0x118);
    strcpy_s(local_378,0x10,_Src);
    pcVar11 = local_378;
    sVar8 = strlen(pcVar11);
    if ((sVar8 != 0) && (uVar7 = FUN_180002de4(pcVar11,local_378), (int)uVar7 != 0))
    goto LAB_180002fd9;
  }
  _Src = "8.8.8.8";
  strcpy_s(local_378,0x10,"8.8.8.8");
LAB_180002fd9:
  FUN_180002148("0x02, DNS:%s",local_378,_Src,param_4);
  puVar12 = local_1c8;
  iVar3 = Ordinal_115(0x202);
  if (iVar3 == 0) {
    DestinationAddress = Ordinal_11(local_378);
    if (DestinationAddress == 0xffffffff) {
      lVar5 = Ordinal_52(local_378);
      if (lVar5 == 0) {
        FUN_180002148("0x02, Invalid IP or domain name: %s",local_378,_Src,param_4);
        return;
      }
      DestinationAddress = *(IPAddr *)**(undefined8 **)(lVar5 + 0x18);
    }
    IcmpHandle = IcmpCreateFile();
    if (IcmpHandle != (HANDLE)0xffffffffffffffff) {
      FUN_18001cca0(&local_350.Ttl,0,0x10);
      local_350.Ttl = 1;
      FUN_18001cca0((undefined1 (*) [16])local_340,0x30,0x20);
      bVar2 = true;
      iVar3 = 10;
      do {
        if (iVar3 == 0) break;
        uVar7 = 0x20;
        DVar4 = IcmpSendEcho(IcmpHandle,DestinationAddress,local_340,0x20,&local_350,local_318,0x48,
                             3000);
        if (DVar4 != 0) {
          uVar9 = Ordinal_12(local_318[0]);
          FUN_180002148("0x02, %d:%s",(ulonglong)local_350.Ttl,uVar9,uVar7);
          local_368[0] = 0;
          local_368._1_8_ = 0;
          local_35f = 0;
          local_357 = 0;
          local_355 = 0;
          puVar6 = (undefined8 *)Ordinal_12(local_318[0]);
          puVar10 = (undefined8 *)local_368;
          uVar13 = 0x14;
          FUN_18001cfc0(puVar10,puVar6,0x14);
          puVar12 = local_368;
          uVar9 = FUN_180002de4(puVar10,puVar12);
          if ((int)uVar9 == 1) {
            FUN_18001cfc0(puVar1,(undefined8 *)local_368,0x14);
            return;
          }
          if (local_318[0] == DestinationAddress) {
            FUN_180002148("Trace complete.",puVar12,uVar13,uVar7);
            bVar2 = false;
          }
        }
        local_350.Ttl = local_350.Ttl + 1;
        iVar3 = iVar3 + -1;
      } while (bVar2);
      IcmpCloseHandle(IcmpHandle);
      Ordinal_116();
      return;
    }
    pcVar11 = "0x02, Unable to open ICMP file.";
  }
  else {
    pcVar11 = "0x02, WSAStartup failed.";
  }
  FUN_180002148(pcVar11,puVar12,_Src,param_4);
  return;
}
