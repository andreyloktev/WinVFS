#pragma once

#include "winvfs_common.h"


/**
* Read data form a block device.
* @param blockDev block device object
* @param flags block device specific flags
* @param offset offset to start reading from
* @param pBuffer output buffer 
* @param szBuffer buffer size( amount bytes to read )
* @rapam pReadBytes actual amount read bytes
* @return error code
*/
NTSTATUS blockdev_read( _In_ PDEVICE_OBJECT pBlockDev, _In_ UINT32 flags, _In_ LONGLONG offset, _Out_ PVOID pBuffer, _In_ UINT32 szBuffer, _Out_ PUINT32 pReadBytes );

/**
* Write data to a block device.
* @param blockDev block device object
* @param flags block device specific flags
* @param offset offset to start reading from
* @param pBuffer input buffer 
* @param szBuffer buffer size( amount bytes to write )
* @rapam pWrittenBytes actual amount written bytes
* @return error code
*/
NTSTATUS blockdev_write( _In_ PDEVICE_OBJECT pBlockDev, _In_ UINT32 flags, _In_ LONGLONG offset, _In_ PVOID pBuffer, _In_ UINT32 szBuffer, _Out_ PUINT32 pWrittenBytes );

/**
* Flush all block device buffers
* @param blockDev block device object
*/
NTSTATUS blockdev_flush( _In_ PDEVICE_OBJECT pBlockDev );

/**
* Ioctl
* @param blockDev block device object
* @param ioctl control code to a block device
* @param pInBuffer input buffer
* @param szInBuffer input buffer size
* @param pOutBuffer output buffer
* @param zsOutBuffer output buffer size
* @rapam pBytes bytes retuned
* @return error code
*/
NTSTATUS blockdev_ioctl( 
                        _In_        PDEVICE_OBJECT pBlockDev
                       ,_In_        UINT32 ioctl
                       ,_In_opt_    PVOID pInBuffer
                       ,_In_        UINT32 szInBuffer
                       ,_Out_opt_   PVOID pOutBuffer
                       ,_In_        UINT32 szOutBuffer
                       ,_Out_opt_   PUINT32 pBytes
                    );