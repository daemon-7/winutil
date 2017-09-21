
#include "ncSystemUtility.h"
#include "ncScopedHandle.h"

void main()
{
	BYTE nFileType = 0;
	DWORD dwCrtPid = GetCurrentProcessId();

	// 打开“NUL”文件以便后续获取文件句柄类型值。
	ncScopedHandle hTempFile = CreateFile(_T("NUL"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
	if (NULL == hTempFile) {
		return;
	}

	// 获取当前系统中所有的句柄信息。
	PSYSTEM_HANDLE_INFORMATION pshi = ncSystemUtility::GetSystemHandleInformation();
	if (NULL == pshi) {
		return;
	}

	// 获取当前系统的文件句柄类型值。
	for (DWORD i = 0; i < pshi->NumberOfHandles; ++i) {
		if (pshi->Handles[i].UniqueProcessId == dwCrtPid && hTempFile == (HANDLE)pshi->Handles[i].HandleValue) {
			nFileType = pshi->Handles[i].ObjectTypeIndex;
			break;
		}
	}

	free(pshi);

	return;
}
