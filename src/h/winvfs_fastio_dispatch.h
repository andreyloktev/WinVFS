#pragma once

//FastIO functions
//There are only functions here which are implemented in the Microsoft fastfat driver sample.
//Function descriptions are from the Microsoft fastfat driver sample

#include <winvfs.h>

/**
* This routine checks if fast i/o is possible for a read/write operation
*
* @param pFileObject supplies the file object used in the query
* @param pFileOffset supplies the starting byte offset for the read/write operation
* @param length supplies the length, in bytes, of the read/write operation
* @param wait indicates if we can wait
* @param lockKey supplies the lock key
* @param checkForReadOperation indicates if this is a check for a read or write
*        operation
* @param pIoStatus receives the status of the operation if our return value is
*                  FastIoReturnError
* @param pDeviceObject device object
* @return TRUE if fast I/O is possible and FALSE if the caller needs
*         to take the long route.
*/
_Function_class_(FAST_IO_CHECK_IF_POSSIBLE)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_check_if_possible(
    _In_    PFILE_OBJECT        pFileObject
   ,_In_    PLARGE_INTEGER      pFileOffset
   ,_In_    ULONG               length
   ,_In_    BOOLEAN             wait
   ,_In_    ULONG               lockKey
   ,_In_    BOOLEAN             checkForReadOperation
   ,_Out_   PIO_STATUS_BLOCK    pIoStatus
   ,_In_    PDEVICE_OBJECT      pDeviceObject
   );

