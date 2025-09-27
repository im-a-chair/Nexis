#include "Jobs.h"
#include "std.h"
#include "SIMD/simd.h"

///TODO: add wrapers to make `_nxis_save_context` and `_nxis_load_context` work with rip/eip/pc/r15; i.e. yield-resume functions

#ifdef NXS_COMPILER_MSVC
__pragma(pack(push, 1));
#endif
typedef struct _nxis_context_T {
#ifdef NXS_X64
    nxis_uint64_t rip;
    nxis_uint64_t rbp;
    nxis_uint64_t rsp;
    nxis_uint64_t rbx;
    nxis_uint64_t rdi;
    nxis_uint64_t rsi;
    nxis_uint64_t r12;
    nxis_uint64_t r13;
    nxis_uint64_t r14;
    nxis_uint64_t r15;
    #if defined(NXS_AVX) && defined(NXS_PLATFORM_WIN32)
        nxis_float32x8_t ymm6;
        nxis_float32x8_t ymm7;
        nxis_float32x8_t ymm8;
        nxis_float32x8_t ymm9;
        nxis_float32x8_t ymm10;
        nxis_float32x8_t ymm11;
        nxis_float32x8_t ymm12;
        nxis_float32x8_t ymm13;
        nxis_float32x8_t ymm14;
        nxis_float32x8_t ymm15;
    #elif defined(NXS_SSE2) && defined(NXS_PLATFORM_WIN32)
        nxis_float32x4_t xmm6;
        nxis_float32x4_t xmm7;
        nxis_float32x4_t xmm8;
        nxis_float32x4_t xmm9;
        nxis_float32x4_t xmm10;
        nxis_float32x4_t xmm11;
        nxis_float32x4_t xmm12;
        nxis_float32x4_t xmm13;
        nxis_float32x4_t xmm14;
        nxis_float32x4_t xmm15;
    #endif //NXS_SSE2 && NXS_PLATFORM_WIN32
#elif defined(NXS_X86)
    nxis_uint32_t eip;
    nxis_uint32_t ebp;
    nxis_uint32_t esp;
    nxis_uint32_t ebx;
    nxis_uint32_t edi;
    nxis_uint32_t esi;
#elif defined(NXS_ARM64)
    nxis_uint64_t PC;
    nxis_uint64_t X19;
    nxis_uint64_t X20;
    nxis_uint64_t X21;
    nxis_uint64_t X22;
    nxis_uint64_t X23;
    nxis_uint64_t X24;
    nxis_uint64_t X25;
    nxis_uint64_t X26;
    nxis_uint64_t X27;
    nxis_uint64_t X28;
    nxis_uint64_t X29;
    nxis_uint64_t X30;
    nxis_uint64_t SP;
    #ifdef NXS_ARM_NEON
        nxis_float32x4_t V8;
        nxis_float32x4_t V9;
        nxis_float32x4_t V10;
        nxis_float32x4_t V11;
        nxis_float32x4_t V12;
        nxis_float32x4_t V13;
        nxis_float32x4_t V14;
        nxis_float32x4_t V15;
    #endif
    #ifdef NXS_ARM_SVE
        nxis_float32x16_t Z8;
        nxis_float32x16_t Z9;
        nxis_float32x16_t Z10;
        nxis_float32x16_t Z11;
        nxis_float32x16_t Z12;
        nxis_float32x16_t Z13;
        nxis_float32x16_t Z14;
        nxis_float32x16_t Z15;
    #endif
#elif defined(NXS_ARM)
    nxis_uint32_t R4;
    nxis_uint32_t R5;
    nxis_uint32_t R6;
    nxis_uint32_t R7;
    nxis_uint32_t R8;
    nxis_uint32_t R9;
    nxis_uint32_t R10;
    nxis_uint32_t R11;
    nxis_uint32_t R13; //SP
    nxis_uint32_t R14; //LR
    nxis_uint32_t R15; //PC
    #ifdef NXS_ARM_NEON
        nxis_uint64_t D8;
        nxis_uint64_t D9;
        nxis_uint64_t D10;
        nxis_uint64_t D11;
        nxis_uint64_t D12;
        nxis_uint64_t D13;
        nxis_uint64_t D14;
        nxis_uint64_t D15;
    #endif
#endif
}
#if defined(NXS_COMPILER_GCC) || defined(NXS_COMPILER_CLANG)
__attribute__((packed))
#endif
_nxis_context;
#ifdef NXS_COMPILER_MSVC
__pragma(pack(pop));
#endif

