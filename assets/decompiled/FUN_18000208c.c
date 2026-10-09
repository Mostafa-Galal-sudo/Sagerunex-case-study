void FUN_18000208c(HANDLE param_1)

{
  _FILETIME local_res10 [3];
  _SYSTEMTIME local_18;
  
  local_res10[0].dwLowDateTime = 0;
  local_res10[0].dwHighDateTime = 0;
  local_18.wYear = 0;
  local_18.wMonth = 0;
  local_18.wDayOfWeek = 0;
  local_18.wDay = 0;
  local_18.wHour = 0;
  local_18.wMinute = 0;
  local_18.wSecond = 0;
  local_18.wMilliseconds = 0;
  GetLocalTime(&local_18);
  local_18.wYear = 0x7db;
  SystemTimeToFileTime(&local_18,local_res10);
  SetFileTime(param_1,local_res10,local_res10,local_res10);
  return;
}
