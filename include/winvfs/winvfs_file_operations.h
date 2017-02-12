#pragma once

#include <ntifs.h>
#include "winvfs_file_control_block.h"


/**Find a file or directory by its name
* @param pParentDir a parent directory object
* @param pFileName a file name to locate
* @param pDesiredAccess a desired access to an existing file
* @param fileAttr a desired file attributes
* @param pFile return a new FCB if file exists. Otherwise nullptr is returned 
* @return STATUS_SUCCESS if file exists. Otherwise a return code.
*/
typedef NTSTATUS (*WinVfsLookupCallback)( 
                                            _In_ PWinvfsFCB pParentDir
                                           ,_In_ PUNICODE_STRING pFileName
                                           ,_In_ PACCESS_MASK pDesiredAccess
                                           ,_In_ ULONG fileAttr
                                           ,_Out_ PWinvfsFCB *pFile
                                        );

/**Create a new file or directory
* @param pParentDir a parent directory object where a new file must be located
* @param pNewFileName a file name for a new file
* @param fileType what to create
* @param fileAttr file attributes for a new file
* @param pNewFile if file is created then a new FCB is returned. Otherwise nullptr is returned.
* @return STATUS_SUCCESS if a file is created. Otherwise a return code.
*/
typedef NTSTATUS (*WinVfsCreateFileCallback)(
                                                _In_ PWinvfsFCB pParentDir
                                               ,_In_ PUNICODE_STRING pNewFileName
                                               ,_In_ WinVfsFileType fileType
                                               ,_In_ ULONG fileAttr
                                               ,_Out_ PWinvfsFCB *pNewFile
                                            );

/***/
typedef NTSTATUS (*WinVfsCleanupCallback)();

/***/
typedef NTSTATUS (*WinVfsCloseFileCallback)();

/***/
typedef NTSTATUS (*WinVfsReadFileCallback)();

/***/
typedef NTSTATUS (*WinVfsWriteFileCallback)();

/***/
typedef NTSTATUS (*WinVfsFlushFileBuffers)();

/***/
typedef NTSTATUS (*WinVfsGetFileInformationCallback)();

/***/
typedef NTSTATUS (*WinVfsReadDirectoryCallback)();

/***/
typedef NTSTATUS (*WinVfsCreateHardLinkCallback)();

/***/
typedef NTSTATUS (*WinVfsRenameFileCallback)();

/***/
typedef NTSTATUS (*WinVfsDeleteFileCallback)();

/***/
typedef NTSTATUS (*WinVfsSetFileSizeCallback)();

/***/
typedef NTSTATUS (*WinVfsGetFileEACallback)();

/***/
typedef NTSTATUS (*WinVfsSetFileEACallback)();

/***/
typedef NTSTATUS (*WinVfsGetFileSecurityCallback)();

/***/
typedef NTSTATUS (*WinVfsSetFileSecurityCallback)();


typedef struct _WIN_VFS_FILE_OPERATIONS
{
    WinVfsLookupCallback                WinVfsFileDispatchLookup;
    WinVfsCreateFileCallback            WinVfsFileDispatchCreate;
    WinVfsCleanupCallback               WinVfsFileDispatchCleanup;
    WinVfsCloseFileCallback             WinVfsFileDispatchClose;
    WinVfsReadFileCallback              WinVfsFileDispatchRead;
    WinVfsWriteFileCallback             WinVfsFileDispatchWrite;
    WinVfsFlushFileBuffers              WinVfsFileDispatchFlush;
    WinVfsGetFileInformationCallback    WinVfsFileDispatchGetInformation;
    WinVfsCreateHardLinkCallback        WinVfsFileDispatchCreateHardlink;
    WinVfsReadDirectoryCallback         WinVfsFileDispatchReadDirectory;
    WinVfsRenameFileCallback            WinVfsFileDispatchRename;
    WinVfsDeleteFileCallback            WinVfsFileDispatchDelete;
    WinVfsSetFileSizeCallback           WinVfsFileDispatchSetSize;
    WinVfsGetFileEACallback             WinVfsFileDispatchGetExtendedAttrs;
    WinVfsSetFileEACallback             WinVfsFileDispatchSetExtendedAttrs;
    WinVfsGetFileSecurityCallback       WinVfsFileDispatchGetSecurity;
    WinVfsSetFileSecurityCallback       WinVfsFileDispatchSetSecurity;
} WIN_VFS_FILE_OPERATIONS, *PWIN_VFS_FILE_OPERATIONS;

