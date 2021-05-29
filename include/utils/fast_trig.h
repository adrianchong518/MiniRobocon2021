/*
 * cos_fast.h: Fixed-point cos() and sin() functions, based on a sixth
 * degree polynomial approximation.
 *
 * argument is in units of 2*M_PI/2^16.
 * result is in units of 1/2^14 (range = [-2^14 : 2^14]).
 *
 * The cosine function uses an even-polynomial approximation of
 * cos(M_PI/2*x) for x in [0:1], and symmetries when x is outside [0:1].
 * Sine is defined as sin(x) = cos(3*M_PI/2+x).
 */

#pragma once
#include <stdint.h>

#define FAST_TRIG_RAD_TO_UINT 10430.37835047
#define FAST_TRIG_UINT_TO_RAD 0.00009587379
#define FAST_TRIG_RETURN_TO_RESULT 0.00005940358
#define FAST_TRIG_ATAN2_SCALING 32767

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Sixth degree polynomial:
 *      cos(M_PI/2*x) ~ (1 - x^2)*(1 - x^2*(0.23352 - 0.019531*x^2))
 * for x in [0:1]. Max error = 9.53e-5
 */
int16_t cos_fast(uint16_t x);

/*
 * Fixed point sin().
 */
static inline int16_t sin_fast(uint16_t x) { return cos_fast(0xc000 + x); }

/*
 * Fixed point atan() function: sixth degree polynomial approximation.
 *
 * argument is in units of 1/2^15 (range = [0 : 2^15]).
 * result is in units of 2*M_PI/2^16 (range = [0 : 2^13]).
 *
 * Uses the approximation
 *      atan(x) ~ M_PI/4 * P(x), with
 *      P(x) = x * (1 + (1 - x) * Q(x))
 *      Q(x) = 0.271553 + x*(0.299045 + x*(-0.270519 + x*0.0625))
 * for x in [0 : 1]. Max error = 1.31e-4
 */
uint16_t atan_fast(uint16_t x);

/*
 * Fixed point atan2().
 *
 * arguments are in arbitrary units, as long as they have the *same*
 * unit, range is [-32767 : +32767], -32768 does *not* work!
 * result is in units of 2*M_PI/2^16 (range = [0 : 2^13]).
 *
 * Reduces the argument to the first octant and calculates atan(y/x).
 * The octants are numbered, CCW: 0, 1, 5, 4, 6, 7, 3, 2.
 */
uint16_t atan2_fast(int16_t y, int16_t x);
#ifdef __cplusplus
}
#endif