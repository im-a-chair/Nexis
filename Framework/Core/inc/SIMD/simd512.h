#ifndef _NXS_SIMD512_H_
#define _NXS_SIMD512_H_
#include "std.h"
#include "SIMD/simd.h"

//blend/select (use or ignore values based on bitmap)

/** nxis_blend_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_blend_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b, const nxis_mask64_t m) {
    return;
}

/** nxis_blend_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_blend_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b, const nxis_mask64_t m) {
    return;
}

/** nxis_blend_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_blend_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b, const nxis_mask32_t m) {
    return;
}

/** nxis_blend_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_blend_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b, const nxis_mask32_t m) {
    return;
}

/** nxis_blend_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_blend_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b, const nxis_mask16_t m) {
    return;
}

/** nxis_blend_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_blend_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b, const nxis_mask16_t m) {
    return;
}

/** nxis_blend_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_blend_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b, const nxis_mask8_t m) {
    return;
}

/** nxis_blend_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_blend_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b, const nxis_mask8_t m) {
    return;
}

/** nxis_blend_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_blend_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b, const nxis_mask32_t m) {
    return;
}

/** nxis_blend_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_blend_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b, const nxis_mask16_t m) {
    return;
}

/** nxis_blend_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_blend_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b, const nxis_mask8_t m) {
    return;
}

//Round

/** nxis_trunc_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_trunc_float16x32(const nxis_float16x32_t n) {
    return;
}

/** nxis_ceil_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_ceil_float16x32(const nxis_float16x32_t n) {
    return;
}

/** nxis_floor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_floor_float16x32(const nxis_float16x32_t n) {
    return;
}

/** nxis_trunc_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_trunc_float32x16(const nxis_float32x16_t n) {
    return;
}

/** nxis_ceil_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_ceil_float32x16(const nxis_float32x16_t n) {
    return;
}

/** nxis_floor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_floor_float32x16(const nxis_float32x16_t n) {
    return;
}

/** nxis_trunc_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_trunc_float64x8(const nxis_float64x8_t n) {
    return;
}

/** nxis_ceil_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_ceil_float64x8(const nxis_float64x8_t n) {
    return;
}

/** nxis_floor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_floor_float64x8(const nxis_float64x8_t n) {
    return;
}

//load (from array or &struct, i.e. pointer)

/** nxis_load_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_load_int8x64(const nxis_int8_t* restrict in) {
    return;
}

/** nxis_load_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_load_uint8x64(const nxis_uint8_t* restrict in) {
    return;
}

/** nxis_load_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_load_int16x32(const nxis_int16_t* restrict in) {
    return;
}

/** nxis_load_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_load_uint16x32(const nxis_uint16_t* restrict in) {
    return;
}

/** nxis_load_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_load_int32x16(const nxis_int32_t* restrict in) {
    return;
}

/** nxis_load_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_load_uint32x16(const nxis_uint32_t* restrict in) {
    return;
}

/** nxis_load_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_load_int64x8(const nxis_int64_t* restrict in) {
    return;
}

/** nxis_load_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_load_uint64x8(const nxis_uint64_t* restrict in) {
    return;
}

/** nxis_load_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_load_float16x32(const nxis_float16_t* restrict in) {
    return;
}

/** nxis_load_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_load_float32x16(const nxis_float32_t* restrict in) {
    return;
}

/** nxis_load_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_load_float64x8(const nxis_float64_t* restrict in) {
    return;
}

//load (from aligned array or &struct, i.e. pointer, but aligned)

/** nxis_load_aligned_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_load_aligned_int8x64(const nxis_int8_t* restrict in) {
    return;
}

/** nxis_load_aligned_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_load_aligned_uint8x64(const nxis_uint8_t* restrict in) {
    return;
}

/** nxis_load_aligned_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_load_aligned_int16x32(const nxis_int16_t* restrict in) {
    return;
}

/** nxis_load_aligned_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_load_aligned_uint16x32(const nxis_uint16_t* restrict in) {
    return;
}

/** nxis_load_aligned_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_load_aligned_int32x16(const nxis_int32_t* restrict in) {
    return;
}

/** nxis_load_aligned_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_load_aligned_uint32x16(const nxis_uint32_t* restrict in) {
    return;
}

/** nxis_load_aligned_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_load_aligned_int64x8(const nxis_int64_t* restrict in) {
    return;
}

/** nxis_load_aligned_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_load_aligned_uint64x8(const nxis_uint64_t* restrict in) {
    return;
}

/** nxis_load_aligned_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_load_aligned_float16x32(const nxis_float16_t* restrict in) {
    return;
}

/** nxis_load_aligned_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_load_aligned_float32x16(const nxis_float32_t* restrict in) {
    return;
}

/** nxis_load_aligned_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_load_aligned_float64x8(const nxis_float64_t* restrict in) {
    return;
}

//store `v` in array/stuct `n`

/** nxis_store_int8x64
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_int8x64(nxis_int8_t* restrict n, const nxis_int8x64_t v) {
    return;
}

/** nxis_store_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_uint8x64(nxis_uint8_t* restrict n, const nxis_uint8x64_t v) {
    return;
}

/** nxis_store_int16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_int16x32(nxis_int16_t* restrict n, const nxis_int16x32_t v) {
    return;
}

/** nxis_store_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_uint16x32(nxis_uint16_t* restrict n, const nxis_uint16x32_t v) {
    return;
}

/** nxis_store_int32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_int32x16(nxis_int32_t* restrict n, const nxis_int32x16_t v) {
    return;
}

/** nxis_store_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_uint32x16(nxis_uint32_t* restrict n, const nxis_uint32x16_t v) {
    return;
}

/** nxis_store_int64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_int64x8(nxis_int64_t* restrict n, const nxis_int64x8_t v) {
    return;
}

/** nxis_store_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_uint64x8(nxis_uint64_t* restrict n, const nxis_uint64x8_t v) {
    return;
}

/** nxis_store_float16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_float16x32(nxis_float16_t* restrict n, const nxis_float16x32_t v) {
    return;
}

/** nxis_store_float32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_float32x16(nxis_float32_t* restrict n, const nxis_float32x16_t v) {
    return;
}

/** nxis_store_float64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_float64x8(nxis_float64_t* restrict n, const nxis_float64x8_t v) {
    return;
}

//store `v` in aligned array/struct `n`

/** nxis_store_aligned_int8x64
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_int8x64(nxis_int8_t* restrict n, const nxis_int8x64_t v) {
    return;
}

/** nxis_store_aligned_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_uint8x64(nxis_uint8_t* restrict n, const nxis_uint8x64_t v) {
    return;
}

/** nxis_store_aligned_int16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_int16x32(nxis_int16_t* restrict n, const nxis_int16x32_t v) {
    return;
}

/** nxis_store_aligned_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_uint16x32(nxis_uint16_t* restrict n, const nxis_uint16x32_t v) {
    return;
}

/** nxis_store_aligned_int32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_int32x16(nxis_int32_t* restrict n, const nxis_int32x16_t v) {
    return;
}

/** nxis_store_aligned_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_uint32x16(nxis_uint32_t* restrict n, const nxis_uint32x16_t v) {
    return;
}

/** nxis_store_aligned_int64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_int64x8(nxis_int64_t* restrict n, const nxis_int64x8_t v) {
    return;
}

/** nxis_store_aligned_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_uint64x8(nxis_uint64_t* restrict n, const nxis_uint64x8_t v) {
    return;
}

/** nxis_store_aligned_float16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_float16x32(nxis_float16_t* restrict n, const nxis_float16x32_t v) {
    return;
}

/** nxis_store_aligned_float32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_float32x16(nxis_float32_t* restrict n, const nxis_float32x16_t v) {
    return;
}

/** nxis_store_aligned_float64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_store_aligned_float64x8(nxis_float64_t* restrict n, const nxis_float64x8_t v) {
    return;
}

//broadcast `n` to all lanes of `v`; set all lanes of `v` to `n`

/** nxis_broadcast_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_broadcast_int8x64(const nxis_int8x64_t v, const nxis_int8_t n) {
    return;
}

/** nxis_broadcast_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_broadcast_uint8x64(const nxis_uint8x64_t v, const nxis_uint8_t n) {
    return;
}

/** nxis_broadcast_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_broadcast_int16x32(const nxis_int16x32_t v, const nxis_int16_t n) {
    return;
}

/** nxis_broadcast_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_broadcast_uint16x32(const nxis_uint16x32_t v, const nxis_uint16_t n) {
    return;
}

/** nxis_broadcast_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_broadcast_int32x16(const nxis_int32x16_t v, const nxis_int32_t n) {
    return;
}

/** nxis_broadcast_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_broadcast_uint32x16(const nxis_uint32x16_t v, const nxis_uint32_t n) {
    return;
}

/** nxis_broadcast_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_broadcast_int64x8(const nxis_int64x8_t v, const nxis_int64_t n) {
    return;
}

/** nxis_broadcast_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_broadcast_uint64x8(const nxis_uint64x8_t v, const nxis_uint64_t n) {
    return;
}

/** nxis_broadcast_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_broadcast_float16x32(const nxis_float16x32_t v, const nxis_float16x32_t n) {
    return;
}

/** nxis_broadcast_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_broadcast_float32x16(const nxis_float32x16_t v, const nxis_float32x16_t n) {
    return;
}

/** nxis_broadcast_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_broadcast_float64x8(const nxis_float64x8_t v, const nxis_float64_t n) {
    return;
}

//set `lane` of `v` to `value`

/** nxis_set_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_set_int8x64(const nxis_int8x64_t v, const nxis_uint8_t lane, const nxis_int8_t n) {
    return;
}

/** nxis_set_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_set_uint8x64(const nxis_uint8x64_t v, const nxis_uint8_t lane, const nxis_uint8_t n) {
    return;
}

/** nxis_set_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_set_int16x32(const nxis_int16x32_t v, const nxis_uint8_t lane, const nxis_int16_t n) {
    return;
}

/** nxis_set_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_set_uint16x32(const nxis_uint16x32_t v, const nxis_uint8_t lane, const nxis_uint16_t n) {
    return;
}

/** nxis_set_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_set_int32x16(const nxis_int32x16_t v, const nxis_uint8_t lane, const nxis_int32_t n) {
    return;
}

/** nxis_set_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_set_uint32x16(const nxis_uint32x16_t v, const nxis_uint8_t lane, const nxis_uint32_t n) {
    return;
}

/** nxis_set_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_set_int64x8(const nxis_int64x8_t v, const nxis_uint8_t lane, const nxis_int64_t n) {
    return;
}

/** nxis_set_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_set_uint64x8(const nxis_uint64x8_t v, const nxis_uint8_t lane, const nxis_uint64_t n) {
    return;
}

/** nxis_set_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_set_float16x32(const nxis_float16x32_t v, const nxis_uint8_t lane, const nxis_float16x32_t n) {
    return;
}

/** nxis_set_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_set_float32x16(const nxis_float32x16_t v, const nxis_uint8_t lane, const nxis_float32x16_t n) {
    return;
}

/** nxis_set_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_set_float64x8(const nxis_float64x8_t v, const nxis_uint8_t lane, const nxis_float64_t n) {
    return;
}

//unpack/zip (get part of it as smaller value e.g. upper half of __m128i as uint64_t)

/** nxis_interleave_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_interleave_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_interleave_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_interleave_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_interleave_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_interleave_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_interleave_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_interleave_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_interleave_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_interleave_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_interleave_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_interleave_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_interleave_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_interleave_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_interleave_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_interleave_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_interleave_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_interleave_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_interleave_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_interleave_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_interleave_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_interleave_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_gather_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_gather_int8x64(const nxis_int8_t* restrict base, const nxis_int32x16_t offsets[4]) {
    return;
}

/** nxis_gather_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_gather_uint8x64(const nxis_uint8_t* restrict base, const nxis_int32x16_t offsets[4]) {
    return;
}

/** nxis_gather_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_gather_int16x32(const nxis_int16_t* restrict base, const nxis_int32x16_t offsets[2]) {
    return;
}

/** nxis_gather_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_gather_uint16x32(const nxis_uint16_t* restrict base, const nxis_int32x16_t offsets[2]) {
    return;
}

/** nxis_gather_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_gather_int32x16(const nxis_int32_t* restrict base, const nxis_int32x16_t offsets) {
    return;
}

/** nxis_gather_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_gather_uint32x16(const nxis_uint32_t* restrict base, const nxis_int32x16_t offsets) {
    return;
}

/** nxis_gather_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_gather_int64x8(const nxis_int64_t* restrict base, const nxis_int32x8_t offsets) {
    return;
}

/** nxis_gather_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_gather_uint64x8(const nxis_uint64_t* restrict base, const nxis_int32x8_t offsets) {
    return;
}

/** nxis_gather_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_gather_float16x32(const nxis_float16_t* restrict base, const nxis_int32x16_t offsets[2]) {
    return;
}

/** nxis_gather_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_gather_float32x16(const nxis_float32_t* restrict base, const nxis_int32x16_t offsets) {
    return;
}

/** nxis_gather_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_gather_float64x8(const nxis_float64_t* restrict base, const nxis_int32x8_t offsets) {
    return;
}

/** nxis_scatter_int8x64
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_int8x64(const nxis_int8x64_t v, const nxis_int8_t* restrict base, const nxis_int32x16_t offsets[4]) {
    return;
}

/** nxis_scatter_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_uint8x64(const nxis_uint8x64_t v, const nxis_uint8_t* restrict base, const nxis_int32x16_t offsets[4]) {
    return;
}

/** nxis_scatter_int16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_int16x32(const nxis_int16x32_t v, const nxis_int16_t* restrict base, const nxis_int32x16_t offsets[2]) {
    return;
}

/** nxis_scatter_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_uint16x32(const nxis_uint16x32_t v, const nxis_uint16_t* restrict base, const nxis_int32x16_t offsets[2]) {
    return;
}

/** nxis_scatter_int32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_int32x16(const nxis_int32x16_t v, const nxis_int32_t* restrict base, const nxis_int32x16_t offsets) {
    return;
}

/** nxis_scatter_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_uint32x16(const nxis_uint32x16_t v, const nxis_uint32_t* restrict base, const nxis_int32x16_t offsets) {
    return;
}

/** nxis_scatter_int64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_int64x8(const nxis_int64x8_t v, const nxis_int64_t* restrict base, const nxis_int32x8_t offsets) {
    return;
}

/** nxis_scatter_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_uint64x8(const nxis_uint64x8_t v, const nxis_uint64_t* restrict base, const nxis_int32x8_t offsets) {
    return;
}

/** nxis_scatter_float16x32
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_float16x32(const nxis_float16x32_t v, const nxis_float16_t* restrict base, const nxis_int32x16_t offsets[2]) {
    return;
}

/** nxis_scatter_float32x16
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_float32x16(const nxis_float32x16_t v, const nxis_float32_t* restrict base, const nxis_int32x16_t offsets) {
    return;
}

/** nxis_scatter_float64x8
 * TODO:
 */
