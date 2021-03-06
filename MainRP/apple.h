/*
 * MainRP/apple.h
 *
 * Copyright (c) 2015 Roderick W. Smith
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __APPLE_H_
#define __APPLE_H_

// Apple's GUID
#define APPLE_GUID { 0x7c436110, 0xab2a, 0x4bbb, { 0xa8, 0x80, 0xfe, 0x41, 0x99, 0x5c, 0x9f, 0x82 } };

// Apple's NVRAM ACCESS FLAGS
#define APPLE_FLAGS EFI_VARIABLE_BOOTSERVICE_ACCESS|EFI_VARIABLE_RUNTIME_ACCESS|EFI_VARIABLE_NON_VOLATILE;

// These codes are returned in the first byte of the csr-active-config variable
#define CSR_ALLOW_UNTRUSTED_KEXTS            0x001
#define CSR_ALLOW_UNRESTRICTED_FS            0x002
#define CSR_ALLOW_TASK_FOR_PID               0x004
#define CSR_ALLOW_KERNEL_DEBUGGER            0x008
#define CSR_ALLOW_APPLE_INTERNAL             0x010
#define CSR_ALLOW_UNRESTRICTED_DTRACE        0x020
#define CSR_ALLOW_UNRESTRICTED_NVRAM         0x040
#define CSR_ALLOW_DEVICE_CONFIGURATION       0x080
#define CSR_ALLOW_ANY_RECOVERY_OS            0x100
#define CSR_ALLOW_UNAPPROVED_KEXTS           0x200
#define CSR_ALLOW_EXECUTABLE_POLICY_OVERRIDE 0x400
#define CSR_ALLOW_UNAUTHENTICATED_ROOT       0x800
#define CSR_END_OF_LIST                      0xFFFFFFFF

// Some summaries....
#define SIP_ENABLED  (CSR_ALLOW_APPLE_INTERNAL)
#define SIP_DISABLED (CSR_ALLOW_UNTRUSTED_KEXTS | \
    CSR_ALLOW_UNRESTRICTED_FS | \
    CSR_ALLOW_TASK_FOR_PID | \
    CSR_ALLOW_APPLE_INTERNAL | \
    CSR_ALLOW_UNRESTRICTED_DTRACE | \
    CSR_ALLOW_UNRESTRICTED_NVRAM)
#define SIP_DISABLED_EX (SIP_DISABLED | \
    CSR_ALLOW_UNAUTHENTICATED_ROOT)
#define SIP_DISABLED_ANY (SIP_DISABLED_EX | \
    CSR_ALLOW_ANY_RECOVERY_OS)
#define SIP_DISABLED_KEXT (SIP_DISABLED_ANY | \
    CSR_ALLOW_UNAPPROVED_KEXTS)
#define SIP_DISABLED_DEBUG (SIP_DISABLED_KEXT | \
    CSR_ALLOW_KERNEL_DEBUGGER)
#define SIP_DISABLED_DEVICE (SIP_DISABLED_DEBUG | \
    CSR_ALLOW_DEVICE_CONFIGURATION)
#define CSR_MAX_LEGAL_VALUE (CSR_ALLOW_UNTRUSTED_KEXTS | \
    CSR_ALLOW_UNRESTRICTED_FS | \
    CSR_ALLOW_TASK_FOR_PID | \
    CSR_ALLOW_KERNEL_DEBUGGER | \
    CSR_ALLOW_APPLE_INTERNAL | \
    CSR_ALLOW_UNRESTRICTED_DTRACE | \
    CSR_ALLOW_UNRESTRICTED_NVRAM | \
    CSR_ALLOW_DEVICE_CONFIGURATION | \
    CSR_ALLOW_ANY_RECOVERY_OS | \
    CSR_ALLOW_UNAPPROVED_KEXTS | \
    CSR_ALLOW_EXECUTABLE_POLICY_OVERRIDE | \
    CSR_ALLOW_UNAUTHENTICATED_ROOT)

extern CHAR16 *gCsrStatus;

EFI_STATUS SetAppleOSInfo();
EFI_STATUS GetCsrStatus(UINT32 *CsrValue);
EFI_STATUS CheckAppleNvramEntry (
    IN  CHAR16      *NameNVRAM,
    IN  CONST VOID  *DataNVRAM
);

VOID RecordgCsrStatus(UINT32 CsrStatus, BOOLEAN DisplayMessage);
VOID RotateCsrValue(VOID);
VOID TrimForce(VOID);
VOID DisableMacCompatCheck(VOID);
VOID DisableAMFI(VOID);
VOID *GetAppleNvramEntry (
    IN      CHAR16        *VariableName,
    OUT     UINT32        *Attributes    OPTIONAL,
    OUT     UINTN         *DataSize      OPTIONAL
);

#endif
