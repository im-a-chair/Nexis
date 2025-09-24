#ifndef _NXS_MATH_H_
#define _NXS_MATH_H_
#include "std.h"
#include "SIMD/simd.h"
#include <math.h>

/** TODO:
 * implement SIMD usage
 *  remember to avoid branching as much as possible
 */

/** NXS_Vec2 */
typedef NXS_ALIGN(NXS_VEC_ALIGN) union NXS_Vec2_T  {
    struct {
        float x;
        float y;
    };
    float v[2];
} NXS_Vec2;

/** NXS_Vec3 */
typedef NXS_ALIGN(NXS_VEC_ALIGN) union NXS_Vec3_T  {
    struct {
        float x;
        float y;
        float z;
    };
    float v[3];
} NXS_Vec3;

/** NXS_Vec4 */
typedef NXS_ALIGN(NXS_VEC_ALIGN) union NXS_Vec4_T  {
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    float v[4];
} NXS_Vec4;

/** NXS_Mat2 */
typedef NXS_ALIGN(NXS_VEC_ALIGN) union NXS_Mat2_T  {
    float m[2][2];
    float elements[4];
    NXS_Vec2 columns[2];
} NXS_Mat2;

/** NXS_Mat3 */
typedef NXS_ALIGN(NXS_VEC_ALIGN * 4) union NXS_Mat3_T  {
    float m[3][3];
    float elements[9];
    NXS_Vec3 columns[3];
} NXS_Mat3;

/** NXS_Mat4 */
typedef NXS_ALIGN(NXS_VEC_ALIGN * 4) union NXS_Mat4_T {
    float m[4][4];
    float elements[16];
    NXS_Vec4 columns[4];
} NXS_Mat4;

/** NXS_Quaternion */
typedef NXS_Vec4 NXS_Quaternion;

/** NXS_Tensor */
// typedef NXS_ALIGN(
//     NXS_VEC_ALIGN * 4 /*though cant fit, should still work*/
// ) union NXS_Ten3_T  { //3x3x3, less essential
//     float t[3][3][3];
//     float elements[27];
//     NXS_Mat3 layers[3];
//     NXS_Vec3 columns[3][3];
// } NXS_Ten3;

