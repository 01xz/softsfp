#ifndef __SFP_ROUND_H
#define __SFP_ROUND_H

#ifdef __cplusplus
extern "C" {
#endif

#include "pack.h"
#include "sfp_types.h"

typedef enum {
    TONEAREST,
    TONEAREST_EVEN,
    TOWARDZERO,
    UPWARD,
    DOWNWARD
} ROUND_MODE;

#ifndef DEFAULT_ROUND_MODE
#define DEFAULT_ROUND_MODE TONEAREST
#endif

unpacked_t us_round(unpacked_t us, int fs, ROUND_MODE mode);

#ifdef __cplusplus
}
#endif

#endif
