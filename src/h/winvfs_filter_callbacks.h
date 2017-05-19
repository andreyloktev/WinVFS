#pragma once

//Filter callbacks
//There are only functions here which are implemented in the Microsoft fastfat driver sample.
//Function descriptions are from the Microsoft fastfat driver sample

#include <winvfs.h>

/**
* This is the callback routine for MM to use to acquire the file exclusively.
*
* NOTE:  This routine expects the default FSRTL routine to be used to release
*        the resource.  If this routine is ever changed to acquire something
*        other than main, a corresponding release routine will be required.
*
* @param pCallbackData Filter based callback data that provides the file object we
*                             want to acquire.
* @param ppCompletionContext Ignored.
* @return On success we return STATUS_FSFILTER_OP_COMPLETED_SUCCESSFULLY.
*         If SyncType is SyncTypeCreateSection, we return a status that indicates whether there
*         are any writers to this file.  Note that main is acquired, so new handles cannot be opened.
*/
_Requires_lock_held_(_Global_critical_region_)    
NTSTATUS
winvfs_fltr_callback_acquire_for_carete_section(
    _In_ PFS_FILTER_CALLBACK_DATA pCallbackData,
    _Out_ PVOID *ppCompletionContext
    );