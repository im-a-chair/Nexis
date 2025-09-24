#ifndef _NXS_SIMD_H_
#define _NXS_SIMD_H_
#include "std.h"
#include "SIMD/fp16.h"

// ---- Types -----

/** types
| Bitness   | x86             | ARM                                        | min set x86     | min set ARM |
|-----------|-----------------|--------------------------------------------|-----------------|-------------|
| 8 sint    | int8_t          | int8_t                                     | all             | all         |
| 8 uint    | uint8_t         | uint8_t                                    | all             | all         |
| 8 float   | n/a             | n/a                                        | n/a             | n/a         |
| 16 sint   | int16_t         | int16_t                                    | all             | all         |
| 16 uint   | sint16_t        | sint16_t                                   | all             | all         |
| 16 float  | _fp16           | __fp16                                     | F16C            | FEAT_FP16   |
| 32 sint   | int32_t         | int32_t                                    | all             | all         |
| 32 uint   | sint32_t        | sint32_t                                   | all             | all         |
| 32 float  | float           | float                                      | FPU             | FPU         |
| 64 sint   | int64_t         | int64_t                                    | MMX, 64bit      | 64-bit      |
| 64 uint   | sint64_t        | sint64_t                                   | MMX, 64bit      | 64-bit      |
| 64 float  | double          | double                                     | FPU             | FPU         |
|-----------|-----------------|--------------------------------------------|-----------------|-------------|
| 128 int   | __m128i         | int8x16_t, int16x8_t, int32x4_t, int64x2_t | SSE2            | NEON        |
| 128 float | __m128, __m128d | float16x8_t, float32x4_t, float64x2_t      | SSE(2 for `*d`) | NEON        |
| 256 int   | __m256i         | svint8_t, svint16_t, svint32_t, svint64_t  | AVX             | SVE         |
| 256 float | __m256, __m256d | svfloat16_t, svfloat32_t, svfloat64_t      | AVX             | SVE         |
| 512 int   | __m512i         | svint8_t, svint16_t, svint32_t, svint64_t  | AVX512          | SVE         |
| 512 float | __m512, __m512d | svfloat16_t, svfloat32_t, svfloat64_t      | AVX512          | SVE         |
| +   int   | n/a             | svint8_t, svint16_t, svint32_t, svint64_t  | n/a             | SVE         |
| +   float | n/a             | svfloat16_t, svfloat32_t, svfloat64_t      | n/a             | SVE         |
| mask8     | __mmask8        | svbool_t                                   | AVX512          | SVE         |
| mask16    | __mmask16       | svbool_t                                   | AVX512          | SVE         |
| mask32    | __mmask32       | svbool_t                                   | AVX512          | SVE         |
| mask64    | __mmask64       | svbool_t                                   | AVX512          | SVE         |
|-----------|-----------------|--------------------------------------------|-----------------|-------------|
*/

