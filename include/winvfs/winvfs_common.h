#pragma once

#include <ntifs.h>

typedef enum _WinVfsNodeType
{
    WinVfsFile = 'VFSF'
    ,WinVfsDirectory = 'VFCD'
    ,WinVfsContext = 'VFSC'
    ,WinVfsVolume = 'VFSV'
} WinVfsNodeType;