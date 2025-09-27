#ifndef NXS_STD_H
#define NXS_STD_H
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <err.h>
#include <limits.h>
#include <assert.h>
#define NXS_ASSERT(condition) assert(condition)
#ifdef NXS_STD_USE_SDL3
#include <SDL3/SDL.h>
#endif

//version
#define NXS_VERSION_MAJOR 0 //is alpha
#define NXS_VERSION_MINOR 6 //ECS, Logging, Math, Scene, SIMD & std
#define NXS_VERSION_PATCH 0

//OS detection macros
#if !defined(NXS_PLATFORM_LINUX)   || !defined(NXS_PLATFORM_ANDROID)    || !defined(NXS_PLATFORM_FREEBSD) \
 || !defined(NXS_PLATFORM_NETBSD)  || !defined(NXS_PLATFORM_OPENBSD)    || !defined(NXS_PLATFORM_APPLE)   \
 || !defined(NXS_PLATFORM_WIN32)   || !defined(NXS_PLATFORM_CYGWIN)     || !defined(NXS_PLATFORM_QNXNTO)  \
 || !defined(NXS_PLATFORM_HURD)    || !defined(NXS_PLATFORM_SOLARIS)    || !defined(NXS_PLATFORM_AIX)     \
 || !defined(NXS_PLATFORM_WASM)    || !defined(NXS_PLATFORM_EMSCRIPTEN) || !defined(NXS_PLATFORM_BSDI)    \
 || !defined(NXS_PLATFORM_HAIKU)   || !defined(NXS_PLATFORM_OS2)        || !defined(NXS_PLATFORM_3DS)     \
 || !defined(NXS_PLATFORM_RISCOS)   /*|| !defined(NXS_PLATFORM_CUSTOM)*/
    #if defined(SDL_PLATFORM_LINUX) || defined(__linux__)
        #define NXS_PLATFORM_LINUX __linux__
    #elif defined(SDL_PLATFORM_ANDROID) || defined(__ANDROID__)
        #define NXS_PLATFORM_ANDROID __ANDROID__
    #elif defined(SDL_PLATFORM_FREEBSD) || defined(__FreeBSD__)
        #define NXS_PLATFORM_FREEBSD __FreeBSD__
    #elif defined(SDL_PLATFORM_NETBSD) || defined(__NetBSD__)
        #define NXS_PLATFORM_NETBSD __NetBSD__
    #elif defined(SDL_PLATFORM_OPENBSD) || defined(__OpenBSD__)
        #define NXS_PLATFORM_OPENBSD __OpenBSD__
    #elif defined(SDL_PLATFORM_APPLE) || defined(__APPLE__)
        #define NXS_PLATFORM_APPLE __APPLE__
    #elif defined(SDL_PLATFORM_WINDOWS) || defined(_WIN32)
        #define NXS_PLATFORM_WIN32 _WIN32
    #elif defined(SDL_PLATFORM_CYGWIN) || defined(__CYGWIN__)
        #define NXS_PLATFORM_CYGWIN __CYGWIN__
    #elif defined(SDL_PLATFORM_QNXNTO) || defined(__QNX__) || defined(__QNXNTO__)
        #define NXS_PLATFORM_QNXNTO 1
    #elif defined(SDL_PLATFORM_HURD) || defined(__hurd__) || defined(__gnu_hurd__)
        #define NXS_PLATFORM_HURD 1
    #elif defined(SDL_PLATFORM_SOLARIS) || defined(__sun) || defined(__SVR4)
        #define NXS_PLATFORM_SOLARIS 1
    #elif defined(SDL_PLATFORM_EMSCRIPTEN) || defined(__EMSCRIPTEN__)
        #define NXS_PLATFORM_WASM __EMSCRIPTEN__
        #define NXS_PLATFORM_EMSCRIPTEN __EMSCRIPTEN__
    #elif defined(SDL_PLATFORM_BSDI) || defined(__bsdi__)
        #define NXS_PLATFORM_BSDI __bsdi__
    #elif defined(SDL_PLATFORM_HAIKU) || defined(__HAIKU__)
        #define NXS_PLATFORM_HAIKU __HAIKU__
    #elif defined(SDL_PLATFORM_OS2)|| defined(OS2) || defined(_OS2) || defined(__OS2__)
        #define NXS_PLATFORM_OS2 1
    #elif defined(SDL_PLATFORM_3DS) || defined(__3DS__)
        #define NXS_PLATFORM_3DS __3DS__
    #elif defined(SDL_PLATFORM_RISCOS) || defined(__riscos__) || defined(__riscos)
        #define NXS_PLATFORM_RISCOS 1
    #elif defined(SDL_PLATFORM_AIX) || defined(_AIX)
        #define NXS_PLATFORM_AIX _AIX
    #else
        #error "unsupported OS"
    #endif
