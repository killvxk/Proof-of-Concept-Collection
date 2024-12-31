#include "debug.h"

#ifdef MODULE_DEBUG
#include <ShellAPI.h>
#include <Shlobj.h>
#include <Tlhelp32.h>
#include <strsafe.h>

#include "..\common\mem.h"
#include "..\common\string.h"
#include "..\common\utils.h"
#include "..\common\file.h"

DWORD dwCurrentProcessID;
LPSTR pszCurrentProcessName;
LPWSTR pwzDebugLocation;

extern bot_t bot;


void WINAPI InitDebug(void)
{
	//hDebugFile = InitDebugFileHandle(/*L"\\USERPROFILE\\Desktop\\desktop.txt"*/L"\\SystemRoot\\debug.txt");
	dwCurrentProcessID = Utils_GetCurrentProcessId();
	pszCurrentProcessName = Utils_GetCurrentProcessName();
	if((pwzDebugLocation = Utils_GetPath(PATH_APPDATA)) != 0)
		StrConcatW(&pwzDebugLocation, L"debug.txt");
}

void WINAPI WriteDebugData(const LPSTR pszFunction, const LPSTR pszData, const LPSTR pszFile, int iLine)
{
	IO_STATUS_BLOCK io;
	NTSTATUS s;

	char szBuffer[3072];

	memzero(&szBuffer, sizeof(szBuffer));
	CWA(wsprintfA)(szBuffer, "Function=\"%s\" File=\"%s\" Line=\"%d\" PID=\"0x%x\" Name=\"%s\"\r\n Data=\"%s\"\r\n", pszFunction, pszFile, iLine, GetCurrentProcessId(), NULL, pszData);
	OutputDebugStringA(szBuffer);
}
#endif