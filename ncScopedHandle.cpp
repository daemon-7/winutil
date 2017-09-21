
#include "ncScopedHandle.h"

ncScopedHandle::ncScopedHandle (HANDLE handle)
	: _handle(handle)
{
}

ncScopedHandle::~ncScopedHandle()
{
	if (NULL != _handle && INVALID_HANDLE_VALUE != _handle) {
		CloseHandle(_handle);
	}
}

ncScopedHandle::operator HANDLE () const
{
	return _handle;
}

HANDLE* 
ncScopedHandle::operator& ()
{
	return &_handle;
}

void 
ncScopedHandle::operator= (HANDLE handle)
{
	if (NULL == _handle && INVALID_HANDLE_VALUE != _handle) {
		CloseHandle(_handle);
	}
	_handle = handle;
}
