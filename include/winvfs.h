#pragma once

#include <ntifs.h>

typedef void *PWIN_VFS;

typedef NTSTATUS (*WinVfsCallback)(  );

/**
* WinVFS callbacks which are called by WinVFS library.
*/
typedef struct _WIN_VFS_CALLBACKS
{
    WinVfsCallback WinVfsDispatchLookup;
    WinVfsCallback WinVfsDispatchCreate;
    WinVfsCallback WinVfsDispatchCleanup;
    WinVfsCallback WinVfsDispatchClose;
    WinVfsCallback WinVfsDispatchFileRead;
    WinVfsCallback WinVfsDispatchFileWrite;
    WinVfsCallback WinVfsDispatchReadDirectory;
} WIN_VFS_CALLBACKS, *PWIN_VFS_CALLBACKS;

/**
* Create and initialize WIN_VFS object.
* @in pFileSystemDevObjName device object name representing  the driver itself so that requests can be targeted to the driver. For example "mount" request.
* @in pCallbacks callbacks which are called by WinVFS library
*/
NTSTATUS InitializeWinVFS( _In_ PUNICODE_STRING pFileSystemDevObjName, _In_ PWIN_VFS_CALLBACKS pCallbacks, _Out_ PWIN_VFS *ppWinVFS );

/**
* Routine to initialize DRIVER_OBJECT structrue
*/
NTSTATUS InitializeDriverObject( _In_ PWIN_VFS pWinVFS, _In_ PDRIVER_OBJECT pDrvObj, _In_ PUNICODE_STRING pRegPath );