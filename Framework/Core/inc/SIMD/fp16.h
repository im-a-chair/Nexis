#ifndef _NXS_FP16_H_
#define _NXS_FP16_H_
#include "std.h"
#include "SIMD/simd.h"

///TODO: account for atomics

//half-precision floating point
#ifdef NXS_FP16
typedef __fp16 nxis_float16_t;
#else
    #warning "using fallback software implementation of `nxis_float16_t`, please make sure to use dedicated functions to control the value"
    /* layout (IEEE754 half presision)
        0 00000 0000000000
        │ └─┬─┘ └──┬─────┘
        │   │      └─ mantissa (M) 10 bits; number after decimal point
        │   └─ exponent (E) 5 bits; has bias of `15`; value is `E + 15`
        └─ sign bit (S) 1 bit; 0 for positive, 1 for negative
    */
    typedef nxis_uint16_t  nxis_float16_t;

    //constants
    #warning "assuming IEEE754 for float32"
    #define NXS_F32_EXP_BIAS 127
    #define NXS_F16_EXP_BIAS 15
    #define NXS_F16_EXP_MAX  30  // max exponent val. before infinity (31 is Inf/NaN)
    #define NXS_F16_MANT_BITS 10 // float16 mantissa size
#endif

/** nxis_float16_to_float32
 * Casts/Converts a `nxis_float16_t` to a `nxis_float32_t` (which can often be directly cast to a simple `float`)
 * 
 * \returns the `nxis_float32_t` conversion of the supplied `nxis_float16_t` value
 * \param f the `nxis_float16_t` value to convert to a `nxis_float32_t` value
 * 
 * On x86 with AVX, it'll use `_mm_cvtsh_ss`, other wise `_mm_cvtss_f32(_mm_cvtph_ps((__m128i*)&f))` will be used
 * 
 * On ARM, `vld1_lane_f16` is used, followed by `vcvt_f32_f16`, with lastly `vgetq_lane_f32` to 'devectorize' it
 * 
 * The fallback tries to use masking for a (near) branchless convertion,
 * there is still one conditional which checks if the number is denormal
 * and returns if not, to avoid the more complex/expensive code used for
 * a denormal number, which uses `__builtin_clz` on gcc/clang
 * and a while loop on MSVC.
 * 
 * \note the fallback will only work on little-endian systems,
 *  though near all x86 and arm systems are little endian,
 *  so this shouldnt be a problem.
 * 
 * \todo TODO: clean up math (like in `nxis_float32_to_float16`) and improve/simplefy denormal calculation
 */
