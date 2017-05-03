#include <winvfs/winvfs_cache.h>

//Function implementations are based on Microsoft fastfat code( splaysup.c )

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, winvfs_cache_insert_entry)
#pragma alloc_text(PAGE, winvfs_cache_remove_entry)
#pragma alloc_text(PAGE, winvfs_cache_find_entry
#endif

void winvfs_cache_insert_entry( _Inout_ PRTL_SPLAY_LINKS *ppRoot, _In_ PWinVfsCacheEntry pNewEntry, _In_ WinVfsCahceCompare compare )
{
    WinVfsComparisonResult result = IsEqual;
    WinVfsCahceCompare compare = NULL;
    PWinVfsCacheEntry pCahceEntry = NULL;
    PRTL_SPLAY_LINKS node = NULL;

    PAGED_CODE();

    if( NULL == pNewEntry || NULL == ppRoot )
    {
        //Error
        return;
    }

    RtlInitializeSplayLinks( &pNewEntry->links );

    //If cache is empty then pNewEntry will be root
    if( NULL == *ppRoot )
    {
        pNewEntry->isEntryInCache = TRUE;
        *ppRoot = &pNewEntry->links;
        return;
    }

    node = *ppRoot;

    while( TRUE )
    {
        pCahceEntry = CONTAINING_RECORD( node, WinVfsCacheEntry, links );

        result = compare( pCahceEntry, pNewEntry );


        //Entry is already in the cache. Nothing to do.
        if( IsEqual == result )
        {
            return;
        }
        else if( IsGreaterThan == result )
        {
            if( NULL == RtlLeftChild( &pCahceEntry->links ) )
            {
                pNewEntry->isEntryInCache = TRUE;
                RtlInsertAsLeftChild( &pCahceEntry->links, &pNewEntry->links );
                break;
            }
            else
            {
                node = RtlLeftChild( &pCahceEntry->links );
                continue;
            }
        }
        else
        {
            if( NULL == RtlRightChild( &pCahceEntry->links ) )
            {
                pNewEntry->isEntryInCache = TRUE;
                RtlInsertAsRightChild( &pCahceEntry->links, &pNewEntry->links );
                break;
            }
            else
            {
                node = RtlRightChild( &pCahceEntry->links );
                continue;
            }
        }
    }
}

void winvfs_cache_remove_entry( _Inout_ PRTL_SPLAY_LINKS *ppRoot, _In_ PWinVfsCacheEntry pEntry )
{
    PAGED_CODE();

    if( NULL == pEntry || NULL == ppRoot )
    {
        //Error
        return;
    }

    if( pEntry->isEntryInCache )
    {
        *ppRoot = RtlDelete( &pEntry->links );
    }
}

PWinVfsCacheEntry winvfs_cache_find_entry( _In_ PRTL_SPLAY_LINKS pRoot, _In_ PWinVfsCacheEntry pEntryToFind, _In_ WinVfsCahceCompare compare )
{
    PAGED_CODE();

    return NULL;
}