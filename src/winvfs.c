#include <winvfs.h>
#include "h/winvfs_buffer.h"
#include "h/winvfs_internal.h"
#include "h/winvfs_dispatch.h"
#include "h/winvfs_fastio_dispatch.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, winvfs_init)
#pragma alloc_text(PAGE, winvfs_create_device_object)
#pragma alloc_text(PAGE, winvfs_init_driver_object)
#endif


NTSTATUS winvfs_init( 
                            _In_   PWinVfsFileOperations    pFileOperations
                           ,_In_   PWinVfsVoluneOperations  pVolumeOperations
                           ,_In_   BOOLEAN                  isPageFileSupported
                           ,_Out_  PVOID*                   ppWinVFS
                        )
{
    PWinVfs *ppWinVfsIn = winvfs_cast_to( PWinVfs*, ppWinVFS );

    PAGED_CODE();

    if( 
        NULL == ppWinVfsIn 
        || NULL == pFileOperations 
        || NULL == pVolumeOperations
        )
    {
        return STATUS_INVALID_PARAMETER;
    }

    *ppWinVfsIn = winvfs_malloc( WinVfsNonPagedPool, (SIZE_T)sizeof( WinVfs ) );
    if( NULL == *ppWinVfsIn )
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    (*ppWinVfsIn)->pFileOperations = pFileOperations;
    (*ppWinVfsIn)->pVolumeOperations = pVolumeOperations;
    (*ppWinVfsIn)->isPageFileSupported = isPageFileSupported;

    InitializeListHead( &(*ppWinVfsIn)->devObjectList );

    return STATUS_SUCCESS;
}


NTSTATUS winvfs_create_device_object( 
                                        _In_ PDRIVER_OBJECT     pDrvObj
                                       ,_In_ PUNICODE_STRING    pFileSystemDevObjName
                                       ,_In_ DEVICE_TYPE        devType
                                       ,_In_ PVOID              pWinVFS
                                    )
{
    NTSTATUS status = STATUS_ACCESS_DENIED;
    PWinVfs pWinVfsIn = winvfs_cast_to( PWinVfs, pWinVFS );
    PWinVfsNamedDevice pWinVfsNamedDevice = NULL;

    PAGED_CODE();

    if( NULL == pDrvObj || NULL == pFileSystemDevObjName || NULL == pWinVfsIn )
    {
        return STATUS_INVALID_PARAMETER;
    }

    pWinVfsNamedDevice = winvfs_malloc( WinVfsPagedPool, (ULONG)sizeof(WinVfsNamedDevice) );
    if( NULL == pWinVfsNamedDevice )
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    status = IoCreateDevice( 
                            pDrvObj
                           ,0
                           ,pFileSystemDevObjName
                           ,devType
                           ,0
                           ,FALSE
                           ,&pWinVfsNamedDevice->pDevObj );

    if( FAILED(status) )
    {
        return status;
    }

    InsertTailList( &pWinVfsIn->devObjectList, &pWinVfsNamedDevice->entry );

    return STATUS_SUCCESS;
}


NTSTATUS winvfs_init_driver_object( _In_ PVOID pWinVFS, _In_ PDRIVER_OBJECT pDrvObj, _In_ PUNICODE_STRING pRegPath )
{
    NTSTATUS status = STATUS_ACCESS_DENIED;
    PWinVfs pWinVfsIn = winvfs_cast_to(PWinVfs,pWinVFS); 

    PAGED_CODE();

    if( NULL == pWinVfsIn || NULL == pDrvObj )
    {
        return STATUS_INVALID_PARAMETER;
    }

    //Save driver regestry path
    if( pRegPath )
    {
        pWinVfsIn->regPath.MaximumLength = pRegPath->Length + sizeof(WCHAR);
        pWinVfsIn->regPath.Length = 0;
        pWinVfsIn->regPath.Buffer = winvfs_malloc( WinVfsPagedPool, pRegPath->Length );
        if( NULL == pWinVfsIn->regPath.Buffer )
        {
            return STATUS_INSUFFICIENT_RESOURCES;
        }

        RtlCopyUnicodeString( &pWinVfsIn->regPath, pRegPath );
    }

    pDrvObj->DriverUnload = winvfs_driver_unload;

    pDrvObj->MajorFunction[IRP_MJ_CREATE]               = winvfs_dispatch_create;
    pDrvObj->MajorFunction[IRP_MJ_CLEANUP]              = winvfs_dispatch_cleanup;
    pDrvObj->MajorFunction[IRP_MJ_CLOSE]                = winvfs_dispatch_close;
    pDrvObj->MajorFunction[IRP_MJ_DEVICE_CONTROL]       = winvfs_dispatch_device_control;
    pDrvObj->MajorFunction[IRP_MJ_FILE_SYSTEM_CONTROL]  = winvfs_dispatch_filesystem_control;
    pDrvObj->MajorFunction[IRP_MJ_FLUSH_BUFFERS]        = winvfs_dispatch_flush_buffers;
    pDrvObj->MajorFunction[IRP_MJ_POWER]                = winvfs_dispatch_power;
    pDrvObj->MajorFunction[IRP_MJ_QUERY_INFORMATION]    = winvfs_dispatch_query_info;
    pDrvObj->MajorFunction[IRP_MJ_READ]                 = winvfs_dispatch_read;
    pDrvObj->MajorFunction[IRP_MJ_SET_INFORMATION]      = winvfs_dispatch_set_info;
    pDrvObj->MajorFunction[IRP_MJ_SHUTDOWN]             = winvfs_dispatch_shutdown;
    pDrvObj->MajorFunction[IRP_MJ_WRITE]                = winvfs_dispatch_write;

    pDrvObj->FastIoDispatch = winvfs_init_fastio_table();

    return STATUS_NOT_IMPLEMENTED;
}