NXS_STATIC_INLINE void nxis_scatter_float64x8(const nxis_float64x8_t v, const nxis_float64_t* restrict base, const nxis_int32x8_t offsets) {
    return;
}

/** nxis_extract_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_extract_int8x64(const nxis_int8x64_t v, const int lane) {
    return;
}

/** nxis_extract_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8_t nxis_extract_uint8x64(const nxis_uint8x64_t v, const int lane) {
    return;
}

/** nxis_extract_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_extract_int16x32(const nxis_int16x32_t v, const int lane) {
    return;
}

/** nxis_extract_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_extract_uint16x32(const nxis_uint16x32_t v, const int lane) {
    return;
}

/** nxis_extract_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32_t nxis_extract_int32x16(const nxis_int32x16_t v, const int lane) {
    return;
}

/** nxis_extract_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32_t nxis_extract_uint32x16(const nxis_uint32x16_t v, const int lane) {
    return;
}

/** nxis_extract_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64_t nxis_extract_int64x8(const nxis_int64x8_t v, const int lane) {
    return;
}

/** nxis_extract_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64_t nxis_extract_uint64x8(const nxis_uint64x8_t v, const int lane) {
    return;
}

/** nxis_extract_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_extract_float16x32(const nxis_float16x32_t v, const int lane) {
    return;
}

/** nxis_extract_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32_t nxis_extract_float32x16(const nxis_float32x16_t v, const int lane) {
    return;
}

/** nxis_extract_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64_t nxis_extract_float64x8(const nxis_float64x8_t v, const int lane) {
    return;
}

///shuffle/permute/unzip -- implemented in x86 with 2 ops, REMEMBER: to optimize in masked version

/** nxis_permute_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64x2_t nxis_permute_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_permute_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64x2_t nxis_permute_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_permute_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32x2_t nxis_permute_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_permute_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32x2_t nxis_permute_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_permute_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16x2_t nxis_permute_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_permute_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16x2_t nxis_permute_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_permute_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8x2_t nxis_permute_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_permute_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8x2_t nxis_permute_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_permute_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32x2_t nxis_permute_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_permute_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16x2_t nxis_permute_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_permute_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8x2_t nxis_permute_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_add_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_add_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_add_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_add_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_add_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_add_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_add_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_add_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_add_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_add_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_add_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_add_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_add_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_add_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_add_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_add_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_add_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_add_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_add_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_add_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_add_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_add_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_subtract_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_subtract_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_subtract_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_subtract_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_subtract_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_subtract_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_subtract_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_subtract_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_subtract_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_subtract_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_subtract_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_subtract_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_subtract_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_subtract_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_subtract_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_subtract_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_subtract_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_subtract_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_subtract_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_subtract_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_subtract_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_subtract_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_multiply_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_multiply_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_multiply_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_multiply_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_multiply_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_multiply_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_multiply_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_multiply_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_multiply_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_multiply_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_multiply_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_multiply_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_multiply_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_multiply_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_multiply_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_multiply_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_multiply_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_multiply_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_multiply_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_multiply_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_multiply_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_multiply_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_divide_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_divide_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_divide_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_divide_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_divide_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_divide_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_divide_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_divide_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_divide_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_divide_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_divide_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_divide_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_divide_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_divide_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_divide_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_divide_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_divide_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_divide_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_divide_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_divide_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_divide_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_divide_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_absolute_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_absolute_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_absolute_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_absolute_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_absolute_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_absolute_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_absolute_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_absolute_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_absolute_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_absolute_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_absolute_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_absolute_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_absolute_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_absolute_float64x8(const nxis_float64x8_t v) {
    return;
}

//sign -- returns (info on) sign-bit as int

/** nxis_sign_int8x64
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_sign_int16x32
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_sign_int32x16
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_sign_int64x8
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_sign_float16x32
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_sign_float32x16
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_sign_float64x8
 * TODO:
 */
