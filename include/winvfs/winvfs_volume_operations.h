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
* @param pBuffer buffer. Buffer type depends on FS_INFORMATION_CLASS.
* @param szBuffer buffer size.
* @param pBytes bytes retrived.
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsQueryVolumeInformation)(
                                                    _In_    PWinVfsVcb              pVCB
                                                   ,_In_    FS_INFORMATION_CLASS    fiClass
                                                   ,_Out_   PVOID                   pBuffer
                                                   ,_In_    UINT32                  szBuffer
                                                   ,_Out_   UINT32                  pBytes
                                                );

/** Set volume information
* @param pVCB volume to set information about
* @param viClass query information class
* @param pBuffer buffer. Buffer type depends on FS_INFORMATION_CLASS.
* @param szBuffer buffer size.
* @param pBytes bytes set.
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsSetVolumeInformation)(
                                                _In_    PWinVfsVcb              pVCB
                                               ,_In_    FS_INFORMATION_CLASS    viClass
                                               ,_In_    PVOID                   pBuffer
                                               ,_In_    UINT32                  szBuffer
                                               ,_Out_   UINT32                  pBytes
                                            );

/**FSCTL
* @param pVCB volume
* @param controlCode file system control code
* @param pInBuffer input buffer. Input buffer type depends on control code.
* @param szInBuffer input buffer size.
* @param pOutBuffer output buffer. Out buffer type dependes on control code.
* @param szOutBuffer output buffer size.
* @param pBytes bytes retrieved.
* @return STATUS_SUCCESS if operation comletes successfully 
*/
typedef NTSTATUS (*WinVfsFSCTL)(
                                    _In_    PWinVfsVcb      pVCB
                                   ,_In_    ULONG           controlCode
                                   ,_In_    PVOID           pInBuffer
                                   ,_In_    UINT32          szInBuffer
                                   ,_Out_   PVOID           pOutBuffer
                                   ,_In_    UINT32          szOutBuffer
                                   ,_Out_   UINT32          pBytes
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

typedef struct _WIN_VFS_VOLUME_OPERATIONS
{
    WinVfsFlushVolume               WinVfsFlushVolumeDispatch;
    WinVfsQueryVolumeInformation    WinVfsQueryVolumeInformationDispatch;
    WinVfsSetVolumeInformation      WinVfsSetVolumeInformationDispatch;
    WinVfsFSCTL                     WinVfsFSCTLDispatch;
    WinVfsMount                     WinVfsMountDispatch;
}WinVfsVoluneOperations,*PWinVfsVoluneOperations;