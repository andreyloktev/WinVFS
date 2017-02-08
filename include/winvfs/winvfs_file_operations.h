#pragma once

#include <ntifs.h>

/***/
typedef NTSTATUS (*WinVfsLookupCallback)();

/***/
typedef NTSTATUS (*WinVfsCreateFileCallback)();

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