NXS_STATIC_INLINE int nxis_sign_float64x8(const nxis_float64x8_t v) {
    return;
}

//FMA (Fused Multiply Add) `(A * B) + C` (invert B for Fused Divide Add)

/** nxis_fma_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_fma_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b, const nxis_int8x64_t c) {
    return;
}

/** nxis_fma_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_fma_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b, const nxis_uint8x64_t c) {
    return;
}

/** nxis_fma_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_fma_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b, const nxis_int16x32_t c) {
    return;
}

/** nxis_fma_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_fma_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b, const nxis_uint16x32_t c) {
    return;
}

/** nxis_fma_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_fma_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b, const nxis_int32x16_t c) {
    return;
}

/** nxis_fma_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_fma_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b, const nxis_uint32x16_t c) {
    return;
}

/** nxis_fma_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_fma_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b, const nxis_int64x8_t c) {
    return;
}

/** nxis_fma_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_fma_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b, const nxis_uint64x8_t c) {
    return;
}

/** nxis_fma_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_fma_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b, const nxis_float16x32_t c) {
    return;
}

/** nxis_fma_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_fma_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b, const nxis_float32x16_t c) {
    return;
}

/** nxis_fma_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_fma_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b, const nxis_float64x8_t c) {
    return;
}

//FMS (Fused Multiply Subtract) `(A * B) - C` (use reciprecal B for Fused Divide Subtract)

/** nxis_fms_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_fms_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b, const nxis_int8x64_t c) {
    return;
}

/** nxis_fms_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_fms_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b, const nxis_uint8x64_t c) {
    return;
}

/** nxis_fms_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_fms_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b, const nxis_int16x32_t c) {
    return;
}

/** nxis_fms_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_fms_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b, const nxis_uint16x32_t c) {
    return;
}

/** nxis_fms_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_fms_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b, const nxis_int32x16_t c) {
    return;
}

/** nxis_fms_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_fms_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b, const nxis_uint32x16_t c) {
    return;
}

/** nxis_fms_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_fms_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b, const nxis_int64x8_t c) {
    return;
}

/** nxis_fms_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_fms_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b, const nxis_uint64x8_t c) {
    return;
}

/** nxis_fms_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_fms_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b, const nxis_float16x32_t c) {
    return;
}

/** nxis_fms_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_fms_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b, const nxis_float32x16_t c) {
    return;
}

/** nxis_fms_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_fms_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b, const nxis_float64x8_t c) {
    return;
}

//NFMA (Negative Fused Multiply Add) `-(A * B) + C`, use reciprocal B for NFD(ivide)A

/** nxis_nfma_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_nfma_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b, const nxis_int8x64_t c) {
    return;
}

/** nxis_nfma_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_nfma_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b, const nxis_uint8x64_t c) {
    return;
}

/** nxis_nfma_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_nfma_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b, const nxis_int16x32_t c) {
    return;
}

/** nxis_nfma_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_nfma_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b, const nxis_uint16x32_t c) {
    return;
}

/** nxis_nfma_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_nfma_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b, const nxis_int32x16_t c) {
    return;
}

/** nxis_nfma_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_nfma_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b, const nxis_uint32x16_t c) {
    return;
}

/** nxis_nfma_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_nfma_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b, const nxis_int64x8_t c) {
    return;
}

/** nxis_nfma_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_nfma_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b, const nxis_uint64x8_t c) {
    return;
}

/** nxis_nfma_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_nfma_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b, const nxis_float16x32_t c) {
    return;
}

/** nxis_nfma_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_nfma_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b, const nxis_float32x16_t c) {
    return;
}

/** nxis_nfma_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_nfma_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b, const nxis_float64x8_t c) {
    return;
}

//NFMS (Negative Fused Multiply Subtract) `-(A * B) - C`, use reciprocal B for NFD(ivide)S

/** nxis_nfms_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_nfms_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b, const nxis_int8x64_t c) {
    return;
}

/** nxis_nfms_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_nfms_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b, const nxis_uint8x64_t c) {
    return;
}

/** nxis_nfms_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_nfms_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b, const nxis_int16x32_t c) {
    return;
}

/** nxis_nfms_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_nfms_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b, const nxis_uint16x32_t c) {
    return;
}

/** nxis_nfms_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_nfms_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b, const nxis_int32x16_t c) {
    return;
}

/** nxis_nfms_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_nfms_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b, const nxis_uint32x16_t c) {
    return;
}

/** nxis_nfms_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_nfms_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b, const nxis_int64x8_t c) {
    return;
}

/** nxis_nfms_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_nfms_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b, const nxis_uint64x8_t c) {
    return;
}

/** nxis_nfms_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_nfms_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b, const nxis_float16x32_t c) {
    return;
}

/** nxis_nfms_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_nfms_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b, const nxis_float32x16_t c) {
    return;
}

/** nxis_nfms_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_nfms_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b, const nxis_float64x8_t c) {
    return;
}

//inverse/reciprocal (1/x)

/** nxis_reciprocal_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_reciprocal_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_reciprocal_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_reciprocal_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_reciprocal_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_reciprocal_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_reciprocal_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_reciprocal_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_reciprocal_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_reciprocal_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_reciprocal_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_reciprocal_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_reciprocal_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_reciprocal_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_reciprocal_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_reciprocal_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_reciprocal_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_reciprocal_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_reciprocal_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_reciprocal_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_reciprocal_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_reciprocal_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_sqrt_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_sqrt_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_sqrt_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_sqrt_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_sqrt_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_sqrt_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_sqrt_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_sqrt_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_sqrt_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_sqrt_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_sqrt_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_sqrt_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_sqrt_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_sqrt_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_sqrt_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_sqrt_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_sqrt_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_sqrt_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_sqrt_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_sqrt_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_sqrt_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_sqrt_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_rsqrt_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_rsqrt_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_rsqrt_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_rsqrt_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_rsqrt_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_rsqrt_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_rsqrt_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_rsqrt_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_rsqrt_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_rsqrt_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_rsqrt_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_rsqrt_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_rsqrt_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_rsqrt_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_rsqrt_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_rsqrt_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_rsqrt_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_rsqrt_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_rsqrt_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_rsqrt_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_rsqrt_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_rsqrt_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_min_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_min_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_min_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_min_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_min_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_min_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_min_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_min_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_min_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_min_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_min_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_min_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_min_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_min_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_min_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_min_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_min_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_min_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_min_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_min_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_min_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_min_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_max_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_max_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_max_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_max_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_max_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_max_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_max_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_max_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_max_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_max_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_max_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_max_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_max_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_max_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_max_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_max_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_max_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_max_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_max_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_max_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_max_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_max_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_add_hor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_add_hor_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_add_hor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8_t nxis_add_hor_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_add_hor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_add_hor_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_add_hor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_add_hor_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_add_hor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32_t nxis_add_hor_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_add_hor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32_t nxis_add_hor_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_add_hor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64_t nxis_add_hor_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_add_hor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64_t nxis_add_hor_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_add_hor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_add_hor_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_add_hor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32_t nxis_add_hor_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_add_hor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64_t nxis_add_hor_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_sub_hor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_sub_hor_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_sub_hor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8_t nxis_sub_hor_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_sub_hor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_sub_hor_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_sub_hor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_sub_hor_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_sub_hor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32_t nxis_sub_hor_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_sub_hor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32_t nxis_sub_hor_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_sub_hor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64_t nxis_sub_hor_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_sub_hor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64_t nxis_sub_hor_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_sub_hor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_sub_hor_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_sub_hor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32_t nxis_sub_hor_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_sub_hor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64_t nxis_sub_hor_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_min_hor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_min_hor_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_min_hor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8_t nxis_min_hor_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_min_hor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_min_hor_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_min_hor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_min_hor_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_min_hor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32_t nxis_min_hor_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_min_hor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32_t nxis_min_hor_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_min_hor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64_t nxis_min_hor_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_min_hor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64_t nxis_min_hor_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_min_hor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_min_hor_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_min_hor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32_t nxis_min_hor_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_min_hor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64_t nxis_min_hor_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_max_hor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_max_hor_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_max_hor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8_t nxis_max_hor_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_max_hor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_max_hor_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_max_hor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_max_hor_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_max_hor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32_t nxis_max_hor_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_max_hor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32_t nxis_max_hor_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_max_hor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64_t nxis_max_hor_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_max_hor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64_t nxis_max_hor_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_max_hor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_max_hor_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_max_hor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32_t nxis_max_hor_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_max_hor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64_t nxis_max_hor_float64x8(const nxis_float64x8_t v) {
    return;
}

//eq_hor -- true if all elements/vec-members are equal

/** nxis_eq_hor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_eq_hor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_eq_hor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_eq_hor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_eq_hor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_eq_hor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_eq_hor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_eq_hor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_eq_hor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_eq_hor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_eq_hor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eq_hor_float64x8(const nxis_float64x8_t v) {
    return;
}

//SAD -- sum of absolute differences

/** nxis_sad_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_sad_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_sad_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8_t nxis_sad_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_sad_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_sad_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_sad_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_sad_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_sad_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32_t nxis_sad_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_sad_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32_t nxis_sad_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_sad_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64_t nxis_sad_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_sad_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64_t nxis_sad_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_sad_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_sad_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_sad_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32_t nxis_sad_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_sad_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64_t nxis_sad_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_not_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_not_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_not_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_not_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_not_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_not_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_not_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_not_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_not_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_not_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_not_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_not_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_not_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_not_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_not_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_not_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_not_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_not_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_not_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_not_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_not_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_not_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_and_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_and_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_and_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_and_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_and_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_and_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_and_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_and_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_and_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_and_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_and_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_and_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_and_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_and_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_and_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_and_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_and_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_and_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_and_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_and_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_and_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_and_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_or_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_or_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_or_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_or_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_or_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_or_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_or_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_or_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_or_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_or_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_or_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_or_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_or_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_or_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_or_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_or_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_or_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_or_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_or_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_or_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_or_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_or_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_xor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_xor_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_xor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_xor_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_xor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_xor_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_xor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_xor_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_xor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_xor_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_xor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_xor_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_xor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_xor_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_xor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_xor_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_xor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_xor_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_xor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_xor_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_xor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_xor_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

//eq -- equal (==)

/** nxis_eq_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_eq_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_eq_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_eq_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_eq_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_eq_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_eq_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_eq_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_eq_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_eq_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_eq_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_eq_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_eq_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_eq_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_eq_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_eq_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_eq_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_eq_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_eq_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_eq_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_eq_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_eq_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

//gt -- greater than (>)

/** nxis_gt_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_gt_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_gt_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_gt_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_gt_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_gt_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_gt_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_gt_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_gt_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_gt_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_gt_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_gt_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_gt_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_gt_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_gt_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_gt_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_gt_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_gt_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_gt_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_gt_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_gt_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_gt_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

//lt -- less than (<)

/** nxis_lt_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_lt_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_lt_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_lt_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_lt_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_lt_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_lt_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_lt_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_lt_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_lt_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_lt_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_lt_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_lt_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_lt_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_lt_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_lt_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_lt_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_lt_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_lt_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_lt_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_lt_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_lt_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

//ge -- greater or equal (>=)

/** nxis_ge_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_ge_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_ge_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_ge_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_ge_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_ge_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_ge_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_ge_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_ge_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_ge_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_ge_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_ge_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_ge_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_ge_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_ge_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_ge_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_ge_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_ge_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_ge_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_ge_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_ge_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_ge_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

//le -- less or equal (<=)

/** nxis_le_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_le_int8x64(const nxis_int8x64_t a, const nxis_int8x64_t b) {
    return;
}

/** nxis_le_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_le_uint8x64(const nxis_uint8x64_t a, const nxis_uint8x64_t b) {
    return;
}

/** nxis_le_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_le_int16x32(const nxis_int16x32_t a, const nxis_int16x32_t b) {
    return;
}

/** nxis_le_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_le_uint16x32(const nxis_uint16x32_t a, const nxis_uint16x32_t b) {
    return;
}

/** nxis_le_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_le_int32x16(const nxis_int32x16_t a, const nxis_int32x16_t b) {
    return;
}

/** nxis_le_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_le_uint32x16(const nxis_uint32x16_t a, const nxis_uint32x16_t b) {
    return;
}

/** nxis_le_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_le_int64x8(const nxis_int64x8_t a, const nxis_int64x8_t b) {
    return;
}

/** nxis_le_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_le_uint64x8(const nxis_uint64x8_t a, const nxis_uint64x8_t b) {
    return;
}

/** nxis_le_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_le_float16x32(const nxis_float16x32_t a, const nxis_float16x32_t b) {
    return;
}

/** nxis_le_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_le_float32x16(const nxis_float32x16_t a, const nxis_float32x16_t b) {
    return;
}

/** nxis_le_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_le_float64x8(const nxis_float64x8_t a, const nxis_float64x8_t b) {
    return;
}

/** nxis_shftr_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_shftr_int8x64(const nxis_int8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_shftr_uint8x64(const nxis_uint8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_shftr_int16x32(const nxis_int16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_shftr_uint16x32(const nxis_uint16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_shftr_int32x16(const nxis_int32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_shftr_uint32x16(const nxis_uint32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_shftr_int64x8(const nxis_int64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_shftr_uint64x8(const nxis_uint64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_shftr_float16x32(const nxis_float16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_shftr_float32x16(const nxis_float32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftr_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_shftr_float64x8(const nxis_float64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_shftl_int8x64(const nxis_int8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_shftl_uint8x64(const nxis_uint8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_shftl_int16x32(const nxis_int16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_shftl_uint16x32(const nxis_uint16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_shftl_int32x16(const nxis_int32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_shftl_uint32x16(const nxis_uint32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_shftl_int64x8(const nxis_int64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_shftl_uint64x8(const nxis_uint64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_shftl_float16x32(const nxis_float16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_shftl_float32x16(const nxis_float32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_shftl_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_shftl_float64x8(const nxis_float64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_rotr_int8x64(const nxis_int8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_rotr_uint8x64(const nxis_uint8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_rotr_int16x32(const nxis_int16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_rotr_uint16x32(const nxis_uint16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_rotr_int32x16(const nxis_int32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_rotr_uint32x16(const nxis_uint32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_rotr_int64x8(const nxis_int64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_rotr_uint64x8(const nxis_uint64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_rotr_float16x32(const nxis_float16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_rotr_float32x16(const nxis_float32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotr_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_rotr_float64x8(const nxis_float64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_rotl_int8x64(const nxis_int8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_rotl_uint8x64(const nxis_uint8x64_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_rotl_int16x32(const nxis_int16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_rotl_uint16x32(const nxis_uint16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_rotl_int32x16(const nxis_int32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_rotl_uint32x16(const nxis_uint32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_rotl_int64x8(const nxis_int64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_rotl_uint64x8(const nxis_uint64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_rotl_float16x32(const nxis_float16x32_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_rotl_float32x16(const nxis_float32x16_t v, const nxis_uint_t count) {
    return;
}

/** nxis_rotl_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_rotl_float64x8(const nxis_float64x8_t v, const nxis_uint_t count) {
    return;
}

/** nxis_popcount_hor_int8x64
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_popcount_hor_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_popcount_hor_int16x32
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_popcount_hor_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_popcount_hor_int32x16
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_popcount_hor_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_popcount_hor_int64x8
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_popcount_hor_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_popcount_hor_float16x32
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_popcount_hor_float32x16
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_popcount_hor_float64x8
 * TODO:
 */
