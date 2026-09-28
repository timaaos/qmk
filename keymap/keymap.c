 /* Copyright 2020 Naoki Katahira
  *
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 2 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

#include QMK_KEYBOARD_H
#include <stdio.h>

// Layers 0-3 imported from "voskhod lily58.vil" (Vial export):
// 0 = QWERTY, 1 = Colemak-DH, 2 = Lower (MO(2), left thumb), 3 = Raise (MO(3), right thumb).
// Layer 4 = Game, layer 5 = Media — empty (transparent) for now, editable live in Vial.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
    KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,   KC_EQL,
    KC_ESC,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_LBRC,
    KC_TAB,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_RBRC,
   KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,   KC_DEL,  KC_MINS,     KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_QUOT,
   KC_LGUI,  KC_LCTL,    MO(2),   KC_SPC,   KC_ENT,    MO(3),  KC_BSPC,  KC_LALT
),

[1] = LAYOUT(
    KC_GRV,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,   KC_EQL,
    KC_ESC,     KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_J,     KC_L,     KC_U,     KC_Y,  KC_SCLN,  KC_LBRC,
    KC_TAB,     KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_M,     KC_N,     KC_E,     KC_I,     KC_O,  KC_RBRC,
   KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,   KC_DEL,  KC_MINS,     KC_K,     KC_H,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_QUOT,
   KC_LGUI,  KC_LCTL,    MO(2),   KC_SPC,   KC_ENT,    MO(3),  KC_BSPC,  KC_LALT
),

[2] = LAYOUT(
    KC_F12,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,
    KC_ESC,  KC_MINS, LSFT(KC_3), LSFT(KC_4), LSFT(KC_6), LSFT(KC_MINUS),  KC_MINS,     KC_7,     KC_8,     KC_9,  KC_PPLS,  KC_CALC,
    KC_TAB, LSFT(KC_2), LSFT(KC_1), LSFT(KC_7), LSFT(KC_9), LSFT(KC_0),  KC_PAST,     KC_4,     KC_5,     KC_6,     KC_0,  KC_PEQL,
   KC_LSFT,  KC_UNDO,   KC_CUT,  KC_COPY,  KC_PSTE,  KC_BSLS,  _______,  _______,  KC_PSLS,     KC_1,     KC_2,     KC_3,  KC_PDOT,  KC_LCTL,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

[3] = LAYOUT(
   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
   XXXXXXX,  XXXXXXX,  XXXXXXX,   KC_NUM,   KC_INS,  KC_CAPS,  KC_WH_U,  KC_HOME,    KC_UP,   KC_END,  KC_BSPC,  XXXXXXX,
   _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_WH_D,  KC_LEFT,  KC_DOWN, KC_RIGHT,  KC_PGUP,  KC_PSCR,
   _______,  XXXXXXX,  KC_VOLD,  KC_MUTE,  KC_VOLU,  XXXXXXX,  _______,  XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_PGDN,  XXXXXXX,
   _______,  _______,  _______,  _______,  _______,  _______,  KC_BSPC,  KC_LALT
),

[4] = LAYOUT(
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

[5] = LAYOUT(
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
),

};

#ifdef OLED_ENABLE

#include "logo.h"

static void print_status_narrow(void) {
  // Print current mode
  oled_write_P(PSTR("\n\n"), false);

  switch (get_highest_layer(layer_state)) {
      case 0:
          oled_write_ln_P(PSTR("Qwrt"), false);
          break;
      case 1:
          oled_write_ln_P(PSTR("Clmk"), false);
          break;
      default:
          oled_write_P(PSTR("Mod\n"), false);
          break;
  }
  oled_write_P(PSTR("\n\n"), false);
  // Print current layer
  oled_write_ln_P(PSTR("LAYER"), false);
  switch (get_highest_layer(layer_state)) {
      case 0:
      case 1:
          oled_write_P(PSTR("Base\n"), false);
          break;
      case 2:
          oled_write_P(PSTR("Lower"), false);
          break;
      case 3:
          oled_write_P(PSTR("Raise"), false);
          break;
      case 4:
          oled_write_P(PSTR("Game "), false);
          break;
      case 5:
          oled_write_P(PSTR("Media"), false);
          break;
      default:
          oled_write_ln_P(PSTR("Undef"), false);
  }
  // CapsLock status at the very bottom of the 16-line display.
  led_t led_usb_state = host_keyboard_led_state();
  oled_set_cursor(0, 14);
  oled_write_P(PSTR("CAPS"), false);
  oled_set_cursor(0, 15);
  oled_write_P(led_usb_state.caps_lock ? PSTR("ON ") : PSTR("OFF"), false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // Both halves are mounted vertically: rotate both.
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
      print_status_narrow();
  } else {
      oled_write_raw_P(lily58_logo, LOGO_BYTES);
  }
return false;
}

#endif

