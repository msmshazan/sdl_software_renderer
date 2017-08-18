/*
  HandmadeMath.h v1.2.0
  
  This is a single header file with a bunch of useful functions for
  basic game math operations.
  
  =============================================================================
  
  You MUST
  
     #define MATH_IMPLEMENTATION
     
  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:
  
     #define MATH_IMPLEMENTATION
     #include "HandmadeMath.h"
     
  All other files should just #include "HandmadeMath.h" without the #define.
  
  =============================================================================
  
  For overloaded and operator overloaded versions of the base C functions,
  you MUST
  
     #define MATH_CPP_MODE
     
  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:
  
     #define MATH_IMPLEMENTATION
     #define MATH_CPP_MODE
     #include "HandmadeMath.h"
     
  All other files should just #include "HandmadeMath.h" without the #define.
  
  =============================================================================
  
  To disable SSE intrinsics, you MUST
  
  #define MATH_NO_SSE
  
  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:
  
     #define MATH_IMPLEMENTATION
     #define MATH_CPP_MODE
     #define MATH_NO_SSE
     #include "HandmadeMath.h"
     
     or
     
     #define MATH_IMPLEMENTATION
     #define MATH_NO_SSE
     #include "HandmadeMath.h"
     
  =============================================================================
  
  To disable inlining functions, you MUST
  
  #define MATH_NO_INLINE
  
  in EXACTLY one C or C++ file that includes this header, BEFORE the
  include, like this:
  
     #define MATH_IMPLEMENTATION
     #define MATH_CPP_MODE
     #define MATH_NO_INLINE
     #include "HandmadeMath.h"
     
  All other files should just #include "HandmadeMath.h" without the #define.
  
  =============================================================================
  
  To use HandmadeMath without the CRT, you MUST 
  
     #define SINF MySinF
     #define COSF MyCosF
     #define TANF MyTanF
     #define SQRTF MySqrtF
     #define EXPF MyExpF
     #define LOGF MyLogF
     #define ACOSF MyACosF
     #define ATANF MyATanF
     #define ATAN2F MYATan2F
     
  Provide your own implementations of SinF, CosF, TanF, ACosF, ATanF, ATan2F, 
  ExpF, and LogF in EXACTLY one C or C++ file that includes this header,
  BEFORE the include, like this:     
  
     #define SINF MySinF
     #define COSF MyCosF
     #define TANF MyTanF
     #define SQRTF MySqrtF
     #define EXPF MyExpF
     #define LOGF MyLogF
     #define ACOSF MyACosF
     #define ATANF MyATanF
     #define ATAN2F MyATan2F
     #define MATH_IMPLEMENTATION
     #define MATH_CPP_MODE
     #include "HandmadeMath.h"
     
  If you do not define all five of these, HandmadeMath.h will use the
  versions of these functions that are provided by the CRT.
  
  =============================================================================
  
  Version History:
      0.2 (*) Updated documentation
          (*) Better C compliance
          (*) Prefix all handmade math functions 
          (*) Better operator overloading
      0.2a
          (*) Prefixed Macros
      0.2b
          (*) Disabled warning 4201 on MSVC as it is legal is C11
          (*) Removed the f at the end of PI to get 64bit precision
      0.3
          (*) Added +=, -=, *=, /= for vec2, vec3, vec4
      0.4
          (*) SSE Optimized SqrtF
          (*) SSE Optimized RSqrtF
          (*) Removed CRT
      0.5
          (*) Added scalar multiplication and division for vectors
              and matrices
          (*) Added matrix subtraction and += for mat4
          (*) Reconciled all headers and implementations
          (*) Tidied up, and filled in a few missing operators
      0.5.1
          (*) Ensured column-major order for matrices throughout
          (*) Fixed Translate producing row-major matrices
      0.5.2
          (*) Fixed SSE code in SqrtF
          (*) Fixed SSE code in RSqrtF
      0.6
          (*) Added Unit testing
          (*) Made Power faster
          (*) Fixed possible efficiency problem with Normalize 
          (*) RENAMED LengthSquareRoot to LengthSquared
          (*) RENAMED RSqrtF to RSquareRootF
          (*) RENAMED SqrtF to SquareRootF
          (*) REMOVED Inner function (user should use Dot now)
          (*) REMOVED FastInverseSquareRoot function declaration
      0.7 
          (*) REMOVED LengthSquared in MATH_IMPLEMENTATION (should
              use LengthSquaredVec3, or MATH_CPP_MODE for function
              overloaded version)
          (*) REMOVED Length in MATH_IMPLEMENTATION (should use
              LengthVec3, MATH_CPP_MODE for function
              overloaded version)
          (*) REMOVED Normalize in MATH_IMPLEMENTATION (should use
              NormalizeVec3, or MATH_CPP_MODE for function
              overloaded version)
          (*) Added LengthSquaredVec2
          (*) Added LengthSquaredVec4
          (*) Addd LengthVec2
          (*) Added LengthVec4
          (*) Added NormalizeVec2
          (*) Added NormalizeVec4
     1.0
          (*) Lots of testing!
     1.1
          (*) Quaternion support
          (*) Added type quaternion
          (*) Added Quaternion
          (*) Added QuaternionV4
          (*) Added AddQuaternion
          (*) Added SubtractQuaternion
          (*) Added MultiplyQuaternion
          (*) Added MultiplyQuaternionF
          (*) Added DivideQuaternionF
          (*) Added InverseQuaternion
          (*) Added DotQuaternion
          (*) Added NormalizeQuaternion
          (*) Added Slerp
          (*) Added QuaternionToMat4
          (*) Added QuaternionFromAxisAngle
     1.1.1
          (*) Resolved compiler warnings on gcc and g++
     1.1.2
          (*) Fixed invalid DEF's in the function definitions
     1.1.3
          (*) Fixed compile error in C mode
     1.1.4
          (*) Fixed SSE being included on platforms that don't support it
          (*) Fixed divide-by-zero errors when normalizing zero vectors.
     1.1.5
          (*) Add Width and Height to Vec2
          (*) Made it so you can supply your own SqrtF 
     1.2.0
          (*) Added equality functions for Vec2, Vec3, and Vec4.
              (*) Added EqualsVec2, EqualsVec3, and EqualsVec4
              (*) Added C++ overloaded Equals for all three
              (*) Added C++ == and != operators for all three
          (*) SSE'd MultiplyMat4 (this is _WAY_ faster)
          (*) SSE'd Transpose
          
  LICENSE
  
  This software is in the public domain. Where that dedication is not
  recognized, you are granted a perpetual, irrevocable license to copy,
  distribute, and modify this file as you see fit.
  
  CREDITS
  
  Written by Zakary Strange (zak@handmade.network && @strangezak)
  
  Functionality:
   Matt Mascarenhas (@miblo_)
   Aleph
   FieryDrake (@fierydrake)
   Gingerbill (@TheGingerBill)
   Ben Visness (@bvisness) 
   Trinton Bullard (@Peliex_Dev)
   
  Fixes:
   Jeroen van Rijn (@J_vanRijn)
   Kiljacken (@Kiljacken)
   Insofaras (@insofaras)
   Daniel Gibson (@DanielGibson)
*/


/* let's figure out if SSE is really available (unless disabled anyway)
   (it isn't on non-x86/x86_64 platforms or even x86 without explicit SSE support)
   => only use "#ifdef MATH__USE_SSE" to check for SSE support below this block! */
#ifndef MATH_NO_SSE

# ifdef _MSC_VER
   /* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#  if defined(_M_AMD64) || ( defined(_M_IX86_FP) && _M_IX86_FP >= 1 )
#   define MATH__USE_SSE 1
#  endif
# else /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#  ifdef __SSE__ /* they #define __SSE__ if it's supported */
#   define MATH__USE_SSE 1
#  endif /*  __SSE__ */
# endif /* not _MSC_VER */

#endif /* #ifndef MATH_NO_SSE */

#include <stdint.h> // This is for types