NXS_STATIC_INLINE nxis_float32_t nxis_float16_to_float32(const nxis_float16_t f) {
#ifdef NXS_FP16
    #ifdef NXS_AVX512F
        return _mm_cvtsh_ss(f);
    #elif defined(NXS_F16C)
        return _mm_cvtss_f32(_mm_cvtph_ps((__m128i*)&f));
    #elif defined(NXS_ARM)
        register float16x4_t h_vec = vld1_lane_f16(&h, vdup_n_f16(0.0f16), 0); //convert to vec
        register float32x4_t f_vec = vcvt_f32_f16(h_vec); //convert to fp32
        return vgetq_lane_f32(f_vec, 0); //convert to scalar & return
    #endif
#else
    NXS_ASSERT(NXS_BYTE_ORDER_LITTLE_ENDIAN == 1); //assuring little endian, should be the case for both x86 and arm

    register nxis_uint32_t f32 = 0; //should be accumulator (i.e. return register)

    //get float16 components
    register nxis_uint32_t sign     = (nxis_uint32_t)(f & 0x8000) >> 15;
    register nxis_uint32_t exponent = (f & 0x7C00) >> 10;
    register nxis_uint32_t mantissa = f & 0x03FF;

    // set sign bit
    f32 |= sign << 31;

    register bool MantZero = (mantissa == 0x00);
    register bool ExpFull = (exponent == 0x1F);
    register bool ExpZero = (exponent == 0x00);
    register bool Inf = (ExpFull && MantZero);
    register bool NaN = (ExpFull && !MantZero);
    //register bool Zero = (ExpZero && MantZero);
    register bool Denormal = (ExpZero && !MantZero);
    register bool Normal = !Inf && !NaN && !Denormal/*&& !Zero*/;

    //if exponent all ones (0xFF) and mantissa is 0; Inf (infinity),
    f32 |= (0x7F800000 * Inf);

    //if exponent all ones (0xFF) and mantissa != 0; NaN (Not a Number),
    f32 |= (0x7FC00000 * NaN); //use quiet NaN (most significant mantissa bit set)

    //if exponent is not all ones and not 0, its a normal number
    f32 |= (
        ((exponent - NXS_F16_EXP_BIAS + NXS_F32_EXP_BIAS) << 23) | //exponent: (f32_exp = f16_exp - 15 + 127)
        (mantissa << (23 - NXS_F16_MANT_BITS)) //mantissa: (shift left by 13; from 10 to 23)
        * Normal);

    //if not denormal, avoid complex/expensive (clz) code
    if (!Denormal) {
        return *(nxis_float32_t*)&f32;
    }

    //else (exponent == 0); exponent is denormal (or zero, but zero has already been handled)
    register nxis_uint32_t f32_Denormal = 0;

#if defined(NXS_COMPILER_CLANG) || defined(NXS_COMPILER_GCC)
    //the number of leading zeros in the 10-bit mantissa field.
    register int lead_zeros_mantissa = __builtin_clz(mantissa) - (32 - NXS_F16_MANT_BITS); 

    //exponent = -1 + 1 (for the hidden bit) - lead_zeros_mantissa 
    //new_exponent = 1 - lead_zeros_mantissa + NXS_F32_EXP_BIAS
    register nxis_int32_t f32_exponent = 1 - lead_zeros_mantissa + NXS_F32_EXP_BIAS;

    //mantissa: shift left by lead_zeros_mantissa to normalize, then remove the implicit '1' and align.
    register nxis_uint32_t denorm_mantissa = mantissa << lead_zeros_mantissa;

    //align mantissa to 23 bits (remove implicit '1' and shift to position 0)
    denorm_mantissa &= 0x07FFFFF; //mask out the leading '1' and higher bits
    denorm_mantissa <<= (23 - NXS_F16_MANT_BITS); //align to the 32-bit mantissa slot
    
    f32_Denormal = ((nxis_uint32_t)f32_exponent << 23) | denorm_mantissa;
#else
    //denormalized: Must normalize for the 32-bit format.
    //start with the smallest normal exponent (1 - NXS_F32_EXP_BIAS)
    register nxis_int32_t f32_exponent = 1;
    register nxis_uint32_t f32_mantissa = mantissa; // 10 bits

    //reconstruct the hidden '1' bit for denormalized numbers
    //search for the leading '1' and shift until it's in the 11th bit position (hidden bit).
    while ((f32_mantissa & 0x0400) == 0) {
        f32_mantissa <<= 1;
        f32_exponent -= 1;
    }

    //subtract the implicit '1' and shift the mantissa to the 23-bit position
    f32_mantissa &= 0x03FF; // Remove the implicit leading '1'
    f32_mantissa <<= (23 - NXS_F16_MANT_BITS);

    //new 32-bit Exponent is the calculated value + NXS_F32_EXP_BIAS
    f32_exponent += NXS_F32_EXP_BIAS; 

    f32 |= (nxis_uint32_t)f32_exponent << 23;
    f32 |= f32_mantissa;
#endif //compiler == clang | gcc
    return *(nxis_float32_t*)&f32;
#endif //NXS_FP16
}