///TODO: use SIMD to store in parralel (for ARM, can use `vstmia`/`vstm` to store multiple `dN` registers at a time)
///TODO: Fix SVE store/load logic, currently flawed due to the variable lenght of the `zN` registers
static void _nxis_save_context(_nxis_context* context_buf) {
#ifdef NXS_COMPILER_MSVC
    #ifdef NXS_X64
        __asm {
            //mov [context_buf + 0x00], rip
            mov [context_buf + 0x08], rbp
            mov [context_buf + 0x10], rsp
            mov [context_buf + 0x18], rbx
            mov [context_buf + 0x20], rdi
            mov [context_buf + 0x28], rsi
            mov [context_buf + 0x30], r12
            mov [context_buf + 0x38], r13
            mov [context_buf + 0x40], r14
            mov [context_buf + 0x48], r15
        #if defined(NXS_AVX) && defined(NXS_PLATFORM_WIN32)
            vmovaps [context_buf + 0x050], ymm6
            vmovaps [context_buf + 0x070], ymm7
            vmovaps [context_buf + 0x090], ymm8
            vmovaps [context_buf + 0x0B0], ymm9
            vmovaps [context_buf + 0x0D0], ymm10
            vmovaps [context_buf + 0x0F0], ymm11
            vmovaps [context_buf + 0x110], ymm12
            vmovaps [context_buf + 0x130], ymm13
            vmovaps [context_buf + 0x150], ymm14
            vmovaps [context_buf + 0x170], ymm15
        #elif defined(NXS_SSE2) && defined(NXS_PLATFORM_WIN32)
            movaps [context_buf + 0x50], xmm6
            movaps [context_buf + 0x60], xmm7
            movaps [context_buf + 0x70], xmm8
            movaps [context_buf + 0x80], xmm9
            movaps [context_buf + 0x90], xmm10
            movaps [context_buf + 0xA0], xmm11
            movaps [context_buf + 0xB0], xmm12
            movaps [context_buf + 0xC0], xmm13
            movaps [context_buf + 0xD0], xmm14
            movaps [context_buf + 0xE0], xmm15
        #endif //NXS_(SSE2|AVX) && NXS_PLATFORM_WIN32
        };
    #elif defined(NXS_X86)
        __asm {
            //mov [context_buf + 0x00], eip
            mov [context_buf + 0x04], ebp
            mov [context_buf + 0x08], esp
            mov [context_buf + 0x0C], ebx
            mov [context_buf + 0x10], edi
            mov [context_buf + 0x14], esi
        };
    #elif defined(NXS_ARM64)
        #error "arm inline asm isn't (sufficiently) supported on msvc"
    #elif defined(NXS_ARM)
        #error "arm inline asm isn't (sufficiently) supported on msvc"
    #else
        #error "CPU architecture not supported"
    #endif
#elif defined(NXS_COMPILER_CLANG) || defined(NXS_COMPILER_GCC)
    #ifdef NXS_X64
        asm volatile (
            //"movq %rip, 0x00(%0)"
            "movq %rbp, 0x08(%0)"
            "movq %rsp, 0x10(%0)"
            "movq %rbx, 0x18(%0)"
            "movq %rdi, 0x20(%0)"
            "movq %rsi, 0x28(%0)"
            "movq %r12, 0x30(%0)"
            "movq %r13, 0x38(%0)"
            "movq %r14, 0x40(%0)"
            "movq %r15, 0x48(%0)"
            : //out -- none
            : "r" (context_buf) //in
        );
        #if defined(NXS_AVX) && defined(NXS_PLATFORM_WIN32)
            asm volatile (
                "vmovaps %ymm6,  0x050(%0)"
                "vmovaps %ymm7,  0x070(%0)"
                "vmovaps %ymm8,  0x090(%0)"
                "vmovaps %ymm9,  0x0B0(%0)"
                "vmovaps %ymm10, 0x0D0(%0)"
                "vmovaps %ymm11, 0x0F0(%0)"
                "vmovaps %ymm12, 0x110(%0)"
                "vmovaps %ymm13, 0x130(%0)"
                "vmovaps %ymm14, 0x150(%0)"
                "vmovaps %ymm15, 0x170(%0)"
                : //out -- none
                : "r" (context_buf) //in
            );
        #elif defined(NXS_SSE2) && defined(NXS_PLATFORM_WIN32)
            asm volatile (
                "movaps %xmm6,  0x50(%0)"
                "movaps %xmm7,  0x60(%0)"
                "movaps %xmm8,  0x70(%0)"
                "movaps %xmm9,  0x80(%0)"
                "movaps %xmm10, 0x90(%0)"
                "movaps %xmm11, 0xA0(%0)"
                "movaps %xmm12, 0xB0(%0)"
                "movaps %xmm13, 0xC0(%0)"
                "movaps %xmm14, 0xD0(%0)"
                "movaps %xmm15, 0xE0(%0)"
                : //out -- none
                : "r" (context_buf) //in
            );
        #endif //NXS_(SSE2|AVX) && NXS_PLATFORM_WIN32
    #elif defined(NXS_X86)
        asm volatile (
            //"movl %eip, 0x00(%0)"
            "movl %ebp, 0x04(%0)"
            "movl %esp, 0x08(%0)"
            "movl %ebx, 0x0C(%0)"
            "movl %edi, 0x10(%0)"
            "movl %esi, 0x14(%0)"
            : //out -- none
            : "r" (context_buf) //in
        );
    #elif defined(NXS_ARM64)
        int arm_neon_offset = 0;
        asm volatile (
            //"str %x30, [%[ptr], 0x00]" //PC
            "str %x19, [%[ptr], 0x08]"
            "str %x20, [%[ptr], 0x10]"
            "str %x21, [%[ptr], 0x18]"
            "str %x22, [%[ptr], 0x20]"
            "str %x23, [%[ptr], 0x28]"
            "str %x24, [%[ptr], 0x30]"
            "str %x25, [%[ptr], 0x38]"
            "str %x26, [%[ptr], 0x40]"
            "str %x27, [%[ptr], 0x48]"
            "str %x28, [%[ptr], 0x50]"
            "str %x29, [%[ptr], 0x58]"
            "str %x30, [%[ptr], 0x60]"
            "mov %x10, %sp"
            "str %x10, [%[ptr], 0x68]"
            : //out -- none
            : [ptr] "r" (context_buf) //in
            : "x10" //write registers
        );
        #ifdef NXS_ARM_NEON
            asm volatile (
                "str %v8,  [%[ptr], 0x70]"
                "str %v9,  [%[ptr], 0x80]"
                "str %v10, [%[ptr], 0x90]"
                "str %v11, [%[ptr], 0xA0]"
                "str %v12, [%[ptr], 0xB0]"
                "str %v13, [%[ptr], 0xC0]"
                "str %v14, [%[ptr], 0xD0]"
                "str %v15, [%[ptr], 0xE0]"
                : //out -- none
                : [ptr] "r" (context_buf) //in
            );
            arm_neon_offset += 1024; //8 * sizeof(nxis_float32x4_t);
        #endif
        #ifdef NXS_ARM_SVE
            asm volatile (
                //assuming offset of 0x70 from base registers (with `+ offset` for NEON ofc.)
                "str %z8,  [%[ptr], 0x070 + %[offset]]"
                "str %z9,  [%[ptr], 0x270 + %[offset]]"
                "str %z10, [%[ptr], 0x470 + %[offset]]"
                "str %z11, [%[ptr], 0x670 + %[offset]]"
                "str %z12, [%[ptr], 0x870 + %[offset]]"
                "str %z13, [%[ptr], 0xA70 + %[offset]]"
                "str %z14, [%[ptr], 0xC70 + %[offset]]"
                "str %z15, [%[ptr], 0xE70 + %[offset]]"
                : //out -- none
                : [ptr] "r" (context_buf), [offset] "r" (arm_neon_offset) //in
            );
        #endif
    #elif defined(NXS_ARM)
        asm volatile (
            "str %r4,  [%[ptr], 0x00]"
            "str %r5,  [%[ptr], 0x04]"
            "str %r6,  [%[ptr], 0x08]"
            "str %r7,  [%[ptr], 0x0C]"
            "str %r8,  [%[ptr], 0x10]"
            "str %r9,  [%[ptr], 0x14]"
            "str %r10, [%[ptr], 0x18]"
            "str %r11, [%[ptr], 0x1C]"
            "str %r13, [%[ptr], 0x20]" //SP
            "str %r14, [%[ptr], 0x24]" //LR
            //"str %r15, [%[ptr], 0x28]" //PC
            : //out -- none
            : [ptr] "r" (context_buf)
        );
        #ifdef NXS_ARM_NEON
            asm volatile (
                "str d8,  [%[ptr], 0x02C]"
                "str d9,  [%[ptr], 0x034]"
                "str d10, [%[ptr], 0x03C]"
                "str d11, [%[ptr], 0x044]"
                "str d12, [%[ptr], 0x04C]"
                "str d13, [%[ptr], 0x054]"
                "str d14, [%[ptr], 0x05C]"
                "str d15, [%[ptr], 0x064]"
                : //out -- none
                : [ptr] "r" (context_buf)
            );
        #endif
    #else
        #error "CPU architecture not supported"
    #endif
#else
    #error "compiler not supported"
#endif
}