#ifdef MATH__USE_SSE
#include <xmmintrin.h>
#endif

#ifndef MATH_H
#define MATH_H

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

#ifdef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef MATH_STATIC
#define DEF static
#else
#define DEF extern
#endif

#ifdef MATH_NO_INLINE
#define INLINE
#elif _MSC_VER && !__INTEL_COMPILER
#define INLINE __inline
#else
#define INLINE inline
#endif

#if !defined(SINF) || !defined(COSF) || !defined(TANF) || \
    !defined(SQRTF) || !defined(EXPF) || !defined(LOGF) || \
    !defined(ACOSF) || !defined(ATANF)|| !defined(ATAN2F)
#include <math.h>    
#endif
    
#ifndef SINF
#define SINF sinf
#endif    
        
#ifndef COSF
#define COSF cosf
#endif    
        
#ifndef TANF
#define TANF tanf
#endif        

#ifndef SQRTF
#define SQRTF sqrtf
#endif    
    
#ifndef EXPF
#define EXPF expf
#endif

#ifndef LOGF
#define LOGF logf
#endif

#ifndef ACOSF
#define ACOSF acosf
#endif

#ifndef ATANF
#define ATANF atanf
#endif

#ifndef ATAN2F
#define ATAN2F atan2f
#endif

#define PI32 3.14159265359f
#define PI 3.14159265358979323846

#define MIN(a, b) (a) > (b) ? (b) : (a)
#define MAX(a, b) (a) < (b) ? (b) : (a)
#define ABS(a) ((a) > 0 ? (a) : -(a))
#define MOD(a, m) ((a) % (m)) >= 0 ? ((a) % (m)) : (((a) % (m)) + (m))
#define SQUARE(x) ((x) * (x))

typedef union vec2
{
    struct
    {
        float X, Y;
    };

    struct
    {
        float U, V;
    };

    struct
    {
        float Left, Right;
    };
    
    struct
    {
        float Width, Height;
    };

    float Elements[2];
} vec2;

typedef union vec3
{
    struct
    {
        float X, Y, Z;
    };

    struct
    {
        float U, V, W;
    };

    struct
    {
        float R, G, B;
    };

    struct
    {
        vec2 XY;
        float Ignored0_;
    };

    struct
    {
        float Ignored1_;
        vec2 YZ;
    };

    struct
    {
        vec2 UV;
        float Ignored2_;
    };

    struct
    {
        float Ignored3_;
        vec2 VW;
    };

    float Elements[3];
} vec3;

typedef union vec4
{
    struct
    {
        union
        {
            vec3 XYZ;
            struct
            {
                float X, Y, Z;
            };
        };

        float W;
    };
    struct
    {
        union
        {
            vec3 RGB;
            struct
            {
                float R, G, B;
            };
        };

        float A;
    };

    struct
    {
        vec2 XY;
        float Ignored0_;
        float Ignored1_;
    };

    struct
    {
        float Ignored2_;
        vec2 YZ;
        float Ignored3_;
    };

    struct
    {
        float Ignored4_;
        float Ignored5_;
        vec2 ZW;
    };

    float Elements[4];
} vec4;

typedef union mat4
{
       float Elements[4][4];
  
        float Element[16];
    
#ifdef MATH__USE_SSE
    __m128 Rows[4];
#endif
} mat4;

typedef union quaternion
{
    struct
    {
        union
        {
            vec3 XYZ;
            struct
            {
                float X, Y, Z;
            };
        };
        
        float W;
    };
    
    float Elements[4];
} quaternion;

//typedef int32_t bool;

typedef vec2 v2;
typedef vec3 v3;
typedef vec4 v4;
typedef mat4 m4;    

DEF float SinF(float Angle);
DEF float TanF(float Angle);
DEF float ATanF(float Theta);
DEF float ATan2F(float Theta, float Theta2);
DEF float CosF(float Angle);
DEF float ACosF(float Theta);
DEF float ExpF(float Float);
DEF float LogF(float Float);

DEF float ToRadians(float Degrees);
DEF float SquareRootF(float Float);
DEF float RSquareRootF(float Float);

DEF float LengthSquaredVec2(vec2 A);
DEF float LengthSquaredVec3(vec3 A);
DEF float LengthSquaredVec4(vec4 A);

DEF float LengthVec2(vec2 A);    
DEF float LengthVec3(vec3 A);    
DEF float LengthVec4(vec4 A);    

DEF float Power(float Base, int Exponent);
DEF float PowerF(float Base, float Exponent);
DEF float Lerp(float A, float Time, float B);
DEF float Clamp(float Min, float Value, float Max);

DEF vec2 NormalizeVec2(vec2 A);
DEF vec3 NormalizeVec3(vec3 A);
DEF vec4 NormalizeVec4(vec4 A);

DEF float DotVec2(vec2 VecOne, vec2 VecTwo);
DEF float DotVec3(vec3 VecOne, vec3 VecTwo);
DEF float DotVec4(vec4 VecOne, vec4 VecTwo);

DEF vec3 Cross(vec3 VecOne, vec3 VecTwo);

DEF vec2 Vec2(float X, float Y);
DEF vec2 Vec2i(int X, int Y);
DEF vec3 Vec3(float X, float Y, float Z);
DEF vec3 Vec3i(int X, int Y, int Z);
DEF vec4 Vec4(float X, float Y, float Z, float W);
DEF vec4 Vec4i(int X, int Y, int Z, int W);
DEF vec4 Vec4v(vec3 Vector, float W);

DEF vec2 AddVec2(vec2 Left, vec2 Right);
DEF vec3 AddVec3(vec3 Left, vec3 Right);
DEF vec4 AddVec4(vec4 Left, vec4 Right);

DEF vec2 SubtractVec2(vec2 Left, vec2 Right);
DEF vec3 SubtractVec3(vec3 Left, vec3 Right);
DEF vec4 SubtractVec4(vec4 Left, vec4 Right);

DEF vec2 MultiplyVec2(vec2 Left, vec2 Right);
DEF vec2 MultiplyVec2f(vec2 Left, float Right);
DEF vec3 MultiplyVec3(vec3 Left, vec3 Right);
DEF vec3 MultiplyVec3f(vec3 Left, float Right);
DEF vec4 MultiplyVec4(vec4 Left, vec4 Right);
DEF vec4 MultiplyVec4f(vec4 Left, float Right);

DEF vec2 DivideVec2(vec2 Left, vec2 Right);
DEF vec2 DivideVec2f(vec2 Left, float Right);
DEF vec3 DivideVec3(vec3 Left, vec3 Right);
DEF vec3 DivideVec3f(vec3 Left, float Right);
DEF vec4 DivideVec4(vec4 Left, vec4 Right);
DEF vec4 DivideVec4f(vec4 Left, float Right);

DEF bool EqualsVec2(vec2 Left, vec2 Right);
DEF bool EqualsVec3(vec3 Left, vec3 Right);
DEF bool EqualsVec4(vec4 Left, vec4 Right);

DEF mat4 Mat4(void);
DEF mat4 Mat4d(float Diagonal);
DEF mat4 AddMat4(mat4 Left, mat4 Right);
DEF mat4 SubtractMat4(mat4 Left, mat4 Right);

#ifdef MATH__USE_SSE
DEF __m128 LinearCombineSSE(__m128 Left, mat4 Right);
#endif 

DEF mat4 MultiplyMat4(mat4 Left, mat4 Right);
DEF mat4 MultiplyMat4f(mat4 Matrix, float Scalar);
DEF vec4 MultiplyMat4ByVec4(mat4 Matrix, vec4 Vector);
DEF mat4 DivideMat4f(mat4 Matrix, float Scalar);

DEF mat4 Transpose(mat4 Matrix);

DEF mat4 Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
DEF mat4 Perspective(float FOV, float AspectRatio, float Near, float Far);

DEF mat4 Translate(vec3 Translation);
DEF mat4 Rotate(float Angle, vec3 Axis);
DEF mat4 Scale(vec3 Scale);

