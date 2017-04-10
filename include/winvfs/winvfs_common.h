#pragma once

#include <ntifs.h>

typedef enum _WinVfsNodeType
{
    WinVfsFile = 'VFSF'
    ,WinVfsDirectory = 'VFCD'
    ,WinVfsContext = 'VFSC'
    ,WinVfsVolume = 'VFSV'
} WinVfsNodeType;


typedef struct _WinVfsBufer
{
} WinVfsBuffer, *PWinVfsBuffer;