NXS_STATIC_INLINE int nxis_popcount_hor_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_popcount_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_popcount_int8x64(const nxis_int8x64_t v) {
    return;
}

/** nxis_popcount_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_popcount_uint8x64(const nxis_uint8x64_t v) {
    return;
}

/** nxis_popcount_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_popcount_int16x32(const nxis_int16x32_t v) {
    return;
}

/** nxis_popcount_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_popcount_uint16x32(const nxis_uint16x32_t v) {
    return;
}

/** nxis_popcount_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_popcount_int32x16(const nxis_int32x16_t v) {
    return;
}

/** nxis_popcount_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_popcount_uint32x16(const nxis_uint32x16_t v) {
    return;
}

/** nxis_popcount_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_popcount_int64x8(const nxis_int64x8_t v) {
    return;
}

/** nxis_popcount_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_popcount_uint64x8(const nxis_uint64x8_t v) {
    return;
}

/** nxis_popcount_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_popcount_float16x32(const nxis_float16x32_t v) {
    return;
}

/** nxis_popcount_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_popcount_float32x16(const nxis_float32x16_t v) {
    return;
}

/** nxis_popcount_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_popcount_float64x8(const nxis_float64x8_t v) {
    return;
}

/** nxis_bit_extract_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_bit_extract_int8x64(const nxis_int8x64_t v, const nxis_int8x64_t mask) {
    return;
}

/** nxis_bit_extract_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_bit_extract_uint8x64(const nxis_uint8x64_t v, const nxis_uint8x64_t mask) {
    return;
}

/** nxis_bit_extract_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_bit_extract_int16x32(const nxis_int16x32_t v, const nxis_int16x32_t mask) {
    return;
}

/** nxis_bit_extract_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_bit_extract_uint16x32(const nxis_uint16x32_t v, const nxis_uint16x32_t mask) {
    return;
}

/** nxis_bit_extract_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_bit_extract_int32x16(const nxis_int32x16_t v, const nxis_int32x16_t mask) {
    return;
}

/** nxis_bit_extract_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_bit_extract_uint32x16(const nxis_uint32x16_t v, const nxis_uint32x16_t mask) {
    return;
}

/** nxis_bit_extract_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_bit_extract_int64x8(const nxis_int64x8_t v, const nxis_int64x8_t mask) {
    return;
}

/** nxis_bit_extract_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_bit_extract_uint64x8(const nxis_uint64x8_t v, const nxis_uint64x8_t mask) {
    return;
}

/** nxis_bit_extract_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_bit_extract_float16x32(const nxis_float16x32_t v, const nxis_float16x32_t mask) {
    return;
}

/** nxis_bit_extract_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_bit_extract_float32x16(const nxis_float32x16_t v, const nxis_float32x16_t mask) {
    return;
}

/** nxis_bit_extract_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_bit_extract_float64x8(const nxis_float64x8_t v, const nxis_float64x8_t mask) {
    return;
}

/** nxis_bit_deposit_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_bit_deposit_int8x64(const nxis_int8x64_t v, const nxis_int8x64_t mask) {
    return;
}

/** nxis_bit_deposit_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_bit_deposit_uint8x64(const nxis_uint8x64_t v, const nxis_uint8x64_t mask) {
    return;
}

/** nxis_bit_deposit_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_bit_deposit_int16x32(const nxis_int16x32_t v, const nxis_int16x32_t mask) {
    return;
}

/** nxis_bit_deposit_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_bit_deposit_uint16x32(const nxis_uint16x32_t v, const nxis_uint16x32_t mask) {
    return;
}

/** nxis_bit_deposit_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_bit_deposit_int32x16(const nxis_int32x16_t v, const nxis_int32x16_t mask) {
    return;
}

/** nxis_bit_deposit_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_bit_deposit_uint32x16(const nxis_uint32x16_t v, const nxis_uint32x16_t mask) {
    return;
}

/** nxis_bit_deposit_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_bit_deposit_int64x8(const nxis_int64x8_t v, const nxis_int64x8_t mask) {
    return;
}

/** nxis_bit_deposit_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_bit_deposit_uint64x8(const nxis_uint64x8_t v, const nxis_uint64x8_t mask) {
    return;
}

/** nxis_bit_deposit_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_bit_deposit_float16x32(const nxis_float16x32_t v, const nxis_float16x32_t mask) {
    return;
}

/** nxis_bit_deposit_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_bit_deposit_float32x16(const nxis_float32x16_t v, const nxis_float32x16_t mask) {
    return;
}

/** nxis_bit_deposit_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_bit_deposit_float64x8(const nxis_float64x8_t v, const nxis_float64x8_t mask) {
    return;
}

#endif //_NXS_SIMD512_H_