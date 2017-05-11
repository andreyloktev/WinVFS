#pragma once

#include "winvfs_common.h"
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
                                            _In_ PWinVfsFcb             pParentDir
                                           ,_In_ PUNICODE_STRING        pFileName
                                           ,_In_ PACCESS_MASK           pDesiredAccess
                                           ,_In_ ULONG                  fileAttr
                                           ,_In_ PIO_SECURITY_CONTEXT   pSecurityCtxt
                                           ,_Out_ PWinVfsFcb*           ppFile
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
                                                _In_ PWinVfsFcb             pParentDir
                                               ,_In_ PUNICODE_STRING        pNewFileName
                                               ,_In_ WinVfsNodeType         fileType
                                               ,_In_ ULONG                  fileAttr
                                               ,_In_ PIO_SECURITY_CONTEXT   pSecurityCtxt
                                               ,_Out_ PWinVfsFcb*           ppNewFile
                                            );

/**Close a file object. It's called before deallocate WinvfsFCB object
* @param pFile file object to close
*/
typedef NTSTATUS (*WinVfsCloseFileCallback)( _In_ PWinVfsFcb pFile );

/** Read a file
* @param pFile          a file object to read from
* @param offset         file offset to begin reading from
* @param pBuffer        pointer to buffer structure
* @param bytesToRead    bytes to read
* @param pBytes         amount read bytes
* @return STATUS_SUCCESS if information is read successfully.
*/
typedef NTSTATUS (*WinVfsReadFileCallback)(
                                            _In_    PWinVfsFcb pFile
                                           ,_In_    LARGE_INTEGER offset
                                           ,_Out_   PVOID pBuffer
                                           ,_In_    UINT32 bytesToRead
                                           ,_Out_   PUINT32 pBytes
                                        );

/**Write a file
* @param pFile          a file object to write to
* @param offset         file offset to begin writting to
* @param pBuffer        pointer to buffer structure
* @param bytesToRead    bytes to write
* @param pBytes         amount written bytes 
* @return STATUS_SUCCESS if information is written successfully
*/
typedef NTSTATUS (*WinVfsWriteFileCallback)(
                                            _In_    PWinVfsFcb pFile
                                           ,_In_    LARGE_INTEGER offset
                                           ,_In_    PVOID pBuffer
                                           ,_In_    UINT32 bytesToWrite
                                           ,_Out_   PUINT32 pBytes
                                        );

/**Flush file buffers
* @param pFileObj file object to flush
* @return STATUS_SUCCESS if file is flushhed successfully
*/
typedef NTSTATUS (*WinVfsFlushFileBuffersCallback)( _In_ PWinVfsFcb pFileObj );

/**Gey information about a file
* @param pFileObj a file to get information about
* @param fiClass a value that specifies which structure to use to query or set information for a file object.
* @param pBuffer buffer. Buffer type depends on FILE_INFORMATION_CLASS.
* @param szBuffer buffer size
* @param pBytes bytes retrieved
* @return STATUS_SUCCESS if information can be retrieved.
*/
typedef NTSTATUS (*WinVfsGetFileInformationCallback)(
                                                        _In_    PWinVfsFcb pFileObj
                                                       ,_In_    FILE_INFORMATION_CLASS fiClass
                                                       ,_Out_   PVOID pBuffer
                                                       ,_In_    UINT32 szBuffer
                                                       ,_Out_   PULONG pBytes
                                                    );

/**Gey information about a file
* @param pFileObj a file to set information to
* @param fiClass a value that specifies which structure to use to query or set information for a file object.
* @param pBuffer buffer with file information. Buffer type depends on FILE_INFORMATION_CLASS.
* @param szBuffer buffer size
* @param pBytes bytes set
* @return STATUS_SUCCESS if information can be retrieved.
*/
typedef NTSTATUS (*WinVfsSetFileInformationCallback)(
                                                        _In_    PWinVfsFcb pFileObj
                                                       ,_In_    FILE_INFORMATION_CLASS fiClass
                                                       ,_In_    PVOID pBuffer
                                                       ,_In_    UINT32 szBuffer
                                                       ,_Out_   PULONG pBytes
                                                    );

/**Enumerate a directory
* @param pFileObj a directory to enumerate
* @param searchPattern a search pattern
* @param fiClass what does information need?
* @param fileOffset file entry offset(index) in a directory. If there are files when buffer is filled then cuurent directory position is saved via pFileOffset
* @param pBuffer buffer. It's cast to a structure depending on the fiClass parameter
* @param szBuffer buffer size.
* @return STATUS_SUCCESS if there is no more space in the buffer but file entries exist yet
          STATUS_NO_MORE_FILES if there are not more files in a directory
          STATUS_NO_SUCH_FILE if there is not a file satisfying to search patter
*/
typedef NTSTATUS (*WinVfsReadDirectoryCallback)(
                                                    _In_    PWinVfsFcb              pFileObj
                                                   ,_In_    UNICODE_STRING          searchPattern
                                                   ,_In_    FILE_INFORMATION_CLASS  fiClass
                                                   ,_Inout_ PULONG                  pFileOffset
                                                   ,_Out_   PVOID                   pBuffer
                                                   ,_In_    UINT32                  szBuffer
                                            );


/**Delete a file
* @param pFileObj file to delete
* @return if success return STATUS_SUCCESS
*/
typedef NTSTATUS (*WinVfsDeleteFileCallback)( _In_  PWinVfsFcb pFileObj );


typedef struct _WIN_VFS_FILE_OPERATIONS
{
    WinVfsLookupCallback                WinVfsFileLookup;
    WinVfsCreateFileCallback            WinVfsFileCreate;
    WinVfsCloseFileCallback             WinVfsFileClose;
    WinVfsReadFileCallback              WinVfsFileRead;
    WinVfsWriteFileCallback             WinVfsFileWrite;
    WinVfsFlushFileBuffersCallback      WinVfsFileFlush;
    WinVfsGetFileInformationCallback    WinVfsFileGetInformation;
    WinVfsReadDirectoryCallback         WinVfsFileReadDirectory;
    WinVfsDeleteFileCallback            WinVfsFileDelete; 
} WinVfsFileOperations, *PWinVfsFileOperations;

