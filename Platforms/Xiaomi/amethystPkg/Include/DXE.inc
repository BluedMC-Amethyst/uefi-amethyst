  INF MdeModulePkg/Core/Dxe/DxeMain.inf
  INF MdeModulePkg/Universal/PCD/Dxe/Pcd.inf

  INF Binaries/amethyst/QcomPkg/Drivers/EnvDxe/EnvDxeEnhanced.inf

  INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/ReportStatusCodeRouterRuntimeDxe.inf
  INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/StatusCodeHandlerRuntimeDxe.inf
  INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
  INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf

  INF Binaries/amethyst/QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf
  INF Binaries/amethyst/QcomPkg/Drivers/TzDxe/ScmDxeCompat.inf
  INF Binaries/amethyst/QcomPkg/Drivers/TzDxe/TzDxeLA.inf

  INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
  INF MdeModulePkg/Universal/Variable/RuntimeDxe/VariableRuntimeDxe.inf
  INF EmbeddedPkg/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
  INF MdeModulePkg/Universal/ResetSystemRuntimeDxe/ResetSystemRuntimeDxe.inf
  INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
  INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  INF ArmPkg/Drivers/ArmGicDxe/ArmGicDxe.inf
  INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf

  INF Binaries/amethyst/QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/HWIODxe/HWIODxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
  # Disabled for bring-up: PmicDxe hits a blocked SPMI channel (0x0C74D008) under Gunyah.
  # INF Binaries/amethyst/QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf

  INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf

  INF Binaries/amethyst/MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  INF Binaries/amethyst/MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  INF MdeModulePkg/Universal/Disk/RamDiskDxe/RamDiskDxe.inf

  INF FatPkg/EnhancedFatDxe/Fat.inf
  INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf

  # Disabled for bring-up: the UFS LUs are stopped after ABL exits (sense 02/04/02) and UFSDxe asserts.
  # INF Binaries/amethyst/QcomPkg/Drivers/UFSDxe/UFSDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/NpaDxe/NpaDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/ULogDxe/ULogDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/VcsDxe/VcsDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/ClockDxe/ClockDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/ICBDxe/ICBDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/SmemDxe/SmemDxe.inf

  INF MdeModulePkg/Universal/BdsDxe/BdsDxe.inf


  INF EmbeddedPkg/SimpleTextInOutSerial/SimpleTextInOutSerial.inf
  INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
  INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf

!if $(USE_CUSTOM_DISPLAY_DRIVER) == 1
  INF Binaries/amethyst/QcomPkg/Drivers/CPRDxe/CPRDxe.inf
!endif
  INF Binaries/amethyst/QcomPkg/Drivers/GpiDxe/GpiDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/SPIDxe/SPIDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/I2CDxe/I2CDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/SdccDxe/SdccDxe.inf
  # Disabled for bring-up: loads TrustZone apps or firmware from partitions, unavailable while UFSDxe is off.
  # INF Binaries/amethyst/QcomPkg/Drivers/FeatureEnablerDxe/FeatureEnablerDxe.inf

!if $(USE_CUSTOM_DISPLAY_DRIVER) == 1
  INF Binaries/amethyst/QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
!else
  INF SiliciumPkg/Drivers/SimpleFbDxe/SimpleFbDxe.inf
!endif

  # Disabled for bring-up: PmicDxe hits a blocked SPMI channel (0x0C74D008) under Gunyah.
  # INF Binaries/amethyst/QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
  # Disabled for bring-up: PmicDxe hits a blocked SPMI channel (0x0C74D008) under Gunyah.
  # INF Binaries/amethyst/QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/Smp2pDxe/Smp2pDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/SSRDxe/SSRDxe.inf
  # Crashes
  # INF Binaries/amethyst/QcomPkg/Drivers/GLinkDxe/GLinkDxe.inf
  # Disabled for bring-up: PmicDxe hits a blocked SPMI channel (0x0C74D008) under Gunyah.
  # INF Binaries/amethyst/QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
  # Disabled for bring-up: PmicDxe hits a blocked SPMI channel (0x0C74D008) under Gunyah.
  # INF Binaries/amethyst/QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/TsensDxe/TsensDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/LimitsDxe/LimitsDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/XhciDxe/XhciDxe.inf

  INF MdeModulePkg/Bus/Usb/UsbBusDxe/UsbBusDxe.inf
  INF MdeModulePkg/Bus/Usb/UsbKbDxe/UsbKbDxe.inf
  INF MdeModulePkg/Bus/Usb/UsbMassStorageDxe/UsbMassStorageDxe.inf

  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/UsbMsdDxe/UsbMsdDxe.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/UsbDeviceDxe/UsbDeviceDxe.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/UsbConfigDxe/UsbConfigDxe.inf
  # Disabled for bring-up: without PmicDxe, UsbConfigDxe falls back to an unknown platform and faults on 0x221C8300.
  # INF Binaries/amethyst/QcomPkg/Drivers/UsbInitDxe/UsbInitDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/UCDxe/UCDxe.inf
  INF Binaries/amethyst/QcomPkg/Drivers/RNGDxe/RngDxe.inf
  # Disabled for bring-up: loads TrustZone apps or firmware from partitions, unavailable while UFSDxe is off.
  # INF Binaries/amethyst/QcomPkg/Drivers/PILDxe/PILDxe.inf
  # Disabled for bring-up: loads TrustZone apps or firmware from partitions, unavailable while UFSDxe is off.
  # INF Binaries/amethyst/QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
