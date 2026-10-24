##
#
#  Copyright (c) 2011 - 2022, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2020, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#  Copyright (c) Microsoft Corporation.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##
#
#  Xiaomi Redmi Note 14 Pro+ 5G, "amethyst", SM7635. Started from OnePlus giuliaPkg (SM8650, the same Lanai UEFI branch).
#  The memory map is generated from the phone's XBL config device tree (tools/uefi/xbl-memmap-to-c.py in
#  rootstockos/iosonandng); the vendor DXEs come from the phone's own uefi partition via UEFIReader.
#

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = amethyst
  PLATFORM_GUID                  = C3166E6C-484B-411B-BE01-9EE08A767D03
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/amethystPkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = RELEASE|DEBUG
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = amethystPkg/amethyst.fdf
  USE_CUSTOM_DISPLAY_DRIVER      = 0

!include VolcanoPkg/VolcanoPkg.dsc.inc

[PcdsFixedAtBuild]
  #
  # DDR Memory
  #
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000

  #
  # UEFI Stack (UEFI_Stack in the memory map)
  #
  gArmPlatformTokenSpaceGuid.PcdCPUCoresStackBase|0xA760D000
  gArmPlatformTokenSpaceGuid.PcdCPUCorePrimaryStackSize|0x40000

  #
  # SMBIOS
  #
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemManufacturer|"Xiaomi"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"amethyst"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Redmi Note 14 Pro+ 5G"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"N14P"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemBoardModel|"amethyst"

  #
  # Simple Frame Buffer (O16U 1.5K AMOLED, 1220x2712, video mode; Display_Reserved at 0xE3940000)
  #
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferWidth|1220
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferHeight|2712
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferColorDepth|32

  #
  # Platform PEI
  #
  gQcomPkgTokenSpaceGuid.PcdPlatformType|"LA"

[LibraryClasses]
  #
  # Memory Libraries
  #
  MemoryMapLib|amethystPkg/Library/MemoryMapLib/MemoryMapLib.inf

  #
  # QCOM Libraries
  #
  ConfigurationMapLib|amethystPkg/Library/ConfigurationMapLib/ConfigurationMapLib.inf

[Components]
  #
  # ACPI Tables
  #
  #amethyst/AcpiTables.inf

  # UniXNU removed for local build_uefi.py test

  #
  # Keys over SPMI (power = Enter, volume up/down = Up/Down) without the vendor PMIC stack; see its README.md.
  #
  amethystPkg/Drivers/ShengKeyInputDxe/ShengKeyInputDxe.inf

[LibraryClasses]
  FdtLib|MdePkg/Library/BaseFdtLib/BaseFdtLib.inf
