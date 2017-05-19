#pragma once

#include "winvfs_common.h"
#include "winvfs_file_control_block.h"

typedef enum WIN_VFS_VCB_CONDITION {
    WinVfsVcbGood = 1,
    WinVfsVcbNotMounted,
    WinVfsVcbBad
} WinVfsVcbCondition;

typedef struct WinVfsVolumeControlBlock
{
    WinVfsNodeType nodeType;
    
    //Common header for cache manager
    FSRTL_ADVANCED_FCB_HEADER volumeFileHeader;
    
    //a resource to protect the fields contained within the WinVfsVCB
    ERESOURCE resource;
    
    //each WinVfsVCB is accessible on a global linked list
    LIST_ENTRY nextWinVfsVCB;
    
    //link to VPB structure created by the NT I/O Manager
    PVPB pVPB;
    
    //flags( see below )
    ULONG flags;

    //WinVfsVcb state
    WinVfsVcbCondition vcbState;
    
    //A count of the number of open files/directories
    //As long as the count is != 0, the volume can not be dismounted or locked
    ULONG numberOfOpennedFiles;

    //  The following is the head of a list of notify Irps.
    LIST_ENTRY dirNotifyListHead;

    //  The following is used to synchronize the dir notify list.
    PNOTIFY_SYNC notifySync;

    //Device object created by a file system driver
    PDEVICE_OBJECT pWinVfsVcbDeviceObject;

    //Target(real) device object
    PDEVICE_OBJECT pTargetDEviceObject;

    //  The volume GUID of the target device object.
    GUID volumeGuid;

    //  The volume GUID path of the target device object.
    UNICODE_STRING volumeGuidPath;

    //Root directory
    PWinVfsFcb pRootDir;

    //WinVfs extension special for data of 3d party drivers
    PVOID pVcbExtension;

    //Is page file supported by fsd implementation
    BOOLEAN isPageFileSupported;

    //For volume opeation, we don't create a WinVfsFCB( we use WinVfsVCB directly instead )
    //So all CCB structure for the volume open opearation are linked directly to the WinVfsVCB
    LIST_ENTRY pWinVfsCCBListHead;

    //All openned files are binded together for VCB
    LIST_ENTRY nextFCB;

    //Pointer to a stream file object created for the volume information
    //to be more easily read form secondary storage
    PFILE_OBJECT pStreamFileObject;

    //Required to use the Cache Manager
    SECTION_OBJECT_POINTERS sectionsObject;

    //File sizes required to use Cache Manager
    LARGE_INTEGER allocationSize;
    LARGE_INTEGER fileSize;
    LARGE_INTEGER validDataLength;
} WinVfsVcb, *PWinVfsVcb;


const UINT32 WINVFS_VCB_FLAG_VOLUME_MOUNTED             = 0x000000001LU;
const UINT32 WINVFS_VCB_FLAG_VOLUME_LOCKED              = 0x000000002LU;
const UINT32 WINVFS_VCB_FLAG_VOLUME_BEING_DISMOUNTED    = 0x000000004LU;
const UINT32 WINVFS_VCB_FLAG_VOLUME_SHUTDOWN            = 0x000000008LU;
const UINT32 WINVFS_VCB_FLAG_VOLUME_READ_ONLY           = 0x000000010LU;
const UINT32 WINVFS_VCB_FLAG_VOLUME_INITIALIZED         = 0x000000020LU;

inline void WinVfsSetVcbExtension( PWinVfsVcb pVcb, PVOID pExt )
{
    pVcb->pVcbExtension = pExt;
}

inline PVOID WinVfsExtension( PWinVfsVcb pVcb )
{
    return pVcb->pVcbExtension;
}


//  The Volume Device Object is an I/O system device object with a workqueue
//  and an VCB record appended to the end.  There are multiple of these
//  records, one for every mounted volume, and are created during
//  a volume mount operation.  The work queue is for handling an overload of
//  work requests to the volume.
typedef struct _WIN_VFS_VOLUME_DEVICE_OBJECT 
{
    DEVICE_OBJECT deviceObject;

    //  The following field tells how many requests for this volume have
    //  either been enqueued to ExWorker threads or are currently being
    //  serviced by ExWorker threads.  If the number goes above
    //  a certain threshold, put the request on the overflow queue to be
    //  executed later.
    ULONG postedRequestCount;

    //  The following field indicates the number of IRP's waiting
    //  to be serviced in the overflow queue.
    ULONG overflowQueueCount;

    //  The following field contains the queue header of the overflow queue.
    //  The Overflow queue is a list of IRP's linked via the IRP's ListEntry
    //  field.
    LIST_ENTRY overflowQueue;

    //  The following spinlock protects access to all the above fields.
    KSPIN_LOCK overflowQueueSpinLock;

    //  This is a common head for the FAT volume file
    FSRTL_COMMON_FCB_HEADER volumeFileHeader;

    //  This is the file system specific volume control block.
    PWinVfsVcb pWinVfsVcb;

} WinVfsDeviceObject, *PWinVfsDeviceObject;