//SSE | NEON
#ifdef NXS_SSE
typedef __m128  nxis_float32x4_t;
#elif defined(NXS_ARM_NEON)
typedef float32x4_t nxis_float32x4_t;
#else
typedef struct NXS_ALIGN(16) {nxis_float32_t v[4];} nxis_float32x4_t;
#endif
#ifdef NXS_SSE2
typedef __m128i nxis_int8x16_t;
typedef __m128i nxis_uint8x16_t;
typedef __m128i nxis_int16x8_t;
typedef __m128i nxis_uint16x8_t;
typedef __m128i nxis_int32x4_t;
typedef __m128i nxis_uint32x4_t;
typedef __m128i nxis_int64x2_t;
typedef __m128i nxis_uint64x2_t;
typedef __m128d nxis_float64x2_t;
#elif defined(NXS_ARM_NEON)
typedef int8x16_t   nxis_int8x16_t;
typedef uint8x16_t  nxis_uint8x16_t;
typedef int16x8_t   nxis_int16x8_t;
typedef uint16x8_t  nxis_uint16x8_t;
typedef int32x4_t   nxis_int32x4_t;
typedef uint32x4_t  nxis_uint32x4_t;
typedef int64x2_t   nxis_int64x2_t;
typedef uint64x2_t  nxis_uint64x2_t;
typedef float64x2_t nxis_float64x2_t;
#else
typedef struct NXS_ALIGN(16) {nxis_int8_t    v[16];} nxis_int8x16_t;
typedef struct NXS_ALIGN(16) {nxis_uint8_t   v[16];} nxis_uint8x16_t;
typedef struct NXS_ALIGN(16) {nxis_int16_t   v[8]; } nxis_int16x8_t;
typedef struct NXS_ALIGN(16) {nxis_uint16_t  v[8]; } nxis_uint16x8_t;
typedef struct NXS_ALIGN(16) {nxis_int32_t   v[4]; } nxis_int32x4_t;
typedef struct NXS_ALIGN(16) {nxis_uint32_t  v[4]; } nxis_uint32x4_t;
typedef struct NXS_ALIGN(16) {nxis_int64_t   v[2]; } nxis_int64x2_t;
typedef struct NXS_ALIGN(16) {nxis_uint64_t  v[2]; } nxis_uint64x2_t;
typedef struct NXS_ALIGN(16) {nxis_float64_t v[2]; } nxis_float64x2_t;
#endif
//AVX | SVE
#ifdef NXS_AVX
typedef __m256i nxis_int8x32_t;
typedef __m256i nxis_uint8x32_t;
typedef __m256i nxis_int16x16_t;
typedef __m256i nxis_uint16x16_t;
typedef __m256i nxis_int32x8_t;
typedef __m256i nxis_uint32x8_t;
typedef __m256i nxis_int64x4_t;
typedef __m256i nxis_uint64x4_t;
typedef __m256  nxis_float32x8_t;
typedef __m256d nxis_float64x4_t;
#elif defined(NXS_ARM_SVE)
typedef svint8_t    nxis_int8x32_t;
typedef svuint8_t   nxis_uint8x32_t;
typedef svint16_t   nxis_int16x16_t;
typedef svuint16_t  nxis_uint16x16_t;
typedef svint32_t   nxis_int32x8_t;
typedef svuint32_t  nxis_uint32x8_t;
typedef svint64_t   nxis_int64x4_t;
typedef svuint64_t  nxis_uint64x4_t;
typedef svfloat32_t nxis_float32x8_t;
typedef svfloat64_t nxis_float64x4_t;
#else
typedef struct NXS_ALIGN(32) {nxis_int8x16_t   v[2];} nxis_int8x32_t;
typedef struct NXS_ALIGN(32) {nxis_uint8x16_t  v[2];} nxis_uint8x32_t;
typedef struct NXS_ALIGN(32) {nxis_int16x8_t   v[2];} nxis_int16x16_t;
typedef struct NXS_ALIGN(32) {nxis_uint16x8_t  v[2];} nxis_uint16x16_t;
typedef struct NXS_ALIGN(32) {nxis_int32x4_t   v[2];} nxis_int32x8_t;
typedef struct NXS_ALIGN(32) {nxis_uint32x4_t  v[2];} nxis_uint32x8_t;
typedef struct NXS_ALIGN(32) {nxis_int64x2_t   v[2];} nxis_int64x4_t;
typedef struct NXS_ALIGN(32) {nxis_uint64x2_t  v[2];} nxis_uint64x4_t;
typedef struct NXS_ALIGN(32) {nxis_float32x4_t v[2];} nxis_float32x8_t;
typedef struct NXS_ALIGN(32) {nxis_float64x2_t v[2];} nxis_float64x4_t;
#endif
//AVX512
#ifdef NXS_AVX512F
typedef __m512i nxis_int8x64_t;
typedef __m512i nxis_uint8x64_t;
typedef __m512i nxis_int16x32_t;
typedef __m512i nxis_uint16x32_t;
typedef __m512i nxis_int32x16_t;
typedef __m512i nxis_uint32x16_t;
typedef __m512i nxis_int64x8_t;
typedef __m512i nxis_uint64x8_t;
typedef __m512  nxis_float32x16_t;
typedef __m512d nxis_float64x8_t;
#elif defined(NXS_ARM_SVE)
typedef svint8_t    nxis_int8x64_t;
typedef svuint8_t   nxis_uint8x64_t;
typedef svint16_t   nxis_int16x32_t;
typedef svuint16_t  nxis_uint16x32_t;
typedef svint32_t   nxis_int32x16_t;
typedef svuint32_t  nxis_uint32x16_t;
typedef svint64_t   nxis_int64x8_t;
typedef svuint64_t  nxis_uint64x8_t;
typedef svfloat32_t nxis_float32x16_t;
typedef svfloat64_t nxis_float64x8_t;
#else
typedef struct NXS_ALIGN(64) {nxis_int8x32_t   v[2];} nxis_int8x64_t;
typedef struct NXS_ALIGN(64) {nxis_uint8x32_t  v[2];} nxis_uint8x64_t;
typedef struct NXS_ALIGN(64) {nxis_int16x16_t  v[2];} nxis_int16x32_t;
typedef struct NXS_ALIGN(64) {nxis_uint16x16_t v[2];} nxis_uint16x32_t;
typedef struct NXS_ALIGN(64) {nxis_int32x8_t   v[2];} nxis_int32x16_t;
typedef struct NXS_ALIGN(64) {nxis_uint32x8_t  v[2];} nxis_uint32x16_t;
typedef struct NXS_ALIGN(64) {nxis_int64x4_t   v[2];} nxis_int64x8_t;
typedef struct NXS_ALIGN(64) {nxis_uint64x4_t  v[2];} nxis_uint64x8_t;
typedef struct NXS_ALIGN(64) {nxis_float32x8_t v[2];} nxis_float32x16_t;
typedef struct NXS_ALIGN(64) {nxis_float64x4_t v[2];} nxis_float64x8_t;
#endif
#ifdef NXS_AVX512FP16
typedef __m128h  nxis_float16x8_t;
typedef __m256h  nxis_float16x16_t;
typedef __m512h  nxis_float16x32_t;
#elif defined(NXS_ARM_NEON_FP16)
typedef float16x8_t nxis_float16x8_t;
typedef svfloat16_t nxis_float16x16_t;
typedef svfloat16_t nxis_float16x32_t;
#else
typedef struct NXS_ALIGN(16) {nxis_float16_t    v[8];} nxis_float16x8_t;
typedef struct NXS_ALIGN(32) {nxis_float16x8_t  v[2];} nxis_float16x16_t;
typedef struct NXS_ALIGN(64) {nxis_float16x16_t v[2];} nxis_float16x32_t;
#endif
//masks (AVX512 | SVE)
#ifdef NXS_AVX512F
typedef __mmask8  nxis_mask8_t;
typedef __mmask16 nxis_mask16_t;
typedef __mmask32 nxis_mask32_t;
typedef __mmask64 nxis_mask64_t;
#elif defined(NXS_ARM_SVE)
typedef svbool_t nxis_mask8_t;
typedef svbool_t nxis_mask16_t;
typedef svbool_t nxis_mask32_t;
typedef svbool_t nxis_mask64_t;
#else
typedef nxis_uint8_t  nxis_mask8_t;
typedef nxis_uint16_t nxis_mask16_t;
typedef nxis_uint32_t nxis_mask32_t;
typedef nxis_uint64_t nxis_mask64_t;
#endif

//for unpacking/deinternleaving funcitons
#ifdef NXS_ARM_NEON
//arm has native double vector types
typedef int8x16x2_t nxis_int8x16x2_t;
typedef uint8x16x2_t nxis_uint8x16x2_t;
typedef int16x8x2_t nxis_int16x8x2_t;
typedef uint16x8x2_t nxis_uint16x8x2_t;
typedef int32x4x2_t nxis_int32x4x2_t;
typedef uint32x4x2_t nxis_uint32x4x2_t;
typedef int64x2x2_t nxis_int64x2x2_t;
typedef uint64x2x2_t nxis_uint64x2x2_t;
typedef float16x8x2_t nxis_float16x8x2_t;
typedef float32x4x2_t nxis_float32x4x2_t;
typedef float64x2x2_t nxis_float64x2x2_t;
#else
typedef struct {nxis_int8x16_t    a; nxis_int8x16_t    b;} nxis_int8x16x2_t;
typedef struct {nxis_uint8x16_t   a; nxis_uint8x16_t   b;} nxis_uint8x16x2_t;
typedef struct {nxis_int16x8_t    a; nxis_int16x8_t    b;} nxis_int16x8x2_t;
typedef struct {nxis_uint16x8_t   a; nxis_uint16x8_t   b;} nxis_uint16x8x2_t;
typedef struct {nxis_int32x4_t    a; nxis_int32x4_t    b;} nxis_int32x4x2_t;
typedef struct {nxis_uint32x4_t   a; nxis_uint32x4_t   b;} nxis_uint32x4x2_t;
typedef struct {nxis_int64x2_t    a; nxis_int64x2_t    b;} nxis_int64x2x2_t;
typedef struct {nxis_uint64x2_t   a; nxis_uint64x2_t   b;} nxis_uint64x2x2_t;
typedef struct {nxis_float16x8_t  a; nxis_float16x8_t  b;} nxis_float16x8x2_t;
typedef struct {nxis_float32x4_t  a; nxis_float32x4_t  b;} nxis_float32x4x2_t;
typedef struct {nxis_float64x2_t  a; nxis_float64x2_t  b;} nxis_float64x2x2_t;
#endif