DEF mat4 LookAt(vec3 Eye, vec3 Center, vec3 Up);

DEF quaternion Quaternion(float X, float Y, float Z, float W);
DEF quaternion QuaternionV4(vec4 Vector);
DEF quaternion AddQuaternion(quaternion Left, quaternion Right);
DEF quaternion SubtractQuaternion(quaternion Left, quaternion Right);
DEF quaternion MultiplyQuaternion(quaternion Left, quaternion Right);
DEF quaternion MultiplyQuaternionF(quaternion Left, float Multiplicative);
DEF quaternion DivideQuaternionF(quaternion Left, float Dividend);
DEF quaternion InverseQuaternion(quaternion Left);
DEF float DotQuaternion(quaternion Left, quaternion Right);
DEF quaternion NormalizeQuaternion(quaternion Left);
DEF quaternion NLerp(quaternion Left, float Time, quaternion Right);
DEF quaternion Slerp(quaternion Left, float Time, quaternion Right);
DEF mat4 QuaternionToMat4(quaternion Left);
DEF quaternion QuaternionFromAxisAngle(vec3 Axis, float AngleOfRotation);

#ifdef __cplusplus
}
#endif

#ifdef MATH_CPP_MODE

DEF float Length(vec2 A);
DEF float Length(vec3 A);
DEF float Length(vec4 A);

DEF float LengthSquared(vec2 A);
DEF float LengthSquared(vec3 A);
DEF float LengthSquared(vec4 A);

DEF vec2 Normalize(vec2 A);
DEF vec3 Normalize(vec3 A);
DEF vec4 Normalize(vec4 A);
DEF quaternion Normalize(quaternion A);

DEF float Dot(vec2 VecOne, vec2 VecTwo);
DEF float Dot(vec3 VecOne, vec3 VecTwo);
DEF float Dot(vec4 VecOne, vec4 VecTwo);
DEF float Dot(quaternion QuatOne, quaternion QuatTwo);

DEF vec2 Add(vec2 Left, vec2 Right);
DEF vec3 Add(vec3 Left, vec3 Right);
DEF vec4 Add(vec4 Left, vec4 Right);
DEF mat4 Add(mat4 Left, mat4 Right);
DEF quaternion Add(quaternion Left, quaternion Right);

DEF vec2 Subtract(vec2 Left, vec2 Right);
DEF vec3 Subtract(vec3 Left, vec3 Right);
DEF vec4 Subtract(vec4 Left, vec4 Right);
DEF mat4 Subtract(mat4 Left, mat4 Right);
DEF quaternion Subtract(quaternion Left, quaternion Right);

DEF vec2 Multiply(vec2 Left, vec2 Right);
DEF vec2 Multiply(vec2 Left, float Right);
DEF vec3 Multiply(vec3 Left, vec3 Right);
DEF vec3 Multiply(vec3 Left, float Right);
DEF vec4 Multiply(vec4 Left, vec4 Right);
DEF vec4 Multiply(vec4 Left, float Right);
DEF mat4 Multiply(mat4 Left, mat4 Right);
DEF mat4 Multiply(mat4 Left, float Right);
DEF vec4 Multiply(mat4 Matrix, vec4 Vector);
DEF quaternion Multiply(quaternion Left, quaternion Right);
DEF quaternion Multiply(quaternion Left, float Right);

DEF vec2 Divide(vec2 Left, vec2 Right);
DEF vec2 Divide(vec2 Left, float Right);
DEF vec3 Divide(vec3 Left, vec3 Right);
DEF vec3 Divide(vec3 Left, float Right);
DEF vec4 Divide(vec4 Left, vec4 Right);
DEF vec4 Divide(vec4 Left, float Right);
DEF mat4 Divide(mat4 Left, float Right);
DEF quaternion Divide(quaternion Left, quaternion Right);
DEF quaternion Divide(quaternion Left, float Right);

DEF bool Equals(vec2 Left, vec2 Right);
DEF bool Equals(vec3 Left, vec3 Right);
DEF bool Equals(vec4 Left, vec4 Right);

DEF vec2 operator+(vec2 Left, vec2 Right);
DEF vec3 operator+(vec3 Left, vec3 Right);
DEF vec4 operator+(vec4 Left, vec4 Right);
DEF mat4 operator+(mat4 Left, mat4 Right);
DEF quaternion operator+(quaternion Left, quaternion Right);

DEF vec2 operator-(vec2 Left, vec2 Right);
DEF vec3 operator-(vec3 Left, vec3 Right);
DEF vec4 operator-(vec4 Left, vec4 Right);
DEF mat4 operator-(mat4 Left, mat4 Right);
DEF quaternion operator-(quaternion Left, quaternion Right);

DEF vec2 operator*(vec2 Left, vec2 Right);
DEF vec3 operator*(vec3 Left, vec3 Right);
DEF vec4 operator*(vec4 Left, vec4 Right);
DEF mat4 operator*(mat4 Left, mat4 Right);
DEF quaternion operator*(quaternion Left, quaternion Right);

DEF vec2 operator*(vec2 Left, float Right);
DEF vec3 operator*(vec3 Left, float Right);
DEF vec4 operator*(vec4 Left, float Right);
DEF mat4 operator*(mat4 Left, float Right);
DEF quaternion operator*(quaternion Left, float Right);

DEF vec2 operator*(float Left, vec2 Right);
DEF vec3 operator*(float Left, vec3 Right);
DEF vec4 operator*(float Left, vec4 Right);
DEF mat4 operator*(float Left, mat4 Right);
DEF quaternion operator*(float Left, quaternion Right);

DEF vec4 operator*(mat4 Matrix, vec4 Vector);

DEF vec2 operator/(vec2 Left, vec2 Right);
DEF vec3 operator/(vec3 Left, vec3 Right);
DEF vec4 operator/(vec4 Left, vec4 Right);

DEF vec2 operator/(vec2 Left, float Right);
DEF vec3 operator/(vec3 Left, float Right);
DEF vec4 operator/(vec4 Left, float Right);
DEF mat4 operator/(mat4 Left, float Right);
DEF quaternion operator/(quaternion Left, float Right);

DEF vec2 &operator+=(vec2 &Left, vec2 Right);
DEF vec3 &operator+=(vec3 &Left, vec3 Right);
DEF vec4 &operator+=(vec4 &Left, vec4 Right);
DEF mat4 &operator+=(mat4 &Left, mat4 Right);
DEF quaternion &operator+=(quaternion &Left, quaternion Right);

DEF vec2 &operator-=(vec2 &Left, vec2 Right);
DEF vec3 &operator-=(vec3 &Left, vec3 Right);
DEF vec4 &operator-=(vec4 &Left, vec4 Right);
DEF mat4 &operator-=(mat4 &Left, mat4 Right);
DEF quaternion &operator-=(quaternion &Left, quaternion Right);

DEF vec2 &operator*=(vec2 &Left, vec2 Right);
DEF vec3 &operator*=(vec3 &Left, vec3 Right);
DEF vec4 &operator*=(vec4 &Left, vec4 Right);

DEF vec2 &operator*=(vec2 &Left, float Right);
DEF vec3 &operator*=(vec3 &Left, float Right);
DEF vec4 &operator*=(vec4 &Left, float Right);
DEF mat4 &operator*=(mat4 &Left, float Right);
DEF quaternion &operator*=(quaternion &Left, float Right);

DEF vec2 &operator/=(vec2 &Left, vec2 Right);
DEF vec3 &operator/=(vec3 &Left, vec3 Right);
DEF vec4 &operator/=(vec4 &Left, vec4 Right);

DEF vec2 &operator/=(vec2 &Left, float Right);
DEF vec3 &operator/=(vec3 &Left, float Right);
DEF vec4 &operator/=(vec4 &Left, float Right);
DEF mat4 &operator/=(mat4 &Left, float Right);
DEF quaternion &operator/=(quaternion &Left, float Right);

