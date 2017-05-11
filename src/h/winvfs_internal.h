#pragma once

#include <winvfs.h>

#define winvfs_cast_to( TYPE, POINTER ) (TYPE)(POINTER)

#ifndef FAILED
#define FAILED(st) ( STATUS_SUCCESS != (st) )
#endif

#ifndef SUCCESS
#define SUCCESS(st) ( STATUS_SUCCESS == (st) )
#endif

/**
* The main structure of WinVfs library.
* It contains set of file and volume operations callbacks. If someone callback is NULL then default operations will be call( return STATUS_NOT_IMPLEMENTED )
*/
typedef struct WIN_VFS
{
    PWinVfsFileOperations   pFileOperations;
    PWinVfsVoluneOperations pVolumeOperations;

    //Named device obejcts is bind together. Named device obejects is neccesasry for specific ioctls.
    LIST_ENTRY              devObjectList;
    UNICODE_STRING          regPath;
} WinVfs, *PWinVfs;

typedef struct WIN_VFS_NAMED_DEVICE
{
    PDEVICE_OBJECT pDevObj;
    LIST_ENTRY entry;
} WinVfsNamedDevice, *PWinVfsNamedDevice;