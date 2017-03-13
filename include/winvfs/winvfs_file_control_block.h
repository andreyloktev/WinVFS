#pragma once

#include <ntifs.h>

typedef enum _WinVfsFileType
{
    WINVFS_FILE,
    WINVFS_DIRECTORY
} WinVfsFileType;

typedef struct WinVfsFileControlBlock
{
    WinVfsFileType nodeType;
    PVOID pFsContext;
} WinVfsFCB, *PWinVfsFCB;