/**
  Copyright (c) 2011-2017, ARM Limited. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/

#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/PrePiLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SerialPortLib.h>
#include <Library/PlatformSecLib.h>
#include <Library/PrePiHobListPointerLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/MemoryMapHelperLib.h>
#include <Library/TimerLib.h>
#include <Library/HobLib.h>

#include "Sec.h"

//
// The value the previous stage passed in x0 is published under this GUID as a
// UINT64.  UniXNU's UniXNURamDiskDxe reads it as the firmware device tree and
// takes the payload volume from /chosen/linux,initrd-start and -end.
//
STATIC CONST EFI_GUID  mEntryArgHobGuid = {
  0xDAEE82E6, 0x8090, 0x4E72, { 0xBF, 0xB9, 0x78, 0xC1, 0x3C, 0xD4, 0xE3, 0x59 }
};

STATIC CONST EFI_GUID  mEmbeddedPayloadHobGuid = {
  0xA8E7F3A4, 0xE28B, 0x4E66, { 0xA4, 0x6E, 0x99, 0x72, 0x78, 0x65, 0x72, 0x31 }
};

typedef struct {
  UINT64  Base;
  UINT64  Size;
} EMBEDDED_PAYLOAD;

STATIC UINT64  mEntryArgument;
STATIC EMBEDDED_PAYLOAD  mEmbeddedPayload;

#ifndef MDEPKG_NDEBUG
STATIC
VOID
ClearFrameBuffer (VOID)
{
  EFI_MEMORY_REGION_DESCRIPTOR FrameBufferRegion;

  // Locate "Display Reserved" Memory Region
  LocateMemoryRegionByName ("Display Reserved", &FrameBufferRegion);
  LocateMemoryRegionByName ("Display_Reserved", &FrameBufferRegion);

  // Clear Memory Region
  if (FrameBufferRegion.Address != 0 && FrameBufferRegion.Length != 0) {
    ZeroMem ((VOID *)FrameBufferRegion.Address, FrameBufferRegion.Length);
  }
}

STATIC
VOID
PrintFirmwareVersion (VOID)
{
  // Clear Frame Buffer
  ClearFrameBuffer ();

  // Print UEFI Version Message
  DEBUG ((EFI_D_WARN, "\n"));
  DEBUG ((EFI_D_WARN, "Project Silicium for %a %a\n",            FixedPcdGetPtr (PcdSmbiosSystemManufacturer), FixedPcdGetPtr (PcdSmbiosSystemModel)));
  DEBUG ((EFI_D_WARN, "Firmware Version %s Build at %a on %a\n", PcdGetPtr (PcdFirmwareVersionString), __TIME__, __DATE__));
  DEBUG ((EFI_D_WARN, "\n"));
}
#endif

STATIC
EFI_STATUS
InitializeMemory (VOID)
{
  EFI_STATUS                    Status;
  EFI_MEMORY_REGION_DESCRIPTOR  UefiMemoryRegion;
  EFI_HOB_HANDOFF_INFO_TABLE   *HobList;

  // Locate "DXE Heap" Memory Region
  LocateMemoryRegionByName ("DXE Heap", &UefiMemoryRegion);
  LocateMemoryRegionByName ("DXE_Heap", &UefiMemoryRegion);

  // Save UEFI Memory Details
  UINTN UefiMemoryBase = UefiMemoryRegion.Address;
  UINTN UefiMemorySize = UefiMemoryRegion.Length;

  // Verify UEFI Memory Base
  if (UefiMemoryBase == 0 && UefiMemorySize == 0) {
    DEBUG ((EFI_D_ERROR, "Failed to Locate \"DXE Heap\" Memory Region!\n"));
    return EFI_NOT_FOUND;
  }

  // Initialize HOB List
  HobList = HobConstructor ((VOID *)UefiMemoryBase, UefiMemorySize, (VOID *)UefiMemoryBase, (VOID *)(UefiMemoryBase + UefiMemorySize));
  PrePeiSetHobList (HobList);

  // Initialize MMU & Memory HOBs
  Status = MemoryPeim (UefiMemoryBase, UefiMemorySize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Build Stack HOB
  BuildStackHob (FixedPcdGet64 (PcdCPUCoresStackBase), FixedPcdGet32 (PcdCPUCorePrimaryStackSize));

  // Publish the entry argument for DXE, which cannot read the SEC entry
  // registers.  Only a value that can be a 64-bit physical address is
  // published: a zero, a small integer, or a non-canonical value in x0 must not
  // turn into a pointer that a later driver dereferences.
  if ((mEntryArgument >= 0x80000000) && (mEntryArgument < 0x0001000000000000) &&
      ((mEntryArgument & 7) == 0))
  {
    BuildGuidDataHob (&mEntryArgHobGuid, &mEntryArgument, sizeof (mEntryArgument));
  }

  if ((mEmbeddedPayload.Base >= 0x80000000) &&
      (mEmbeddedPayload.Base < 0x0001000000000000) &&
      ((mEmbeddedPayload.Base & 7) == 0) &&
      (mEmbeddedPayload.Size != 0) && ((mEmbeddedPayload.Size & 511) == 0))
  {
    BuildGuidDataHob (&mEmbeddedPayloadHobGuid, &mEmbeddedPayload, sizeof (mEmbeddedPayload));
  }

  return EFI_SUCCESS;
}

STATIC
VOID
SecMain (VOID)
{
  EFI_STATUS Status;

  // Do Platform Specific Initialization
  PlatformInitialize ();

#ifndef MDEPKG_NDEBUG
  // Initialize Serial Port
  Status = SerialPortInitialize ();
  if (EFI_ERROR (Status)) {
    return;
  }

  // Print Firmware Version
  PrintFirmwareVersion ();

  // Initialize Debug Agent
  InitializeDebugAgent (DEBUG_AGENT_INIT_POSTMEM_SEC, NULL, NULL);
  SaveAndSetDebugTimerInterrupt (TRUE);
#endif

  // Initialize Memory
  Status = InitializeMemory ();
  if (EFI_ERROR (Status)) {
    return;
  }

  // Build CPU HOB
  BuildCpuHob (ArmGetPhysicalAddressBits (), PcdGet8 (PcdPrePiCpuIoSize));

  // Set the Boot Mode
  SetBootMode (BOOT_WITH_DEFAULT_SETTINGS);

  // Initialize Platform HOBs
  Status = PlatformPeim ();
  if (EFI_ERROR (Status)) {
    return;
  }

  // Run Library Cconstructors
  ProcessLibraryConstructorList ();

  // Decompress all FVs
  Status = DecompressFirstFv ();
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to Decompress FV! Status = %r\n", Status));
    return;
  }

  // Load DXE Core
  Status = LoadDxeCoreFromFv (NULL, 0);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to Load DXE Core! Status = %r\n", Status));
  }
}

VOID
SecEntry (
  IN UINT64  EntryArgument,
  IN UINT64  EmbeddedPayloadBase,
  IN UINT64  EmbeddedPayloadSize
  )
{
  // Record the handoff argument before anything can clobber it.  The FD range
  // is written back below, so this store reaches DRAM with the rest of them.
  mEntryArgument = EntryArgument;
  mEmbeddedPayload.Base = EmbeddedPayloadBase;
  mEmbeddedPayload.Size = EmbeddedPayloadSize;

  // Disable Data Cache
  ArmDisableDataCache ();

  // Invalidate Instruction Cache
  ArmInvalidateInstructionCache ();

  // Enable Instruction Cache
  ArmEnableInstructionCache ();

  // Write back and invalidate Stack & UEFI FD D-Cache. A plain invalidate would discard what the entry code just stored there
  // (live stack frames) if the previous stage left the data cache on.
  WriteBackInvalidateDataCacheRange ((VOID *)FixedPcdGet64 (PcdCPUCoresStackBase), FixedPcdGet32 (PcdCPUCorePrimaryStackSize));
  WriteBackInvalidateDataCacheRange ((VOID *)FixedPcdGet64 (PcdFdBaseAddress),     FixedPcdGet32 (PcdFdSize));

  // Verify Exception Vector Table
  ASSERT (((UINTN)SecVectorTable & ARM_VECTOR_TABLE_ALIGNMENT) == 0);

  // Enable new Exception Vector Table
  ArmWriteVBar ((UINTN)SecVectorTable);

  // Enter Main SEC Function
  SecMain ();
}