#endif

#if defined(NXS_X86) || defined(NXS_X64) || defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
    #if !defined(NXS_X86) && !defined(NXS_X64) && (defined(__x86_64__) || defined(_M_X64))
        #define NXS_X64
        #define NXS_X86 64
    #elif !defined(NXS_X86)
        #define NXS_X86 32
    #endif
    #define NXS_VEC_ALIGN 16
    #define NXS_BYTE_ORDER_LITTLE_ENDIAN 1
#elif defined(NXS_ARM) || defined(NXS_ARM64) || defined(__aarch64__) || defined(_M_ARM64) || defined(__arm__) || defined(_M_ARM)
    #if !defined(NXS_ARM) && !defined(NXS_ARM64) && (defined(__aarch64__) || defined(_M_ARM64))
        #define NXS_ARM64
        #define NXS_ARM 64
        #define NXS_VEC_ALIGN 16
    #elif !defined(NXS_ARM)
        #define NXS_ARM 32
        #define NXS_VEC_ALIGN 8
    #endif

    #ifndef NXS_COMPILER_MSVC
        #if defined(__ARMEB__) || defined(__AARCH64EB__) || (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
            #define NXS_BYTE_ORDER_BIG_ENDIAN -1
        #else
            #define NXS_BYTE_ORDER_LITTLE_ENDIAN 1
        #endif
    #else
        #if defined(__ARMEB__) || defined(__AARCH64EB__)
            #define NXS_BYTE_ORDER_BIG_ENDIAN -1
        #else
            #define NXS_BYTE_ORDER_LITTLE_ENDIAN 1
        #endif
    #endif
#elif !defined(NXS_WASM) && defined(NXS_PLATFORM_WASM)
	#if defined(__wasm64__)
	    #define NXS_WASM 64
        #define NXS_WASM64
	#else
	    #define NXS_WASM 32
	#endif
	#define NXS_VEC_ALIGN 16
    #define NXS_BYTE_ORDER_LITTLE_ENDIAN 1

	#ifdef __wasm_simd128__
        #include <wasm_simd128.h>
        #define NXS_SIMD_WASM
	#endif
#else
	#error "CPU architecture no supported"
#endif

#if defined(__GNUC__)
    #define NXS_COMPILER_GCC __GNUC__
    #ifdef NXS_X86
        #define NXS_BREAKPOINT() asm volatile ("int $0x3")
    #elif defined(NXS_ARM64)
        #define NXS_BREAKPOINT() asm volatile ("brk 0")
    #else
        #define NXS_BREAKPOINT() __builtin_trap()
    #endif
#elif defined(__clang__)
    #define NXS_COMPILER_CLANG __clang__
    #define NXS_BREAKPOINT() __builtin_debugtrap()
#elif defined(_MSC_VER)
    #define NXS_COMPILER_MSVC _MSC_VER
    #define NXS_BREAKPOINT() __debugbreak()
#endif
#if defined(__MINGW64__) || defined (__MINGW32__)
	#define NXS_COMPILER_MINGW
#endif