//SVE doesnt have dedicated types, so it just uses the same
typedef struct {nxis_int8x32_t    a; nxis_int8x32_t    b;} nxis_int8x32x2_t;
typedef struct {nxis_uint8x32_t   a; nxis_uint8x32_t   b;} nxis_uint8x32x2_t;
typedef struct {nxis_int16x16_t   a; nxis_int16x16_t   b;} nxis_int16x16x2_t;
typedef struct {nxis_uint16x16_t  a; nxis_uint16x16_t  b;} nxis_uint16x16x2_t;
typedef struct {nxis_int32x8_t    a; nxis_int32x8_t    b;} nxis_int32x8x2_t;
typedef struct {nxis_uint32x8_t   a; nxis_uint32x8_t   b;} nxis_uint32x8x2_t;
typedef struct {nxis_int64x4_t    a; nxis_int64x4_t    b;} nxis_int64x4x2_t;
typedef struct {nxis_uint64x4_t   a; nxis_uint64x4_t   b;} nxis_uint64x4x2_t;
typedef struct {nxis_float16x16_t a; nxis_float16x16_t b;} nxis_float16x16x2_t;
typedef struct {nxis_float32x8_t  a; nxis_float32x8_t  b;} nxis_float32x8x2_t;
typedef struct {nxis_float64x4_t  a; nxis_float64x4_t  b;} nxis_float64x4x2_t;
typedef struct {nxis_int8x64_t    a; nxis_int8x64_t    b;} nxis_int8x64x2_t;
typedef struct {nxis_uint8x64_t   a; nxis_uint8x64_t   b;} nxis_uint8x64x2_t;
typedef struct {nxis_int16x32_t   a; nxis_int16x32_t   b;} nxis_int16x32x2_t;
typedef struct {nxis_uint16x32_t  a; nxis_uint16x32_t  b;} nxis_uint16x32x2_t;
typedef struct {nxis_int32x16_t   a; nxis_int32x16_t   b;} nxis_int32x16x2_t;
typedef struct {nxis_uint32x16_t  a; nxis_uint32x16_t  b;} nxis_uint32x16x2_t;
typedef struct {nxis_int64x8_t    a; nxis_int64x8_t    b;} nxis_int64x8x2_t;
typedef struct {nxis_uint64x8_t   a; nxis_uint64x8_t   b;} nxis_uint64x8x2_t;
typedef struct {nxis_float16x32_t a; nxis_float16x32_t b;} nxis_float16x32x2_t;
typedef struct {nxis_float32x16_t a; nxis_float32x16_t b;} nxis_float32x16x2_t;
typedef struct {nxis_float64x8_t  a; nxis_float64x8_t  b;} nxis_float64x8x2_t;

// ----- Functions -----
//usual syntax: nxis_<operation>[_<variation>]_<type>[_mask][_sat]
    //`_sat` meaning the op is the saturated variant

//mask bitwise ops

/** nxis_not_mask8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_not_mask8(const nxis_mask8_t a, const nxis_mask8_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_and_mask8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_and_mask8(const nxis_mask8_t a, const nxis_mask8_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_or_mask8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_or_mask8(const nxis_mask8_t a, const nxis_mask8_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_xor_mask8
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask8_t nxis_xor_mask8(const nxis_mask8_t a, const nxis_mask8_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_not_mask16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_not_mask16(const nxis_mask16_t a, const nxis_mask16_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_and_mask16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_and_mask16(const nxis_mask16_t a, const nxis_mask16_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_or_mask16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_or_mask16(const nxis_mask16_t a, const nxis_mask16_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_xor_mask16
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask16_t nxis_xor_mask16(const nxis_mask16_t a, const nxis_mask16_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_not_mask32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_not_mask32(const nxis_mask32_t a, const nxis_mask32_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_and_mask32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_and_mask32(const nxis_mask32_t a, const nxis_mask32_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_or_mask32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_or_mask32(const nxis_mask32_t a, const nxis_mask32_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_xor_mask32
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask32_t nxis_xor_mask32(const nxis_mask32_t a, const nxis_mask32_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_not_mask64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_not_mask64(const nxis_mask64_t a, const nxis_mask64_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_and_mask64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_and_mask64(const nxis_mask64_t a, const nxis_mask64_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_or_mask64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_or_mask64(const nxis_mask64_t a, const nxis_mask64_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

/** nxis_xor_mask64
 * TODO:
 */
NXS_STATIC_INLINE nxis_mask64_t nxis_xor_mask64(const nxis_mask64_t a, const nxis_mask64_t b) {
#ifdef NXS_AVX512F
    return;
#elif defined(NXS_ARM_SVE)
    return;
#else
    return;
#endif
}

//Widening/Narrowing

