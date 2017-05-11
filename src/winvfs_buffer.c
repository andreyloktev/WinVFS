#include "h/winvfs_buffer.h"

PVOID winvfs_malloc( WinVfsPoolType poolType, SIZE_T bytes )
{
    if( 0 == bytes )
    {
        return NULL;
    }

    return ExAllocatePoolWithTag( 
                                    WinVfsPagedPool == poolType ? PagedPool :
                                    #if _WIN32_WINNT >= _WIN32_WINNT_WIN8
                                    NonPagedPoolNx
                                    #else
                                    NonPagedPool
                                    #endif
                                    ,bytes
                                    ,'SFVW'
                            );
}

void winvfs_free( PVOID p )
{
    ExFreePoolWithTag( p, 'SFVW' );
}