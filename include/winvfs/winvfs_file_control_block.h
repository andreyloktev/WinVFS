#pragma once

#include "winvfs_common.h"

typedef struct WinVfsFileControlBlock
{
    //FCB type
    WinVfsNodeType nodeType;
    PVOID pWinVfsContext;
} WinVfsFcb, *PWinVfsFcb;

inline WinVfsNodeType WinVfsFCBType( PWinVfsFcb pFCB )
{
    return pFCB->nodeType;    
}

inline bool IsWinVfsFCBFile( PWinVfsFcb pFCB )
{
    return WinVfsFile == pFCB->nodeType;
}

inline bool IsWinVfsFCBDirectory( PWinVfsFcb pFCB )
{
    return WinVfsDirectory == pFCB->nodeType;
}

inline bool IsWinVfsFCBVolume( PWinVfsFcb pFCB )
{
    return WinVfsVolume == pFCB->nodeType;
}