#pragma once

#include <winvfs/winvfs_common.h>

//Pool type
typedef enum
{
    WinVfsPagedPool
    ,WinVfsNonPagedPool
} WinVfsPoolType;

/**
* Alloc memory
* @param poolType dynamic memory pool type
* @param bytes amount bytes to alloc
*/
PVOID winvfs_malloc( WinVfsPoolType poolType, SIZE_T bytes );

/**
* Free dynamic memory
* @param p pointer to allocted memory via winvfs_malloc
*/
void winvfs_free( PVOID p );


/**
* Zero memory
* @param p buffer
* @[aram bytes amount bytes to zero
*/
void winvfs_zero_memory( PVOID p, SIZE_T bytes );
