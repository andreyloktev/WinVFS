#include <winvfs.h>
#include "h/winvfs_buffer.h"
#include "h/winvfs_internal.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, winvfs_init)
#pragma alloc_text(PAGE, winvfs_create_device_object)
#pragma alloc_text(PAGE, winvfs_init_driver_object)
#endif


NTSTATUS winvfs_init( 
                            _In_   PWinVfsFileOperations    pFileOperations
                           ,_In_   PWinVfsVoluneOperations  pVolumeOperations
                           ,_Out_  PVOID*                   ppWinVFS
                        )
{
    PAGED_CODE();

    PWinVfs *ppWinVfsIn = winvfs_cast_to( PWinVfs*, ppWinVFS );

    if( 
        NULL == ppWinVfsIn 
        || NULL == pFileOperations 
        || NULL == pVolumeOperations
        )
    {
        return STATUS_INVALID_PARAMETER;
    }

    *ppWinVfsIn = winvfs_malloc( WinVfsPagedPool, (SIZE_T)sizeof( WinVfs ) );
    if( NULL == *ppWinVfsIn )
    {
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    (*ppWinVfsIn)->pFileOperations = pFileOperations;
    (*ppWinVfsIn)->pVolumeOperations = pVolumeOperations;

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
    PAGED_CODE();

    NTSTATUS status = STATUS_ACCESS_DENIED;
    PWinVfs pWinVfsIn = winvfs_cast_to( PWinVfs, pWinVFS );
    PWinVfsNamedDevice pWinVfsNamedDevice = NULL;

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
    PAGED_CODE();

    if( NULL == pWinVFS || NULL == pDrvObj )
    {
        return STATUS_INVALID_PARAMETER;
    }



    return STATUS_NOT_IMPLEMENTED;
}