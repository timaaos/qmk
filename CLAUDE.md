# My Lily58 Vial keymap

## Hardware
- Lily58 split keyboard ("Восход Клавиатуры" build), identical to QMK's `lily58/rev1`.
- Controllers: RP2040 Pro Micro–compatible boards (16 MB flash), 3.3 V.
- One 128x32 OLED per half, mounted vertically (`OLED_ROTATION_270`).
- Halves connected by a TRRS cable. Never plug/unplug it while USB is connected.
- Future plan: add a trackpad (likely Cirque Pinnacle over I2C, sharing the bus with the OLED).

## Firmware
- Uses **Vial** and must stay Vial-compatible. The user remaps keys in the Vial app and keeps a saved `.vil` layout.
- This repo holds only the keymap (`keymap/`) plus a GitHub Actions workflow. There is no QMK source in the repo, by design. Do not turn this into a full fork.
- The build downloads official `vial-kb/vial-qmk`, pinned to commit `d2e952ee92b58fe6a6ea571e137e6fc33e1fead4`. It copies `keymap/` to `keyboards/lily58/keymaps/mine` and builds:
  ```
  make lily58/rev1:mine CONVERT_TO=rp2040_ce EXTRAFLAGS=-DINIT_EE_HANDS_LEFT   # left half
  make lily58/rev1:mine CONVERT_TO=rp2040_ce EXTRAFLAGS=-DINIT_EE_HANDS_RIGHT  # right half
  ```
  Delete `.build` between the two builds.
- Handedness is `EE_HANDS`: each half gets its own `.uf2` (left/right), after which USB can go into either half.
- The pinned vial-qmk version uses older keycode names (e.g. `KC_WH_U`, `TAPPING_FORCE_HOLD`). Don't "modernize" them to mainline QMK names unless the pinned commit changes.
- Keep `VIAL_KEYBOARD_UID` in `config.h` unchanged, so the saved `.vil` keeps loading.

## Files in `keymap/`
- `keymap.c`: layers 0–5 (0 QWERTY, 1 Colemak, 2 Lower, 3 Raise, 4 Game, 5 Media) and all OLED code at the bottom.
  - Master (USB) half: layer name + Caps Lock status.
  - Other half: static classic Lily58 logo (flower + wordmark), no WPM/Num Lock.
- `logo.h`: 32x128 static Lily58 logo bitmap for the rotated OLED.
- `config.h`, `rules.mk`: Vial settings, `EE_HANDS`, LTO.
- `vial.json`: layout definition for the Vial app.

## Flashing
- `scripts/flash.sh`: downloads the latest successful CI build (`gh run download`) and walks through flashing both halves (waits for the `RPI-RP2` drive, copies the matching `.uf2`). Requires `gh` authenticated against this repo.
- Manual alternative: enter bootloader mode by double-tapping the reset button; an `RPI-RP2` drive appears.
- Copy the matching `.uf2` onto that drive; the half reboots automatically.
- Then load the saved `.vil` in Vial (File → Load saved layout) if the remaps were reset.

## User environment
- NixOS. Prefer `nix-shell -p ...` for temporary tools instead of changing the system config.
- For local builds, the toolchain needs `gcc-arm-embedded` (arm-none-eabi-gcc), Python with `qmk` and vial-qmk's `requirements.txt`, and `QMK_HOME` pointing at the vial-qmk checkout.