DEF bool operator==(vec2 Left, vec2 Right);
DEF bool operator==(vec3 Left, vec3 Right);
DEF bool operator==(vec4 Left, vec4 Right);

DEF bool operator!=(vec2 Left, vec2 Right);
DEF bool operator!=(vec3 Left, vec3 Right);
DEF bool operator!=(vec4 Left, vec4 Right);

#endif /* MATH_CPP */

#ifdef __clang__
#pragma GCC diagnostic pop
#endif

#endif /* MATH_H */

#ifdef MATH_IMPLEMENTATION

INLINE float
SinF(float Angle)
{
    float Result = 0.0f;

    Result = SINF(Angle);
    return (Result);
}

INLINE float
CosF(float Angle)
{
    float Result = 0.0f;

    Result = COSF(Angle);
    return (Result);
}

INLINE float
TanF(float Radians)
{
    float Result = 0.0f;

    Result = TANF(Radians);
    return (Result);
}

INLINE float
ACosF(float Radians)
{
    float Result = 0.0f;

    Result = ACOSF(Radians);
    return (Result);
}

INLINE float
ATanF(float Radians)
{
    float Result = 0.0f;

    Result = ATANF(Radians);
    return (Result);
}

INLINE float
Atan2F(float Left, float Right)
{
    float Result = 0.0f;

    Result = ATAN2F(Left, Right);
    return (Result);
}

INLINE float
ExpF(float Float)
{
    float Result = 0.0f;

    Result = EXPF(Float);
    return (Result);
}

INLINE float
LogF(float Float)
{
    float Result = 0.0f;

    Result = LOGF(Float);
    return (Result);
}

INLINE float
ToRadians(float Degrees)
{
    float Result = 0.0f;

    Result = Degrees * (PI32 / 180.0f);
    return (Result);
}

INLINE float
SquareRootF(float Value)
{
    float Result = 0.0f;

#ifdef MATH__USE_SSE
    __m128 In = _mm_set_ss(Value);
    __m128 Out = _mm_sqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#else
    Result = SQRTF(Value);
#endif 

    return(Result);
}

INLINE float
RSquareRootF(float Value)
{
    float Result = 0.0f;

#ifdef MATH__USE_SSE
    __m128 In = _mm_set_ss(Value);
    __m128 Out = _mm_rsqrt_ss(In);
    Result = _mm_cvtss_f32(Out);
#else
    Result = 1.0f/SquareRootF(Value);
#endif

    return(Result);
}

INLINE float
LengthSquaredVec2(vec2 A)
{
    float Result = 0.0f;
    
    Result = DotVec2(A, A);
    
    return(Result);
}

INLINE float
LengthSquaredVec3(vec3 A)
{
    float Result = 0.0f;

    Result = DotVec3(A, A);
    
    return (Result);
}

INLINE float 
LengthSquaredVec4(vec4 A)
{
    float Result = 0.0f;
    
    Result = DotVec4(A, A);
    
    return(Result);
}

INLINE float
LengthVec2(vec2 A)
{
    float Result = 0.0f;
    
    Result = SquareRootF(LengthSquaredVec2(A));
    
    return(Result);
}

INLINE float
LengthVec3(vec3 A)
{
    float Result = 0.0f;

    Result = SquareRootF(LengthSquaredVec3(A));
    
    return (Result);
}

INLINE float 
LengthVec4(vec4 A)
{
    float Result = 0.0f;
    
    Result = SquareRootF(LengthSquaredVec4(A));
    
    return(Result);
}

INLINE float
Power(float Base, int Exponent)
{
    float Result = 1.0f;
    float Mul = Exponent < 0 ? 1.f / Base : Base;
    unsigned int X = Exponent < 0 ? -Exponent : Exponent;
    while (X)
    {
        if (X & 1)
        {
            Result *= Mul;
        }
        
        Mul *= Mul;
        X >>= 1;
    }
    
    return (Result);
}

INLINE float
PowerF(float Base, float Exponent)
{
    return EXPF(Exponent * LOGF(Base));
}

INLINE float
Lerp(float A, float Time, float B)
{
    float Result = 0;

    Result = (1.0f - Time) * A + Time * B;
    return (Result);
}

INLINE float
Clamp(float Min, float Value, float Max)
{
    float Result = Value;

    if(Result < Min)
    {
        Result = Min;
    }
    else if(Result > Max)
    {
        Result = Max;
    }

    return (Result);
}

INLINE vec2
NormalizeVec2(vec2 A)
{
    vec2 Result = {0};

    float VectorLength = LengthVec2(A);
    
    /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
    if (VectorLength != 0.0f)
    {
        Result.X = A.X * (1.0f / VectorLength);
        Result.Y = A.Y * (1.0f / VectorLength);
    }
    
    return (Result);
}

INLINE vec3
NormalizeVec3(vec3 A)
{
    vec3 Result = {0};

    float VectorLength = LengthVec3(A);
    
    /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
    if (VectorLength != 0.0f)
    {
        Result.X = A.X * (1.0f / VectorLength);
        Result.Y = A.Y * (1.0f / VectorLength);
        Result.Z = A.Z * (1.0f / VectorLength);
    }
    
    return (Result);
}

INLINE vec4
NormalizeVec4(vec4 A)
{
    vec4 Result = {0};

    float VectorLength = LengthVec4(A);
    
    /* NOTE(kiljacken): We need a zero check to not divide-by-zero */
    if (VectorLength != 0.0f)
    {
        Result.X = A.X * (1.0f / VectorLength);
        Result.Y = A.Y * (1.0f / VectorLength);
        Result.Z = A.Z * (1.0f / VectorLength);
        Result.W = A.W * (1.0f / VectorLength);
    }
    
    return (Result);
}

INLINE float
DotVec2(vec2 VecOne, vec2 VecTwo)
{
    float Result = 0.0f;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y);
    
    return (Result);
}

INLINE float
DotVec3(vec3 VecOne, vec3 VecTwo)
{
    float Result = 0.0f;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z);
    
    return (Result);
}

INLINE float
DotVec4(vec4 VecOne, vec4 VecTwo)
{
    float Result = 0.0f;

    Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z) + (VecOne.W * VecTwo.W);
    
    return (Result);
}

INLINE vec3
Cross(vec3 VecOne, vec3 VecTwo)
{
    vec3 Result = {0};

    Result.X = (VecOne.Y * VecTwo.Z) - (VecOne.Z * VecTwo.Y);
    Result.Y = (VecOne.Z * VecTwo.X) - (VecOne.X * VecTwo.Z);
    Result.Z = (VecOne.X * VecTwo.Y) - (VecOne.Y * VecTwo.X);

    return (Result);
}

INLINE vec2
Vec2(float X, float Y)
{
    vec2 Result = {0};

    Result.X = X;
    Result.Y = Y;

    return (Result);
}

INLINE vec2
Vec2i(int X, int Y)
{
    vec2 Result = {0};

    Result.X = (float)X;
    Result.Y = (float)Y;

    return (Result);
}

INLINE vec3
Vec3(float X, float Y, float Z)
{
    vec3 Result = {0};

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;

    return (Result);
}

INLINE vec3
Vec3i(int X, int Y, int Z)
{
    vec3 Result = {0};

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;

    return (Result);
}

INLINE vec4
Vec4(float X, float Y, float Z, float W)
{
    vec4 Result = {0};

    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;

    return (Result);
}

INLINE vec4
Vec4i(int X, int Y, int Z, int W)
{
    vec4 Result = {0};

    Result.X = (float)X;
    Result.Y = (float)Y;
    Result.Z = (float)Z;
    Result.W = (float)W;

    return (Result);
}

INLINE vec4
Vec4v(vec3 Vector, float W)
{
    vec4 Result = {0};

    Result.XYZ = Vector;
    Result.W = W;

    return (Result);
}

INLINE vec2
AddVec2(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;

    return (Result);
}

INLINE vec3
AddVec3(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;

    return (Result);
}