//SIMD support
#ifdef NXS_X86
    #include <immintrin.h>
    #include <x86intrin.h>

    #ifndef __MMX__
        #error "CPU too old; MMX not supported"
    #endif

    #if !defined(NXS_FP16) && (defined(__F16C__) || defined(__AVX512FP16__))
        #define NXS_F16C __F16C__
        #define NXS_FP16 __fp16
    #endif

    #define NXS_MMX __MMX__
    #if !defined(NXS_SSE) && defined(__SSE__)
        #define NXS_SSE __SSE__
    #endif
    #if !defined(NXS_SSE2) && defined(__SSE2__)
        #define NXS_SSE2 __SSE2__
    #endif
    #if !defined(NXS_SSE3) && defined(__SSE3__)
        #define NXS_SSE3 __SSE3__
    #endif
    #if !defined(NXS_SSSE3) && defined(__SSSE3__)
        #define NXS_SSSE3 __SSSE3__
    #endif
    #if !defined(NXS_SSE4_1) && defined(__SSE4_1__)
        #define NXS_SSE4_1 __SSE4_1__
    #endif
    #if !defined(NXS_SSE4_2) && defined(__SSE4_2__)
        #define NXS_SSE4_2 __SSE4_2__
    #endif
    #if !defined(NXS_AVX) && defined(__AVX__)
        #define NXS_AVX __AVX__
    #endif
    #if !defined(NXS_AVX2) && defined(__AVX2__)
        #define NXS_AVX2 __AVX2__
    #endif
    #if !defined(NXS_AVX512F) && defined(__AVX512F__)
        #define NXS_AVX512F __AVX512F__
    #endif
    #if !defined(NXS_AVX512CD) && defined(__AVX512CD__)
        #define NXS_AVX512CD __AVX512CD__
    #endif
    #if !defined(NXS_AVX512ER) && defined(__AVX512ER__)
        #define NXS_AVX512ER __AVX512ER__
    #endif
    #if !defined(NXS_AVX512PF) && defined(__AVX512PF__)
        #define NXS_AVX512PF __AVX512PF__
    #endif
    #if !defined(NXS_AVX5124FMAPS) && defined(__AVX5124FMAPS__)
        #define NXS_AVX5124FMAPS __AVX5124FMAPS__
    #endif
    #if !defined(NXS_AVX512VL) && defined(__AVX512VL__)
        #define NXS_AVX512VL __AVX512VL__
    #endif
    #if !defined(NXS_AVX512DQ) && defined(__AVX512DQ__)
        #define NXS_AVX512DQ __AVX512DQ__
    #endif
    #if !defined(NXS_AVX512BW) && defined(__AVX512BW__)
        #define NXS_AVX512BW __AVX512BW__
    #endif
    #if !defined(NXS_AVX512VBMI) && defined(__AVX512VBMI__)
        #define NXS_AVX512VBMI __AVX512VBMI__
    #endif
    #if !defined(NXS_AVX512VPOPCNTDQ) && defined(__AVX512VPOPCNTDQ__)
        #define NXS_AVX512VPOPCNTDQ __AVX512VPOPCNTDQ__
    #endif
    #if !defined(NXS_AVX512VBMI2) && defined(__AVX512VBMI2__)
        #define NXS_AVX512VBMI2 __AVX512VBMI2__
    #endif
    #if !defined(NXS_AVX512BITALG) && defined(__AVX512BITALG__)
        #define NXS_AVX512BITALG __AVX512BITALG__
    #endif
    #if !defined(NXS_AVX512VP2INTERSECT) && defined(__AVX512VP2INTERSECT__)
        #define NXS_AVX512VP2INTERSECT __AVX512VP2INTERSECT__
    #endif
    #if !defined(NXS_AVX512FP16) && defined(__AVX512FP16__)
        #define NXS_AVX512FP16 __AVX512FP16__
    #endif
    #if !defined(NXS_AVX512GFNI) && defined(__AVX512GFNI__)
        #define NXS_AVX512GFNI __AVX512GFNI__
    #endif
    #if !defined(NXS_AVX512VAES) && defined(__AVX512VAES__)
        #define NXS_AVX512VAES __AVX512VAES__
    #endif
    #if !defined(NXS_AVX512VPCLMULQDQ) && defined(__AVX512VPCLMULQDQ__)
        #define NXS_AVX512VPCLMULQDQ __AVX512VPCLMULQDQ__
    #endif
    #if !defined(NXS_AVX512IFMA) && defined(__AVX512IFMA__) //(&? __AVX512VL__)
        #define NXS_AVX512IFMA __AVX512IFMA__
        #ifdef NXS_AVX512VL
            #define NXS_AVX512IFMAVL
        #endif
    #endif
    #if !defined(NXS_FMA) && defined(__FMA__)
        #define NXS_FMA __FMA__
    #endif
    #if !defined(NXS_FMA4) && defined(__FMA4__)
        #define NXS_FMA4 __FMA4__
    #endif
