#include <winvfs/winvfs_block_device.h>

NTSTATUS blockdev_read( _In_ DEVICE_OBJECT blockDev, _In_ UINT32 flags, _In_ LONGLONG offset, _Out_ PVOID pBuffer, _In_ UINT32 szBuffer, _Out_ PUINT32 pReadBytes )
{
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS blockdev_write( _In_ DEVICE_OBJECT blockDev, _In_ UINT32 flags, _In_ LONGLONG offset, _In_ PVOID pBuffer, _In_ UINT32 szBuffer, _Out_ PUINT32 pWrittenBytes )
{
    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS blockdev_flush( _In_ DEVICE_OBJECT blockDev )
{
    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS blockdev_ioctl( 
                        _In_        DEVICE_OBJECT blockDev
                       ,_In_        UINT32 ioctl
                       ,_In_opt_    PVOID pInBuffer
                       ,_In_        UINT32 szInBuffer
                       ,_Out_opt_   PVOID pOutBuffer
                       ,_In_        UINT32 szOutBuffer
                       ,_Out_opt_   PUINT32 pBytes
                    )
{
    return STATUS_NOT_IMPLEMENTED;
}