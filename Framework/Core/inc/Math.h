#ifndef _NXS_MATH_H_
#define _NXS_MATH_H_
#include "std.h"
#include <math.h>

/** TODO:
 * finish function implementations
 * use SIMD.h
 */

/** NXS_Vec2 */
typedef NXS_ALIGN(16) union NXS_Vec2_T  {
    struct {
        float x;
        float y;
    };
    float v[2];
} NXS_Vec2;

/** NXS_Vec3 */
typedef NXS_ALIGN(16) union NXS_Vec3_T  {
    struct {
        float x;
        float y;
        float z;
    };
    float v[3];
} NXS_Vec3;

/** NXS_Vec4 */
typedef NXS_ALIGN(16) union NXS_Vec4_T  {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float v[4];
} NXS_Vec4;

/** NXS_Mat2 */
typedef NXS_ALIGN(16) union NXS_Mat2_T  {
    float m[2][2];
    float elements[4];
    NXS_Vec2 columns[2];
} NXS_Mat2;

/** NXS_Mat3 */
typedef NXS_ALIGN(64) union NXS_Mat3_T  {
    float m[3][3];
    float elements[9];
    NXS_Vec3 columns[3];
} NXS_Mat3;

/** NXS_Mat4 */
typedef NXS_ALIGN(64) union NXS_Mat4_T {
    float m[4][4];
    float elements[16];
    NXS_Vec4 columns[4];
} NXS_Mat4;

/** NXS_Quaternion */
typedef NXS_Vec4 NXS_Quaternion;

/** NXS_Tensor */
typedef NXS_ALIGN(64/*though cant fit, should still work*/) union NXS_Ten3_T  { //3x3x3, less essential
    float t[3][3][3];
    float elements[27];
    NXS_Mat3 layers[3];
    NXS_Vec3 columns[3][3];
} NXS_Ten3;

/** NXS_Vec2ToVec3 */
static inline NXS_Vec3 NXS_Vec2ToVec3(NXS_Vec2 v);

/** NXS_Vec2ToVec4 */
static inline NXS_Vec4 NXS_Vec2ToVec4(NXS_Vec2 v);

/** NXS_Vec3ToVec2 */
static inline NXS_Vec2 NXS_Vec3ToVec2(NXS_Vec3 v);

/** NXS_Vec3ToVec4 */
static inline NXS_Vec4 NXS_Vec3ToVec4(NXS_Vec3 v);

/** NXS_Vec4ToVec2 */
static inline NXS_Vec2 NXS_Vec4ToVec2(NXS_Vec4 v);

/** NXS_Vec4ToVec3 */
static inline NXS_Vec3 NXS_Vec4ToVec3(NXS_Vec4 v);

/** NXS_Mat2ToMat3 */
static inline NXS_Mat3 NXS_Mat2ToMat3(const NXS_Mat2* restrict m);

/** NXS_Mat2ToMat4 */
static inline NXS_Mat4 NXS_Mat2ToMat4(const NXS_Mat2* restrict m);

/** NXS_Mat3ToMat2 */
static inline NXS_Mat2 NXS_Mat3ToMat2(const NXS_Mat3* restrict m);

/** NXS_Mat3ToMat4 */
static inline NXS_Mat4 NXS_Mat3ToMat4(const NXS_Mat3* restrict m);

/** NXS_Mat4ToMat2 */
static inline NXS_Mat2 NXS_Mat4ToMat2(const NXS_Mat4* restrict m);

/** NXS_Mat4ToMat3 */
static inline NXS_Mat3 NXS_Mat4ToMat3(const NXS_Mat4* restrict m);

/** NXS_QuaternionToMat4 */
static inline NXS_Mat4 NXS_QuaternionToMat4(NXS_Quaternion q);

/** NXS_QuaternionToVec4 */
#define NXS_QuaternionToVec4(q) ((NXS_Vec4)q)

/** NXS_QuaternionToVec3 */
#define NXS_QuaternionToVec3(q) NXS_Vec4ToVec3(NXS_QuaternionToVec4(q))

/** NXS_Mat3ToQuaternion */
static inline NXS_Quaternion NXS_Mat3ToQuaternion(const NXS_Mat3* restrict m);

