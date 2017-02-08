#pragma once

#include <ntifs.h>
#include "winvfs/winvfs_file_operations.h"
#include "winvfs/winvfs_volume_operations.h"

typedef void *PWIN_VFS;




//========= WinVFS volume operation callbacks which are called by WinVFS library. ====================


typedef struct _WIN_VFS_VOLUME_OPERATIONS
{
} WIN_VFS_VOLUME_OPERATIONS, *PWIN_VFS_VOLUME_OPERATIONS;

//====================================================================================================

/**
* Create and initialize WIN_VFS object.
* @in pCallbacks callbacks which are called by WinVFS library
*/
NTSTATUS InitializeWinVFS( 
                            _In_   PWIN_VFS_FILE_OPERATIONS    pFileOperationss
                            ,_In_   PWIN_VFS_VOLUME_OPERATIONS  pVolumeOperations
                            ,_Out_  PWIN_VFS*                   ppWinVFS
                        );

/**
* Creaete a device object representing  the driver itself so that requests can be targeted to the driver. For example "mount" request.
* @in pFileSystemDevObjName device object name.
* @in pWinVFS WinVFS object
* @out status code
*/
NTSTATUS CreateWinVFSDeviceObject( _In_ PUNICODE_STRING pFileSystemDevObjName, _In_ PWIN_VFS pWinVFS );

/**
* Routine to initialize DRIVER_OBJECT structrue
*/
NTSTATUS InitializeDriverObject( _In_ PWIN_VFS pWinVFS, _In_ PDRIVER_OBJECT pDrvObj, _In_ PUNICODE_STRING pRegPath );