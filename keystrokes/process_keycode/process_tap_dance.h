#ifndef PROCESS_TAP_DANCE_H
#define PROCESS_TAP_DANCE_H

#ifdef TAP_DANCE_ENABLE

#include <stdbool.h>
#include <inttypes.h>

typedef struct
{
  uint8_t count;
  uint16_t keycode;
  uint16_t timer;
} kk_tap_dance_state_t;

#define TD(n) (KK_TAP_DANCE + n)

typedef enum
{
  KK_TAP_DANCE_TYPE_PAIR,
  KK_TAP_DANCE_TYPE_FN,
} kk_tap_dance_type_t;

typedef void (*kk_tap_dance_user_fn_t) (kk_tap_dance_state_t *state);

typedef struct
{
  kk_tap_dance_type_t type;
  union {
    struct {
      uint16_t kc1;
      uint16_t kc2;
    } pair;
    kk_tap_dance_user_fn_t fn;
  };
} kk_tap_dance_action_t;

#define ACTION_TAP_DANCE_DOUBLE(kc1, kc2) { \
    .type = KK_TAP_DANCE_TYPE_PAIR,         \
    .pair = { kc1, kc2 }                    \
  }

#define ACTION_TAP_DANCE_FN(user_fn) { \
    .type = KK_TAP_DANCE_TYPE_FN, \
    .fn = user_fn                 \
  }

extern const kk_tap_dance_action_t tap_dance_actions[];

/* To be used internally */

bool process_tap_dance(uint16_t keycode, keyrecord_t *record);
void matrix_scan_tap_dance (void);
void reset_tap_dance (kk_tap_dance_state_t *state);

#else

#define TD(n) KC_NO

#endif

#endif
