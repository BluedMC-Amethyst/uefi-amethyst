# ShengKeyInputDxe (from UniXNU/uefi-sheng)

Copied unchanged from `Platforms/Xiaomi/shengPkg/Drivers/ShengKeyInputDxe` in UniXNU/uefi-sheng
(BSD-2-Clause-Patent). It reads the power and volume keys straight from the PMIC over SPMI, through the arbiter's
`core` (0x0C400000) and `obsrvr` (0x0C440000) windows, and publishes a SimpleTextIn device with a device path in
ConIn. The vendor PMIC/Buttons stack isn't needed.

On the Nothing Phone (3a) the key wiring matches sheng's register for register (from the phone's live device tree):

| Key | Location | Matches sheng's |
|---|---|---|
| Power | PMK8550, SID 0, PON (`pon_hlos@1300`), KPDPWR bit 7 | yes |
| Volume down | same PON register, RESIN bit 6 | yes |
| Volume up | PMXR2230, SID 1, GPIO 6 (`pinctrl@8800`, PPID 0x18d), active low | yes |

Both windows are among the SPMI regions the phone's own Linux is given. The external abort that disabled PmicDxe
was in the `chnls` window, which this driver doesn't use.