INLINE vec4
AddVec4(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return (Result);
}

INLINE vec2
SubtractVec2(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;

    return (Result);
}

INLINE vec3
SubtractVec3(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;

    return (Result);
}

INLINE vec4
SubtractVec4(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return (Result);
}

INLINE vec2
MultiplyVec2(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;

    return (Result);
}

INLINE vec2
MultiplyVec2f(vec2 Left, float Right)
{
    vec2 Result = {0};

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;

    return (Result);
}

INLINE vec3
MultiplyVec3(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;

    return (Result);
}

INLINE vec3
MultiplyVec3f(vec3 Left, float Right)
{
    vec3 Result = {0};

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;

    return (Result);
}

INLINE vec4
MultiplyVec4(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result.X = Left.X * Right.X;
    Result.Y = Left.Y * Right.Y;
    Result.Z = Left.Z * Right.Z;
    Result.W = Left.W * Right.W;

    return (Result);
}

INLINE vec4
MultiplyVec4f(vec4 Left, float Right)
{
    vec4 Result = {0};

    Result.X = Left.X * Right;
    Result.Y = Left.Y * Right;
    Result.Z = Left.Z * Right;
    Result.W = Left.W * Right;

    return (Result);
}

INLINE vec2
DivideVec2(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;

    return (Result);
}

INLINE vec2
DivideVec2f(vec2 Left, float Right)
{
    vec2 Result = {0};

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;

    return (Result);
}

INLINE vec3
DivideVec3(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;

    return (Result);
}

INLINE vec3
DivideVec3f(vec3 Left, float Right)
{
    vec3 Result = {0};

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;

    return (Result);
}

INLINE vec4
DivideVec4(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result.X = Left.X / Right.X;
    Result.Y = Left.Y / Right.Y;
    Result.Z = Left.Z / Right.Z;
    Result.W = Left.W / Right.W;

    return (Result);
}

INLINE vec4
DivideVec4f(vec4 Left, float Right)
{
    vec4 Result = {0};

    Result.X = Left.X / Right;
    Result.Y = Left.Y / Right;
    Result.Z = Left.Z / Right;
    Result.W = Left.W / Right;

    return (Result);
}

INLINE bool
EqualsVec2(vec2 Left, vec2 Right)
{
    bool Result = 0;

    Result = (Left.X == Right.X && Left.Y == Right.Y);

    return (Result);
}

INLINE bool
EqualsVec3(vec3 Left, vec3 Right)
{
    bool Result = 0;

    Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z);

    return (Result);
}

INLINE bool
EqualsVec4(vec4 Left, vec4 Right)
{
    bool Result = 0;

    Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W);

    return (Result);
}

INLINE mat4
Mat4(void)
{
    mat4 Result = {0};

    return (Result);
}

INLINE mat4
Mat4d(float Diagonal)
{
    mat4 Result = Mat4();

    Result.Elements[0][0] = Diagonal;
    Result.Elements[1][1] = Diagonal;
    Result.Elements[2][2] = Diagonal;
    Result.Elements[3][3] = Diagonal;

    return (Result);
}

INLINE mat4
AddMat4(mat4 Left, mat4 Right)
{
    mat4 Result = Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] + Right.Elements[Columns][Rows];
        }
    }

    return (Result);
}

INLINE mat4
SubtractMat4(mat4 Left, mat4 Right)
{
    mat4 Result = Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Left.Elements[Columns][Rows] - Right.Elements[Columns][Rows];
        }
    }

    return (Result);
}

#ifdef MATH__USE_SSE
INLINE __m128
LinearCombineSSE(__m128 Left, mat4 Right)
{
    __m128 Result = {};
    Result = _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x00), Right.Rows[0]);
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x55), Right.Rows[1]));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xaa), Right.Rows[2]));
    Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xff), Right.Rows[3]));
    
    return(Result);
}
#endif

INLINE mat4
MultiplyMat4(mat4 Left, mat4 Right)
{
    mat4 Result = Mat4();

#ifdef MATH__USE_SSE
    
    mat4 TransposedLeft = Transpose(Left);
    mat4 TransposedRight = Transpose(Right);

    Result.Rows[0] = LinearCombineSSE(TransposedLeft.Rows[0], TransposedRight);
    Result.Rows[1] = LinearCombineSSE(TransposedLeft.Rows[1], TransposedRight);
    Result.Rows[2] = LinearCombineSSE(TransposedLeft.Rows[2], TransposedRight);
    Result.Rows[3] = LinearCombineSSE(TransposedLeft.Rows[3], TransposedRight);       
    
    Result = Transpose(Result);
    
#else
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            float Sum = 0;
            int CurrentMatrice;
            for(CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
            {
                Sum += Left.Elements[CurrentMatrice][Rows] * Right.Elements[Columns][CurrentMatrice];
            }

            Result.Elements[Columns][Rows] = Sum;
        }
    }
#endif 
    return (Result);
}

INLINE mat4
MultiplyMat4f(mat4 Matrix, float Scalar)
{
    mat4 Result = Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] * Scalar;
        }
    }

    return (Result);
}

INLINE vec4
MultiplyMat4ByVec4(mat4 Matrix, vec4 Vector)
{
    vec4 Result = {0};
    
    int Columns, Rows;
    for(Rows = 0; Rows < 4; ++Rows)
    {
        float Sum = 0;
        for(Columns = 0; Columns < 4; ++Columns)
        {
            Sum += Matrix.Elements[Columns][Rows] * Vector.Elements[Columns];
        }
        
        Result.Elements[Rows] = Sum;
    }
    
    return (Result);
}

INLINE mat4
DivideMat4f(mat4 Matrix, float Scalar)
{
    mat4 Result = Mat4();

    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Columns][Rows] = Matrix.Elements[Columns][Rows] / Scalar;
        }
    }

    return (Result);
}

INLINE mat4
Transpose(mat4 Matrix)
{
    mat4 Result = Mat4();

#ifdef MATH__USE_SSE
    Result = Matrix;
    
    _MM_TRANSPOSE4_PS(Result.Rows[0], Result.Rows[1], Result.Rows[2], Result.Rows[3]);    
#else 
    int Columns;
    for(Columns = 0; Columns < 4; ++Columns)
    {
        int Rows;
        for(Rows = 0; Rows < 4; ++Rows)
        {
            Result.Elements[Rows][Columns] = Matrix.Elements[Columns][Rows];
        }
    }
#endif 
        
    return (Result);
}

INLINE mat4
Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = 2.0f / (Right - Left);
    Result.Elements[1][1] = 2.0f / (Top - Bottom);
    Result.Elements[2][2] = 2.0f / (Near - Far);

    Result.Elements[3][0] = (Left + Right) / (Left - Right);
    Result.Elements[3][1] = (Bottom + Top) / (Bottom - Top);
    Result.Elements[3][2] = (Far + Near) / (Near - Far);

    return (Result);
}

INLINE mat4
Perspective(float FOV, float AspectRatio, float Near, float Far)
{
    mat4 Result = Mat4d(1.0f);

    float TanThetaOver2 = TanF(FOV * (PI32 / 360.0f));
    
    Result.Elements[0][0] = 1.0f / TanThetaOver2;
    Result.Elements[1][1] = AspectRatio / TanThetaOver2;
    Result.Elements[2][3] = -1.0f;
    Result.Elements[2][2] = (Near + Far) / (Near - Far);
    Result.Elements[3][2] = (2.0f * Near * Far) / (Near - Far);
    Result.Elements[3][3] = 0.0f;

    return (Result);
}

INLINE mat4
Translate(vec3 Translation)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[3][0] = Translation.X;
    Result.Elements[3][1] = Translation.Y;
    Result.Elements[3][2] = Translation.Z;

    return (Result);
}

