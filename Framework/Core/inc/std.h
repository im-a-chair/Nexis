#ifndef _NXS_STD_H_
#define _NXS_STD_H_
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <float.h>
#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <err.h>

#if (defined(NXS_RELEASE) || defined(NXS_NDEBUG)) && !defined(NDEBUG)
#define NDEBUG
#endif
#include <assert.h>
#define NXS_ASSERT(condition) assert(condition)

#if defined(__GNUC__) || defined(__clang__)
    // GNU GCC and Clang
    #define NXS_ALIGN(N) __attribute__((aligned(N)))
    #define NXS_ALIGNED_MALLOC(size, align) memalign(align, size)
    #define NXS_ALIGNED_FREE(ptr) free(ptr)
#elif defined(_MSC_VER)
    // Microsoft Visual C++
    #define NXS_ALIGN(N) __declspec(align(N))
    #define NXS_ALIGNED_MALLOC(size, align) _aligned_malloc(size, align)
    #define NXS_ALIGNED_FREE(ptr) _aligned_free(ptr)
#elif __STDC_VERSION__ >= 201112L
    // C11 Standard
    #include <stdalign.h>
    #define NXS_ALIGN(N) _Alignas(N)
    #define NXS_ALIGNED_MALLOC(size, align) aligned_alloc(align, size)
    #define NXS_ALIGNED_FREE(ptr) free(ptr)
#else
    // Fallback for older or unsupported compilers
    #error "Compiler not supported for aligned memory; please use GNU gcc, MSVC or C11 and above"
#endif

typedef unsigned int uint_t;
typedef signed int sint_t;

/** NXS_TRY_CALLOC
 * allocates `count`*`sizeof(*type)` bytes to `ptr` using `calloc` or prints error to `stderr`
 * 
 * \param ptr the pointer to allocate (should be declared beforehand)
 * \param type the datatype of `ptr` (NOT the type `ptr` is a pointer to)
 * \param count if `ptr` is an array, the size of the array
 * \param onfail_func the code block to execute on failure
 * 
 * \sa NXS_TRY_CALLOC_LOG
 */
#define NXS_TRY_CALLOC(ptr, type, count, onfail_func) \
    ptr = (type)calloc(count, sizeof(*ptr));           \
    if (!ptr) {                                        \
        fprintf(stderr, "Allocation failed for " #ptr ": %s\n", strerror(errno)); \
        onfail_func;                                   \
        return NULL;                                   \
    }

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
/** TWO_PASS_QUERRY
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

#endif //_NXS_STD_H_