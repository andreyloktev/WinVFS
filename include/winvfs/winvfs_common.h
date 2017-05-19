#pragma once

#include <ntifs.h>
#include <ntstrsafe.h>

typedef enum _WinVfsNodeType
{
    WinVfsFile = 'VFSF'
    ,WinVfsDirectory = 'VFCD'
    ,WinVfsContext = 'VFSC'
    ,WinVfsVolume = 'VFSV'
} WinVfsNodeType;