/**
* This routine is for the fast query call for basic file information.
*
* @param pFileObject Supplies the file object used in this operation
* @paarm wait indicates if we are allowed to wait for the information
* @param pBuffer supplies the output buffer to receive the basic information
* @param pIoStatus receives the final status of the operation
* @param pDeviceObject device object
*
* @return TRUE if the operation succeeded and FALSE if the caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_QUERY_BASIC_INFO)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_query_basic_info(
    _In_    PFILE_OBJECT            pFileObject
   ,_In_    BOOLEAN                 wait
   ,_Out_   PFILE_BASIC_INFORMATION pBuffer
   ,_Out_   PIO_STATUS_BLOCK        pIoStatus
   ,_In_    PDEVICE_OBJECT          pDeviceObject
   );

/**
* This routine is for the fast query call for standard file information.
*
* @param pFileObject supplies the file object used in this operation
* @param wait indicates if we are allowed to wait for the information
* @param pBuffer supplies the output buffer to receive the basic information
* @param pIoStatus receives the final status of the operation
* @param pDeviceObject device object
*
* @return TRUE if the operation succeeded and FALSE if the caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_QUERY_STANDARD_INFO)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_query_standart_info(
    _In_    PFILE_OBJECT                pFileObject
   ,_In_    BOOLEAN                     wait
   ,_Out_   PFILE_STANDARD_INFORMATION  pBuffer
   ,_Out_   PIO_STATUS_BLOCK            pIoStatus
   ,_In_    PDEVICE_OBJECT              pDeviceObject
   );

/**
* This is a call back routine for doing the fast lock call.
*
* @param pFileObject supplies the file object used in this operation
* @param pFileOffset supplies the file offset used in this operation
* @param pLength supplies the length used in this operation
* @param pProcessId supplies the process ID used in this operation
* @param key supplies the key used in this operation
* @param failImmediately indicates if the request should fail immediately
*        if the lock cannot be granted.
* @param exclusiveLock indicates if this is a request for an exclusive or
*        shared lock
* @param pIoStatus receives the Status if this operation is successful
* @param pDeviceObject device object
*
* @return TRUE if this operation completed and FALSE if caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_LOCK)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_lock (
    _In_    PFILE_OBJECT        pFileObject
   ,_In_    PLARGE_INTEGER      pFileOffset
   ,_In_    PLARGE_INTEGER      pLength
   ,_In_    PEPROCESS           pProcessId
   ,_In_    ULONG               key
   ,_In_    BOOLEAN             failImmediately
   ,_In_    BOOLEAN             exclusiveLock
   ,_Out_   PIO_STATUS_BLOCK    pIoStatus
   ,_In_    PDEVICE_OBJECT      pDeviceObject
   );

/**
* This is a call back routine for doing the fast unlock single call.
*
* @param pFileObject supplies the file object used in this operation
* @param pFileOffset supplies the file offset used in this operation
* @param pLength supplies the length used in this operation
* @param pProcessId supplies the process ID used in this operation
* @param key supplies the key used in this operation
* @param pIoStatus receives the Status if this operation is successful
* @param pDeviceObject device object
*
* @return TRUE if this operation completed and FALSE if caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_UNLOCK_SINGLE)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_unlock_single(
    _In_    PFILE_OBJECT        pFileObject
   ,_In_    PLARGE_INTEGER      pFileOffset
   ,_In_    PLARGE_INTEGER      pLength
   ,_In_    PEPROCESS           pProcessId
   ,_In_    ULONG               key
   ,_Out_   PIO_STATUS_BLOCK    pIoStatus
   ,_In_    PDEVICE_OBJECT      pDeviceObject
   );

/**
* This is a call back routine for doing the fast unlock all call.
*
* @param pFileObject supplies the file object used in this operation
* @param pProcessId supplies the process ID used in this operation
* @param pIoStatus receives the Status if this operation is successful
* @param pDeviceObject device object
*
* @return TRUE if this operation completed and FALSE if caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_UNLOCK_ALL)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_unlock_all(
    _In_    PFILE_OBJECT        pFileObject
   ,_In_    PEPROCESS           pProcessId
   ,_Out_   PIO_STATUS_BLOCK    pIoStatus
   ,_In_    PDEVICE_OBJECT      pDeviceObject
   );

/**
* This is a call back routine for doing the fast unlock all by key call.

* @param pFileObject supplies the file object used in this operation
* @param pProcessId supplies the process ID used in this operation
* @param key supplies the key used in this operation
* @param pIoStatus receives the Status if this operation is successful
* @param pdeviceObject device object
*
* @return TRUE if this operation completed and FALSE if caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_UNLOCK_ALL_BY_KEY)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_unlock_all_by_key(
    _In_    PFILE_OBJECT        pFileObject
   ,_In_    PVOID               pProcessId
   ,_In_    ULONG               key
   ,_Out_   PIO_STATUS_BLOCK    pIoStatus
   ,_In_    PDEVICE_OBJECT      pDeviceObject
   );

/**
* This routine is for the fast query call for network open information.

* @param pFileObject supplies the file object used in this operation
* @paran wait indicates if we are allowed to wait for the information
* @param pBuffer supplies the output buffer to receive the information
* @param pIoStatus receives the final status of the operation
* @param pdeviceObject device object
*
* @return TRUE if the operation succeeded and FALSE if the caller
*         needs to take the long route.
*/
_Function_class_(FAST_IO_QUERY_NETWORK_OPEN_INFO)
_IRQL_requires_same_
BOOLEAN
winvfs_fastio_query_network_open_info(
    _In_    PFILE_OBJECT                    pFileObject
   ,_In_    BOOLEAN                         wait
   ,_Out_   PFILE_NETWORK_OPEN_INFORMATION  pBuffer
   ,_Out_   PIO_STATUS_BLOCK                pIoStatus
   ,_In_    PDEVICE_OBJECT                  pDeviceObject
   );

/**
* This routine is for fast acquire call for a file system resource prior to a cache flush.

* @param pFileObject supplies the file object used in this operation
* @param pdeviceObject device object
*
* @return STATUS_SUCCESS if the operation succeeded.
*/
_Function_class_(FAST_IO_ACQUIRE_FOR_CCFLUSH)
_IRQL_requires_same_
NTSTATUS
winvfs_fastio_acquire_for_ccflush(
    _In_ PFILE_OBJECT   pFileObject
   ,_In_ PDEVICE_OBJECT pDeviceObject
   );

/**
* This routine is for fast release call for a file system resource previously acquired for a cache flush.
*
* @param pFileObject supplies the file object used in this operation
* @param pdeviceObject device object
*
* @return STATUS_SUCCESS if the operation succeeded.
*/
_Function_class_(FAST_IO_RELEASE_FOR_CCFLUSH)
_IRQL_requires_same_
NTSTATUS
winvfs_fastio_release_for_ccflush(
    _In_ PFILE_OBJECT   pFileObject
   ,_In_ PDEVICE_OBJECT pDeviceObject
   );

/**
* Initialize fast io table.
*
* @return pointer to fast io table. Otherwise NULL in case of error
*/
_IRQL_requires_max_(PASSIVE_LEVEL)
PFAST_IO_DISPATCH winvfs_init_fastio_table();