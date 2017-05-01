#pragma once

#include <winvfs/winvfs_common.h>


typedef enum _ComparisonResult
{
    IsEqual
    ,IsGreaterThan
    ,IsLessThan
} ComparisonResult;

/*Functicon to compare two entries. It returnes three possible resulsts
* pE1 and pE2 are equal
* pE1 is greater than pE2
* pE2 is less than pE2
* @param pE1 first entry
* @param pE2 second entry
* @result compare result
*/
typedef ComparisonResult ( *WinVfsCahceCompare )( struct WIN_VFS_CACHE_ENTRY *pE1, struct WIN_VFS_CACHE_ENTRY *pE2 );

//It's a base struact for all entries which will be stored in the cache
typedef struct WIN_VFS_CACHE_ENTRY
{
    //Entry type
    ULONG entryType;

    //Functicon to compaer two entries.
    WinVfsCahceCompare compare;

    //All entries are binded.
    PRTL_SPLAY_LINKS pLinks;

} WinVfsCacheEntry, *PWinVfsCacheEntry;

/**
* Add a new entry in a cache. If entry already exists an old entry is removed.
* @param pRootEntry root node of a cache
* @param pNewEntry entry to insert
*/
void winvfs_cache_insert_entry( PWinVfsCacheEntry pRootEntry, PWinVfsCacheEntry pNewEntry );

/**
* Remove entry from a cache.
* @param pRootEntry root node of a cache
* @param pEntry entry to remove
* @return removed entry. If entry is not in a cache NULL is returned.
*/
PWinVfsCacheEntry winvfs_cache_remove_entry( PWinVfsCacheEntry pRootEntry, PWinVfsCacheEntry pNewEntry );

/**
* Find an entry. EntryType and and entry context must be initialized in the pEntryToFind. All other field must be zero.
* @param pRootEntry root node of a cache
* @param pEntryToFind entry to find
* @return found cache entry. If entry is not in the cache NULL is returned.
*/
PWinVfsCacheEntry winvfs_cache_find_entry( PWinVfsCacheEntry pRootEntry, PWinVfsCacheEntry pEntryToFind );