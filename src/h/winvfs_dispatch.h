#pragma once

#include <winvfs.h>

_Function_class_(IRP_MJ_CREATE)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_create( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_CLEANUP)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_cleanup( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_CLOSE)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_close( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_DEVICE_CONTROL)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_device_control( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_FILE_SYSTEM_CONTROL)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_filesystem_control( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_FLUSH_BUFFERS)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_flush_buffers( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_PNP)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_pnp( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_POWER)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_power( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_QUERY_INFORMATION)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_query_info( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_READ)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_read( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_SET_INFORMATION)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_set_info( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_SHUTDOWN)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_shutdown( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(IRP_MJ_WRITE)
_IRQL_requires_max_(DISPATCH_LEVEL)
NTSTATUS winvfs_dispatch_write( _In_ PDEVICE_OBJECT pDevObj, _In_ PIRP *pIrp );

_Function_class_(DRIVER_UNLOAD)
_IRQL_requires_max_(PASSIVE_LEVEL)
void winvfs_driver_unload ( _In_ PDRIVER_OBJECT DriverObject );