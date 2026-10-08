/*
 * Laptop tests for bits.h. No board needed.
 *
 *   gcc -std=c11 -Wall -Wextra -Iinclude test/test_bits.c -o test_bits
 *   ./test_bits
 *
 * A failed assert stops the program and prints the file and line.
 */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "bits.h"

static void test_bit_set(void)
{
    assert(bit_set(0x00000000u, 0) == 0x00000001u);
    assert(bit_set(0x00000000u, 31) == 0x80000000u);
    assert(bit_set(0x00000008u, 3) == 0x00000008u);   /* already set */
    assert(bit_set(0x0000000Fu, 6) == 0x0000004Fu);   /* others untouched */
}

static void test_bit_clear(void)
{
    assert(bit_clear(0x000000FFu, 0) == 0x000000FEu);
    assert(bit_clear(0xFFFFFFFFu, 31) == 0x7FFFFFFFu);
    assert(bit_clear(0x000000FEu, 0) == 0x000000FEu); /* already clear */
}

static void test_bit_toggle(void)
{
    assert(bit_toggle(0x00000000u, 0) == 0x00000001u);
    assert(bit_toggle(0x00000001u, 0) == 0x00000000u);
    assert(bit_toggle(0x00000000u, 31) == 0x80000000u);
    assert(bit_toggle(0x80000000u, 31) == 0x00000000u);
}

static void test_bit_is_set(void)
{
    assert(bit_is_set(0x00000001u, 0));
    assert(bit_is_set(0x80000000u, 31));
    assert(bit_is_set(0x00000010u, 4));
    assert(!bit_is_set(0x00000010u, 3));
    assert(!bit_is_set(0x7FFFFFFFu, 31));
}

static void test_field_get(void)
{
    /* bits 7..4 of 0xA5 are 0xA */
    assert(field_get(0x000000A5u, 0x000000F0u, 4) == 0xAu);
    /* bits 3..0 of 0xA5 are 0x5 */
    assert(field_get(0x000000A5u, 0x0000000Fu, 0) == 0x5u);
    /* a field in the top byte, with other bits set around it */
    assert(field_get(0x12FFFFFFu, 0xFF000000u, 24) == 0x12u);
}

static void test_field_set(void)
{
    /* replace bits 7..4, keep bits 3..0 */
    assert(field_set(0x000000A5u, 0x000000F0u, 4, 0x3u) == 0x00000035u);
    /* surrounding bits are left alone */
    assert(field_set(0xFFFFFFFFu, 0x000000F0u, 4, 0x0u) == 0xFFFFFF0Fu);
    /* a field in the top byte */
    assert(field_set(0x00FFFFFFu, 0xFF000000u, 24, 0x12u) == 0x12FFFFFFu);
    /* a value too wide for the field must not spill into its neighbours */
    assert(field_set(0x00000000u, 0x000000F0u, 4, 0xFFu) == 0x000000F0u);
}

static void test_set_then_get(void)
{
    uint32_t value = field_set(0xDEADBEEFu, 0x00000F00u, 8, 0x7u);
    assert(field_get(value, 0x00000F00u, 8) == 0x7u);
}

int main(void)
{
    test_bit_set();
    test_bit_clear();
    test_bit_toggle();
    test_bit_is_set();
    test_field_get();
    test_field_set();
    test_set_then_get();

    printf("All bit helper tests passed.\n");
    return 0;
}