#elif defined(NXS_ARM)
    #if !defined(NXS_ARM_FP16) && defined(__ARM_FEATURE_FP16_SCALAR_ARITHMETIC)
        #define NXS_FP16 __fp16
        #define NXS_ARM_FP16 __ARM_FEATURE_FP16_SCALAR_ARITHMETIC
    #endif
    #if !defined(NXS_ARM_NEON) && defined(__ARM_NEON)
        #define NXS_ARM_NEON __ARM_NEON
        #ifdef __ARM_NEON_FP16_
            #define NXS_ARM_NEON_FP16 __ARM_NEON_FP16_
        #endif
    #endif
    #if !defined(NXS_ARM_SVE) && defined(__ARM_FEATURE_SVE)
        #define NXS_ARM_SVE __ARM_FEATURE_SVE
    #endif

    #ifdef NXS_ARM_FP16
        #include <arm_fp16.h>
    #endif
    #ifdef NXS_ARM_SVE
        #include <arm_sve.h>
    #endif
    #ifdef NXS_ARM_NEON
        #ifdef NXS_COMPILER_MSVC
            #ifdef NXS_ARM64
                #include <arm64_neon.h>
            #else
                #include <intrin.h>
            #endif
        #else
            #include <arm_neon.h>

            #ifdef NXS_ARM_SVE
                #include <arm_neon_sve_bridge.h>
            #endif
        #endif
    #endif
#endif

//export visibility macro, mostly for C++
#ifdef NXS_COMPILER_MSVC
    #define NXS_EXPORT __declspec(dllexport)
#elif defined(NXS_COMPILER_GCC) || defined(NXS_COMPILER_CLANG)
    #define NXS_EXPORT __attribute__((visibility("default")))
#endif

#if (defined(NXS_RELEASE) || defined(NXS_NDEBUG)) && !defined(NDEBUG)
    #define NDEBUG
    #define NXS_IF_DEBUG(...)
    #define NXS_IF_RELEASE(...) __VA_ARGS__
#elif !defined(NXS_DEBUG)
    #define NXS_DEBUG
    #define NXS_IF_DEBUG(...) __VA_ARGS__
    #define NXS_IF_RELEASE(...)
#else
    #define NXS_IF_DEBUG(...) __VA_ARGS__
    #define NXS_IF_RELEASE(...)
#endif

#ifdef NXS_NO_FORCE_INLINE
    #define NXS_INLINE inline
    #define NXS_STATIC_INLINE static inline
#elif defined(NXS_COMPILER_GCC) || defined(NXS_COMPILER_CLANG)
	#define NXS_INLINE __inline__ __attribute__((always_inline))
	#define NXS_STATIC_INLINE static __inline__ __attribute__((always_inline))
#elif defined(NXS_COMPILER_MSVC)
	#define NXS_INLINE __forceinline
	#define NXS_STATIC_INLINE static __forceinline
#else
	#error "compiler not supported"
#endif

#if defined(NXS_COMPILER_GCC) || defined(NXS_COMPILER_CLANG)
    #define NXS_ALLOC_FUNC __attribute__((malloc))
#elif defined(NXS_COMPILER_MSVC)
    #define NXS_ALLOC_FUNC _Ret_maybenull_ __declspec(restrict) __declspec(noalias)
#else
	#error "compiler not supported"
#endif

#if defined(NXS_COMPILER_GCC) || defined(NXS_COMPILER_CLANG)
    #include <malloc.h>
    #define NXS_ALIGN(N) __attribute__((aligned(N)))
    #define NXS_ALIGNED_MALLOC(size, align) memalign(align, size)
    #define NXS_ALIGNED_FREE(ptr) free(ptr)
#elif defined(NXS_COMPILER_MSVC)
    #include <malloc.h>
    #define NXS_ALIGN(N) __declspec(align(N))
    #define NXS_ALIGNED_MALLOC(size, align) _aligned_malloc(size, align)
    #define NXS_ALIGNED_FREE(ptr) _aligned_free(ptr)