/** nxis_int8x16_to_int16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int8x16_to_int16x8(const nxis_int8x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int16x8_to_int32x4(const nxis_int16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_int32x4_to_int64x2(const nxis_int32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x2_to_int32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int64x2_to_int32x4(const nxis_int64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int32x4_to_int16x8(const nxis_int32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int8x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_int16x8_to_int8x16(const nxis_int16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x16_to_uint16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint8x16_to_uint16x8(const nxis_uint8x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint16x8_to_uint32x4(const nxis_uint16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_uint32x4_to_uint64x2(const nxis_uint32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x2_to_uint32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint64x2_to_uint32x4(const nxis_uint64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint32x4_to_uint16x8(const nxis_uint32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint8x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_uint16x8_to_uint8x16(const nxis_uint16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x8_to_float32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float16x8_to_float32x4(const nxis_float16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_float32x4_to_float64x2(const nxis_float32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x2_to_float32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float64x2_to_float32x4(const nxis_float64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_float32x4_to_float16x8(const nxis_float32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x32_to_int16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int8x32_to_int16x16(const nxis_int8x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int16x16_to_int32x8(const nxis_int16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_int32x8_to_int64x4(const nxis_int32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x4_to_int32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int64x4_to_int32x8(const nxis_int64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int32x8_to_int16x16(const nxis_int32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int8x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_int16x16_to_int8x32(const nxis_int16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x32_to_uint16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint8x32_to_uint16x16(const nxis_uint8x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint16x16_to_uint32x8(const nxis_uint16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_uint32x8_to_uint64x4(const nxis_uint32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x4_to_uint32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint64x4_to_uint32x8(const nxis_uint64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint32x8_to_uint16x16(const nxis_uint32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint8x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_uint16x16_to_uint8x32(const nxis_uint16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x16_to_float32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float16x16_to_float32x8(const nxis_float16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_float32x8_to_float64x4(const nxis_float32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x4_to_float32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float64x4_to_float32x8(const nxis_float64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_float32x8_to_float16x16(const nxis_float32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x64_to_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int8x64_to_int16x32(const nxis_int8x64_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int16x32_to_int32x16(const nxis_int16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_int32x16_to_int64x8(const nxis_int32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x8_to_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int64x8_to_int32x16(const nxis_int64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int32x16_to_int16x32(const nxis_int32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_int16x32_to_int8x64(const nxis_int16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x64_to_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint8x64_to_uint16x32(const nxis_uint8x64_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint16x32_to_uint32x16(const nxis_uint16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_uint32x16_to_uint64x8(const nxis_uint32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x8_to_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint64x8_to_uint32x16(const nxis_uint64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint32x16_to_uint16x32(const nxis_uint32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_uint16x32_to_uint8x64(const nxis_uint16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x32_to_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float16x32_to_float32x16(const nxis_float16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_float32x16_to_float64x8(const nxis_float32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x8_to_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float64x8_to_float32x16(const nxis_float64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_float32x16_to_float16x32(const nxis_float32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

//Convert/Cast

/** nxis_int8x16_to_uint8x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_int8x16_to_uint8x16(const nxis_int8x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x16_to_int8x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_uint8x16_to_int8x16(const nxis_uint8x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_uint16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_int16x8_to_uint16x8(const nxis_int16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_int16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_uint16x8_to_int16x8(const nxis_uint16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_uint32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_int32x4_to_uint32x4(const nxis_int32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_int32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_uint32x4_to_int32x4(const nxis_uint32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x2_to_uint64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_int64x2_to_uint64x2(const nxis_int64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x2_to_int64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_uint64x2_to_int64x2(const nxis_uint64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_float16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_int16x8_to_float16x8(const nxis_int16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x8_to_int16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_float16x8_to_int16x8(const nxis_float16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_float16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_uint16x8_to_float16x8(const nxis_uint16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x8_to_uint16x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_float16x8_to_uint16x8(const nxis_float16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_float32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_int32x4_to_float32x4(const nxis_int32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_int32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_float32x4_to_int32x4(const nxis_float32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_float32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_uint32x4_to_float32x4(const nxis_uint32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_uint32x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_float32x4_to_uint32x4(const nxis_float32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x2_to_float64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_int64x2_to_float64x2(const nxis_int64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x2_to_int64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_float64x2_to_int64x2(const nxis_float64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x2_to_float64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_uint64x2_to_float64x2(const nxis_uint64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x2_to_uint64x2
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_float64x2_to_uint64x2(const nxis_float64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x32_to_uint8x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_int8x32_to_uint8x32(const nxis_int8x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x32_to_int8x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_uint8x32_to_int8x32(const nxis_uint8x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_uint16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_int16x16_to_uint16x16(const nxis_int16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_int16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_uint16x16_to_int16x16(const nxis_uint16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_uint32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_int32x8_to_uint32x8(const nxis_int32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_int32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_uint32x8_to_int32x8(const nxis_uint32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x4_to_uint64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_int64x4_to_uint64x4(const nxis_int64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x4_to_int64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_uint64x4_to_int64x4(const nxis_uint64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_float16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_int16x16_to_float16x16(const nxis_int16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x16_to_int16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_float16x16_to_int16x16(const nxis_float16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_float16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_uint16x16_to_float16x16(const nxis_uint16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x16_to_uint16x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_float16x16_to_uint16x16(const nxis_float16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_float32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_int32x8_to_float32x8(const nxis_int32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_int32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_float32x8_to_int32x8(const nxis_float32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_float32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_uint32x8_to_float32x8(const nxis_uint32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_uint32x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_float32x8_to_uint32x8(const nxis_float32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x4_to_float64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_int64x4_to_float64x4(const nxis_int64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x4_to_int64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_float64x4_to_int64x4(const nxis_float64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x4_to_float64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_uint64x4_to_float64x4(const nxis_uint64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x4_to_uint64x4
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_float64x4_to_uint64x4(const nxis_float64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x64_to_uint8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_int8x64_to_uint8x64(const nxis_int8x64_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x64_to_int8x64
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_uint8x64_to_int8x64(const nxis_uint8x64_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_int16x32_to_uint16x32(const nxis_int16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_uint16x32_to_int16x32(const nxis_uint16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_int32x16_to_uint32x16(const nxis_int32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_uint32x16_to_int32x16(const nxis_uint32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x8_to_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_int64x8_to_uint64x8(const nxis_int64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x8_to_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_uint64x8_to_int64x8(const nxis_uint64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_int16x32_to_float16x32(const nxis_int16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x32_to_int16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_float16x32_to_int16x32(const nxis_float16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_float16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_uint16x32_to_float16x32(const nxis_uint16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x32_to_uint16x32
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_float16x32_to_uint16x32(const nxis_float16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_int32x16_to_float32x16(const nxis_int32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_int32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_float32x16_to_int32x16(const nxis_float32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_float32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_uint32x16_to_float32x16(const nxis_uint32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_uint32x16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_float32x16_to_uint32x16(const nxis_float32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x8_to_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_int64x8_to_float64x8(const nxis_int64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x8_to_int64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_float64x8_to_int64x8(const nxis_float64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x8_to_float64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_uint64x8_to_float64x8(const nxis_uint64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x8_to_uint64x8
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_float64x8_to_uint64x8(const nxis_float64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

//Widening/Narrowing -- saturated

/** nxis_int8x16_to_int16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int8x16_to_int16x8_sat(const nxis_int8x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int16x8_to_int32x4_sat(const nxis_int16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_int32x4_to_int64x2_sat(const nxis_int32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x2_to_int32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int64x2_to_int32x4_sat(const nxis_int64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int32x4_to_int16x8_sat(const nxis_int32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int8x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_int16x8_to_int8x16_sat(const nxis_int16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x16_to_uint16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint8x16_to_uint16x8_sat(const nxis_uint8x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint16x8_to_uint32x4_sat(const nxis_uint16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_uint32x4_to_uint64x2_sat(const nxis_uint32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x2_to_uint32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint64x2_to_uint32x4_sat(const nxis_uint64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint32x4_to_uint16x8_sat(const nxis_uint32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint8x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_uint16x8_to_uint8x16_sat(const nxis_uint16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x8_to_float32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float16x8_to_float32x4_sat(const nxis_float16x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_float32x4_to_float64x2_sat(const nxis_float32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x2_to_float32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float64x2_to_float32x4_sat(const nxis_float64x2_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_float32x4_to_float16x8_sat(const nxis_float32x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x32_to_int16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int8x32_to_int16x16_sat(const nxis_int8x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int16x16_to_int32x8_sat(const nxis_int16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_int32x8_to_int64x4_sat(const nxis_int32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x4_to_int32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int64x4_to_int32x8_sat(const nxis_int64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int32x8_to_int16x16_sat(const nxis_int32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int8x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_int16x16_to_int8x32_sat(const nxis_int16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x32_to_uint16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint8x32_to_uint16x16_sat(const nxis_uint8x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint16x16_to_uint32x8_sat(const nxis_uint16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_uint32x8_to_uint64x4_sat(const nxis_uint32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x4_to_uint32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint64x4_to_uint32x8_sat(const nxis_uint64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint32x8_to_uint16x16_sat(const nxis_uint32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint8x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_uint16x16_to_uint8x32_sat(const nxis_uint16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x16_to_float32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float16x16_to_float32x8_sat(const nxis_float16x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_float32x8_to_float64x4_sat(const nxis_float32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x4_to_float32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float64x4_to_float32x8_sat(const nxis_float64x4_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_float32x8_to_float16x16_sat(const nxis_float32x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x64_to_int16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int8x64_to_int16x32_sat(const nxis_int8x64_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int16x32_to_int32x16_sat(const nxis_int16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_int32x16_to_int64x8_sat(const nxis_int32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x8_to_int32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int64x8_to_int32x16_sat(const nxis_int64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int32x16_to_int16x32_sat(const nxis_int32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int8x64_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_int16x32_to_int8x64_sat(const nxis_int16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x64_to_uint16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint8x64_to_uint16x32_sat(const nxis_uint8x64_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint16x32_to_uint32x16_sat(const nxis_uint16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_uint32x16_to_uint64x8_sat(const nxis_uint32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x8_to_uint32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint64x8_to_uint32x16_sat(const nxis_uint64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint32x16_to_uint16x32_sat(const nxis_uint32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint8x64_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_uint16x32_to_uint8x64_sat(const nxis_uint16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x32_to_float32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float16x32_to_float32x16_sat(const nxis_float16x32_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_float32x16_to_float64x8_sat(const nxis_float32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x8_to_float32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float64x8_to_float32x16_sat(const nxis_float64x8_t n) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_float32x16_to_float16x32_sat(const nxis_float32x16_t n) {
    ///TODO: add `#ifdef`s
    return;
}

//Convert/Cast -- saturated

/** nxis_int8x16_to_uint8x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_int8x16_to_uint8x16_sat(const nxis_int8x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x16_to_int8x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_uint8x16_to_int8x16_sat(const nxis_uint8x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x8_to_uint16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_int16x8_to_uint16x8_sat(const nxis_int16x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x8_to_int16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_uint16x8_to_int16x8_sat(const nxis_uint16x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x4_to_uint32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_int32x4_to_uint32x4_sat(const nxis_int32x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x4_to_int32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_uint32x4_to_int32x4_sat(const nxis_uint32x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x2_to_uint64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_int64x2_to_uint64x2_sat(const nxis_int64x2_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x2_to_int64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_uint64x2_to_int64x2_sat(const nxis_uint64x2_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x8_to_float16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_int16x8_to_float16x8_sat(const nxis_int16x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x8_to_int16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_float16x8_to_int16x8_sat(const nxis_float16x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x8_to_float16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_uint16x8_to_float16x8_sat(const nxis_uint16x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x8_to_uint16x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_float16x8_to_uint16x8_sat(const nxis_float16x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x4_to_float32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_int32x4_to_float32x4_sat(const nxis_int32x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x4_to_int32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_float32x4_to_int32x4_sat(const nxis_float32x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x4_to_float32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_uint32x4_to_float32x4_sat(const nxis_uint32x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x4_to_uint32x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_float32x4_to_uint32x4_sat(const nxis_float32x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x2_to_float64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_int64x2_to_float64x2_sat(const nxis_int64x2_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x2_to_int64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_float64x2_to_int64x2_sat(const nxis_float64x2_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x2_to_float64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_uint64x2_to_float64x2_sat(const nxis_uint64x2_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x2_to_uint64x2_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_float64x2_to_uint64x2_sat(const nxis_float64x2_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int8x32_to_uint8x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_int8x32_to_uint8x32_sat(const nxis_int8x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x32_to_int8x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_uint8x32_to_int8x32_sat(const nxis_uint8x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x16_to_uint16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_int16x16_to_uint16x16_sat(const nxis_int16x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x16_to_int16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_uint16x16_to_int16x16_sat(const nxis_uint16x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x8_to_uint32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_int32x8_to_uint32x8_sat(const nxis_int32x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x8_to_int32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_uint32x8_to_int32x8_sat(const nxis_uint32x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x4_to_uint64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_int64x4_to_uint64x4_sat(const nxis_int64x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x4_to_int64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_uint64x4_to_int64x4_sat(const nxis_uint64x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x16_to_float16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_int16x16_to_float16x16_sat(const nxis_int16x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x16_to_int16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_float16x16_to_int16x16_sat(const nxis_float16x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x16_to_float16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_uint16x16_to_float16x16_sat(const nxis_uint16x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x16_to_uint16x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_float16x16_to_uint16x16_sat(const nxis_float16x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x8_to_float32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_int32x8_to_float32x8_sat(const nxis_int32x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x8_to_int32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_float32x8_to_int32x8_sat(const nxis_float32x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x8_to_float32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_uint32x8_to_float32x8_sat(const nxis_uint32x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x8_to_uint32x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_float32x8_to_uint32x8_sat(const nxis_float32x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x4_to_float64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_int64x4_to_float64x4_sat(const nxis_int64x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x4_to_int64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_float64x4_to_int64x4_sat(const nxis_float64x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x4_to_float64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_uint64x4_to_float64x4_sat(const nxis_uint64x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x4_to_uint64x4_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_float64x4_to_uint64x4_sat(const nxis_float64x4_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int8x64_to_uint8x64_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_int8x64_to_uint8x64_sat(const nxis_int8x64_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x64_to_int8x64_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_uint8x64_to_int8x64_sat(const nxis_uint8x64_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x32_to_uint16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_int16x32_to_uint16x32_sat(const nxis_int16x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x32_to_int16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_uint16x32_to_int16x32_sat(const nxis_uint16x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x16_to_uint32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_int32x16_to_uint32x16_sat(const nxis_int32x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x16_to_int32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_uint32x16_to_int32x16_sat(const nxis_uint32x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x8_to_uint64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_int64x8_to_uint64x8_sat(const nxis_int64x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x8_to_int64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_uint64x8_to_int64x8_sat(const nxis_uint64x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x32_to_float16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_int16x32_to_float16x32_sat(const nxis_int16x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x32_to_int16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_float16x32_to_int16x32_sat(const nxis_float16x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x32_to_float16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_uint16x32_to_float16x32_sat(const nxis_uint16x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x32_to_uint16x32_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_float16x32_to_uint16x32_sat(const nxis_float16x32_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x16_to_float32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_int32x16_to_float32x16_sat(const nxis_int32x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x16_to_int32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_float32x16_to_int32x16_sat(const nxis_float32x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x16_to_float32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_uint32x16_to_float32x16_sat(const nxis_uint32x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x16_to_uint32x16_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_float32x16_to_uint32x16_sat(const nxis_float32x16_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x8_to_float64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_int64x8_to_float64x8_sat(const nxis_int64x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x8_to_int64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_float64x8_to_int64x8_sat(const nxis_float64x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x8_to_float64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_uint64x8_to_float64x8_sat(const nxis_uint64x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x8_to_uint64x8_sat
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_float64x8_to_uint64x8_sat(const nxis_float64x8_t n) {
    ///TODO: add `ifdef`s
    return;
}

//Widening/Narrowing -- masked

/** nxis_int8x16_to_int16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int8x16_to_int16x8_mask(const nxis_int8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int16x8_to_int32x4_mask(const nxis_int16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_int32x4_to_int64x2_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x2_to_int32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int64x2_to_int32x4_mask(const nxis_int64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int32x4_to_int16x8_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int8x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_int16x8_to_int8x16_mask(const nxis_int16x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x16_to_uint16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint8x16_to_uint16x8_mask(const nxis_uint8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint16x8_to_uint32x4_mask(const nxis_uint16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_uint32x4_to_uint64x2_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x2_to_uint32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint64x2_to_uint32x4_mask(const nxis_uint64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint32x4_to_uint16x8_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint8x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_uint16x8_to_uint8x16_mask(const nxis_uint16x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x8_to_float32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float16x8_to_float32x4_mask(const nxis_float16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_float32x4_to_float64x2_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x2_to_float32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float64x2_to_float32x4_mask(const nxis_float64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_float32x4_to_float16x8_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x32_to_int16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int8x32_to_int16x16_mask(const nxis_int8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int16x16_to_int32x8_mask(const nxis_int16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_int32x8_to_int64x4_mask(const nxis_int32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x4_to_int32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int64x4_to_int32x8_mask(const nxis_int64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int32x8_to_int16x16_mask(const nxis_int32x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int8x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_int16x16_to_int8x32_mask(const nxis_int16x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x32_to_uint16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint8x32_to_uint16x16_mask(const nxis_uint8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint16x16_to_uint32x8_mask(const nxis_uint16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_uint32x8_to_uint64x4_mask(const nxis_uint32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x4_to_uint32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint64x4_to_uint32x8_mask(const nxis_uint64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint32x8_to_uint16x16_mask(const nxis_uint32x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint8x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_uint16x16_to_uint8x32_mask(const nxis_uint16x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x16_to_float32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float16x16_to_float32x8_mask(const nxis_float16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_float32x8_to_float64x4_mask(const nxis_float32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x4_to_float32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float64x4_to_float32x8_mask(const nxis_float64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_float32x8_to_float16x16_mask(const nxis_float32x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x64_to_int16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int8x64_to_int16x32_mask(const nxis_int8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int16x32_to_int32x16_mask(const nxis_int16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_int32x16_to_int64x8_mask(const nxis_int32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x8_to_int32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int64x8_to_int32x16_mask(const nxis_int64x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int32x16_to_int16x32_mask(const nxis_int32x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int8x64_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_int16x32_to_int8x64_mask(const nxis_int16x32_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x64_to_uint16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint8x64_to_uint16x32_mask(const nxis_uint8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint16x32_to_uint32x16_mask(const nxis_uint16x32_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_uint32x16_to_uint64x8_mask(const nxis_uint32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x8_to_uint32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint64x8_to_uint32x16_mask(const nxis_uint64x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint32x16_to_uint16x32_mask(const nxis_uint32x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint8x64_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_uint16x32_to_uint8x64_mask(const nxis_uint16x32_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x32_to_float32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float16x32_to_float32x16_mask(const nxis_float16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_float32x16_to_float64x8_mask(const nxis_float32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x8_to_float32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float64x8_to_float32x16_mask(const nxis_float64x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_float32x16_to_float16x32_mask(const nxis_float32x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

//Convert/Cast -- masked

/** nxis_int8x16_to_uint8x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_int8x16_to_uint8x16_mask(const nxis_int8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x16_to_int8x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_uint8x16_to_int8x16_mask(const nxis_uint8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x8_to_uint16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_int16x8_to_uint16x8_mask(const nxis_int16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x8_to_int16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_uint16x8_to_int16x8_mask(const nxis_uint16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x4_to_uint32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_int32x4_to_uint32x4_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x4_to_int32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_uint32x4_to_int32x4_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x2_to_uint64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_int64x2_to_uint64x2_mask(const nxis_int64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x2_to_int64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_uint64x2_to_int64x2_mask(const nxis_uint64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x8_to_float16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_int16x8_to_float16x8_mask(const nxis_int16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x8_to_int16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_float16x8_to_int16x8_mask(const nxis_float16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x8_to_float16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_uint16x8_to_float16x8_mask(const nxis_uint16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x8_to_uint16x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_float16x8_to_uint16x8_mask(const nxis_float16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x4_to_float32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_int32x4_to_float32x4_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x4_to_int32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_float32x4_to_int32x4_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x4_to_float32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_uint32x4_to_float32x4_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x4_to_uint32x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_float32x4_to_uint32x4_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x2_to_float64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_int64x2_to_float64x2_mask(const nxis_int64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x2_to_int64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_float64x2_to_int64x2_mask(const nxis_float64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x2_to_float64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_uint64x2_to_float64x2_mask(const nxis_uint64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x2_to_uint64x2_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_float64x2_to_uint64x2_mask(const nxis_float64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int8x32_to_uint8x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_int8x32_to_uint8x32_mask(const nxis_int8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x32_to_int8x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_uint8x32_to_int8x32_mask(const nxis_uint8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x16_to_uint16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_int16x16_to_uint16x16_mask(const nxis_int16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x16_to_int16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_uint16x16_to_int16x16_mask(const nxis_uint16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x8_to_uint32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_int32x8_to_uint32x8_mask(const nxis_int32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x8_to_int32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_uint32x8_to_int32x8_mask(const nxis_uint32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x4_to_uint64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_int64x4_to_uint64x4_mask(const nxis_int64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x4_to_int64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_uint64x4_to_int64x4_mask(const nxis_uint64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x16_to_float16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_int16x16_to_float16x16_mask(const nxis_int16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x16_to_int16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_float16x16_to_int16x16_mask(const nxis_float16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x16_to_float16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_uint16x16_to_float16x16_mask(const nxis_uint16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x16_to_uint16x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_float16x16_to_uint16x16_mask(const nxis_float16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x8_to_float32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_int32x8_to_float32x8_mask(const nxis_int32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x8_to_int32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_float32x8_to_int32x8_mask(const nxis_float32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x8_to_float32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_uint32x8_to_float32x8_mask(const nxis_uint32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x8_to_uint32x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_float32x8_to_uint32x8_mask(const nxis_float32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x4_to_float64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_int64x4_to_float64x4_mask(const nxis_int64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x4_to_int64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_float64x4_to_int64x4_mask(const nxis_float64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x4_to_float64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_uint64x4_to_float64x4_mask(const nxis_uint64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x4_to_uint64x4_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_float64x4_to_uint64x4_mask(const nxis_float64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int8x64_to_uint8x64_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_int8x64_to_uint8x64_mask(const nxis_int8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x64_to_int8x64_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_uint8x64_to_int8x64_mask(const nxis_uint8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x32_to_uint16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_int16x32_to_uint16x32_mask(const nxis_int16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x32_to_int16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_uint16x32_to_int16x32_mask(const nxis_uint16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x16_to_uint32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_int32x16_to_uint32x16_mask(const nxis_int32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x16_to_int32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_uint32x16_to_int32x16_mask(const nxis_uint32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x8_to_uint64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_int64x8_to_uint64x8_mask(const nxis_int64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x8_to_int64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_uint64x8_to_int64x8_mask(const nxis_uint64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x32_to_float16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_int16x32_to_float16x32_mask(const nxis_int16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x32_to_int16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_float16x32_to_int16x32_mask(const nxis_float16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x32_to_float16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_uint16x32_to_float16x32_mask(const nxis_uint16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x32_to_uint16x32_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_float16x32_to_uint16x32_mask(const nxis_float16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x16_to_float32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_int32x16_to_float32x16_mask(const nxis_int32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x16_to_int32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_float32x16_to_int32x16_mask(const nxis_float32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x16_to_float32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_uint32x16_to_float32x16_mask(const nxis_uint32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x16_to_uint32x16_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_float32x16_to_uint32x16_mask(const nxis_float32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x8_to_float64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_int64x8_to_float64x8_mask(const nxis_int64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x8_to_int64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_float64x8_to_int64x8_mask(const nxis_float64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x8_to_float64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_uint64x8_to_float64x8_mask(const nxis_uint64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x8_to_uint64x8_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_float64x8_to_uint64x8_mask(const nxis_float64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

//Widening/Narrowing -- saturated & masked

/** nxis_int8x16_to_int16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int8x16_to_int16x8_sat_mask(const nxis_int8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int16x8_to_int32x4_sat_mask(const nxis_int16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_int32x4_to_int64x2_sat_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x2_to_int32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_int64x2_to_int32x4_sat_mask(const nxis_int64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x4_to_int16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_int32x4_to_int16x8_sat_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x8_to_int8x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_int16x8_to_int8x16_sat_mask(const nxis_int16x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x16_to_uint16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint8x16_to_uint16x8_sat_mask(const nxis_uint8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint16x8_to_uint32x4_sat_mask(const nxis_uint16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_uint32x4_to_uint64x2_sat_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x2_to_uint32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_uint64x2_to_uint32x4_sat_mask(const nxis_uint64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x4_to_uint16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_uint32x4_to_uint16x8_sat_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x8_to_uint8x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_uint16x8_to_uint8x16_sat_mask(const nxis_uint16x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x8_to_float32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float16x8_to_float32x4_sat_mask(const nxis_float16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_float32x4_to_float64x2_sat_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x2_to_float32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_float64x2_to_float32x4_sat_mask(const nxis_float64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x4_to_float16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_float32x4_to_float16x8_sat_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x32_to_int16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int8x32_to_int16x16_sat_mask(const nxis_int8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int16x16_to_int32x8_sat_mask(const nxis_int16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_int32x8_to_int64x4_sat_mask(const nxis_int32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x4_to_int32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_int64x4_to_int32x8_sat_mask(const nxis_int64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x8_to_int16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_int32x8_to_int16x16_sat_mask(const nxis_int32x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x16_to_int8x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_int16x16_to_int8x32_sat_mask(const nxis_int16x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x32_to_uint16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint8x32_to_uint16x16_sat_mask(const nxis_uint8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint16x16_to_uint32x8_sat_mask(const nxis_uint16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_uint32x8_to_uint64x4_sat_mask(const nxis_uint32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x4_to_uint32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_uint64x4_to_uint32x8_sat_mask(const nxis_uint64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x8_to_uint16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_uint32x8_to_uint16x16_sat_mask(const nxis_uint32x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x16_to_uint8x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_uint16x16_to_uint8x32_sat_mask(const nxis_uint16x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x16_to_float32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float16x16_to_float32x8_sat_mask(const nxis_float16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_float32x8_to_float64x4_sat_mask(const nxis_float32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x4_to_float32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_float64x4_to_float32x8_sat_mask(const nxis_float64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x8_to_float16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_float32x8_to_float16x16_sat_mask(const nxis_float32x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int8x64_to_int16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int8x64_to_int16x32_sat_mask(const nxis_int8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int16x32_to_int32x16_sat_mask(const nxis_int16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_int32x16_to_int64x8_sat_mask(const nxis_int32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int64x8_to_int32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_int64x8_to_int32x16_sat_mask(const nxis_int64x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int32x16_to_int16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_int32x16_to_int16x32_sat_mask(const nxis_int32x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_int16x32_to_int8x64_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_int16x32_to_int8x64_sat_mask(const nxis_int16x32_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint8x64_to_uint16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint8x64_to_uint16x32_sat_mask(const nxis_uint8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint16x32_to_uint32x16_sat_mask(const nxis_uint16x32_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_uint32x16_to_uint64x8_sat_mask(const nxis_uint32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint64x8_to_uint32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_uint64x8_to_uint32x16_sat_mask(const nxis_uint64x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint32x16_to_uint16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_uint32x16_to_uint16x32_sat_mask(const nxis_uint32x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_uint16x32_to_uint8x64_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_uint16x32_to_uint8x64_sat_mask(const nxis_uint16x32_t n, const nxis_mask64_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float16x32_to_float32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float16x32_to_float32x16_sat_mask(const nxis_float16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_float32x16_to_float64x8_sat_mask(const nxis_float32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float64x8_to_float32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_float64x8_to_float32x16_sat_mask(const nxis_float64x8_t n, const nxis_mask16_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

/** nxis_float32x16_to_float16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_float32x16_to_float16x32_sat_mask(const nxis_float32x16_t n, const nxis_mask32_t mask) {
    ///TODO: add `#ifdef`s
    return;
}

//Convert/Cast -- saturated & masked

/** nxis_int8x16_to_uint8x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x16_t nxis_int8x16_to_uint8x16_sat_mask(const nxis_int8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x16_to_int8x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x16_t nxis_uint8x16_to_int8x16_sat_mask(const nxis_uint8x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x8_to_uint16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_int16x8_to_uint16x8_sat_mask(const nxis_int16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x8_to_int16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_uint16x8_to_int16x8_sat_mask(const nxis_uint16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x4_to_uint32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_int32x4_to_uint32x4_sat_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x4_to_int32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_uint32x4_to_int32x4_sat_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x2_to_uint64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_int64x2_to_uint64x2_sat_mask(const nxis_int64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x2_to_int64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_uint64x2_to_int64x2_sat_mask(const nxis_uint64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x8_to_float16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_int16x8_to_float16x8_sat_mask(const nxis_int16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x8_to_int16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x8_t nxis_float16x8_to_int16x8_sat_mask(const nxis_float16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x8_to_float16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x8_t nxis_uint16x8_to_float16x8_sat_mask(const nxis_uint16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x8_to_uint16x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x8_t nxis_float16x8_to_uint16x8_sat_mask(const nxis_float16x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x4_to_float32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_int32x4_to_float32x4_sat_mask(const nxis_int32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x4_to_int32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x4_t nxis_float32x4_to_int32x4_sat_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x4_to_float32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x4_t nxis_uint32x4_to_float32x4_sat_mask(const nxis_uint32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x4_to_uint32x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x4_t nxis_float32x4_to_uint32x4_sat_mask(const nxis_float32x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x2_to_float64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_int64x2_to_float64x2_sat_mask(const nxis_int64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x2_to_int64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x2_t nxis_float64x2_to_int64x2_sat_mask(const nxis_float64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x2_to_float64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x2_t nxis_uint64x2_to_float64x2_sat_mask(const nxis_uint64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x2_to_uint64x2_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x2_t nxis_float64x2_to_uint64x2_sat_mask(const nxis_float64x2_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int8x32_to_uint8x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x32_t nxis_int8x32_to_uint8x32_sat_mask(const nxis_int8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x32_to_int8x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x32_t nxis_uint8x32_to_int8x32_sat_mask(const nxis_uint8x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x16_to_uint16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_int16x16_to_uint16x16_sat_mask(const nxis_int16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x16_to_int16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_uint16x16_to_int16x16_sat_mask(const nxis_uint16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x8_to_uint32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_int32x8_to_uint32x8_sat_mask(const nxis_int32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x8_to_int32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_uint32x8_to_int32x8_sat_mask(const nxis_uint32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x4_to_uint64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_int64x4_to_uint64x4_sat_mask(const nxis_int64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x4_to_int64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_uint64x4_to_int64x4_sat_mask(const nxis_uint64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x16_to_float16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_int16x16_to_float16x16_sat_mask(const nxis_int16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x16_to_int16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x16_t nxis_float16x16_to_int16x16_sat_mask(const nxis_float16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x16_to_float16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x16_t nxis_uint16x16_to_float16x16_sat_mask(const nxis_uint16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x16_to_uint16x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x16_t nxis_float16x16_to_uint16x16_sat_mask(const nxis_float16x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x8_to_float32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_int32x8_to_float32x8_sat_mask(const nxis_int32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x8_to_int32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x8_t nxis_float32x8_to_int32x8_sat_mask(const nxis_float32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x8_to_float32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x8_t nxis_uint32x8_to_float32x8_sat_mask(const nxis_uint32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x8_to_uint32x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x8_t nxis_float32x8_to_uint32x8_sat_mask(const nxis_float32x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x4_to_float64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_int64x4_to_float64x4_sat_mask(const nxis_int64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x4_to_int64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x4_t nxis_float64x4_to_int64x4_sat_mask(const nxis_float64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x4_to_float64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x4_t nxis_uint64x4_to_float64x4_sat_mask(const nxis_uint64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x4_to_uint64x4_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x4_t nxis_float64x4_to_uint64x4_sat_mask(const nxis_float64x4_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int8x64_to_uint8x64_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint8x64_t nxis_int8x64_to_uint8x64_sat_mask(const nxis_int8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint8x64_to_int8x64_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8x64_t nxis_uint8x64_to_int8x64_sat_mask(const nxis_uint8x64_t n, const nxis_mask64_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x32_to_uint16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_int16x32_to_uint16x32_sat_mask(const nxis_int16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x32_to_int16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_uint16x32_to_int16x32_sat_mask(const nxis_uint16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x16_to_uint32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_int32x16_to_uint32x16_sat_mask(const nxis_int32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x16_to_int32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_uint32x16_to_int32x16_sat_mask(const nxis_uint32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x8_to_uint64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_int64x8_to_uint64x8_sat_mask(const nxis_int64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x8_to_int64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_uint64x8_to_int64x8_sat_mask(const nxis_uint64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int16x32_to_float16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_int16x32_to_float16x32_sat_mask(const nxis_int16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x32_to_int16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16x32_t nxis_float16x32_to_int16x32_sat_mask(const nxis_float16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint16x32_to_float16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16x32_t nxis_uint16x32_to_float16x32_sat_mask(const nxis_uint16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float16x32_to_uint16x32_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16x32_t nxis_float16x32_to_uint16x32_sat_mask(const nxis_float16x32_t n, const nxis_mask32_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int32x16_to_float32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_int32x16_to_float32x16_sat_mask(const nxis_int32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x16_to_int32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int32x16_t nxis_float32x16_to_int32x16_sat_mask(const nxis_float32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint32x16_to_float32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float32x16_t nxis_uint32x16_to_float32x16_sat_mask(const nxis_uint32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float32x16_to_uint32x16_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint32x16_t nxis_float32x16_to_uint32x16_sat_mask(const nxis_float32x16_t n, const nxis_mask16_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_int64x8_to_float64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_int64x8_to_float64x8_sat_mask(const nxis_int64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x8_to_int64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_int64x8_t nxis_float64x8_to_int64x8_sat_mask(const nxis_float64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_uint64x8_to_float64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_float64x8_t nxis_uint64x8_to_float64x8_sat_mask(const nxis_uint64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

/** nxis_float64x8_to_uint64x8_sat_mask
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint64x8_t nxis_float64x8_to_uint64x8_sat_mask(const nxis_float64x8_t n, const nxis_mask8_t mask) {
    ///TODO: add `ifdef`s
    return;
}

#endif //_NXS_SIMD_H_