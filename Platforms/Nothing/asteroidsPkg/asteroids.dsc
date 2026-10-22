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
#  Nothing Phone (3a), "asteroids", SM7635. Started from OnePlus giuliaPkg (SM8650, the same Lanai UEFI branch).
#  The memory map is generated from the phone's XBL config device tree (tools/uefi/xbl-memmap-to-c.py in
#  rootstockos/iosonandng); the vendor DXEs come from the phone's own uefi partition via UEFIReader.
#

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = asteroids
  PLATFORM_GUID                  = CBB5F959-1B62-48EB-A09D-FA3CD7B11FF7
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/asteroidsPkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = RELEASE|DEBUG
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = asteroidsPkg/asteroids.fdf
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
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemManufacturer|"Nothing"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"asteroids"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Phone (3a)"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"A059"
  gSiliciumPkgTokenSpaceGuid.PcdSmbiosSystemBoardModel|"asteroids"

  #
  # Simple Frame Buffer (Visionox rm69220, 1080x2392, video mode; Display_Reserved at 0xE3940000)
  #
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferWidth|1080
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferHeight|2392
  gSiliciumPkgTokenSpaceGuid.PcdFrameBufferColorDepth|32

  #
  # Platform PEI
  #
  gQcomPkgTokenSpaceGuid.PcdPlatformType|"LA"

[LibraryClasses]
  #
  # Memory Libraries
  #
  MemoryMapLib|asteroidsPkg/Library/MemoryMapLib/MemoryMapLib.inf

  #
  # QCOM Libraries
  #
  ConfigurationMapLib|asteroidsPkg/Library/ConfigurationMapLib/ConfigurationMapLib.inf

[Components]
  #
  # ACPI Tables
  #
  #asteroids/AcpiTables.inf

  #
  # UniXNU boot manager and XNU loader. Their packages come from the UniXNU tree (PACKAGES_PATH set by
  # `unixnu build firmware`), so this platform builds with the unixnu driver rather than build_uefi.py.
  #
  UniXNUPkg/Application/UniXNU/UniXNU.inf
  UniXNUPkg/Driver/UniXNUDxe/UniXNUDxe.inf
  DarwinBootPkg/Driver/DarwinBoot.inf

  #
  # Keys over SPMI (power = Enter, volume up/down = Up/Down) without the vendor PMIC stack; see its README.md.
  #
  asteroidsPkg/Drivers/ShengKeyInputDxe/ShengKeyInputDxe.inf

[LibraryClasses]
  UniXNULib|UniXNUPkg/Library/UniXNULib/UniXNULib.inf
  FdtLib|MdePkg/Library/BaseFdtLib/BaseFdtLib.inf
