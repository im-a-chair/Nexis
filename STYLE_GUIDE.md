# Code formatting style used in the Nexis engine

This document outlines the code formatting and best practices to maintain a consistent, readable, and maintainable codebase for the Nexis engine. Adhering to these guidelines is a requirement for all code contributions to the point that pull requests _might_ be denied for not adhering to this formatting and these practices.

## example of correctly formatted code
### Header
```C
#ifndef _NXS_HEADER_H_
#define _NXS_HEADER_H_

#include <system_header.h>
#include "local_header.h"

///FIXME: some issue

/** TODO:
 * task 1
 * task 2
 * task 3
 */

/** NXS_ExampleOpaqueType
 * is an opaque type, used in `NXS_FooBarAction`
 * \sa NXS_FooBarAction
 */
typedef struct NXS_ExampleOpaqueType_T NXS_ExampleOpaqueType;

/** NXS_StructType
 * an example typedef of a struct
 */
typedef struct NXS_StructType_T {
    int member_one;
    struct {
        float* member_two;
        size_t count;
    } member_two;
} NXS_StructType;

/** NXS_Struct
 * an example struct
 */
struct NXS_Struct {
    int member_one;
    struct {
        float* member_two;
        size_t count;
    } member_two;
};

/** NXS_FooBarAction
 * appends `num` to the array in `data` and sets `data`'s `member_one` to `num`
 * \param data the `NXS_ExampleOpaqueType` to append `num` to
 * \param num the number to append to `data`'s internal array
 * \note this can fail, use `NXS_Error(NULL)` to get the error
 * \sa NXS_ExampleOpaqueType
 */
void NXS_FooBarAction(const NXS_ExampleOpaqueType* const data, int num);

#endif //_NXS_HEADER_H_
```
### Source file
```C
#include "header.h" //the header with the declerations that correspond to these definitions
#include <system_header.h>
#include "local_header.h"

#define NXS_MAGIC_NUMBER 420

struct NXS_ExampleOpaqueType_T {
    int member_one;
    struct {
        float* member_two;
        size_t count;
    } member_two;
};

float* _nxis_realloc_opaque_type(NXS_ExampleOpaqueType* ptr, int extra_size) {
    NXS_ASSERT(ptr);
    NXS_ASSERT(extra_size != 0);

    float* new = realloc(ptr->member_two.member_two, (ptr->member_two.count + extra_size) * sizeof(float));
    if (!new) {
        NXS_Error(strerror(errno));
        return NULL;
    }
    return new;
}
void NXS_FooBarAction(const NXS_ExampleOpaqueType* const data, int num) {
    NXS_ASSERT(data);
    NXS_ASSERT(num != NXS_MAGIC_NUMBER)

    float* new_data = _nxis_realloc_opaque_type(data, 1);
    if (!new_data) {
        return;
    }
    data->member_two.member_two = new_data;
    data->member_one = num;
    data->member_two.member_two[data->member_two.count++] = num;
}
```
## indentation (tab size & tabs vs spaces)
The ideal method ofindentation is **tabs**, since it allows for the reader to adjust the indentation size, but if you do use **spaces**, use **_4_** space indentation.

TL;DR:
- **tabs** is ideal
- otherwise is **_4_ _space_** indenation
## naming
### types
types (anything declared with `typedef`) should use `PascalCase`.
```C
typedef char CStyleString[];
```
### Structs
structs in any case should use `PascalCase` with a `_T` suffix.
```C
struct Foo_T {
    void* memb1;
    int memb2;
};
```
or
```C
typedef struct Foo_T {
    void* memb1;
    int memb2;
} Foo;
```
### variables
variables and members should use `snake_case`.
```C
int foo_bar;
```
### functions
Global functions should use always `PascalCase`.
```C
void NXS_FooBar(void* bar, int foo);
```
#### internal functions
Unlike API functions, internal functions use `_underscore_lead`_`snake_case`.
```C
void _nxis_internal_foo(int num);
```
### macros, constants & enumumerations
should a be FULLY_CAPITALIZED
## braces & spacing
In EVERY SINGLE case (function, switch, conditionals, loops, etc...), USE K&R bracing ONLY!

This means the opening brace is ALWAYS on the same line as the decleration or definition that its part of.

Like the bracing, a single line brace or parenthesis set DOES NOT have padding, like in e.g. `int main ( int argc, char* argv[] ) {`, instead you would write `int main(int argc, char** argv) {`

#### example:
```C
int foo(int num[5]) {
    if (num == NULL) return 0;
    //may be `if (num == NULL) {return 0;}`

    int ret = 0;
    for (size_t i; i < 5; i++) {
        switch (num[i]) {
            case 0:
                //ret += 0;
                break;
            case 1:
                ret += num[i] + 1;
                break;
            case 2:
                ret += num[i] * 2;
                break;
            default:
                ret += num[i];
                break;
        }
    }

    return ret;
}
```