/** NXS_Vec4ToQuaternion */
#define NXS_Vec4ToQuaternion(v) (NXS_Quaternion)v

/** NXS_Vec3ToQuaternion */
#define NXS_Vec3ToQuaternion(v) (NXS_Quaternion)NXS_Vec3ToVec4(v)

/** NXS_Vec2Add */
static inline NXS_Vec2 NXS_Vec2Add(const NXS_Vec2 a, const NXS_Vec2 b);

/** NXS_Vec2Sub */
static inline NXS_Vec2 NXS_Vec2Sub(const NXS_Vec2 a, const NXS_Vec2 b);

/** NXS_Vec2Mul */
static inline NXS_Vec2 NXS_Vec2Mul(const NXS_Vec2 a, const NXS_Vec2 b); //Hadamard (Component-wise) Product

/** NXS_Vec2Div */
static inline NXS_Vec2 NXS_Vec2Div(const NXS_Vec2 a, const NXS_Vec2 b); //Hadamard (Component-wise) Division

/** NXS_Vec2Scale */
static inline NXS_Vec2 NXS_Vec2Scale(const NXS_Vec2 v, float scalar); //scalar multiplication

/** NXS_Vec2Dot */
static inline float NXS_Vec2Dot(const NXS_Vec2 a, const NXS_Vec2 b);

/** NXS_Vec2ScalarProject */
static inline float NXS_Vec2ScalarProject(const NXS_Vec2 a, const NXS_Vec2 b);

/** NXS_Vec2Mag */
static inline float NXS_Vec2Mag(const NXS_Vec2 v); //magnetude/lenght

/** NXS_Vec2Norm */
static inline NXS_Vec2 NXS_Vec2Norm(const NXS_Vec2 v); //normalization

/** NXS_Vec2Lerp */
static inline NXS_Vec2 NXS_Vec2Lerp(const NXS_Vec2 a, const NXS_Vec2 b, float t); //from a, to b

/** NXS_Vec3Add */
static inline NXS_Vec3 NXS_Vec3Add(const NXS_Vec3 a, const NXS_Vec3 b);

/** NXS_Vec3Sub */
static inline NXS_Vec3 NXS_Vec3Sub(const NXS_Vec3 a, const NXS_Vec3 b);

/** NXS_Vec3Mul */
static inline NXS_Vec3 NXS_Vec3Mul(const NXS_Vec3 a, const NXS_Vec3 b); //Hadamard (Component-wise) Product

/** NXS_Vec3Div */
static inline NXS_Vec3 NXS_Vec3Div(const NXS_Vec3 a, const NXS_Vec3 b); //Hadamard (Component-wise) Division

/** NXS_Vec3Scale */
static inline NXS_Vec3 NXS_Vec3Scale(const NXS_Vec3 v, float scalar); //scalar multiplication

/** NXS_Vec3Dot */
static inline float NXS_Vec3Dot(const NXS_Vec3 a, const NXS_Vec3 b);

/** NXS_Vec3Cross */
static inline NXS_Vec3 NXS_Vec3Cross(const NXS_Vec3 a, const NXS_Vec3 b);

/** NXS_Vec3Mag */
static inline float NXS_Vec3Mag(const NXS_Vec3 v); //magnetude/lenght

/** NXS_Vec3Norm */
static inline NXS_Vec3 NXS_Vec3Norm(const NXS_Vec3 v); //normalization

/** NXS_Vec3Lerp */
static inline NXS_Vec3 NXS_Vec3Lerp(const NXS_Vec3 a, const NXS_Vec3 b, float t); //from a, to b

/** NXS_Vec4Add */
static inline NXS_Vec4 NXS_Vec4Add(const NXS_Vec4 a, const NXS_Vec4 b);

/** NXS_Vec4Sub */
static inline NXS_Vec4 NXS_Vec4Sub(const NXS_Vec4 a, const NXS_Vec4 b);

/** NXS_Vec4Mul */
static inline NXS_Vec4 NXS_Vec4Mul(const NXS_Vec4 a, const NXS_Vec4 b); //Hadamard (Component-wise) Product

/** NXS_Vec4Div */
static inline NXS_Vec4 NXS_Vec4Div(const NXS_Vec4 a, const NXS_Vec4 b); //Hadamard (Component-wise) Division

