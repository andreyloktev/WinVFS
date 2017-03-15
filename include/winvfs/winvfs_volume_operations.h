#pragma once

#include <ntifs.h>
#include "winvfs_block_device.h"
#include "winvfs_volume_control_block.h"

/**Flush all buffers
* @param pVCB volume to flush
* @return STATUS_SUCCESS if operation completes success
*/
typedef NTSTATUS (*WinVfsFlushVolume)( _In_ PWinVfsVcb pVCB );

/** Query volume information
* @param pVCB volume to query information about
* @param viClass query information class
* @param pBuffer buffer
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsQueryVolumeInformation)(
                                                    _In_ PWinVfsVcb             pVCB
                                                   ,_In_ FS_INFORMATION_CLASS   viClass
                                                   ,_Out_ PWinVfsBuffer pBuffer
                                                );

/** Set volume information
* @param pVCB volume to set information about
* @param viClass query information class
* @param pBuffer buffer
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsSetVolumeINformation)(
                                                _In_ PWinVfsVcb             pVCB
                                               ,_In_ FS_INFORMATION_CLASS   viClass
                                               ,_In_ PWinVfsBuffer pBuffer
                                            );

/**FSCTL
* @param pVCB volume
* @param controlCode file system control code
* @param pBuffer buffer
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsFSCTL)(
                                    _In_    PWinVfsVcb     pVCB
                                   ,_In_    ULONG          controlCode
                                   ,_Inout_ PWinVfsBuffer  pBuffer
                            );

/**Mount a volume
* @param pPhysicalVolume physical volume to mount
* @param pVPB volume parameter block
* @param flags mount flags
* @param ppVCB vreated volume control block if mount operation completes success
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsMount)(
                                    _In_    PDEVICE_OBJECT  pPhysicalVolume
                                   ,_In_    PVPB            pVPB
                                   ,_In_    ULONG           flags
                                   ,_Inout_ PWinVfsVcb      *ppVCB
                            );

typedef struct _WIN_VFS_VOLUME_OPERATION
{
    WinVfsFlushVolume               WinVfsFlushVolumeDispatch;
    WinVfsQueryVolumeInformation    WinVfsQueryVolumeInformationDispatch;
    WinVfsSetVolumeINformation      WinVfsSetVolumeInformationDispatch;
    WinVfsFSCTL                     WinVfsFSCTLDispatch;
    WinVfsMount                     WinVfsMountDispatch;
}WIN_VFS_VOLUME_OPERATION,*PWIN_VFS_VOLUME_OPERATION;