#else
    #error "compiler not supported"
#endif

//stdint
typedef unsigned int nxis_uint_t;
typedef signed int nxis_int_t;
typedef int8_t nxis_int8_t;
typedef uint8_t nxis_uint8_t;
typedef int16_t nxis_int16_t;
typedef uint16_t nxis_uint16_t;
typedef int32_t nxis_int32_t;
typedef uint32_t nxis_uint32_t;
typedef int64_t nxis_int64_t;
typedef uint64_t nxis_uint64_t;
#warning "using fallback `nxis_float32_t` and `nxis_float64_t` definitions as `float` and `double`, not guaranteed to be 32 & 64 bits, use with caution!"
typedef float nxis_float32_t NXS_ALIGN(4);
typedef double nxis_float64_t NXS_ALIGN(8);

// ----- Two-Pass Querry Macro -----

#define _NXS_TPQ_GET_MACRO(_1, _2, _3, _4, _5, _6, NAME, ...) NAME
#define NXS_TWO_PASS_QUERY_EXT_FARGS_0(func, largs, rsize, type, rdata) \
    do { \
        (func)(&(rsize), NULL, ##largs); \
        (rdata) = (type*)calloc(1, sizeof(type) * (rsize)); \
        if ((rdata) != NULL) { \
            (func)(&(rsize), (rdata), ##largs); \
        } else { \
            (rsize) = 0; \
        } \
    } while(false)
#define NXS_TWO_PASS_QUERY_EXT_FARGS(func, fargs, largs, rsize, type, rdata) \
    do { \
        (func)(fargs, &(rsize), NULL, ##largs); \
        (rdata) = (type*)calloc(1, sizeof(type) * (rsize)); \
        if ((rdata) != NULL) { \
            (func)(fargs, &(rsize), (rdata), ##largs); \
        } else { \
            (rsize) = 0; \
        } \
    } while(false)
#define NXS_TWO_PASS_QUERY_SRET_EXT_FARGS_0(func, largs, rsize, type, rdata) \
    do { \
        (rsize) = (func)(NULL, ##largs); \
        (rdata) = (type*)calloc(1, sizeof(type) * (rsize)); \
        if ((rdata) != NULL) { \
            (func)((rdata), ##largs); \
        } else { \
            (rsize) = 0; \
        } \
    } while(false)
#define NXS_TWO_PASS_QUERY_SRET_EXT_FARGS(func, fargs, largs, rsize, type, rdata) \
    do { \
        (rsize) = (func)(fargs, NULL, ##largs); \
        (rdata) = (type*)calloc(1, sizeof(type) * (rsize)); \
        if ((rdata) != NULL) { \
            (func)(fargs, (rdata), ##largs); \
        } else { \
            (rsize) = 0; \
        } \
    } while(false)
/** NXS_TWO_PASS_QUERRY
 * used to simplefy a two pass querry
 * (uses `calloc` for allocation)
 * 
 * \warning `rdata` SHOULD STILL BE FREED
 * 
 * \param func the function to use (should not have any braces nor args)
 * \param fargs (first-args) the args to pass before the size and data
 * \param largs (last-args) the args to pass after the size and data
 * \param rsize the variable to store the size in (should not be a pointer), is 0 on failure
 * \param type the type of rdata (minus the pointer op) to use in allocation
 * \param rdata the pointer to a type of type `type` to store the return data in
 */
#define NXS_TWO_PASS_QUERY(func, ...) \
    _NXS_TPQ_GET_MACRO(__VA_ARGS__, NXS_TWO_PASS_QUERY_EXT_FARGS, NXS_TWO_PASS_QUERY_EXT_FARGS_0)(func, ##__VA_ARGS__)
/* like `TWO_PASS_QUERY`, but for functions that return the size instead of using an arg */
#define NXS_TWO_PASS_QUERRY_SIZE_RET_FUNC(func, ...) \
    _NXS_TPQ_GET_MACRO(__VA_ARGS__, NXS_TWO_PASS_QUERY_SRET_EXT_FARGS, NXS_TWO_PASS_QUERY_SRET_EXT_FARGS_0)(func, ##__VA_ARGS__)

#endif //NXS_STD_H