#include <winvfs/winvfs_block_device.h>

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, blockdev_read)
#pragma alloc_text(PAGE, blockdev_write)
#pragma alloc_text(PAGE, blockdev_flush)
#pragma alloc_text(PAGE, blockdev_ioctl)
#endif

NTSTATUS blockdev_read( _In_ PDEVICE_OBJECT pBlockDev, _In_ UINT32 flags, _In_ LONGLONG offset, _Out_ PVOID pBuffer, _In_ UINT32 szBuffer, _Out_ PUINT32 pReadBytes )
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(pBlockDev);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(offset);
    UNREFERENCED_PARAMETER(pBuffer);
    UNREFERENCED_PARAMETER(szBuffer);
    UNREFERENCED_PARAMETER(pReadBytes);

    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS blockdev_write( _In_ PDEVICE_OBJECT pBlockDev, _In_ UINT32 flags, _In_ LONGLONG offset, _In_ PVOID pBuffer, _In_ UINT32 szBuffer, _Out_ PUINT32 pWrittenBytes )
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(pBlockDev);
    UNREFERENCED_PARAMETER(flags);
    UNREFERENCED_PARAMETER(offset);
    UNREFERENCED_PARAMETER(pBuffer);
    UNREFERENCED_PARAMETER(szBuffer);
    UNREFERENCED_PARAMETER(pWrittenBytes);

    return STATUS_NOT_IMPLEMENTED;
}

NTSTATUS blockdev_flush( _In_ PDEVICE_OBJECT pBlockDev )
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(pBlockDev);

    return STATUS_NOT_IMPLEMENTED;
}


NTSTATUS blockdev_ioctl( 
                        _In_        PDEVICE_OBJECT pBlockDev
                       ,_In_        UINT32 ioctl
                       ,_In_opt_    PVOID pInBuffer
                       ,_In_        UINT32 szInBuffer
                       ,_Out_opt_   PVOID pOutBuffer
                       ,_In_        UINT32 szOutBuffer
                       ,_Out_opt_   PUINT32 pBytes
                    )
{
    PAGED_CODE();

    UNREFERENCED_PARAMETER(pBlockDev);
    UNREFERENCED_PARAMETER(ioctl);
    UNREFERENCED_PARAMETER(pInBuffer);
    UNREFERENCED_PARAMETER(szInBuffer);
    UNREFERENCED_PARAMETER(pOutBuffer);
    UNREFERENCED_PARAMETER(szOutBuffer);
    UNREFERENCED_PARAMETER(pBytes);

    return STATUS_NOT_IMPLEMENTED;
}