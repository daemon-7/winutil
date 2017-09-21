
#pragma once

#include <Windows.h>

class ncScopedHandle
{
	ncScopedHandle (const ncScopedHandle&);
	void operator= (const ncScopedHandle&);

public:
	ncScopedHandle (HANDLE handle);
	~ncScopedHandle ();

	operator HANDLE () const;
	PHANDLE operator& ();
	void operator= (HANDLE handle);

private:
	HANDLE _handle;
};