static void _nxis_load_context(_nxis_context* context_buf) {
#ifdef NXS_COMPILER_MSVC
    #ifdef NXS_X64
        __asm {
            //mov rip, [context_buf + 0x00]
            mov rbp, [context_buf + 0x08]
            mov rsp, [context_buf + 0x10]
            mov rbx, [context_buf + 0x18]
            mov rdi, [context_buf + 0x20]
            mov rsi, [context_buf + 0x28]
            mov r12, [context_buf + 0x30]
            mov r13, [context_buf + 0x38]
            mov r14, [context_buf + 0x40]
            mov r15, [context_buf + 0x48]
        #if defined(NXS_AVX) && defined(NXS_PLATFORM_WIN32)
            vmovaps ymm6,  [context_buf + 0x050]
            vmovaps ymm7,  [context_buf + 0x070]
            vmovaps ymm8,  [context_buf + 0x090]
            vmovaps ymm9,  [context_buf + 0x0B0]
            vmovaps ymm10, [context_buf + 0x0D0]
            vmovaps ymm11, [context_buf + 0x0F0]
            vmovaps ymm12, [context_buf + 0x110]
            vmovaps ymm13, [context_buf + 0x130]
            vmovaps ymm14, [context_buf + 0x150]
            vmovaps ymm15, [context_buf + 0x170]
        #elif defined(NXS_SSE2) && defined(NXS_PLATFORM_WIN32)
            movaps xmm6,  [context_buf + 0x50]
            movaps xmm7,  [context_buf + 0x60]
            movaps xmm8,  [context_buf + 0x70]
            movaps xmm9,  [context_buf + 0x80]
            movaps xmm10, [context_buf + 0x90]
            movaps xmm11, [context_buf + 0xA0]
            movaps xmm12, [context_buf + 0xB0]
            movaps xmm13, [context_buf + 0xC0]
            movaps xmm14, [context_buf + 0xD0]
            movaps xmm15, [context_buf + 0xE0]
        #endif //NXS_(SSE2|AVX) && NXS_PLATFORM_WIN32
        };
    #elif defined(NXS_X86)
        __asm {
            //mov eip, [context_buf + 0x00]
            mov ebp, [context_buf + 0x04]
            mov esp, [context_buf + 0x08]
            mov ebx, [context_buf + 0x0C]
            mov edi, [context_buf + 0x10]
            mov esi, [context_buf + 0x14]
        };
    #elif defined(NXS_ARM64)
        #error "arm inline asm isn't (sufficiently) supported on msvc"
    #elif defined(NXS_ARM)
        #error "arm inline asm isn't (sufficiently) supported on msvc"
    #else
        #error "CPU architecture not supported"
    #endif
#elif defined(NXS_COMPILER_CLANG) || defined(NXS_COMPILER_GCC)
    #ifdef NXS_X64
        asm volatile (
            //"movq 0x00(%0), %rip"
            "movq 0x08(%0), %rbp"
            "movq 0x10(%0), %rsp"
            "movq 0x18(%0), %rbx"
            "movq 0x20(%0), %rdi"
            "movq 0x28(%0), %rsi"
            "movq 0x30(%0), %r12"
            "movq 0x38(%0), %r13"
            "movq 0x40(%0), %r14"
            "movq 0x48(%0), %r15"
            : //out -- none
            : "r" (context_buf) //in
        );
        #if defined(NXS_AVX) && defined(NXS_PLATFORM_WIN32)
            asm volatile (
                "vmovaps 0x050(%0), %ymm6"
                "vmovaps 0x070(%0), %ymm7"
                "vmovaps 0x090(%0), %ymm8"
                "vmovaps 0x0B0(%0), %ymm9"
                "vmovaps 0x0D0(%0), %ymm10"
                "vmovaps 0x0F0(%0), %ymm11"
                "vmovaps 0x110(%0), %ymm12"
                "vmovaps 0x130(%0), %ymm13"
                "vmovaps 0x150(%0), %ymm14"
                "vmovaps 0x170(%0), %ymm15"
                : //out -- none
                : "r" (context_buf) //in
            );
        #elif defined(NXS_SSE2) && defined(NXS_PLATFORM_WIN32)
            asm volatile (
                "movaps 0x50(%0), %xmm6"
                "movaps 0x60(%0), %xmm7"
                "movaps 0x70(%0), %xmm8"
                "movaps 0x80(%0), %xmm9"
                "movaps 0x90(%0), %xmm10"
                "movaps 0xA0(%0), %xmm11"
                "movaps 0xB0(%0), %xmm12"
                "movaps 0xC0(%0), %xmm13"
                "movaps 0xD0(%0), %xmm14"
                "movaps 0xE0(%0), %xmm15"
                : //out -- none
                : "r" (context_buf) //in
            );
        #endif //NXS_(SSE2|AVX) && NXS_PLATFORM_WIN32
    #elif defined(NXS_X86)
        asm volatile (
            //"movl 0x00(%0), %eip"
            "movl 0x04(%0), %ebp"
            "movl 0x08(%0), %esp"
            "movl 0x0C(%0), %ebx"
            "movl 0x10(%0), %edi"
            "movl 0x14(%0), %esi"
            : //out -- none
            : "r" (context_buf) //in
        );
    #elif defined(NXS_ARM64)
        int arm_neon_offset = 0;
        asm volatile (
            //"ldr %x30, [%[ptr], 0x00]" //PC
            "ldr %x19, [%[ptr], 0x08]"
            "ldr %x20, [%[ptr], 0x10]"
            "ldr %x21, [%[ptr], 0x18]"
            "ldr %x22, [%[ptr], 0x20]"
            "ldr %x23, [%[ptr], 0x28]"
            "ldr %x24, [%[ptr], 0x30]"
            "ldr %x25, [%[ptr], 0x38]"
            "ldr %x26, [%[ptr], 0x40]"
            "ldr %x27, [%[ptr], 0x48]"
            "ldr %x28, [%[ptr], 0x50]"
            "ldr %x29, [%[ptr], 0x58]"
            "ldr %x30, [%[ptr], 0x60]"
            "ldr %x10, [%[ptr], 0x68]"
            "mov %sp, %x10"
            : //out -- none
            : [ptr] "r" (context_buf) //in
            : "x10" //write registers
        );
        #ifdef NXS_ARM_NEON
            asm volatile (
                "ldr %v8,  [%[ptr], 0x70]"
                "ldr %v9,  [%[ptr], 0x80]"
                "ldr %v10, [%[ptr], 0x90]"
                "ldr %v11, [%[ptr], 0xA0]"
                "ldr %v12, [%[ptr], 0xB0]"
                "ldr %v13, [%[ptr], 0xC0]"
                "ldr %v14, [%[ptr], 0xD0]"
                "ldr %v15, [%[ptr], 0xE0]"
                : //out -- none
                : [ptr] "r" (context_buf) //in
            );
            arm_neon_offset += 1024; //8 * sizeof(nxis_float32x4_t);
        #endif
        #ifdef NXS_ARM_SVE
            asm volatile (
                //assuming offset of 0x70 from base registers (with `+ offset` for NEON ofc.)
                "ldr %z8,  [%[ptr], 0x070 + %[offset]]"
                "ldr %z9,  [%[ptr], 0x270 + %[offset]]"
                "ldr %z10, [%[ptr], 0x470 + %[offset]]"
                "ldr %z11, [%[ptr], 0x670 + %[offset]]"
                "ldr %z12, [%[ptr], 0x870 + %[offset]]"
                "ldr %z13, [%[ptr], 0xA70 + %[offset]]"
                "ldr %z14, [%[ptr], 0xC70 + %[offset]]"
                "ldr %z15, [%[ptr], 0xE70 + %[offset]]"
                : //out -- none
                : [ptr] "r" (context_buf), [offset] "r" (arm_neon_offset) //in
            );
        #endif
    #elif defined(NXS_ARM)
        asm volatile (
            "ldr %r4,  [%[ptr], 0x00]"
            "ldr %r5,  [%[ptr], 0x04]"
            "ldr %r6,  [%[ptr], 0x08]"
            "ldr %r7,  [%[ptr], 0x0C]"
            "ldr %r8,  [%[ptr], 0x10]"
            "ldr %r9,  [%[ptr], 0x14]"
            "ldr %r10, [%[ptr], 0x18]"
            "ldr %r11, [%[ptr], 0x1C]"
            "ldr %r13, [%[ptr], 0x20]" //SP
            "ldr %r14, [%[ptr], 0x24]" //LR
            //"ldr %r15, [%[ptr], 0x28]" //PC
            : //out -- none
            : [ptr] "r" (context_buf)
        );
        #ifdef NXS_ARM_NEON
            asm volatile (
                "ldr d8,  [%[ptr], 0x02C]"
                "ldr d9,  [%[ptr], 0x034]"
                "ldr d10, [%[ptr], 0x03C]"
                "ldr d11, [%[ptr], 0x044]"
                "ldr d12, [%[ptr], 0x04C]"
                "ldr d13, [%[ptr], 0x054]"
                "ldr d14, [%[ptr], 0x05C]"
                "ldr d15, [%[ptr], 0x064]"
                : //out -- none
                : [ptr] "r" (context_buf)
            );
        #endif
    #else
        #error "CPU architecture not supported"
    #endif
#else
    #error "compiler not supported"
#endif
}

// -- types --

//scheduler
    //fiber queue
    //
//fiber
    //process/function that might block/yield to give controll to the next fiber
    //each fiber has its own stack and context
//stack
    //stack state
//context
    //register states

// ----- functions ------

// -- init --
//init scheduler for thread
    //...

// -- start fiber --
//fiber create
    //allocate stack for fiber
    //allocate and set context
        //set %rsp (or equiv.) to point to the newly allocated fiber stack
        //set %rip (or equiv.) to point to the start of fiber function
    //new fiber is pushed to scheduler queue

// -- switch fiber --
    //to switch, fiber A calls `yield` and the scheduler calls `resume` on fiber B

//fiber yield
    //the register context is saved to the calling fiber's context
//fiber resume
    //...

// -- terminate fiber --
//fiber destroy
    //...

// -- quit --
//quit scheduler for thread
    //...