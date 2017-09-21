
#include "ncSystemUtility.h"

PSYSTEM_HANDLE_INFORMATION
ncSystemUtility::GetSystemHandleInformation()
{
	NTQUERYSYSTEMINFORMATION fpNtQuerySystemInformation =
		(NTQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(_T("ntdll")), "NtQuerySystemInformation");
	if (NULL == fpNtQuerySystemInformation) {
		return NULL;
	}

	DWORD dwLength = 0;
	SYSTEM_HANDLE_INFORMATION shi;
	ZeroMemory(&shi, sizeof(SYSTEM_HANDLE_INFORMATION));
	NTSTATUS status = fpNtQuerySystemInformation(SystemHandleInformation, &shi, sizeof(shi), &dwLength);
	if (NT_SUCCESS(status)) {
		return NULL;
	}

	PSYSTEM_HANDLE_INFORMATION pshi = (PSYSTEM_HANDLE_INFORMATION)malloc(dwLength);
	ZeroMemory(pshi, dwLength);
	while (true) {
		status = fpNtQuerySystemInformation(SystemHandleInformation, pshi, dwLength, &dwLength);
		if (STATUS_INFO_LENGTH_MISMATCH != status) {
			break;
		}
		pshi = (PSYSTEM_HANDLE_INFORMATION)realloc(pshi, dwLength);
		ZeroMemory(pshi, dwLength);
	}

	if (!NT_SUCCESS(status)) {
		free(pshi);
		pshi = NULL;
	}

	return pshi;
}
