
#include "ncSystemUtility.h"
#include "ncScopedHandle.h"

void main()
{
	BYTE nFileType = 0;
	DWORD dwCrtPid = GetCurrentProcessId();

	// �򿪡�NUL���ļ��Ա������ȡ�ļ��������ֵ��
	ncScopedHandle hTempFile = CreateFile(_T("NUL"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
	if (NULL == hTempFile) {
		return;
	}

	// ��ȡ��ǰϵͳ�����еľ����Ϣ��
	PSYSTEM_HANDLE_INFORMATION pshi = ncSystemUtility::GetSystemHandleInformation();
	if (NULL == pshi) {
		return;
	}

	// ��ȡ��ǰϵͳ���ļ��������ֵ��
	for (DWORD i = 0; i < pshi->NumberOfHandles; ++i) {
		if (pshi->Handles[i].UniqueProcessId == dwCrtPid && hTempFile == (HANDLE)pshi->Handles[i].HandleValue) {
			nFileType = pshi->Handles[i].ObjectTypeIndex;
			break;
		}
	}

	free(pshi);

	return;
}
