#pragma once

#include "winvfs/winvfs_common.h"
#include "winvfs/winvfs_file_operations.h"
#include "winvfs/winvfs_volume_operations.h"

/**
* Create and initialize WIN_VFS object.
* @param pCallbacks callbacks which are called by WinVFS library
*/
NTSTATUS winvfs_init( 
                        _In_   PWinVfsFileOperations    pFileOperationss
                        ,_In_   PWinVfsVoluneOperations  pVolumeOperations
                        ,_Out_  PVOID*                   ppWinVFS
                    );

/**
* Creaete a device object representing  the driver itself so that requests can be targeted to the driver.
* @in pFileSystemDevObjName device object name.
* @in pWinVFS WinVFS object
* @out status code
*/
NTSTATUS winvfs_create_device_object( 
                                        _In_ PDRIVER_OBJECT     pDrvObj
                                       ,_In_ PUNICODE_STRING    pFileSystemDevObjName
                                       ,_In_ DEVICE_TYPE        devType
                                       ,_In_ PVOID              pWinVFS
                                    );

/**
* Routine to initialize DRIVER_OBJECT structrue
*/
NTSTATUS winvfs_init_driver_object( _In_ PVOID pWinVFS, _In_ PDRIVER_OBJECT pDrvObj, _In_ PUNICODE_STRING pRegPath );