Simmilarly, types and other atribute keywords are ALWAYS on the same line as the decleration or definition that its part of.
Thus, use:
```C
static inline int foo() {
    //...
}
```
NEVER:
```C
static
inline
int
foo() {
    //...
}
```
### operator spacing
Do NOT put a space between a function name and the opening parenthesis.

Unlike with functions, put a space between a `while`, `for`, `if` or `switch` keyword and it's openign parenthesis `'('`.

<!-- I sometimes leave out spaces on math operations to indicate theyre preformed first. e.g. `a = b*a + c`, though often i'd use parenthesies i.e. `a = (b * a) + c`, but most times i end up useing a mix of both `a = (a*b) + c` Though i'd reccomend to use proper spacing around opperators wherever possible-->

Operators should be spaced for readability. Use parentheses to explicitly define the order of operations, even if it's already defined by operator precedence. e.g. `a = (b * a) + c` instead of `a = (a*b) + c`, `a = b * a + c` or `a = b*a + c`.
## comments
In most cases you should just use `//` for single line comments and `/* ... */` for multiline comments.
Though for documentation or `TODO:`/`FIXME:` comments please use `///` and `/** ... */`, with doxygen style documentation comments with backslash `\` prefixed directives (e.g. `\returns`)

If ever you do want to write any type of TODO or FIXME comment, you are expected to write it as `TODO` or `FIXME`, **Not** `TO-DO`, `Todo`, `todo`, `Fix-Me`, `fixme`, `fix me` or any other variation.
this is an example of a correctly written `TODO` and `FIXME` comment:
```C
///TODO: add more TODOs, and more detail to the current TODOs

/** TODO: 
 * improve documentation of `foo`
 * make `bar` more efficient
 * add `foobar`, but remember to `...`
 */

///FIXME: `foo` arg `data` is not checked by assert
```
## prefixes
When writing cade for the engine, please prefix anything in C with `NXS_`, ideally you would prefix it with `NXS_` followed by a simmilar prefix of the catagory it belongs to, e.g. `NXS_ECS_` for ECS related symbold

**For C++**, you would use namespaces (like `NXS::` or `NXS::ECS::`), when using `extern "C"`, always use the C-style prefix `NXS_`.

**Internal functions**, unlike types, structs, regular functions, macros and constants, use lower case snake case lead by an underscore, thus the prefix `_nxis_` should be uses (e.g. `_nxis_internal_proc()`)
With this, again, its best to add a seccond prefix of the catagory (e.g. `_nxis_ecs_` for internal ECS funtions)
Though because these should be `inline`d, they dont polute the global namespace and thus have a less strong requirment of the second prefix.
## good practices
though not really a formating matter, is still something to mention.
### asserts
Whenever you are writing a function, minimize the use of return errors for non-runtime errors, use `NXS_ASSERT` instead.

as an example a function that uses `realloc` and takes a pointer to reallocate, should use `NXS_ASSERT` to check if the pointer is valid and a return value to report a `realloc` failure, e.g.
```C
bool foo(int** ptr, size_t current_size) {
    NXS_ASSERT(ptr);
    NXS_ASSERT(*ptr);
    NXS_ASSERT(current_size > 0);

    int* new = (int*)realloc(*ptr, current_size * sizeof(int) * 2);
    if (!new) {
        NXS_Error(strerror(errno));
        return false;
    }

    *ptr = new;
    return true;
}
```

in this code, `NXS_ASSERT` is also used for the size argument. because for performace, when using the C API, like how you should use asserts, you should not use any unecesary defensive practises, like adjusting for a not yet allocated pointer. and though realloc is suppost to allocate the pointer, the size would end up `0`, so it would be a huge wast of processing power, thus use an assert to tell the user that this is happening.

### opaque types

To write a robust API, please use opaque types wherever possible.
If you really dont wont to, for testing or insight, you could leave it public and add a `///TODO: make opaque` comment to let others know it can and should become opaque.

### const correctness
<!-- im pretty loose on it myself, but dont think thats how it should be. -->
Try to use const wherever possible. For example, use const for function arguments that are not written to.

for example, write
```C
bool getlen(const NXS_Opaque const* in, size_t* out) {
    //...
}
```
instead of
```C
bool getlen(NXS_Opaque* data, size_t* out) {
    //...
}
```

### inlining internal functions

Whenever you use an internal function to simplefy the code of a general function (which i definitly encourage), please remember to inline it, so it is less likely to polute the global namespace, when linking and since its just slightly faster and better with internal functions.

### internal structs, enums and unions

When a `struct`, `enum` or `union` is only for unternal use, please _do_ _not_ use `typedef` but unstead just use the `struct`, `enum` or `union` keyword when using it/