#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _RAISE,
  _LOWER,
  _FN,
};

#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)
#define FN      MO(_FN)
#define TGLOWER TG(LOWER)
#define TGRAISE TG(_RAISE)
#define RALTDEL RALT_T(KC_DEL)

static bool is_ctl_pressed;
static bool is_esc_pressed;
static bool is_bspc_pressed;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    KC_ESC, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_TAB, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_UP,  KC_SLSH,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_LCTL,KC_LGUI,KC_LALT,FN,     LOWER,  KC_SPC, KC_SPC, RAISE,  RALTDEL,KC_LEFT,KC_DOWN,KC_RGHT
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
), 

[_LOWER] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    KC_TILD,KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_VOLD,KC_MUTE,KC_VOLU,KC_HOME,KC_PGUP,KC_LCBR,KC_RCBR,KC_PIPE,KC_DQUO,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_MPRV,KC_MPLY,KC_MNXT,KC_END, KC_PGDN,KC_UNDS,KC_PLUS,KC_WH_U,KC_BTN1,KC_MS_U,KC_BTN2,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,KC_WH_D,KC_MS_L,KC_MS_D,KC_MS_R
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_RAISE] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   _______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    KC_CAPS,_______,_______,_______,_______,_______,KC_LBRC,KC_RBRC,KC_BSLS,KC_QUOT,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,DM_REC1,DM_REC2,DM_RSTP,DM_PLY1,DM_PLY2,KC_MINS,KC_EQL, _______,_______,_______,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),

[_FN] = LAYOUT_ortho_4x12 (
// ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┐
    _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_PSCR,KC_INS, KC_P7,  KC_P8,  KC_P9,  KC_PMNS,_______,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_SLCK,KC_APP, KC_P4,  KC_P5,  KC_P6,  KC_PPLS,KC_PENT,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,KC_F9,  KC_F10, KC_F11, KC_F12, KC_PAUS,KC_NLCK,KC_P1,  KC_P2,  KC_P3,  KC_PAST,KC_PSLS,
// ├───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┼───────┤
    _______,_______,_______,_______,TGLOWER,_______,_______,TGRAISE,KC_P0,  KC_PDOT,KC_LPRN,KC_RPRN
// └───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┴───────┘
),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef JOTANCK_LEDS
  writePin(JOTANCK_LED1, (get_highest_layer(state) == _LOWER));
  writePin(JOTANCK_LED2, (get_highest_layer(state) == _RAISE));
  #endif
  return state;
}

bool led_update_user(led_t led_state) {
  // NumLock allways on
  if (!led_state.num_lock) {
    tap_code(KC_NUMLOCK);
  }
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) { 
    case KC_LCTL:
      is_ctl_pressed = record->event.pressed;
      break;
    case KC_ESC:
      is_esc_pressed = record->event.pressed;
      break;
    case KC_BSPC:
      is_bspc_pressed = record->event.pressed;
      break;
  };
  return true;
}

void matrix_scan_user(void) {
  if (is_ctl_pressed && is_esc_pressed && is_bspc_pressed) {
    reset_keyboard();
  }
}
