#pragma once

#include <ntifs.h>

typedef enum _WinVfsNodeType
{
    WinVfsFile
    ,WinVfsDirectory
    ,WinVfsVolume
} WinVfsNodeType;


typedef struct _WinVfsBufer
{
} WinVfsBuffer, *PWinVfsBuffer;