INLINE mat4
Rotate(float Angle, vec3 Axis)
{
    mat4 Result = Mat4d(1.0f);
    
    Axis = NormalizeVec3(Axis);
    
    float SinTheta = SinF(ToRadians(Angle));
    float CosTheta = CosF(ToRadians(Angle));
    float CosValue = 1.0f - CosTheta;
    
    Result.Elements[0][0] = (Axis.X * Axis.X * CosValue) + CosTheta;
    Result.Elements[0][1] = (Axis.X * Axis.Y * CosValue) + (Axis.Z * SinTheta);
    Result.Elements[0][2] = (Axis.X * Axis.Z * CosValue) - (Axis.Y * SinTheta);
    
    Result.Elements[1][0] = (Axis.Y * Axis.X * CosValue) - (Axis.Z * SinTheta);
    Result.Elements[1][1] = (Axis.Y * Axis.Y * CosValue) + CosTheta;
    Result.Elements[1][2] = (Axis.Y * Axis.Z * CosValue) + (Axis.X * SinTheta);
    
    Result.Elements[2][0] = (Axis.Z * Axis.X * CosValue) + (Axis.Y * SinTheta);
    Result.Elements[2][1] = (Axis.Z * Axis.Y * CosValue) - (Axis.X * SinTheta);
    Result.Elements[2][2] = (Axis.Z * Axis.Z * CosValue) + CosTheta;
    
    return (Result);
}

INLINE mat4
Scale(vec3 Scale)
{
    mat4 Result = Mat4d(1.0f);

    Result.Elements[0][0] = Scale.X;
    Result.Elements[1][1] = Scale.Y;
    Result.Elements[2][2] = Scale.Z;

    return (Result);
}

INLINE mat4
LookAt(vec3 Eye, vec3 Center, vec3 Up)
{
    mat4 Result = {0};

    vec3 F = NormalizeVec3(SubtractVec3(Center, Eye));
    vec3 S = NormalizeVec3(Cross(F, Up));
    vec3 U = Cross(S, F);

    Result.Elements[0][0] = S.X;
    Result.Elements[0][1] = U.X;
    Result.Elements[0][2] = -F.X;

    Result.Elements[1][0] = S.Y;
    Result.Elements[1][1] = U.Y;
    Result.Elements[1][2] = -F.Y;

    Result.Elements[2][0] = S.Z;
    Result.Elements[2][1] = U.Z;
    Result.Elements[2][2] = -F.Z;

    Result.Elements[3][0] = -DotVec3(S, Eye);
    Result.Elements[3][1] = -DotVec3(U, Eye);
    Result.Elements[3][2] = DotVec3(F, Eye);
    Result.Elements[3][3] = 1.0f;

    return (Result);
}


INLINE quaternion 
Quaternion(float X, float Y, float Z, float W)
{
    quaternion Result = {0};
    
    Result.X = X;
    Result.Y = Y;
    Result.Z = Z;
    Result.W = W;
    
    return(Result);
}

INLINE quaternion 
QuaternionV4(vec4 Vector)
{
    quaternion Result = {0};
    
    Result.X = Vector.X;
    Result.Y = Vector.Y;
    Result.Z = Vector.Z;
    Result.W = Vector.W;
    
    return(Result);    
}

INLINE quaternion
AddQuaternion(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result.X = Left.X + Right.X;
    Result.Y = Left.Y + Right.Y;
    Result.Z = Left.Z + Right.Z;
    Result.W = Left.W + Right.W;

    return(Result);
}

INLINE quaternion
SubtractQuaternion(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result.X = Left.X - Right.X;
    Result.Y = Left.Y - Right.Y;
    Result.Z = Left.Z - Right.Z;
    Result.W = Left.W - Right.W;

    return(Result);
}

INLINE quaternion
MultiplyQuaternion(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result.X = (Left.X * Right.W) + (Left.Y * Right.Z) - (Left.Z * Right.Y) + (Left.W * Right.X);
    Result.Y = (-Left.X * Right.Z) + (Left.Y * Right.W) + (Left.Z * Right.X) + (Left.W * Right.Y);
    Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X) + (Left.Z * Right.W) + (Left.W * Right.Z);
    Result.W = (-Left.X * Right.X) - (Left.Y * Right.Y) - (Left.Z * Right.Z) + (Left.W * Right.W);

    return(Result);
}

INLINE quaternion
MultiplyQuaternionF(quaternion Left, float Multiplicative)
{
    quaternion Result = {0};

    Result.X = Left.X * Multiplicative;
    Result.Y = Left.Y * Multiplicative;
    Result.Z = Left.Z * Multiplicative;
    Result.W = Left.W * Multiplicative;

    return(Result);
}

INLINE quaternion
DivideQuaternionF(quaternion Left, float Dividend)
{
    quaternion Result = {0};

    Result.X = Left.X / Dividend;
    Result.Y = Left.Y / Dividend;
    Result.Z = Left.Z / Dividend;
    Result.W = Left.W / Dividend;

    return(Result);
}

INLINE quaternion
InverseQuaternion(quaternion Left)
{
    quaternion Conjugate = {0};
    quaternion Result = {0};
    float Norm = 0;
    float NormSquared = 0;

    Conjugate.X = -Left.X;
    Conjugate.Y = -Left.Y;
    Conjugate.Z = -Left.Z;
    Conjugate.W = Left.W;

    Norm = SquareRootF(DotQuaternion(Left, Left));
    NormSquared = Norm * Norm;

    Result.X = Conjugate.X / NormSquared;
    Result.Y = Conjugate.Y / NormSquared;
    Result.Z = Conjugate.Z / NormSquared;
    Result.W = Conjugate.W / NormSquared;

    return(Result);
}

INLINE float
DotQuaternion(quaternion Left, quaternion Right)
{
    float Result = 0.0f;

    Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z) + (Left.W * Right.W);

    return(Result);
}

INLINE quaternion
NormalizeQuaternion(quaternion Left)
{
    quaternion Result = {0};

    float Length = SquareRootF(DotQuaternion(Left, Left));
    Result = DivideQuaternionF(Left, Length);

    return(Result);
}

INLINE quaternion
NLerp(quaternion Left, float Time, quaternion Right)
{
    quaternion Result = {0};

    Result.X = Lerp(Left.X, Time, Right.X);
    Result.Y = Lerp(Left.Y, Time, Right.Y);
    Result.Z = Lerp(Left.Z, Time, Right.Z);
    Result.W = Lerp(Left.W, Time, Right.W);

    Result = NormalizeQuaternion(Result);

    return(Result);
}

INLINE quaternion
Slerp(quaternion Left, float Time, quaternion Right)
{
    quaternion Result = {0};
    quaternion QuaternionLeft = {0};
    quaternion QuaternionRight = {0};

    float Cos_Theta = DotQuaternion(Left, Right);
    float Angle = ACosF(Cos_Theta);
    
    float S1 = SinF((1.0f - Time) * Angle);
    float S2 = SinF(Time * Angle);
    float Is = 1.0f / SinF(Angle);

    QuaternionLeft = MultiplyQuaternionF(Left, S1);
    QuaternionRight = MultiplyQuaternionF(Right, S2);

    Result = AddQuaternion(QuaternionLeft, QuaternionRight);
    Result = MultiplyQuaternionF(Result, Is);

    return(Result);
}

INLINE mat4
QuaternionToMat4(quaternion Left)
{
    mat4 Result = {0};
    Result = Mat4d(1);

    quaternion NormalizedQuaternion = NormalizeQuaternion(Left);
    
    float XX, YY, ZZ,
          XY, XZ, YZ,
          WX, WY, WZ;

    XX = NormalizedQuaternion.X * NormalizedQuaternion.X;
    YY = NormalizedQuaternion.Y * NormalizedQuaternion.Y;
    ZZ = NormalizedQuaternion.Z * NormalizedQuaternion.Z;
    XY = NormalizedQuaternion.X * NormalizedQuaternion.Y;
    XZ = NormalizedQuaternion.X * NormalizedQuaternion.Z;
    YZ = NormalizedQuaternion.Y * NormalizedQuaternion.Z;
    WX = NormalizedQuaternion.W * NormalizedQuaternion.X;
    WY = NormalizedQuaternion.W * NormalizedQuaternion.Y;
    WZ = NormalizedQuaternion.W * NormalizedQuaternion.Z;

    Result.Elements[0][0] = 1.0f - 2.0f * (YY + ZZ);
    Result.Elements[0][1] = 2.0f * (XY + WZ);
    Result.Elements[0][2] = 2.0f * (XZ - WY);

    Result.Elements[1][0] = 2.0f * (XY - WZ);
    Result.Elements[1][1] = 1.0f - 2.0f * (XX + ZZ);
    Result.Elements[1][2] = 2.0f * (YZ + WX);

    Result.Elements[2][0] = 2.0f * (XZ + WY);
    Result.Elements[2][1] = 2.0f * (YZ - WX);
    Result.Elements[2][2] = 1.0f - 2.0f * (XX + YY);

    return(Result);
}

