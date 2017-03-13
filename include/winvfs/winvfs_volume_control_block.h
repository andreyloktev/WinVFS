#pragma once

#include <ntifs.h>

typedef struct WinVfsVolumeControlBlock
{
    PVOID pFsContext;
} WinVfsVCB, *PWinVfsVCB;
