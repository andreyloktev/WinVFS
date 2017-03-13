#pragma once

#include <ntifs.h>
#include "winvfs_file_control_block.h"
#include "winvfs_block_device.h"


/**Find a file or directory by its name
* @param pParentDir a parent directory object
* @param pFileName a file name to locate
* @param pDesiredAccess a desired access to an existing file
* @param fileAttr a desired file attributes
* @param pSecurityCtxt security context 
* @param pFile return a new FCB if file exists. Otherwise nullptr is returned 
* @return STATUS_SUCCESS if file exists. Otherwise a return code.
*/
typedef NTSTATUS (*WinVfsLookupCallback)( 
                                            _In_ PWinVfsFCB             pParentDir
                                           ,_In_ PUNICODE_STRING        pFileName
                                           ,_In_ PACCESS_MASK           pDesiredAccess
                                           ,_In_ ULONG                  fileAttr
                                           ,_In_ PIO_SECURITY_CONTEXT   pSecurityCtxt
                                           ,_Out_ PWinVfsFCB*           ppFile
                                        );

/**Create a new file or directory
* @param pParentDir a parent directory object where a new file must be located
* @param pNewFileName a file name for a new file
* @param fileType what to create
* @param fileAttr file attributes for a new file
* @param pSecurityCtxt security context 
* @param pNewFile if file is created then a new FCB is returned. Otherwise nullptr is returned.
* @return STATUS_SUCCESS if a file is created. Otherwise a return code.
*/
typedef NTSTATUS (*WinVfsCreateFileCallback)(
                                                _In_ PWinVfsFCB             pParentDir
                                               ,_In_ PUNICODE_STRING        pNewFileName
                                               ,_In_ WinVfsFileType         fileType
                                               ,_In_ ULONG                  fileAttr
                                               ,_In_ PIO_SECURITY_CONTEXT   pSecurityCtxt
                                               ,_Out_ PWinVfsFCB*           ppNewFile
                                            );

/**Close a file object. It's called before deallocate WinvfsFCB object
* @param pFile file object to close
*/
typedef NTSTATUS (*WinVfsCloseFileCallback)( _In_ PWinVfsFCB pFile );

/** Read a file
* @param pFile          a file object to read from
* @param offset         file offset to begin reading from
* @param bytesToRead    bytes to read
* @param pBuffer        pointer to buffer structure
*/
typedef NTSTATUS (*WinVfsReadFileCallback)(
                                            _In_ PWinVfsFCB pFile
                                           ,_In_ LARGE_INTEGER offset
                                           ,_In_ DWORD32 bytesToRaad
                                           ,_In_ PWinVfsBuffer pBuffer
                                        );

/**Write a file
* @param pFile          a file object to write to
* @param offset         file offset to begin writting to
* @param bytesToRead    bytes to write
* @param pBuffer        pointer to buffer structure
*/
typedef NTSTATUS (*WinVfsWriteFileCallback)(
                                            _In_ PWinVfsFCB pFile
                                           ,_In_ LARGE_INTEGER offset
                                           ,_In_ DWORD32 bytesToWrite
                                           ,_In_ PWinVfsBuffer pBuffer
                                        );

/**Flush file buffers
* @param pFileObj file object to flush
*/
typedef NTSTATUS (*WinVfsFlushFileBuffers)( _In_ PWinVfsFCB pFileObj );

/**Gey information about a file
* @param pFileObj a file to get information about
* @param fiClass a value that specifies which structure to use to query or set information for a file object.
* @param pBuffer buffer
* @param pBytes bytes retrieved
* @return STATUS_SUCCESS if information can be retrieved.
*/
typedef NTSTATUS (*WinVfsGetFileInformationCallback)(
                                                        _In_    PWinVfsFCB pFileObj
                                                       ,_In_    FILE_INFORMATION_CLASS fiClass
                                                       ,_Inout_ PWinVfsBuffer pBuffer
                                                       ,_Out_   PULONG pBytes
                                                    );

/**Gey information about a file
* @param pFileObj a file to set information to
* @param fiClass a value that specifies which structure to use to query or set information for a file object.
* @param pBuffer buffer
* @param pBytes bytes retrieved
* @return STATUS_SUCCESS if information can be retrieved.
*/
typedef NTSTATUS (*WinVfsSetFileInformationCallback)(
                                                        _In_    PWinVfsFCB pFileObj
                                                       ,_In_    FILE_INFORMATION_CLASS fiClass
                                                       ,_Inout_ PWinVfsBuffer pBuffer
                                                       ,_Out_   PULONG pBytes
                                                    );

/**Enumerate a directory
* @param pFileObj a directory to enumerate
* @param searchPattern a search pattern
* @param fiClass what does information need?
* @param fileOffset file entry offset(index) in a directory
* @param pBuffer buffer. It's cast to a structure depending on the fiClass parameter
* @return STATUS_SUCCESS if there is no more space in the buffer but file entries exist yet
          STATUS_NO_MORE_FILES if there are not more files in a directory
          STATUS_NO_SUCH_FILE if there is not a file satisfying to search patter
*/
typedef NTSTATUS (*WinVfsReadDirectoryCallback)(
                                                    _In_    PWinVfsFCB              pFileObj
                                                   ,_In_    UNICODE_STRING          searchPattern
                                                   ,_In_    FILE_INFORMATION_CLASS  fiClass
                                                   ,_Inout_ ULONG                   fileOffset
                                                   ,_Out_   PWinVfsBuffer           pBuffer
                                            );


/**Delete a file
* @param pFileObj file to delete
* @return if success return STATUS_SUCCESS
*/
typedef NTSTATUS (*WinVfsDeleteFileCallback)( _In_  PWinVfsFCB pFileObj );


typedef struct _WIN_VFS_FILE_OPERATIONS
{
    WinVfsLookupCallback                WinVfsFileDispatchLookup;
    WinVfsCreateFileCallback            WinVfsFileDispatchCreate;
    WinVfsCloseFileCallback             WinVfsFileDispatchClose;
    WinVfsReadFileCallback              WinVfsFileDispatchRead;
    WinVfsWriteFileCallback             WinVfsFileDispatchWrite;
    WinVfsFlushFileBuffers              WinVfsFileDispatchFlush;
    WinVfsGetFileInformationCallback    WinVfsFileDispatchGetInformation;
    WinVfsReadDirectoryCallback         WinVfsFileDispatchReadDirectory;
    WinVfsDeleteFileCallback            WinVfsFileDispatchDelete; 
} WIN_VFS_FILE_OPERATIONS, *PWIN_VFS_FILE_OPERATIONS;

