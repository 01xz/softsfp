#include "round.h"
#include "utils.h"

unpacked_t us_round_toward_zero(unpacked_t us, int fs)
{
    us.frac = LMASK(us.frac, fs);
    return us;
}

unpacked_t us_round_upward(unpacked_t us, int fs)
{
    if (LSHIFT(us.frac, fs) == SFP_ZERO) {
        return us;
    }

    if (us.sign) {
        return us_round_toward_zero(us, fs);
    }

    SFP_LUTYPE frac = HIDDEN_BIT(us.frac);
    frac = frac + RSHIFT(SFP_MSB, fs);

    if (RSHIFT(frac, SFP_WIDTH) != 0) {
        us.exp++;
        frac = RSHIFT(frac, 1);
    }

    us.frac = LSHIFT(frac, 1);
    return us_round_toward_zero(us, fs);
}

unpacked_t us_round_downward(unpacked_t us, int fs)
{
    us.sign = !us.sign;
    unpacked_t r = us_round_upward(us, fs);
    r.sign = !r.sign;
    return r;
}

unpacked_t us_round_nearest_awayzero(unpacked_t us, int fs)
{
    SFP_LUTYPE frac = HIDDEN_BIT(us.frac);
    frac = frac + RSHIFT(SFP_MSB, fs + 1);

    if (RSHIFT(frac, SFP_WIDTH) != 0) {
        us.exp++;
        frac = RSHIFT(frac, 1);
    }

    us.frac = LSHIFT(frac, 1);
    return us_round_toward_zero(us, fs);
}

unpacked_t us_round_nearest_even(unpacked_t us, int fs)
{

}

unpacked_t us_round(unpacked_t us, int fs, ROUND_MODE mode)
{
    switch (mode) {
    case TONEAREST:
        return us_round_nearest_awayzero(us, fs);
        break;
    case TONEAREST_EVEN:
        return us_round_nearest_even(us, fs);
        break;
    case TOWARDZERO:
        return us_round_toward_zero(us, fs);
        break;
    case UPWARD:
        return us_round_upward(us, fs);
        break;
    case DOWNWARD:
        return us_round_downward(us, fs);
        break;
    default:
        return us_round_nearest_awayzero(us, fs);
        break;
    }
}
