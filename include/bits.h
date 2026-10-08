/*
 * bits.h - helpers for reading and changing bits in a 32-bit register value.
 *
 * Every function takes a value and returns a new one. None of them touch
 * hardware, so they can be tested on a laptop (see test_bits.c).
 *
 * Bit positions (n) and shifts must be in the range 0..31.
 */
#ifndef BITS_H
#define BITS_H

#include <stdbool.h>
#include <stdint.h>

/* Return value with bit n set to 1. */
static inline uint32_t bit_set(uint32_t value, unsigned n)
{
    return value | (UINT32_C(1) << n);
}

/* Return value with bit n cleared to 0. */
static inline uint32_t bit_clear(uint32_t value, unsigned n)
{
    return value & ~(UINT32_C(1) << n);
}

/* Return value with bit n flipped. */
static inline uint32_t bit_toggle(uint32_t value, unsigned n)
{
    return value ^ (UINT32_C(1) << n);
}

/* Return true if bit n of value is 1. */
static inline bool bit_is_set(uint32_t value, unsigned n)
{
    return (value & (UINT32_C(1) << n)) != 0;
}

/*
 * A field is a group of adjacent bits.
 *   mask  - the field's bits, already in position (0xF0 for bits 7..4)
 *   shift - the position of the field's lowest bit (4 for bits 7..4)
 */

/* Return the field's contents, shifted down so its lowest bit is bit 0. */
static inline uint32_t field_get(uint32_t value, uint32_t mask, unsigned shift)
{
    return (value & mask) >> shift;
}

/*
 * Return value with the field replaced by `field`. All other bits are left
 * unchanged, and any bits of `field` too wide for the mask are discarded.
 */
static inline uint32_t field_set(uint32_t value, uint32_t mask, unsigned shift,
                                 uint32_t field)
{
    return (value & ~mask) | ((field << shift) & mask);
}

#endif /* BITS_H */
