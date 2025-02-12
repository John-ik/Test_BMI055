#pragma once

#define bit_mask(bits, mask) ( bits & mask )

#define bit_set(bits, x) ( bits |= x )

#define bit_clear(bits, x) ( bits &= ~(x) )

#define bit_read(bits, x) ( bits & x )

#define bit_write(bits, x, v) ( v ? bit_set(bits, x) : bit_clear(bits, x) )
