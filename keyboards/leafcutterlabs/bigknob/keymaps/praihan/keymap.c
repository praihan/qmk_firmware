/* Copyright 2021 Craig Gardner 
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

#define _MAIN 0

#define REVERSE_ROTARY 0
#define REVERSE_ORIENTATION 1

// #define TAP_CODE_DELAY 50
// #define tap_code(keycode) tap_code_delay(keycode, TAP_CODE_DELAY)

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
    if (clockwise ^ REVERSE_ROTARY) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  }
  return true;
}

enum custom_keycodes {
  CUSTOM_KC_1 = SAFE_RANGE,
  CUSTOM_KC_2,
  CUSTOM_KC_3,
  CUSTOM_KC_4,
};

static void send_kvm_command(uint16_t custom_keycode) {
  uint16_t key_index = custom_keycode - CUSTOM_KC_1;
  tap_code(KC_SCROLLLOCK);
  tap_code_delay(KC_SCROLLLOCK, 50);
  tap_code_delay(KC_1 + key_index, 100);
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
  case CUSTOM_KC_1 ... CUSTOM_KC_4:
    if (!record->event.pressed) {
      // on release
      send_kvm_command(keycode);
    }
  }
  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_MAIN] = LAYOUT(
    KC_MUTE,
#if REVERSE_ORIENTATION
    CUSTOM_KC_4, CUSTOM_KC_3, CUSTOM_KC_2, CUSTOM_KC_1
#else
    CUSTOM_KC_1, CUSTOM_KC_2, CUSTOM_KC_3, CUSTOM_KC_4
#endif
  )
};