NXS_STATIC_INLINE NXS_Vec3 NXS_Vec2ToVec3(NXS_Vec2 v) {
    NXS_Vec3 ret = {
        .x = v.x,
        .y = v.y,
        .z = 0
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec2ToVec4(NXS_Vec2 v) {
    NXS_Vec4 ret = {
        .x = v.x,
        .y = v.y,
        .z = 0,
        .w = 0
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec3ToVec2(NXS_Vec3 v) {
    NXS_Vec2 ret = {
        .x = v.x,
        .y = v.y
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec3ToVec4(NXS_Vec3 v) {
    NXS_Vec4 ret = {
        .x = v.x,
        .y = v.y,
        .z = v.z,
        .w = 0
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec4ToVec2(NXS_Vec4 v) {
    NXS_Vec2 ret = {
        .x = v.x,
        .y = v.y
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec4ToVec3(NXS_Vec4 v) {
    NXS_Vec3 ret = {
        .x = v.x,
        .y = v.y,
        .z = v.z
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat3 NXS_Mat2ToMat3(const NXS_Mat2* restrict m) {
    NXS_Mat3 ret = {
        .columns = {
            NXS_Vec2ToVec3(m->columns[0]),
            NXS_Vec2ToVec3(m->columns[1]),
            {0, 0, 0}
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat4 NXS_Mat2ToMat4(const NXS_Mat2* restrict m) {
    NXS_Mat4 ret = {
        .columns = {
            NXS_Vec2ToVec4(m->columns[0]),
            NXS_Vec2ToVec4(m->columns[1]),
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat2 NXS_Mat3ToMat2(const NXS_Mat3* restrict m) {
    NXS_Mat2 ret = {
        .columns = {
            NXS_Vec3ToVec2(m->columns[0]),
            NXS_Vec3ToVec2(m->columns[1])
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat4 NXS_Mat3ToMat4(const NXS_Mat3* restrict m) {
    NXS_Mat4 ret = {
        .columns = {
            NXS_Vec3ToVec4(m->columns[0]),
            NXS_Vec3ToVec4(m->columns[1]),
            NXS_Vec3ToVec4(m->columns[2]),
            {0, 0, 0, 0}
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat2 NXS_Mat4ToMat2(const NXS_Mat4* restrict m) {
    NXS_Mat2 ret = {
        .columns = {
            NXS_Vec4ToVec2(m->columns[0]),
            NXS_Vec4ToVec2(m->columns[1])
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat3 NXS_Mat4ToMat3(const NXS_Mat4* restrict m) {
    NXS_Mat3 ret = {
        .columns = {
            NXS_Vec4ToVec3(m->columns[0]),
            NXS_Vec4ToVec3(m->columns[1]),
            NXS_Vec4ToVec3(m->columns[2])
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Mat4 NXS_QuaternionToMat4(NXS_Quaternion q) {
    // It is almost always better to ensure q is normalized beforehand.
    // q = NXS_QuaternionNorm(q); //if not already a vensor (unit quaternion) normailize it

    float x = q.x, y = q.y, z = q.z, w = q.w;

    // Pre-calculate squared terms and products.
    // This structure helps the compiler recognize patterns for SIMD instructions.
    float x2 = x * x;
    float y2 = y * y;
    float z2 = z * z;
    float xy = x * y;
    float xz = x * z;
    float yz = y * z;
    float wx = w * x;
    float wy = w * y;
    float wz = w * z;

    NXS_Mat4 ret = {
        //1-2y^2-2z^2,  2xy-2zw,    2xz-2yw,   0
        //  2xy+2zw,  1-2x^2-2z^2,  2yz-2xw,   0
        //  2xz-2yw,    2yz+2xw,  1-2x^2-2y^2, 0
        //     0,          0,          0,      1
        .m = {
            {1.0f - 2.0f * (y2 + z2), 2.0f        * (xy - wz), 2.0f        * (xz + wy), 0.0f},
            {2.0f        * (xy + wz), 1.0f - 2.0f * (x2 + z2), 2.0f        * (yz - wx), 0.0f},
            {2.0f        * (xz - wy), 2.0f        * (yz + wx), 1.0f - 2.0f * (x2 + y2), 0.0f},
            {0.0f,                    0.0f,                    0.0f,                    1.0f}
        }
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Quaternion NXS_Mat3ToQuaternion(const NXS_Mat3* restrict m) {
    // Cache matrix elements to local variables.
    // This avoids repeated pointer dereferencing and improves readability.
    float m00 = m->m[0][0], m01 = m->m[0][1], m02 = m->m[0][2];
    float m10 = m->m[1][0], m11 = m->m[1][1], m12 = m->m[1][2];
    float m20 = m->m[2][0], m21 = m->m[2][1], m22 = m->m[2][2];

    float trace = m00 + m11 + m22;
    NXS_Quaternion q;

    if (trace > 0.0f) {
        // This is the most common case
        float s = sqrtf(trace + 1.0f);
        q.w = s * 0.5f;
        s = 0.5f / s;
        q.x = (m21 - m12) * s;
        q.y = (m02 - m20) * s;
        q.z = (m10 - m01) * s;
    } else {
        // Handle cases where w is close to 0
        if (m00 > m11 && m00 > m22) { // Column 0 is largest
            float s = sqrtf(1.0f + m00 - m11 - m22);
            q.x = s * 0.5f;
            s = 0.5f / s;
            q.w = (m21 - m12) * s;
            q.y = (m01 + m10) * s;
            q.z = (m02 + m20) * s;
        } else if (m11 > m22) { // Column 1 is largest
            float s = sqrtf(1.0f + m11 - m00 - m22);
            q.y = s * 0.5f;
            s = 0.5f / s;
            q.w = (m02 - m20) * s;
            q.x = (m01 + m10) * s;
            q.z = (m12 + m21) * s;
        } else { // Column 2 is largest
            float s = sqrtf(1.0f + m22 - m00 - m11);
            q.z = s * 0.5f;
            s = 0.5f / s;
            q.w = (m10 - m01) * s;
            q.x = (m02 + m20) * s;
            q.y = (m12 + m21) * s;
        }
    }
    return q;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Add(const NXS_Vec2 a, const NXS_Vec2 b) {
    NXS_Vec2 v = {
        .x = a.x + b.x,
        .y = a.y + b.y
    };
    return v;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Sub(const NXS_Vec2 a, const NXS_Vec2 b) {
    NXS_Vec2 v = {
        .x = a.x - b.x,
        .y = a.y - b.y
    };
    return v;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Mul(const NXS_Vec2 a, const NXS_Vec2 b) {
    NXS_Vec2 v = {
        .x = a.x * b.x,
        .y = a.y * b.y
    };
    return v;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Div(const NXS_Vec2 a, const NXS_Vec2 b) {
    NXS_Vec2 v = {
        .x = a.x / b.x,
        .y = a.y / b.y
    };
    return v;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Scale(const NXS_Vec2 v, float scalar) {
    NXS_Vec2 ret = {
        .x = v.x * scalar,
        .y = v.y * scalar
    };
    return ret;
}
NXS_STATIC_INLINE float NXS_Vec2Dot(const NXS_Vec2 a, const NXS_Vec2 b) {
    return (a.x * b.x) + (a.y * b.y);
}
NXS_STATIC_INLINE float NXS_Vec2ScalarProject(const NXS_Vec2 a, const NXS_Vec2 b) {
    return (a.x*b.y)-(a.y*b.x);
}
NXS_STATIC_INLINE float NXS_Vec2Mag(const NXS_Vec2 v) {
    return sqrtf((v.x*v.x)+(v.y*v.y));
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Norm(const NXS_Vec2 v) {
    // Calculate the squared magnitude (dot product of v with itself).
    const float mag_sq = (v.x * v.x) + (v.y * v.y);

    // Assert that the magnitude is not near zero.
    NXS_ASSERT(mag_sq > FLT_EPSILON);

    // Calculate the inverse magnitude.
    // Compilers with -ffast-math can often convert this into a single,
    // fast "reciprocal square root" (rsqrt) instruction.
    const float inv_mag = 1.0f / sqrtf(mag_sq);

    NXS_Vec2 ret = {
        .x = v.x * inv_mag,
        .y = v.y * inv_mag
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Vec2Lerp(const NXS_Vec2 a, const NXS_Vec2 b, float t) {
    NXS_ASSERT(t <= 1.0f);
    NXS_ASSERT(t >= 0.0f);
    NXS_Vec2 ret = {
        .x = a.x + (b.x - a.x) * t,
        .y = a.y + (b.y - a.y) * t
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Add(const NXS_Vec3 a, const NXS_Vec3 b) {
    NXS_Vec3 ret = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Sub(const NXS_Vec3 a, const NXS_Vec3 b) {
    NXS_Vec3 ret = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Mul(const NXS_Vec3 a, const NXS_Vec3 b) {
    NXS_Vec3 ret = {
        .x = a.x * b.x,
        .y = a.y * b.y,
        .z = a.z * b.z
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Div(const NXS_Vec3 a, const NXS_Vec3 b) {
    NXS_Vec3 ret = {
        .x = a.x / b.x,
        .y = a.y / b.y,
        .z = a.z / b.z
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Scale(const NXS_Vec3 v, float scalar) {
    NXS_Vec3 ret = {
        .x = v.x * scalar,
        .y = v.y * scalar,
        .z = v.z * scalar
    };
    return ret;
}
NXS_STATIC_INLINE float NXS_Vec3Dot(const NXS_Vec3 a, const NXS_Vec3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Cross(const NXS_Vec3 a, const NXS_Vec3 b) {
    NXS_Vec3 ret = {
        .x = (a.y * b.z) - (a.z * b.y),
        .y = (a.z * b.x) - (a.x * b.z),
        .z = (a.x * b.y) - (a.y * b.x)
    };
    return ret;
}
NXS_STATIC_INLINE float NXS_Vec3Mag(const NXS_Vec3 v) {
    return sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z));
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Norm(const NXS_Vec3 v) {
    const float mag_sq = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
    NXS_ASSERT(mag_sq > FLT_EPSILON);
    const float inv_mag = 1.0f / sqrtf(mag_sq);
    NXS_Vec3 ret = {
        .x = v.x * inv_mag,
        .y = v.y * inv_mag,
        .z = v.z * inv_mag
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Vec3Lerp(const NXS_Vec3 a, const NXS_Vec3 b, float t) {
    NXS_ASSERT(t <= 1.0f);
    NXS_ASSERT(t >= 0.0f);
    NXS_Vec3 ret = {
        .x = a.x + (b.x - a.x) * t,
        .y = a.y + (b.y - a.y) * t,
        .z = a.z + (b.z - a.z) * t
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Add(const NXS_Vec4 a, const NXS_Vec4 b) {
    NXS_Vec4 ret = {
        .x = a.x + b.x,
        .y = a.y + b.y,
        .z = a.z + b.z,
        .w = a.w + b.w
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Sub(const NXS_Vec4 a, const NXS_Vec4 b) {
    NXS_Vec4 ret = {
        .x = a.x - b.x,
        .y = a.y - b.y,
        .z = a.z - b.z,
        .w = a.w - b.w
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Mul(const NXS_Vec4 a, const NXS_Vec4 b) {
    NXS_Vec4 ret = {
        .x = a.x * b.x,
        .y = a.y * b.y,
        .z = a.z * b.z,
        .w = a.w * b.w
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Div(const NXS_Vec4 a, const NXS_Vec4 b) {
    NXS_Vec4 ret = {
        .x = a.x / b.x,
        .y = a.y / b.y,
        .z = a.z / b.z,
        .w = a.w / b.w
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Scale(const NXS_Vec4 v, float scalar) {
    NXS_Vec4 ret = {
        .x = v.x * scalar,
        .y = v.y * scalar,
        .z = v.z * scalar,
        .w = v.w * scalar
    };
    return ret;
}
NXS_STATIC_INLINE float NXS_Vec4Dot(const NXS_Vec4 a, const NXS_Vec4 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}
NXS_STATIC_INLINE float NXS_Vec4Mag(const NXS_Vec4 v) {
    return sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z)+(v.w*v.w));
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Norm(const NXS_Vec4 v) {
    float mag = sqrtf((v.x*v.x)+(v.y*v.y)+(v.z*v.z)+(v.w*v.w));
    NXS_ASSERT(mag > FLT_EPSILON); // Check for a near-zero magnitude to prevent division by zero.
    NXS_Vec4 ret = {
        .x = v.x / mag,
        .y = v.y / mag,
        .z = v.z / mag,
        .w = v.w / mag
    };
    return ret;
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Vec4Lerp(const NXS_Vec4 a, const NXS_Vec4 b, float t) {
    NXS_ASSERT(t <= 1.0f);
    NXS_ASSERT(t >= 0.0f);
    NXS_Vec4 ret = {
        .x = a.x + (b.x - a.x) * t,
        .y = a.y + (b.y - a.y) * t,
        .z = a.z + (b.z - a.z) * t,
        .w = a.w + (b.w - a.w) * t
    };
    return ret;
}
NXS_STATIC_INLINE void NXS_Mat2Add(const NXS_Mat2* restrict a, const NXS_Mat2* restrict b, NXS_Mat2* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Vec2Add(a->columns[0], b->columns[0]);
    out->columns[1] = NXS_Vec2Add(a->columns[1], b->columns[1]);
}
NXS_STATIC_INLINE void NXS_Mat2Sub(const NXS_Mat2* restrict a, const NXS_Mat2* restrict b, NXS_Mat2* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Vec2Sub(a->columns[0], b->columns[0]);
    out->columns[1] = NXS_Vec2Sub(a->columns[1], b->columns[1]);
}
NXS_STATIC_INLINE void NXS_Mat2Mul(const NXS_Mat2* restrict a, const NXS_Mat2* restrict b, NXS_Mat2* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Mat2Transform(a, b->columns[0]);
    out->columns[1] = NXS_Mat2Transform(a, b->columns[1]);
}
NXS_STATIC_INLINE void NXS_Mat2Scale(const NXS_Mat2* restrict m, float scalar, NXS_Mat2* restrict out) {
    NXS_ASSERT(m != out);
    out->columns[0] = NXS_Vec2Scale(m->columns[0], scalar);
    out->columns[1] = NXS_Vec2Scale(m->columns[1], scalar);
}
NXS_STATIC_INLINE NXS_Vec2 NXS_Mat2Transform(const NXS_Mat2* restrict m, const NXS_Vec2 v) {
    NXS_Vec2 col0_scaled = NXS_Vec2Scale(m->columns[0], v.x);
    NXS_Vec2 col1_scaled = NXS_Vec2Scale(m->columns[1], v.y);
    return NXS_Vec2Add(col0_scaled, col1_scaled);
}
NXS_STATIC_INLINE void NXS_Mat2Transpose(const NXS_Mat2* restrict m, NXS_Mat2* restrict out) {
    NXS_ASSERT(m != out);
    out->m[0][0] = m->m[0][0]; // No change
    out->m[1][1] = m->m[1][1]; // No change
    out->m[0][1] = m->m[1][0]; // Swap
    out->m[1][0] = m->m[0][1]; // Swap
}
NXS_STATIC_INLINE float NXS_Mat2Determenant(const NXS_Mat2* restrict m) {
    return (m->m[0][0] * m->m[1][1]) - (m->m[0][1] * m->m[1][0]);
}
NXS_STATIC_INLINE void NXS_Mat2Inverse(const NXS_Mat2* restrict m, NXS_Mat2* restrict out) {
    NXS_ASSERT(m != out);
    const float det = (m->m[0][0] * m->m[1][1]) - (m->m[0][1] * m->m[1][0]);
    NXS_ASSERT(det > FLT_EPSILON);
    const float inv_det = 1.0f / det;
    out->m[0][0] =  inv_det * m->m[1][1];
    out->m[0][1] = -inv_det * m->m[0][1];
    out->m[1][0] = -inv_det * m->m[1][0];
    out->m[1][1] =  inv_det * m->m[0][0];
}
NXS_STATIC_INLINE void NXS_Mat3Add(const NXS_Mat3* restrict a, const NXS_Mat3* restrict b, NXS_Mat3* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Vec3Add(a->columns[0], b->columns[0]);
    out->columns[1] = NXS_Vec3Add(a->columns[1], b->columns[1]);
    out->columns[2] = NXS_Vec3Add(a->columns[2], b->columns[2]);
}
NXS_STATIC_INLINE void NXS_Mat3Sub(const NXS_Mat3* restrict a, const NXS_Mat3* restrict b, NXS_Mat3* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Vec3Sub(a->columns[0], b->columns[0]);
    out->columns[1] = NXS_Vec3Sub(a->columns[1], b->columns[1]);
    out->columns[2] = NXS_Vec3Sub(a->columns[2], b->columns[2]);
}
NXS_STATIC_INLINE void NXS_Mat3Mul(const NXS_Mat3* restrict a, const NXS_Mat3* restrict b, NXS_Mat3* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Mat3Transform(a, b->columns[0]);
    out->columns[1] = NXS_Mat3Transform(a, b->columns[1]);
    out->columns[2] = NXS_Mat3Transform(a, b->columns[2]);
}
NXS_STATIC_INLINE void NXS_Mat3Scale(const NXS_Mat3* restrict m, float scalar, NXS_Mat3* restrict out) {
    NXS_ASSERT(m != out);
    out->columns[0] = NXS_Vec3Scale(m->columns[0], scalar);
    out->columns[1] = NXS_Vec3Scale(m->columns[1], scalar);
    out->columns[2] = NXS_Vec3Scale(m->columns[2], scalar);
}
NXS_STATIC_INLINE NXS_Vec3 NXS_Mat3Transform(const NXS_Mat3* restrict m, const NXS_Vec3 v) {
    NXS_Vec3 col0_scaled = NXS_Vec3Scale(m->columns[0], v.x);
    NXS_Vec3 col1_scaled = NXS_Vec3Scale(m->columns[1], v.y);
    NXS_Vec3 col2_scaled = NXS_Vec3Scale(m->columns[2], v.z);
    
    NXS_Vec3 temp = NXS_Vec3Add(col0_scaled, col1_scaled);
    return NXS_Vec3Add(temp, col2_scaled);
}
NXS_STATIC_INLINE void NXS_Mat3Transpose(const NXS_Mat3* restrict m, NXS_Mat3* restrict out) {
    NXS_ASSERT(m != out);
    out->m[0][0] = m->m[0][0];
    out->m[0][1] = m->m[1][0];
    out->m[0][2] = m->m[2][0];
    out->m[1][0] = m->m[0][1];
    out->m[1][1] = m->m[1][1];
    out->m[1][2] = m->m[2][1];
    out->m[2][0] = m->m[0][2];
    out->m[2][1] = m->m[1][2];
    out->m[2][2] = m->m[2][2];
}
NXS_STATIC_INLINE float NXS_Mat3Determenant(const NXS_Mat3* restrict m) {
    return m->m[0][0] * m->m[1][1] * m->m[2][2] +
           m->m[0][1] * m->m[1][2] * m->m[2][0] +
           m->m[0][2] * m->m[1][0] * m->m[2][1] -
           m->m[0][2] * m->m[1][1] * m->m[2][0] -
           m->m[0][1] * m->m[1][0] * m->m[2][2] -
           m->m[0][0] * m->m[1][2] * m->m[2][1];
}
NXS_STATIC_INLINE void NXS_Mat3Inverse(const NXS_Mat3* restrict m, NXS_Mat3* restrict out) {
    NXS_ASSERT(m != out);
    // Cache for readability and to help the optimizer.
    float m00 = m->m[0][0], m01 = m->m[0][1], m02 = m->m[0][2];
    float m10 = m->m[1][0], m11 = m->m[1][1], m12 = m->m[1][2];
    float m20 = m->m[2][0], m21 = m->m[2][1], m22 = m->m[2][2];

    float det = m00 * (m11 * m22 - m12 * m21) -
                m01 * (m10 * m22 - m12 * m20) +
                m02 * (m10 * m21 - m11 * m20);
    
    NXS_ASSERT(det > FLT_EPSILON);

    const float inv_det = 1.0f / det;

    out->m[0][0] = (m11 * m22 - m12 * m21) * inv_det;
    out->m[0][1] = (m02 * m21 - m01 * m22) * inv_det;
    out->m[0][2] = (m01 * m12 - m02 * m11) * inv_det;
    out->m[1][0] = (m12 * m20 - m10 * m22) * inv_det;
    out->m[1][1] = (m00 * m22 - m02 * m20) * inv_det;
    out->m[1][2] = (m02 * m10 - m00 * m12) * inv_det;
    out->m[2][0] = (m10 * m21 - m11 * m20) * inv_det;
    out->m[2][1] = (m01 * m20 - m00 * m21) * inv_det;
    out->m[2][2] = (m00 * m11 - m01 * m10) * inv_det;
}
NXS_STATIC_INLINE void NXS_Mat4Add(const NXS_Mat4* restrict a, const NXS_Mat4* restrict b, NXS_Mat4* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Vec4Add(a->columns[0], b->columns[0]);
    out->columns[1] = NXS_Vec4Add(a->columns[1], b->columns[1]);
    out->columns[2] = NXS_Vec4Add(a->columns[2], b->columns[2]);
    out->columns[3] = NXS_Vec4Add(a->columns[3], b->columns[3]);
}
NXS_STATIC_INLINE void NXS_Mat4Sub(const NXS_Mat4* restrict a, const NXS_Mat4* restrict b, NXS_Mat4* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Vec4Sub(a->columns[0], b->columns[0]);
    out->columns[1] = NXS_Vec4Sub(a->columns[1], b->columns[1]);
    out->columns[2] = NXS_Vec4Sub(a->columns[2], b->columns[2]);
    out->columns[3] = NXS_Vec4Sub(a->columns[3], b->columns[3]);
}
NXS_STATIC_INLINE void NXS_Mat4Mul(const NXS_Mat4* restrict a, const NXS_Mat4* restrict b, NXS_Mat4* restrict out) {
    NXS_ASSERT(a != b);
    NXS_ASSERT(b != out);
    out->columns[0] = NXS_Mat4Transform(a, b->columns[0]);
    out->columns[1] = NXS_Mat4Transform(a, b->columns[1]);
    out->columns[2] = NXS_Mat4Transform(a, b->columns[2]);
    out->columns[3] = NXS_Mat4Transform(a, b->columns[3]);
}
NXS_STATIC_INLINE void NXS_Mat4Scale(const NXS_Mat4* restrict m, float scalar, NXS_Mat4* restrict out) {
    NXS_ASSERT(m != out);
    out->columns[0] = NXS_Vec4Scale(m->columns[0], scalar);
    out->columns[1] = NXS_Vec4Scale(m->columns[1], scalar);
    out->columns[2] = NXS_Vec4Scale(m->columns[2], scalar);
    out->columns[3] = NXS_Vec4Scale(m->columns[3], scalar);
}
NXS_STATIC_INLINE NXS_Vec4 NXS_Mat4Transform(const NXS_Mat4* restrict m, const NXS_Vec4 v) {
    NXS_Vec4 col0_scaled = NXS_Vec4Scale(m->columns[0], v.x);
    NXS_Vec4 col1_scaled = NXS_Vec4Scale(m->columns[1], v.y);
    NXS_Vec4 col2_scaled = NXS_Vec4Scale(m->columns[2], v.z);
    NXS_Vec4 col3_scaled = NXS_Vec4Scale(m->columns[3], v.w);
    
    NXS_Vec4 temp0 = NXS_Vec4Add(col0_scaled, col1_scaled);
    NXS_Vec4 temp1 = NXS_Vec4Add(col2_scaled, col3_scaled);
    return NXS_Vec4Add(temp0, temp1);
}
NXS_STATIC_INLINE void NXS_Mat4Transpose(const NXS_Mat4* restrict m, NXS_Mat4* restrict out) {
    NXS_ASSERT(m != out);
    // Load columns into temporary local variables. This can help the optimizer
    // by improving data locality before the component-wise assignments.
    NXS_Vec4 c0 = m->columns[0];
    NXS_Vec4 c1 = m->columns[1];
    NXS_Vec4 c2 = m->columns[2];
    NXS_Vec4 c3 = m->columns[3];

    out->m[0][0] = c0.x; out->m[0][1] = c1.x; out->m[0][2] = c2.x; out->m[0][3] = c3.x;
    out->m[1][0] = c0.y; out->m[1][1] = c1.y; out->m[1][2] = c2.y; out->m[1][3] = c3.y;
    out->m[2][0] = c0.z; out->m[2][1] = c1.z; out->m[2][2] = c2.z; out->m[2][3] = c3.z;
    out->m[3][0] = c0.w; out->m[3][1] = c1.w; out->m[3][2] = c2.w; out->m[3][3] = c3.w;
}
NXS_STATIC_INLINE float NXS_Mat4Determenant(const NXS_Mat4* restrict m) {
    // Cache matrix elements into local variables. This avoids repeated pointer
    // dereferencing and makes the math below cleaner and easier to optimize.
    const float m00 = m->m[0][0], m01 = m->m[0][1], m02 = m->m[0][2], m03 = m->m[0][3];
    const float m10 = m->m[1][0], m11 = m->m[1][1], m12 = m->m[1][2], m13 = m->m[1][3];
    const float m20 = m->m[2][0], m21 = m->m[2][1], m22 = m->m[2][2], m23 = m->m[2][3];
    const float m30 = m->m[3][0], m31 = m->m[3][1], m32 = m->m[3][2], m33 = m->m[3][3];

    // Pre-calculate 2x2 sub-determinants from the lower-right 3x3 matrix.
    // This avoids redundant calculations when finding the 3x3 cofactors.
    const float sub_d0 = m22 * m33 - m23 * m32;
    const float sub_d1 = m21 * m33 - m23 * m31;
    const float sub_d2 = m21 * m32 - m22 * m31;
    const float sub_d3 = m20 * m33 - m23 * m30;
    const float sub_d4 = m20 * m32 - m22 * m30;
    const float sub_d5 = m20 * m31 - m21 * m30;

    // Calculate the cofactors for the first row.
    const float c0 =  (m11 * sub_d0 - m12 * sub_d1 + m13 * sub_d2);
    const float c1 = -(m10 * sub_d0 - m12 * sub_d3 + m13 * sub_d4);
    const float c2 =  (m10 * sub_d1 - m11 * sub_d3 + m13 * sub_d5);
    const float c3 = -(m10 * sub_d2 - m11 * sub_d4 + m12 * sub_d5);
    
    // The determinant is the dot product of the first row and its cofactors.
    return m00 * c0 + m01 * c1 + m02 * c2 + m03 * c3;
}
NXS_STATIC_INLINE void NXS_Mat4Inverse(const NXS_Mat4* restrict m, NXS_Mat4* restrict out) {
    NXS_ASSERT(m != out);
    //array[row][column]
    //array[z][y][x]
    //array[w][z][y][x]
    //a m->m[0][0]
    //b m->m[0][1]
    //c m->m[1][0]
    //d m->m[1][1]
    //get the determanant

    //2D
    //get adjugate
        //get cofactor matrix
            //get all cofactors in a matrix
            //which for 2D is
                // [ d,-c]
                // [-b, a]
            //for
                // [a, b]
                // [c, d]
        //transpose cofactor (which gets you the adjugate)
            //transposing
                // [ d,-c]
                // [-b, a]
            //gives
                // [ d,-b]
                // [-c, a]
    //multiply adjugate by 1/det as scalar

    //3D
    //get adjugate
        //get cofactor matrix
            //loop over all 3 rows/columns of the cofactor matrix
                //loop over all 3 elements of that row/column
                    //calculate the cofactor
                        //calclulate the minor
                            //take the 2D matrix that is tha 3D without a given row and column
                        //use (-1)^(i+j) * (Minor), where i+j is the sum of the row and column indexes
                    //fill the space with the cofactor
        //transpose cofactor matrix (which gets you the adjugate)
    //multiply adjugate by 1/det as scalar

    //(a, b, c, d)
        //[a, b]
        //[c, d]
    //2D: det = (a * d) - (b * c)
    // c11 = (-1)^(1+1)*((m22*m33)-(m23*m32)), c12 = (-1)^(1+2)*((m21*m33)-(m23*m31)), c13 = (-1)^(1+3)*((m21*m32)-(m22*m31))
    // c21 = (-1)^(2+1)*((m12*m33)-(m13*m32)), c22 = (-1)^(2+2)*((m11*m33)-(m13*m31)), c23 = (-1)^(2+3)*((m11*m32)-(m12*m31))
    // c31 = (-1)^(3+1)*((m12*m23)-(m13*m22)), c32 = (-1)^(3+2)*((m11*m23)-(m13*m21)), c33 = (-1)^(3+3)*((m11*m22)-(m12*m21))

    //transposed
    // m11(c11) = (-1)^(1+1)*((m22*m33)-(m23*m32)), m12(c21) = (-1)^(2+1)*((m12*m33)-(m13*m32)), m13(c31) = (-1)^(3+1)*((m12*m23)-(m13*m22))
    // m21(c12) = (-1)^(1+2)*((m21*m33)-(m23*m31)), m22(c22) = (-1)^(2+2)*((m11*m33)-(m13*m31)), m23(c32) = (-1)^(3+2)*((m11*m23)-(m13*m21))
    // m31(c13) = (-1)^(1+3)*((m21*m32)-(m22*m31)), m32(c23) = (-1)^(2+3)*((m11*m32)-(m12*m31)), m33(c33) = (-1)^(3+3)*((m11*m22)-(m12*m21))

    //times det
    // m11 = (1/det)*((-1)^(1+1)*((m22*m33)-(m23*m32))), m12 = (1/det)*((-1)^(2+1)*((m12*m33)-(m13*m32))), m13 = (1/det)*((-1)^(3+1)*((m12*m23)-(m13*m22)))
    // m21 = (1/det)*((-1)^(1+2)*((m21*m33)-(m23*m31))), m22 = (1/det)*((-1)^(2+2)*((m11*m33)-(m13*m31))), m23 = (1/det)*((-1)^(3+2)*((m11*m23)-(m13*m21)))
    // m31 = (1/det)*((-1)^(1+3)*((m21*m32)-(m22*m31))), m32 = (1/det)*((-1)^(2+3)*((m11*m32)-(m12*m31))), m33 = (1/det)*((-1)^(3+3)*((m11*m22)-(m12*m21)))

    //+- resolved
    // m11 = (1/det)*(  (m22*m33)-(m23*m32)),  m12 = (1/det)*(-((m12*m33)-(m13*m32))), m13 = (1/det)*(  (m12*m23)-(m13*m22))
    // m21 = (1/det)*(-((m21*m33)-(m23*m31))), m22 = (1/det)*(  (m11*m33)-(m13*m31)),  m23 = (1/det)*(-((m11*m23)-(m13*m21)))
    // m31 = (1/det)*(  (m21*m32)-(m22*m31)),  m32 = (1/det)*(-((m11*m32)-(m12*m31))), m33 = (1/det)*(  (m11*m22)-(m12*m21))

    // Cache matrix elements locally.
    const float m00 = m->m[0][0], m01 = m->m[0][1], m02 = m->m[0][2], m03 = m->m[0][3];
    const float m10 = m->m[1][0], m11 = m->m[1][1], m12 = m->m[1][2], m13 = m->m[1][3];
    const float m20 = m->m[2][0], m21 = m->m[2][1], m22 = m->m[2][2], m23 = m->m[2][3];
    const float m30 = m->m[3][0], m31 = m->m[3][1], m32 = m->m[3][2], m33 = m->m[3][3];

    // Pre-calculate pairs and 2x2 sub-determinants to reduce redundancy.
    float s0 = m00 * m11 - m01 * m10;
    float s1 = m00 * m12 - m02 * m10;
    float s2 = m00 * m13 - m03 * m10;
    float s3 = m01 * m12 - m02 * m11;
    float s4 = m01 * m13 - m03 * m11;
    float s5 = m02 * m13 - m03 * m12;

    float c0 = m20 * m31 - m21 * m30;
    float c1 = m20 * m32 - m22 * m30;
    float c2 = m20 * m33 - m23 * m30;
    float c3 = m21 * m32 - m22 * m31;
    float c4 = m21 * m33 - m23 * m31;
    float c5 = m22 * m33 - m23 * m32;

    // Calculate the cofactors for the adjugate matrix.
    // Note: The matrix is being built transposed to get the adjugate directly.
    float adj00 =  (m11 * c5 - m12 * c4 + m13 * c3);
    float adj10 = -(m10 * c5 - m12 * c2 + m13 * c1);
    float adj20 =  (m10 * c4 - m11 * c2 + m13 * c0);
    float adj30 = -(m10 * c3 - m11 * c1 + m12 * c0);

    // Calculate determinant using the first row of cofactors.
    // This reuses the calculated cofactors, saving significant computation.
    float det = m00 * adj00 + m01 * adj10 + m02 * adj20 + m03 * adj30;

    NXS_ASSERT(fabsf(det) > FLT_EPSILON);

    // This is the most important optimization: calculate the reciprocal once!
    const float inv_det = 1.0f / det;
    
    // Assign the first row of the output matrix.
    out->m[0][0] = adj00 * inv_det;
    out->m[1][0] = adj10 * inv_det;
    out->m[2][0] = adj20 * inv_det;
    out->m[3][0] = adj30 * inv_det;
    
    // Calculate and assign the remaining rows of the output matrix.
    out->m[0][1] = -(m01 * c5 - m02 * c4 + m03 * c3) * inv_det;
    out->m[1][1] =  (m00 * c5 - m02 * c2 + m03 * c1) * inv_det;
    out->m[2][1] = -(m00 * c4 - m01 * c2 + m03 * c0) * inv_det;
    out->m[3][1] =  (m00 * c3 - m01 * c1 + m02 * c0) * inv_det;

    out->m[0][2] =  (m31 * s5 - m32 * s4 + m33 * s3) * inv_det;
    out->m[1][2] = -(m30 * s5 - m32 * s2 + m33 * s1) * inv_det;
    out->m[2][2] =  (m30 * s4 - m31 * s2 + m33 * s0) * inv_det;
    out->m[3][2] = -(m30 * s3 - m31 * s1 + m32 * s0) * inv_det;

    out->m[0][3] = -(m21 * s5 - m22 * s4 + m23 * s3) * inv_det;
    out->m[1][3] =  (m20 * s5 - m22 * s2 + m23 * s1) * inv_det;
    out->m[2][3] = -(m20 * s4 - m21 * s2 + m23 * s0) * inv_det;
    out->m[3][3] =  (m20 * s3 - m21 * s1 + m22 * s0) * inv_det;
}

/** NXS_QuaternionToVec4 */
#define NXS_QuaternionToVec4(q) ((NXS_Vec4)q)

/** NXS_QuaternionToVec3 */
#define NXS_QuaternionToVec3(q) NXS_Vec4ToVec3(NXS_QuaternionToVec4(q))

/** NXS_Vec4ToQuaternion */
#define NXS_Vec4ToQuaternion(v) (NXS_Quaternion)v

/** NXS_Vec3ToQuaternion */
#define NXS_Vec3ToQuaternion(v) (NXS_Quaternion)NXS_Vec3ToVec4(v)

/** NXS_QuaternionAdd */
#define NXS_QuaternionAdd(a, b) NXS_Vec4Add(a, b)

/** NXS_QuaternionSub */
#define NXS_QuaternionSub(a, b) NXS_Vec4Sub(a, b)

/** NXS_QuaternionMul
 * Multiplies quaternion `a` by quaternion `b`.
 * \returns the hamilton product of quaternion a and b
 * \param a the first quaternion, to multiply by `a`
 * \param b the second quaternion, to multiply `a` by
 * 
 * \warning Quaternions are non comunicative! This means that a*b is defferent from b*a,
 * this function does a*b, so make sure you use the right order.
 */
NXS_STATIC_INLINE NXS_Quaternion NXS_QuaternionMul(const NXS_Quaternion a, const NXS_Quaternion b) {
    NXS_Quaternion new = {
        .w = a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
        .x = a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        .y = a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        .z = a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w
    };
    return new;
}

/** NXS_QuaternionConjugate */
NXS_STATIC_INLINE NXS_Quaternion NXS_QuaternionConjugate(const NXS_Quaternion q) {
    NXS_Quaternion new = {
        .w = q.w,
        .x = -q.x,
        .y = -q.y,
        .z = -q.z
    };
    return new;
}

/** NXS_QuaternionInverse */
NXS_STATIC_INLINE NXS_Quaternion NXS_QuaternionInverse(const NXS_Quaternion q) {
    float inv_n2 = 1.0f / NXS_QuaternionSqrNorm(q);
    NXS_Quaternion new = {
        .w = q.w * inv_n2,
        .x = -q.x * inv_n2,
        .y = -q.y * inv_n2,
        .z = -q.z * inv_n2
    };
    return new;
}

/** NXS_QuaternionSqrNorm */
#define NXS_QuaternionSqrNorm(q) ((q.w*q.w) + (q.x*q.x) + (q.y*q.y) + (q.z*q.z))

/** NXS_QuaternionSqrNorm */
#define NXS_QuaternionNorm(q) sqrtf(NXS_QuaternionSqrNorm(q))

/** NXS_QuaternionMag */
#define NXS_QuaternionMag(q) NXS_Vec4Mag((NXS_Vec4)q)

/** NXS_QuaternionRDiv */
#define NXS_QuaternionRDiv(a, b) NXS_QuaternionMul(a, NXS_QuaternionInverse(b))

/** NXS_QuaternionLDiv */
#define NXS_QuaternionLDiv(a, b) NXS_QuaternionMul(NXS_QuaternionInverse(b), a)

/** NXS_QuaternionRotateVec3
 * (v' = q*v*(q^-1))
 */
NXS_STATIC_INLINE NXS_Vec3 NXS_QuaternionRotateVec3(const NXS_Quaternion q, const NXS_Vec3 v) {
    //approach when matrix would be reusable:
    // NXS_Mat4 m4 = NXS_QuaternionToMat4(q);
    // NXS_Mat3 m = NXS_Mat4ToMat3(&m4);
    // return NXS_Mat3Transform(&m, v);

    // squared terms
    float qx2 = q.x * q.x;
    float qy2 = q.y * q.y;
    float qz2 = q.z * q.z;
    float qw2 = q.w * q.w;

    // products for the diagonal terms
    float diag_xx = qw2 + qx2 - qy2 - qz2;
    float diag_yy = qw2 - qx2 + qy2 - qz2;
    float diag_zz = qw2 - qx2 - qy2 + qz2;
    
    // products for the off-diagonal terms
    float qxy = 2.0f * q.x * q.y;
    float qxz = 2.0f * q.x * q.z;
    float qyz = 2.0f * q.y * q.z;
    float qwx = 2.0f * q.w * q.x;
    float qwy = 2.0f * q.w * q.y;
    float qwz = 2.0f * q.w * q.z;

    NXS_Vec3 res = {
        .x = v.x * diag_xx + v.y * (qxy - qwz) + v.z * (qxz + qwy),
        .y = v.x * (qxy + qwz) + v.y * diag_yy + v.z * (qyz - qwx),
        .z = v.x * (qxz - qwy) + v.y * (qyz + qwx) + v.z * diag_zz
    };
    return res;
}

/** NXS_QuaternionSlerp */
NXS_STATIC_INLINE NXS_Quaternion NXS_QuaternionSlerp(const NXS_Quaternion a, const NXS_Quaternion b, float t) {
    NXS_ASSERT(t <= 1.0f);
    NXS_ASSERT(t >= 0.0f);

    NXS_Quaternion c = b;

    float dot = NXS_Vec4Dot(a, b);

    if (dot < 0.0f) {
        dot = -dot;
        c.w = -c.w;
        c.x = -c.x;
        c.y = -c.y;
        c.z = -c.z;
    }
    
    if (dot > 0.9995f) { // if angle is small, fall back to lerp
        NXS_Quaternion res = {
            .w = a.w + t * (c.w - a.w),
            .x = a.x + t * (c.x - a.x),
            .y = a.y + t * (c.y - a.y),
            .z = a.z + t * (c.z - a.z)
        };
        return NXS_Vec4Scale(res, 1.0f / NXS_QuaternionNorm(res));
    }

    float angle = acosf(dot);

    float inv_sa = 1.0f / sinf(angle);
    float sat = sinf(angle * t) * inv_sa;
    float sa1t = sinf(angle * (1.0f - t)) * inv_sa;

    NXS_Quaternion ret = {
        .w = sa1t*a.w + sat*c.w,
        .x = sa1t*a.x + sat*c.x,
        .y = sa1t*a.y + sat*c.y,
        .z = sa1t*a.z + sat*c.z
    };

    return ret;
}

// void NXS_Ten3Add(const NXS_Ten3* restrict a, const NXS_Ten3* restrict b, NXS_Ten3* restrict out) {
//     NXS_ASSERT(a != b);
//     NXS_ASSERT(b != out);
//     ...
//     return;
// }
// void NXS_Ten3Sub(const NXS_Ten3* restrict a, const NXS_Ten3* restrict b, NXS_Ten3* restrict out) {
//     NXS_ASSERT(a != b);
//     NXS_ASSERT(b != out);
//     ...
//     return;
// }
// void NXS_Ten3Mul(const NXS_Ten3* restrict a, const NXS_Ten3* restrict b, NXS_Ten3* restrict out) {
//     NXS_ASSERT(a != b);
//     NXS_ASSERT(b != out);
//     ...
//     return;
// }
// void NXS_Ten3Ten3Scale(const NXS_Ten3* restrict t, float scalar, NXS_Ten3* restrict out) {
//     ...
//     return;
// }
// void NXS_Ten3Vec2Mul(const NXS_Ten3* restrict t, const NXS_Vec2 v, NXS_Ten3* restrict out) {
//     NXS_ASSERT(t != out);
//     ...
//     return;
// }
// void NXS_Ten3Vec3Mul(const NXS_Ten3* restrict t, const NXS_Vec3 v, NXS_Ten3* restrict out) {
//     NXS_ASSERT(t != out);
//     ...
//     return;
// }
// void NXS_Ten3Vec4Mul(const NXS_Ten3* restrict t, const NXS_Vec4 v, NXS_Ten3* restrict out) {
//     NXS_ASSERT(t != out);
//     ...
//     return;
// }
// void NXS_Ten3Mat2Mul(const NXS_Ten3* restrict t, const NXS_Mat2* restrict m, NXS_Ten3* restrict out) {
//     NXS_ASSERT(t != m);
//     NXS_ASSERT(m != out);
//     ...
//     return;
// }
// void NXS_Ten3Mat3Mul(const NXS_Ten3* restrict t, const NXS_Mat3* restrict m, NXS_Ten3* restrict out) {
//     NXS_ASSERT(t != m);
//     NXS_ASSERT(m != out);
//     ...
//     return;
// }
// void NXS_Ten3Mat4Mul(const NXS_Ten3* restrict t, const NXS_Mat4* restrict m, NXS_Ten3* restrict out) {
//     NXS_ASSERT(t != m);
//     NXS_ASSERT(m != out);
//     ...
//     return;
// }

#endif //_NXS_MATH_H_