/** NXS_Vec4Scale */
static inline NXS_Vec4 NXS_Vec4Scale(const NXS_Vec4 v, float scalar); //scalar multiplication

/** NXS_Vec4Dot */
static inline float NXS_Vec4Dot(const NXS_Vec4 a, const NXS_Vec4 b);

/** NXS_Vec4Mag */
static inline float NXS_Vec4Mag(const NXS_Vec4 v); //magnetude/lenght

/** NXS_Vec4Norm */
static inline NXS_Vec4 NXS_Vec4Norm(const NXS_Vec4 v); //normalization

/** NXS_Vec4Lerp */
static inline NXS_Vec4 NXS_Vec4Lerp(const NXS_Vec4 a, const NXS_Vec4 b, float t); //from a, to b

/** NXS_Mat2Add */
static inline void NXS_Mat2Add(const NXS_Mat2* restrict a, const NXS_Mat2* restrict b, NXS_Mat2* restrict out);

/** NXS_Mat2Sub */
static inline void NXS_Mat2Sub(const NXS_Mat2* restrict a, const NXS_Mat2* restrict b, NXS_Mat2* restrict out);

/** NXS_Mat2Mul */
void NXS_Mat2Mul(const NXS_Mat2* restrict a, const NXS_Mat2* restrict b, NXS_Mat2* restrict out);

/** NXS_Mat2Scale */
static inline void NXS_Mat2Scale(const NXS_Mat2* restrict m, float scalar, NXS_Mat2* restrict out);

/** NXS_Mat2Transform */
static inline NXS_Vec2 NXS_Mat2Transform(const NXS_Mat2* restrict m, const NXS_Vec2 v);

/** NXS_Mat2Transpose */
static inline void NXS_Mat2Transpose(const NXS_Mat2* restrict m, NXS_Mat2* restrict out);

/** NXS_Mat2Determenant */
static inline float NXS_Mat2Determenant(const NXS_Mat2* restrict m);

/** NXS_Mat2Inverse */
void NXS_Mat2Inverse(const NXS_Mat2* restrict m, NXS_Mat2* restrict out);

/** NXS_Mat3Add */
static inline void NXS_Mat3Add(const NXS_Mat3* restrict a, const NXS_Mat3* restrict b, NXS_Mat3* restrict out);

/** NXS_Mat3Sub */
static inline void NXS_Mat3Sub(const NXS_Mat3* restrict a, const NXS_Mat3* restrict b, NXS_Mat3* restrict out);

/** NXS_Mat3Mul */
void NXS_Mat3Mul(const NXS_Mat3* restrict a, const NXS_Mat3* restrict b, NXS_Mat3* restrict out);

/** NXS_Mat3Scale */
static inline void NXS_Mat3Scale(const NXS_Mat3* restrict m, float scalar, NXS_Mat3* restrict out);

/** NXS_Mat3Transform */
static inline NXS_Vec3 NXS_Mat3Transform(const NXS_Mat3* restrict m, const NXS_Vec3 v);

/** NXS_Mat3Transpose */
static inline void NXS_Mat3Transpose(const NXS_Mat3* restrict m, NXS_Mat3* restrict out);

/** NXS_Mat3Determenant */
float NXS_Mat3Determenant(const NXS_Mat3* restrict m);

/** NXS_Mat3Inverse */
void NXS_Mat3Inverse(const NXS_Mat3* restrict m, NXS_Mat3* restrict out);

/** NXS_Mat4Add */
static inline void NXS_Mat4Add(const NXS_Mat4* restrict a, const NXS_Mat4* restrict b, NXS_Mat4* restrict out);

/** NXS_Mat4Sub */
static inline void NXS_Mat4Sub(const NXS_Mat4* restrict a, const NXS_Mat4* restrict b, NXS_Mat4* restrict out);

/** NXS_Mat4Mul */
void NXS_Mat4Mul(const NXS_Mat4* restrict a, const NXS_Mat4* restrict b, NXS_Mat4* restrict out);

/** NXS_Mat4Scale */
static inline void NXS_Mat4Scale(const NXS_Mat4* restrict m, float scalar, NXS_Mat4* restrict out);

