# amethyst bring-up (Xiaomi Phone (3a), SM7635)

Not a ready-to-flash image. Everything here has been booted only from RAM with `fastboot boot`.

## Origin

- **SoC.** SM7635 ("Volcano"; Qualcomm's UEFI package name is `MilosLAA`). Its UEFI comes from the Lanai (SM8650)
  boot branch: `BOOT.MXF.2.1-01955-LANAI-1.88923.2`. `VolcanoPkg` therefore follows `LanaiPkg`: same GIC map,
  and Lanai's SEC library is reused. It differs in the 3 CPU clusters, ACPI and SMBIOS.
- **Device package.** `amethystPkg` started from OnePlus `giuliaPkg` (SM8650). Its include lists are giulia's
  curated lists, retargeted to the phone's own drivers: 53 of 55 vendor DXEs present; `OplusProject` and `RscDxe`
  dropped.
- **Memory map.** `Library/MemoryMapLib/MemoryMapLib.c` is generated from the phone's XBL config device tree
  (`/soc/memorymap` and `/soc/registermap`, compatible `qcom,uefimem`). The generator's value mapping was learned
  from giulia. The vendor's 4 MiB `UEFI_FD` at 0xA7000000 is split as on giulia: a 1 MiB `FD_Reserved`, then the
  3 MiB FD at 0xA7100000.
- **Configuration map.** Identical to giulia's; the phone's `uefiplat.cfg` has the same hardware values.
- **Boot shim.** `BootShim/BootShim.S` is uefi-sheng's (UniXNU): the header's image size covers shim plus FD, and
  the caches are cleaned before the jump. UniXNU's `bootimg` requires it.
- **Boot image.** Header v4, os_version 17.0.0 and patch 2026-08, matching the phone's own `boot.img`.

Vendor binaries are not in this repository. They come from the phone's own `uefi` partition (UEFIReader) and go
into `Binaries/amethyst`, kept locally.

## State (2026-10-22)

- Mu-Silicium DEBUG build: display correct (1080x2392, 32 bpp, `Display_Reserved` 0xE3940000), DXE through BDS.
- With UniXNU (built by `unixnu build firmware`, see rootstockos/UniXNU-amethyst): the UniXNU menu shows and
  stays up.

Bring-up changes in `Include/APRIORI.inc` and `Include/DXE.inc`, each commented at its line:

| Driver(s) | State | Why |
|---|---|---|
| `SPMIDxe`, `ClockDxe` | giulia's binary patches applied locally (`*.patched.efi`) | identical code in the 01955 build |
| `PmicDxe` and consumers (charger, `ChargerEx`, `PmicGlink`, `Buttons`) | disabled | external abort on SPMI channel 0x0C74D008 under Gunyah |
| `UFSDxe` | disabled | LUs stopped after ABL exit (sense 02/04/02); giulia's sleep → wakeup patch does not carry over to 01955 |
| `FeatureEnablerDxe`, `PILProxyDxe`, `PILDxe` | disabled | load TrustZone apps and firmware from partitions |
| vendor USB stack | disabled | `UsbConfigDxe` faults on 0x221C8300 from a timer once it can't identify the PMIC |

Keys: `Drivers/ShengKeyInputDxe`, taken unchanged from uefi-sheng (the 3a's key registers are the same; see its
README.md). It reads the keys over SPMI (`core` and `obsrvr` windows) and publishes ConIn: volume up/down = Up/Down,
power = Enter. Tested in the UniXNU menu. Without it there's no input device, and UniXNU's idle rotation moves the
highlight every two seconds.
