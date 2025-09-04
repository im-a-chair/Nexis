#include "SIMD.h"

//per platform implement backend header
#if defined(__AVX512F__)
    //implement

    //check subsets
    #if defined(__AVX512DQ__)
        //implement
    #endif
    #if defined(__AVX512BW__)
        //implement
    #endif
    #if defined(__AVX512VL__)
        //implement
    #endif
    #if defined(__AVX512CD__)
        //implement
    #endif
    #if defined(__AVX512ER__)
        //implement
    #endif
    #if defined(__AVX512PF__)
        //implement
    #endif

    //newer extensions
    #if defined(__AVX512VBMI__)
        //implement
    #endif
    #if defined(__AVX512VBMI2__)
        //implement
    #endif
    #if defined(__AVX512VNNI__)
        //implement
    #endif
    #if defined(__AVX512POPCNTDQ__)
        //implement
    #endif
    #if defined(__AVX512IFMA__)
        //implement
    #endif
    #if defined(__AVX512_FP16__)
        //implement
    #endif
#elif defined(__AVX2__)
    //implement
#elif defined(__AVX__)
    //implement
#elif defined(__SSE4_2__)
    //implement
#elif defined(__SSE4_2__)
    //implement
#elif defined(__SSE4_1__)
    //implement
#elif defined(__SSSE3__)
    //implement
#elif defined(__SSE3__)
    //implement
#elif defined(__SSE2__)
    //implement
#elif defined(__SSE__)
    //implement
#elif defined(__ARM_FEATURE_SVE)
    //implement
#elif defined(__ARM_NEON)
    //implement
#else
    //implement fallback code
#endif