INLINE quaternion
QuaternionFromAxisAngle(vec3 Axis, float AngleOfRotation)
{
    quaternion Result = {0};
    float AxisNorm = 0;
    float SineOfRotation = 0;
    vec3 RotatedVector = {0};

    AxisNorm = SquareRootF(DotVec3(Axis, Axis));
    SineOfRotation = SinF(AngleOfRotation / 2.0f);
    RotatedVector = MultiplyVec3f(Axis, SineOfRotation);

    Result.W = CosF(AngleOfRotation / 2.0f);
    Result.XYZ = DivideVec3f(RotatedVector, AxisNorm);

    return(Result);
}

#ifdef MATH_CPP_MODE

INLINE float 
Length(vec2 A)
{
    float Result = 0.0f;
    
    Result = LengthVec2(A);
    
    return(Result);
}

INLINE float 
Length(vec3 A)
{
    float Result = 0.0f;
    
    Result = LengthVec3(A);
    
    return(Result);
}

INLINE float 
Length(vec4 A)
{
    float Result = 0.0f;
    
    Result = LengthVec4(A);
    
    return(Result);
}

INLINE float 
LengthSquared(vec2 A)
{
    float Result = 0.0f;
    
    Result = LengthSquaredVec2(A);
    
    return(Result);
}

INLINE float 
LengthSquared(vec3 A)
{
    float Result = 0.0f;
    
    Result = LengthSquaredVec3(A);
    
    return(Result);
}

INLINE float 
LengthSquared(vec4 A)
{
    float Result = 0.0f;
    
    Result = LengthSquaredVec4(A);
    
    return(Result);
}

INLINE vec2 
Normalize(vec2 A)
{
    vec2 Result = {0};
    
    Result = NormalizeVec2(A);    
    
    return(Result);
}

INLINE vec3 
Normalize(vec3 A)
{
    vec3 Result = {0};
    
    Result = NormalizeVec3(A);
    
    return(Result);
}

INLINE vec4 
Normalize(vec4 A)
{
    vec4 Result = {0};
    
    Result = NormalizeVec4(A);
    
    return(Result);
}

INLINE quaternion
Normalize(quaternion A)
{
    quaternion Result = {0};

    Result = NormalizeQuaternion(A);

    return(Result);
}

INLINE float 
Dot(vec2 VecOne, vec2 VecTwo)
{
    float Result = 0;
    
    Result = DotVec2(VecOne, VecTwo);
    
    return(Result);
}

INLINE float 
Dot(vec3 VecOne, vec3 VecTwo)
{
    float Result = 0;
    
    Result = DotVec3(VecOne, VecTwo);
    
    return(Result);
}

INLINE float 
Dot(vec4 VecOne, vec4 VecTwo)
{
    float Result = 0;
    
    Result = DotVec4(VecOne, VecTwo);
    
    return(Result);
}

INLINE float
Dot(quaternion QuatOne, quaternion QuatTwo)
{
    float Result = 0;

    Result = DotQuaternion(QuatOne, QuatTwo);

    return(Result);
}

INLINE vec2
Add(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = AddVec2(Left, Right);
    return (Result);
}

INLINE vec3
Add(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = AddVec3(Left, Right);
    return (Result);
}

INLINE vec4
Add(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = AddVec4(Left, Right);
    return (Result);
}

INLINE mat4
Add(mat4 Left, mat4 Right)
{
    mat4 Result = {0};

    Result = AddMat4(Left, Right);
    return (Result);
}

INLINE quaternion
Add(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result = AddQuaternion(Left, Right);
    return(Result);
}

INLINE vec2
Subtract(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = SubtractVec2(Left, Right);
    return (Result);
}

INLINE vec3
Subtract(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = SubtractVec3(Left, Right);
    return (Result);
}

INLINE vec4
Subtract(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = SubtractVec4(Left, Right);
    return (Result);
}

INLINE mat4
Subtract(mat4 Left, mat4 Right)
{
    mat4 Result = {0};

    Result = SubtractMat4(Left, Right);
    return (Result);
}

INLINE quaternion
Subtract(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result = SubtractQuaternion(Left, Right);
    return (Result);
}

INLINE vec2
Multiply(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = MultiplyVec2(Left, Right);
    return (Result);
}

INLINE vec2
Multiply(vec2 Left, float Right)
{
    vec2 Result = {0};

    Result = MultiplyVec2f(Left, Right);
    return (Result);
}

INLINE vec3
Multiply(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = MultiplyVec3(Left, Right);
    return (Result);
}

INLINE vec3
Multiply(vec3 Left, float Right)
{
    vec3 Result = {0};

    Result = MultiplyVec3f(Left, Right);
    return (Result);
}

INLINE vec4
Multiply(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = MultiplyVec4(Left, Right);
    return (Result);
}

INLINE vec4
Multiply(vec4 Left, float Right)
{
    vec4 Result = {0};

    Result = MultiplyVec4f(Left, Right);
    return (Result);
}

INLINE mat4
Multiply(mat4 Left, mat4 Right)
{
    mat4 Result = {0};

    Result = MultiplyMat4(Left, Right);
    return (Result);
}

INLINE mat4
Multiply(mat4 Left, float Right)
{
    mat4 Result = {0};

    Result = MultiplyMat4f(Left, Right);
    return (Result);
}

INLINE vec4
Multiply(mat4 Matrix, vec4 Vector)
{
    vec4 Result = {0};

    Result = MultiplyMat4ByVec4(Matrix, Vector);
    return (Result);
}

INLINE quaternion
Multiply(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result = MultiplyQuaternion(Left, Right);
    return (Result);
}

INLINE quaternion
Multiply(quaternion Left, float Right)
{
    quaternion Result = {0};

    Result = MultiplyQuaternionF(Left, Right);
    return (Result);
}

INLINE quaternion
Multiply(float Left, quaternion Right)
{
    quaternion Result = {0};

    Result = MultiplyQuaternionF(Right, Left);
    return (Result);
}

INLINE vec2
Divide(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = DivideVec2(Left, Right);
    return (Result);
}

INLINE vec2
Divide(vec2 Left, float Right)
{
    vec2 Result = {0};

    Result = DivideVec2f(Left, Right);
    return (Result);
}

INLINE vec3
Divide(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = DivideVec3(Left, Right);
    return (Result);
}

INLINE vec3
Divide(vec3 Left, float Right)
{
    vec3 Result = {0};

    Result = DivideVec3f(Left, Right);
    return (Result);
}

INLINE vec4
Divide(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = DivideVec4(Left, Right);
    return (Result);
}

INLINE vec4
Divide(vec4 Left, float Right)
{
    vec4 Result = {0};

    Result = DivideVec4f(Left, Right);
    return (Result);
}

INLINE mat4
Divide(mat4 Left, float Right)
{
    mat4 Result = {0};

    Result = DivideMat4f(Left, Right);
    return (Result);
}

INLINE quaternion
Divide(quaternion Left, float Right)
{
    quaternion Result = {0};

    Result = DivideQuaternionF(Left, Right);
    return (Result);
}