/** NXS_Mat4Transform */
static inline NXS_Vec4 NXS_Mat4Transform(const NXS_Mat4* restrict m, const NXS_Vec4 v);

/** NXS_Mat4Transpose */
static inline void NXS_Mat4Transpose(const NXS_Mat4* restrict m, NXS_Mat4* restrict out);

/** NXS_Mat4Determenant */
float NXS_Mat4Determenant(const NXS_Mat4* restrict m);

/** NXS_Mat4Inverse */
void NXS_Mat4Inverse(const NXS_Mat4* restrict m, NXS_Mat4* restrict out);

/** NXS_QuaternionAdd */
static inline NXS_Quaternion NXS_QuaternionAdd(const NXS_Quaternion a, const NXS_Quaternion b);

/** NXS_QuaternionSub */
static inline NXS_Quaternion NXS_QuaternionSub(const NXS_Quaternion a, const NXS_Quaternion b);

/** NXS_QuaternionMul */
NXS_Quaternion NXS_QuaternionMul(const NXS_Quaternion a, const NXS_Quaternion b);

/** NXS_QuaternionRDiv */
NXS_Quaternion NXS_QuaternionRDiv(const NXS_Quaternion a, const NXS_Quaternion b);

/** NXS_QuaternionLDiv */
NXS_Quaternion NXS_QuaternionLDiv(const NXS_Quaternion a, const NXS_Quaternion b);

/** NXS_QuaternionRotateVec3 */
NXS_Vec3 NXS_QuaternionRotateVec3(const NXS_Quaternion q, const NXS_Vec3 v); // (v' = q*v*(q^-1))

/** NXS_QuaternionNorm */
static inline NXS_Quaternion NXS_QuaternionNorm(const NXS_Quaternion q);

/** NXS_QuaternionMag */
#define NXS_QuaternionMag(q) NXS_Vec4Mag((NXS_Vec4)q)

/** NXS_QuaternionConjugate */
static inline NXS_Quaternion NXS_QuaternionConjugate(const NXS_Quaternion q);

/** NXS_QuaternionInverse */
NXS_Quaternion NXS_QuaternionInverse(const NXS_Quaternion q);

/** NXS_QuaternionSlerp */
NXS_Quaternion NXS_QuaternionSlerp(const NXS_Quaternion a, const NXS_Quaternion b, float t);

/** NXS_Ten3Add */
void NXS_Ten3Add(const NXS_Ten3* restrict a, const NXS_Ten3* restrict b, NXS_Ten3* restrict out);

/** NXS_Ten3Sub */
void NXS_Ten3Sub(const NXS_Ten3* restrict a, const NXS_Ten3* restrict b, NXS_Ten3* restrict out);

/** NXS_Ten3Mul */
void NXS_Ten3Mul(const NXS_Ten3* restrict a, const NXS_Ten3* restrict b, NXS_Ten3* restrict out);

/** NXS_Ten3Ten3Scale */
void NXS_Ten3Ten3Scale(const NXS_Ten3* restrict t, float scalar, NXS_Ten3* restrict out);

/** NXS_Ten3Vec2Mul */
void NXS_Ten3Vec2Mul(const NXS_Ten3* restrict t, const NXS_Vec2 v, NXS_Ten3* restrict out);

/** NXS_Ten3Vec3Mul */
void NXS_Ten3Vec3Mul(const NXS_Ten3* restrict t, const NXS_Vec3 v, NXS_Ten3* restrict out);

/** NXS_Ten3Vec4Mul */
void NXS_Ten3Vec4Mul(const NXS_Ten3* restrict t, const NXS_Vec4 v, NXS_Ten3* restrict out);

/** NXS_Ten3Mat2Mul */
void NXS_Ten3Mat2Mul(const NXS_Ten3* restrict t, const NXS_Mat2* restrict m, NXS_Ten3* restrict out);

/** NXS_Ten3Mat3Mul */
void NXS_Ten3Mat3Mul(const NXS_Ten3* restrict t, const NXS_Mat3* restrict m, NXS_Ten3* restrict out);

/** NXS_Ten3Mat4Mul */
void NXS_Ten3Mat4Mul(const NXS_Ten3* restrict t, const NXS_Mat4* restrict m, NXS_Ten3* restrict out);

#endif //_NXS_MATH_H_