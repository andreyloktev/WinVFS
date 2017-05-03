#pragma once

#include <winvfs/winvfs_common.h>


typedef enum WIN_VFS_COMPARISON_RESULT
{
    IsEqual
    ,IsGreaterThan
    ,IsLessThan
} WinVfsComparisonResult;

/*Functicon to compare two entries. It returnes three possible resulsts
* pE1 and pE2 are equal
* pE1 is greater than pE2
* pE2 is less than pE2
* @param pE1 first entry
* @param pE2 second entry
* @result compare result
*/
typedef WinVfsComparisonResult ( *WinVfsCahceCompare )( struct WIN_VFS_CACHE_ENTRY *pE1, struct WIN_VFS_CACHE_ENTRY *pE2 );

//It's a base struact for all entries which will be stored in the cache
typedef struct WIN_VFS_CACHE_ENTRY
{
    //Entry type
    ULONG entryType;

    //Functicon to compaer two entries.
    BOOLEAN isEntryInCache;

    //All entries are binded.
    RTL_SPLAY_LINKS links;

} WinVfsCacheEntry, *PWinVfsCacheEntry;

/**
* Add a new entry in a cache If it is not yet. If cache is empty ppRoot will be initialized.
* @param pRootEntry root node of a cache
* @param pNewEntry entry to insert
* @param compare function to comapre two entries
*/
void winvfs_cache_insert_entry( _Inout_ PRTL_SPLAY_LINKS *ppRoot, _In_ PWinVfsCacheEntry pNewEntry, _In_ WinVfsCahceCompare compare );

/**
* Remove entry from a cache. Root link is updated after remove cache entry( Need to mark cache empty )
* @param pEntry entry to remove
* @return removed entry. If entry is not in a cache NULL is returned.
*/
void winvfs_cache_remove_entry( _Inout_ PRTL_SPLAY_LINKS *ppRoot, _In_ PWinVfsCacheEntry pEntry );

/**
* Find an entry. EntryType and and entry context must be initialized in the pEntryToFind. All other field must be zero.
* @param pRootEntry root node of a cache
* @param pEntryToFind entry to find
* @param compare function to comapre two entries
* @return found cache entry. If entry is not in the cache NULL is returned.
*/
PWinVfsCacheEntry winvfs_cache_find_entry( _In_ PRTL_SPLAY_LINKS pRoot, _In_ PWinVfsCacheEntry pEntryToFind, _In_ WinVfsCahceCompare compare );