INLINE bool
Equals(vec2 Left, vec2 Right)
{
    bool Result = 0;

    Result = EqualsVec2(Left, Right);
    return (Result);
}

INLINE bool
Equals(vec3 Left, vec3 Right)
{
    bool Result = 0;

    Result = EqualsVec3(Left, Right);
    return (Result);
}

INLINE bool
Equals(vec4 Left, vec4 Right)
{
    bool Result = 0;

    Result = EqualsVec4(Left, Right);
    return (Result);
}

INLINE vec2
operator+(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = Add(Left, Right);
    return (Result);
}

INLINE vec3
operator+(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = Add(Left, Right);
    return (Result);
}

INLINE vec4
operator+(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = Add(Left, Right);
    return (Result);
}

INLINE mat4
operator+(mat4 Left, mat4 Right)
{
    mat4 Result = {0};

    Result = Add(Left, Right);
    return (Result);
}

INLINE quaternion
operator+(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result = Add(Left, Right);
    return (Result);
}

INLINE vec2
operator-(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = Subtract(Left, Right);
    return (Result);
}

INLINE vec3
operator-(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = Subtract(Left, Right);
    return (Result);
}

INLINE vec4
operator-(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = Subtract(Left, Right);
    return (Result);
}

INLINE mat4
operator-(mat4 Left, mat4 Right)
{
    mat4 Result = {0};

    Result = Subtract(Left, Right);
    return (Result);
}

INLINE quaternion
operator-(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result = Subtract(Left, Right);
    return (Result);
}

INLINE vec2
operator*(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE vec3
operator*(vec3 Left, vec3 Right)
{
    vec3 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE vec4
operator*(vec4 Left, vec4 Right)
{
    vec4 Result = Multiply(Left, Right);

    return (Result);
}

INLINE vec2
operator*(vec2 Left, float Right)
{
    vec2 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE vec3
operator*(vec3 Left, float Right)
{
    vec3 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE vec4
operator*(vec4 Left, float Right)
{
    vec4 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE mat4
operator*(mat4 Left, float Right)
{
    mat4 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE vec2
operator*(float Left, vec2 Right)
{
    vec2 Result = {0};

    Result = Multiply(Right, Left);
    return (Result);
}

INLINE vec3
operator*(float Left, vec3 Right)
{
    vec3 Result = {0};

    Result = Multiply(Right, Left);
    return (Result);
}

INLINE vec4
operator*(float Left, vec4 Right)
{
    vec4 Result = {0};

    Result = Multiply(Right, Left);
    return (Result);
}

INLINE mat4
operator*(float Left, mat4 Right)
{
    mat4 Result = {0};

    Result = Multiply(Right, Left);
    return (Result);
}

INLINE mat4
operator*(mat4 Left, mat4 Right)
{
    mat4 Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE vec4
operator*(mat4 Matrix, vec4 Vector)
{
    vec4 Result = {0};

    Result = Multiply(Matrix, Vector);
    return (Result);
}

INLINE quaternion
operator*(quaternion Left, quaternion Right)
{
    quaternion Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE quaternion
operator*(quaternion Left, float Right)
{
    quaternion Result = {0};

    Result = Multiply(Left, Right);
    return (Result);
}

INLINE quaternion
operator*(float Left, quaternion Right)
{
    quaternion Result = {0};

    Result = Multiply(Right, Left);
    return (Result);
}

INLINE vec2
operator/(vec2 Left, vec2 Right)
{
    vec2 Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE vec3
operator/(vec3 Left, vec3 Right)
{
    vec3 Result = {0};
    
    Result = Divide(Left, Right);

    return (Result);
}

INLINE vec4
operator/(vec4 Left, vec4 Right)
{
    vec4 Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE vec2
operator/(vec2 Left, float Right)
{
    vec2 Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE vec3
operator/(vec3 Left, float Right)
{
    vec3 Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE vec4
operator/(vec4 Left, float Right)
{
    vec4 Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE mat4
operator/(mat4 Left, float Right)
{
    mat4 Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE quaternion
operator/(quaternion Left, float Right)
{
    quaternion Result = {0};

    Result = Divide(Left, Right);
    return (Result);
}

INLINE vec2 &
operator+=(vec2 &Left, vec2 Right)
{    
    return (Left = Left + Right);
}

INLINE vec3 &
operator+=(vec3 &Left, vec3 Right)
{    
    return (Left = Left + Right);
}

INLINE vec4 &
operator+=(vec4 &Left, vec4 Right)
{    
    return (Left = Left + Right);
}

INLINE mat4 &
operator+=(mat4 &Left, mat4 Right)
{
    return (Left = Left + Right);
}

INLINE quaternion &
operator+=(quaternion &Left, quaternion Right)
{
    return (Left = Left + Right);
}

INLINE vec2 &
operator-=(vec2 &Left, vec2 Right)
{    
    return (Left = Left - Right);
}

INLINE vec3 &
operator-=(vec3 &Left, vec3 Right)
{    
    return (Left = Left - Right);
}

INLINE vec4 &
operator-=(vec4 &Left, vec4 Right)
{    
    return (Left = Left - Right);
}

INLINE mat4 &
operator-=(mat4 &Left, mat4 Right)
{
    return (Left = Left - Right);
}

INLINE quaternion &
operator-=(quaternion &Left, quaternion Right)
{
    return (Left = Left - Right);
}

INLINE vec2 &
operator/=(vec2 &Left, vec2 Right)
{    
    return (Left = Left / Right);
}

INLINE vec3 &
operator/=(vec3 &Left, vec3 Right)
{    
    return (Left = Left / Right);
}

INLINE vec4 &
operator/=(vec4 &Left, vec4 Right)
{    
    return (Left = Left / Right);
}

INLINE vec2 &
operator/=(vec2 &Left, float Right)
{
    return (Left = Left / Right);
}

INLINE vec3 &
operator/=(vec3 &Left, float Right)
{
    return (Left = Left / Right);
}

INLINE vec4 &
operator/=(vec4 &Left, float Right)
{
    return (Left = Left / Right);
}

INLINE mat4 &
operator/=(mat4 &Left, float Right)
{
    return (Left = Left / Right);
}

INLINE quaternion &
operator/=(quaternion &Left, float Right)
{
    return (Left = Left / Right);
}

INLINE vec2 &
operator*=(vec2 &Left, vec2 Right)
{    
    return (Left = Left * Right);
}

INLINE vec3 &
operator*=(vec3 &Left, vec3 Right)
{    
    return (Left = Left * Right);
}

INLINE vec4 &
operator*=(vec4 &Left, vec4 Right)
{    
    return (Left = Left * Right);
}

INLINE vec2 &
operator*=(vec2 &Left, float Right)
{
    return (Left = Left * Right);
}

INLINE vec3 &
operator*=(vec3 &Left, float Right)
{
    return (Left = Left * Right);
}

INLINE vec4 &
operator*=(vec4 &Left, float Right)
{
    return (Left = Left * Right);
}

INLINE mat4 &
operator*=(mat4 &Left, float Right)
{
    return (Left = Left * Right);
}

INLINE quaternion &
operator*=(quaternion &Left, float Right)
{
    return (Left = Left * Right);
}

INLINE bool
operator==(vec2 Left, vec2 Right)
{
    return EqualsVec2(Left, Right);    
}

INLINE bool
operator==(vec3 Left, vec3 Right)
{
    return EqualsVec3(Left, Right);    
}

INLINE bool
operator==(vec4 Left, vec4 Right)
{
    return EqualsVec4(Left, Right);    
}


INLINE bool 
operator!=(vec2 Left, vec2 Right)
{
    return !EqualsVec2(Left, Right);    
}

INLINE bool 
operator!=(vec3 Left, vec3 Right)
{
    return !EqualsVec3(Left, Right);    
}

INLINE bool 
operator!=(vec4 Left, vec4 Right)
{
    return !EqualsVec4(Left, Right);    
}

#endif /* MATH_CPP_MODE */

#endif /* MATH_IMPLEMENTATION */
