#pragma once

#include "winvfs_common.h"

//Structure is requered to eork with Cache MAnager and VMM
typedef struct WinVfsNTRequiredFileControlBlock
{
    FSRTL_COMMON_FCB_HEADER commonFCBHeader;
    SECTION_OBJECT_POINTERS sectionObject;
    ERESOURCE               mainResource;
    ERESOURCE               paginIoResource;
} WinVfsNTRequiredFCB, *PWinVfsNTRequiredFCB;

typedef struct WinVfsFileControlBlock
{
    //FCB type
    WinVfsNodeType nodeType;

    //Object for CacheMAnager and VMM
    WinVfsNTRequiredFCB NTRequiredFCB;

    //3d party fs context
    PVOID pWinVfsContext;

    //Pointer to volume control block
    PVOID pWinVfsVCB;

    //State infromation for the FCB
    UINT32 flags;

    //all CCBs for this particular FCB are binded together
    LIST_ENTRY nextCCB;

    //Share access
    SHARE_ACCESS shareAccess;

    //Parent FCB
    struct WinVfsFileControlBlock *pParentFCB;

    //Cache manager lazy write thread's Id
    UINT32 lazyWriteThreadId;

    //Whneever a file stream has a create/open operation performed,
    //the Reference count below is incremented and the OpenHandle count
    //below is also incremented.
    //When IRP_MJ_CLEANUP is received, the OpenHandle count below 
    //is decremented.
    //When IRP_MJ_CLOSE is recieved, the Reference count below
    //is decremented.
    //When the Reference count goes down to zero, the FCB can be de-allocated.
    //Note that a zero Reference count implies a zero OPenHandle count.
    //This must always hold true...
    UINT32 referenceCount;
    UINT32 openHandleCount;

    //Byte-range file lock support
    FILE_LOCK fileLock;
} WinVfsFcb, *PWinVfsFcb;

inline WinVfsNodeType WinVfsFCBType( PWinVfsFcb pFCB )
{
    return pFCB->nodeType;
}

inline bool IsWinVfsNodeFile( PWinVfsFcb pFCB )
{
    return WinVfsFile == pFCB->nodeType;
}

inline bool IsWinVfsNodeContext( PWinVfsFcb pFCB )
{
    return WinVfsContext == pFCB->nodeType;
}

inline bool IsWinVfsNodeVolume( PWinVfsFcb pFCB )
{
    return WinVfsVolume == pFCB->nodeType;
}

inline PVOID WinVfsFsContext( PWinVfsFcb pFCB )
{
    return pFCB->pWinVfsContext;
}

inline void SetWinVfsFSContext( PWinVfsFcb pFCB, PVOID fsContext )
{
    pFCB->pWinVfsContext = fsContext;
}

typedef struct WinVfsContextControlBlock
{
    //Node type
    WinVfsNodeType nodeType;

    //Pointer to the associated FCB
    PWinVfsFcb pFCB;

    //all CCB structures for a FCB are linked together
    LIST_ENTRY nextCCB;

    //each CCB is associated with a file object
    PFILE_OBJECT pFileObj;

    //flags(?)
    UINT32 flags;

    union
    {
        LARGE_INTEGER currentBytesOffset;

        struct
        {
            UINT32 currentIndex;
            UNICODE_STRING searchPatterm;
        } Directory;
    } Spceific;
} WinVfsCCB, *PWinVfsCCB;