/** nxis_float32_to_float16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_float32_to_float16(const nxis_float32_t f) {
#ifdef NXS_FP16
    #ifdef NXS_AVX512F
        return _mm_cvtss_sh(f);
    #elif defined(NXS_F16C)
        register __m128 f_vec = _mm_set_ss(*(__m128i*)&f);
        register __m128i h_vec = _mm_cvtps_ph(f_vec, _MM_FROUND_CUR_DIRECTION); 
        return *(nxis_float16_t*)&h_vec;
    #elif defined(NXS_ARM)
        register float32x4_t f_vec = vmovq_n_f32(f); //vectorize
        register float16x4_t h_vec = vcvt_f16_f32(f_vec); //convert
        return vget_lane_f16(h_vec, 0); //devectorize & return
    #endif
#else
    NXS_ASSERT(NXS_BYTE_ORDER_LITTLE_ENDIAN == 1); //assuring little endian, should be the case for both x86 and arm

    register nxis_uint32_t f32 = *(nxis_uint32_t*)&f; 
    register nxis_float16_t f16 = 0;

    //type  mantissa                exp     s
    //fp16 0000000000              00000    0
    //fp32 00000000000000000000000 00000000 0

    //get float components
    register nxis_uint32_t sign = (f32 >> 16) & 0x8000;
    register nxis_uint32_t exponent = (f32 >> 23) & 0xFF;
    register nxis_uint32_t mantissa = f32 & 0x7FFFFF;

    //transfer sign bit
    f16 |= (nxis_uint16_t)(sign >> 16);

    //register bool Zero = (exponent == 0 && mantissa == 0) || (exponent < -10);
    register bool Inf = (exponent == 0xFF && mantissa == 0) || (exponent >= 31);
    register bool NaN = (exponent == 0xFF && mantissa != 0);
    //register bool Denormal = (exponent <= 0 && exponent >= -10 && mantissa == 0);

    f16 |= (nxis_uint16_t)(0x7C00) * Inf; // 0x7C00 = 0 11111 0000000000 (Inf)
    f16 |= (nxis_uint16_t)(0x7E00) * NaN; // 0x7E00 = 0 11111 1000000000 (QNaN)

    exponent += (NXS_F16_EXP_BIAS - NXS_F32_EXP_BIAS) * !(Inf | NaN); // norm num exponent

    ///TODO: calculate denormal, for now, treat as signed zero

    exponent = exponent << (10 * !(Inf | NaN)); // 5-bit exponent in bits 14-10
    mantissa = mantissa >> (13 * !(Inf | NaN)); // 10-bit significand in bits 9-0 (23-13=10 bits kept)

    return f16;
#endif
}

/** nxis_float16_to_uint16
 * TODO:
 */
NXS_STATIC_INLINE nxis_uint16_t nxis_float16_to_uint16(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_uint16_to_float16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_uint16_to_float16(const nxis_uint16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_float16_to_int16
 * TODO:
 */
NXS_STATIC_INLINE nxis_int16_t nxis_float16_to_int16(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_int16_to_float16
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_int16_to_float16(const nxis_int16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_addh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_addh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_subh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_subh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_mulh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_mulh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_divh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_divh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_absh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_absh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_signh
 * TODO:
 */
NXS_STATIC_INLINE nxis_int8_t nxis_signh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_sqrth
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_sqrth(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_logh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_logh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_log2h
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_log2h(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_log10h
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_log10h(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_powh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_powh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_exph
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_exph(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_minh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_minh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_maxh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_maxh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_noth
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_noth(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_andh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_andh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_orh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_orh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_xorh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_xorh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_eqh
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_eqh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_gth
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_gth(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_lth
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_lth(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_geh
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_geh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_leh
 * TODO:
 */
NXS_STATIC_INLINE bool nxis_leh(const nxis_float16_t a, const nxis_float16_t b) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_shftlh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_shftlh(const nxis_float16_t f, const nxis_uint_t count) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_shftrh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_shftrh(const nxis_float16_t f, const nxis_uint_t count) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_rotlh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_rotlh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_rotrh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_rotrh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_ceilh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_ceilh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_trunch
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_trunch(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

/** nxis_floorh
 * TODO:
 */
NXS_STATIC_INLINE nxis_float16_t nxis_floorh(const nxis_float16_t f) {
#ifdef NXS_FP16
    return;
#else
    return;
#endif
}

#endif //_NXS_FP16_H_