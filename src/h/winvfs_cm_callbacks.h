#pragma once

//Cache Manager callbacks
//There are only functions here which are implemented in the Microsoft fastfat driver sample.
//Function descriptions are from the Microsoft fastfat driver sample

#include <winvfs.h>

//=============== File operations Cache Manager callbacks ========================/

/**
* The address of this routine is specified when creating a CacheMap for
* a file.  It is subsequently called by the Lazy Writer prior to its
* performing lazy writes to the file.
    
* @param pFcb the Fcb which was specified as a context parameter for this
*             routine.
* @param wait TRUE if the caller is willing to block.

* @return FALSE if Wait was specified as FALSE and blocking would have
                been required.  The Fcb is not acquired.
*         TRUE - if the Fcb has been acquired

*/
_Requires_lock_held_(_Global_critical_region_)    
BOOLEAN winvfs_cm_acquire_fcb_for_lazywrite( _In_ PVOID pFcb, _In_ BOOLEAN wait );

//=================================================================================/

//==================== Cache Manager callbacks for files ==========================/
//=================================================================================/