/* knot_math.h : May 21st 2020 7:30 pm */

#if !defined(KNOT_MATH_H)

/**
Refactored for naming and integer vector types. Largely representative of Original "Handmade Math".
*/

/**
While license is public domain "This software is in the public domain. Where that dedication is not recognized, you are granted a perpetual, irrevocable license to copy, distribute, and modify this file as you see fit"

Credits:

Origin: HandmadeMath.h v1.6.0
  This is a single header file with a bunch of useful functions for game and
  graphics math operations.

Origin Written by Zakary Strange (zak@strangedev.net && @strangezak)
  
  Origin Functionality:
   Matt Mascarenhas (@miblo_)
   Aleph
   FieryDrake (@fierydrake)
   Gingerbill (@TheGingerBill)
   Ben Visness (@bvisness)
   Trs32on Bullard (@Peliex_Dev)
   
  Origin Fixes:
   Jeroen van Rijn (@J_vanRijn)
   Kiljacken (@Kiljacken)
   Insofaras (@insofaras)
   Daniel Gibson (@DanielGibson)
     
Use:

#define _MATH_IMPLEMENTATION
     #include "knot_math.h"
  
  To disable SSE intrinsics, you MUST
#define _MATH_NO_SSE
*/

/* let's figure out if SSE is really available (unless disabled anyway)
   (it isn't on non-x86/x86_64 platforms or even x86 without explicit SSE support)
   => only use "#ifdef _MATH__USE_SSE" to check for SSE support below this block! */
#ifndef _MATH_NO_SSE

# ifdef _MSC_VER
/* MSVC supports SSE in amd64 mode or _M_IX86_FP >= 1 (2 means SSE2) */
#  if defined(_M_AMD64) || ( defined(_M_IX86_FP) && _M_IX86_FP >= 1 )
#   define _MATH__USE_SSE 1
#  endif
# else /* not MSVC, probably GCC, clang, icc or something that doesn't support SSE anyway */
#  ifdef __SSE__ /* they #define __SSE__ if it's supported */
#   define _MATH__USE_SSE 1
#  endif /*  __SSE__ */
# endif /* not _MSC_VER */

#endif /* #ifndef _MATH_NO_SSE */

#ifdef _MATH__USE_SSE
#include <xmmintrin.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable:4201)
#endif

#ifdef __clang__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-anonymous-struct"
#endif

#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif
	
#define MATH_INLINE static inline
#define EXTERN extern
	
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
	
	typedef union v2
	{
		struct
		{
            r32 X, Y;
        };
        
		struct
		{
			r32 U, V;
		};
		
		struct
		{
			r32 Left, Right;
		};
		
		struct
		{
			r32 Width, Height;
        };
        
        struct
        {
            r32 Min, Max;
        };
        
		struct
		{
			r32 R, G;
		};
		
		r32 Components[2];
		
#ifdef __cplusplus
		inline r32 &operator[](s32 Index)
		{
			return Components[Index];
		}
#endif
	} v2;
	
	typedef union v2i
	{
		struct
		{
            s32 X, Y;
        };
        
		struct
		{
			s32 U, V;
		};
        
		struct
		{
			s32 Left, Right;
		};
		
		struct
		{
			s32 Width, Height;
        };
        
        struct
        {
            s32 Min, Max;
        };
        
		struct
		{
			s32 R, G;
		};
		
		s32 Components[2];
		
#ifdef __cplusplus
		inline s32 &operator[](s32 Index)
		{
			return Components[Index];
		}
#endif
	} v2i;
	
	typedef union v3
	{
		struct
		{
            r32 X, Y, Z;
		};
        
		struct
		{
			r32 U, V, W;
		};
		
		struct
		{
			r32 R, G, B;
        };
        
		struct
		{
			r32 Yaw, Pitch, Roll;
		};
		
		struct
		{
			v2 XY;
			r32 Ignored0_;
		};
		
		struct
		{
			r32 Ignored1_;
			v2 YZ;
		};
		
		struct
		{
			v2 UV;
			r32 Ignored2_;
		};
		
		struct
		{
			r32 Ignored3_;
			v2 VW;
		};
		
		r32 Components[3];
		
#ifdef __cplusplus
		inline r32 &operator[](s32 Index)
		{
			return Components[Index];
		}
#endif
	} v3;
	
	typedef union v3i
	{
		struct
		{
            s32 X, Y, Z;
		};
        
		struct
		{
			s32 U, V, W;
		};
		
		struct
		{
			s32 R, G, B;
        };
        
		struct
		{
			s32 Yaw, Pitch, Roll;
		};
		
		struct
		{
			v2 XY;
			s32 Ignored0_;
		};
		
		struct
		{
			s32 Ignored1_;
			v2 YZ;
		};
		
		struct
		{
			v2 UV;
			s32 Ignored2_;
		};
		
		struct
		{
			s32 Ignored3_;
			v2 VW;
		};
		
		s32 Components[3];
		
#ifdef __cplusplus
		inline s32 &operator[](s32 Index)
		{
			return Components[Index];
		}
#endif
	} v3i;
	
	typedef union v4
	{
		struct
		{
			union
			{
				v3 XYZ;
				struct
				{
                    r32 X, Y, Z;
                };
                
                struct
                {
                    r32 x, y, z;
                };
			};
			
            r32 W;
            r32 w;
		};
		struct
		{
			union
			{
				v3 RGB;
				struct
				{
					r32 R, G, B;
				};
			};
			
			r32 A;
		};
		
		struct
		{
			v2 XY;
			r32 Ignored0_;
			r32 Ignored1_;
		};
		
		struct
		{
			r32 Ignored2_;
			v2 YZ;
			r32 Ignored3_;
		};
		
		struct
		{
			r32 Ignored4_;
			r32 Ignored5_;
			v2 ZW;
		};
		
		r32 Components[4];
		
#ifdef _MATH__USE_SSE
		__m128 InternalComponentsSSE;
#endif
		
#ifdef __cplusplus
		inline r32 &operator[](s32 Index)
		{
			return Components[Index];
		}
#endif
	} v4;
	
	typedef union v4i
	{
		struct
		{
			union
			{
				v3i XYZ;
				struct
				{
                    s32 X, Y, Z;
                };
                
                struct
                {
                    s32 x, y, z;
                };
			};
			
            s32 W;
            s32 w;
		};
		struct
		{
			union
			{
				v3i RGB;
				struct
				{
					s32 R, G, B;
				};
			};
			
			s32 A;
		};
		
		struct
		{
			v2i XY;
			s32 Ignored0_;
			s32 Ignored1_;
		};
		
		struct
		{
			s32 Ignored2_;
			v2i YZ;
			s32 Ignored3_;
		};
		
		struct
		{
			s32 Ignored4_;
			s32 Ignored5_;
			v2i ZW;
		};
		
		s32 Components[4];
		
#ifdef _MATH__USE_SSE
		__m128 InternalComponentsSSE;
#endif
		
#ifdef __cplusplus
		inline s32 &operator[](s32 Index)
		{
			return Components[Index];
		}
#endif
	} v4i;
	
	typedef union m4
	{
		r32 Components[4][4];
        
#ifdef _MATH__USE_SSE
		__m128 Rows[4];
#endif
		
#ifdef __cplusplus
		inline v4 operator[](const s32 Index)
		{
			r32* col = Components[Index];
			
			v4 result;
			result.Components[0] = col[0];
			result.Components[1] = col[1];
			result.Components[2] = col[2];
			result.Components[3] = col[3];
			
			return result;
		}
#endif
	} m4;
	
	typedef union quat
	{
		struct
		{
			union
			{
				v3 XYZ;
				struct
				{
					r32 X, Y, Z;
				};
				struct
				{
					r32 Yaw, Pitch, Roll;
				};
			};
			r32 W;
		};
		
		r32 Components[4];
	} quat;
    
	/*
	 * Floating-pos32 math functions
		 */
    
    MATH_INLINE r32 Radians(r32 Degrees)
    {
        return (Degrees * PI32) / 180.f;
    }
	
	MATH_INLINE r32 SinF(r32 Radians)
	{
		r32 Result = SINF(Radians);
		
		return (Result);
	}
	
	MATH_INLINE r32 CosF(r32 Radians)
	{
		r32 Result = COSF(Radians);
		
		return (Result);
	}
	
	MATH_INLINE r32 TanF(r32 Radians)
	{
		r32 Result = TANF(Radians);
		
		return (Result);
	}
	
	MATH_INLINE r32 ACosF(r32 Radians)
	{
		r32 Result = ACOSF(Radians);
		
		return (Result);
	}
	
	MATH_INLINE r32 ATanF(r32 Radians)
	{
		r32 Result = ATANF(Radians);
		
		return (Result);
	}
	
	MATH_INLINE r32 ATan2F(r32 Left, r32 Right)
	{
		r32 Result = ATAN2F(Left, Right);
		
		return (Result);
	}
	
	MATH_INLINE r32 ExpF(r32 Float)
	{
		r32 Result = EXPF(Float);
		
		return (Result);
	}
	
	MATH_INLINE r32 LogF(r32 Float)
	{
		r32 Result = LOGF(Float);
		
		return (Result);
	}
	
	MATH_INLINE r32 SquareRootF(r32 Float)
	{
		r32 Result;
		
#ifdef _MATH__USE_SSE
		__m128 In = _mm_set_ss(Float);
		__m128 Out = _mm_sqrt_ss(In);
		Result = _mm_cvtss_f32(Out);
#else
		Result = SQRTF(Float);
#endif
		
		return(Result);
	}
	
	MATH_INLINE r32 RSquareRootF(r32 Float)
	{
		r32 Result;
		
#ifdef _MATH__USE_SSE
		__m128 In = _mm_set_ss(Float);
		__m128 Out = _mm_rsqrt_ss(In);
		Result = _mm_cvtss_f32(Out);
#else
		Result = 1.0f/SquareRootF(Float);
#endif
		
		return(Result);
	}
	
	EXTERN r32 Power(r32 Base, s32 Exponent);
	
	MATH_INLINE r32 PowerF(r32 Base, r32 Exponent)
	{
		r32 Result = EXPF(Exponent * LOGF(Base));
		
		return (Result);
	}
	
	
	/*
	 * Utility functions
	 */
	MATH_INLINE r32 ToRadians(r32 Degrees)
	{
		r32 Result = Degrees * (PI32 / 180.0f);
		
		return (Result);
	}
	
	MATH_INLINE r32 Lerp(r32 A, r32 Time, r32 B)
	{
		r32 Result = (1.0f - Time) * A + Time * B;
		
		return (Result);
	}
	
	MATH_INLINE r32 Clamp(r32 Min, r32 Value, r32 Max)
	{
		r32 Result = Value;
		
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
	
	MATH_INLINE r32 Closestf(const r32 Right, const r32 Left, const r32 Target)
	{
		return (Target - Right >= Left - Target) ? Left : Right;
	}
	
	MATH_INLINE s32 Closesti(const u32 Right, const u32 Left, const u32 Target)
	{
		return (Target - Right >= Left - Target) ? Left : Right;
	}
	
	/*
	 * Vector initialization
	 */
	
	MATH_INLINE v2 V2(r32 X, r32 Y)
	{
		v2 Result;
		
		Result.X = X;
		Result.Y = Y;
		
		return (Result);
	}
	
	MATH_INLINE v2i V2i(s32 X, s32 Y)
	{
		v2i Result = {X, Y};
		return Result;
	}
	
	MATH_INLINE v3 V3(r32 X, r32 Y, r32 Z)
	{
		v3 Result;
		
		Result.X = X;
		Result.Y = Y;
		Result.Z = Z;
		
		return (Result);
	}
	
	MATH_INLINE v3i V3i(s32 X, s32 Y, s32 Z)
	{
		v3i Result = {X, Y, Z};
		return Result;
	}
	
	MATH_INLINE v4 V4(r32 X, r32 Y, r32 Z, r32 W)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_setr_ps(X, Y, Z, W);
#else
		Result.X = X;
		Result.Y = Y;
		Result.Z = Z;
		Result.W = W;
#endif
		
		return (Result);
	}
    
#define BLACK V4(0.f, 0.f, 0.f, 1.f)
#define WHITE V4(1.f, 1.f, 1.f, 1.f)
#define RED V4(1.f, 0.f, 0.f, 1.f)
#define GREEN V4(0.f, 1.f, 0.f, 1.f)
#define BLUE V4(0.f, 0.f, 1.f, 1.f)
    
	MATH_INLINE v4i V4i(s32 X, s32 Y, s32 Z, s32 W)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_setr_ps((r32)X, (r32)Y, (r32)Z, (r32)W);
#else
		Result = {X, Y, Z, W};
#endif
		return (Result);
	}
	
	MATH_INLINE v4 V4v(v3 Vector, r32 W)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_setr_ps(Vector.X, Vector.Y, Vector.Z, W);
#else
		Result.XYZ = Vector;
		Result.W = W;
#endif
		
		return (Result);
	}
    
	/*
	 * Binary vector operations
	 */
	
	MATH_INLINE v2 AddV2(v2 Left, v2 Right)
	{
		v2 Result;
		
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v2i AddV2i(v2i Left, v2i Right)
	{
		v2i Result;
		
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v3 AddV3(v3 Left, v3 Right)
	{
		v3 Result;
		
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		Result.Z = Left.Z + Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v3i AddV3i(v3i Left, v3i Right)
	{
		v3i Result;
		
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		Result.Z = Left.Z + Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v4 AddV4(v4 Left, v4 Right)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_add_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		Result.Z = Left.Z + Right.Z;
		Result.W = Left.W + Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4i AddV4i(v4i Left, v4i Right)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_add_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		Result.Z = Left.Z + Right.Z;
		Result.W = Left.W + Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v2 SubtractV2(v2 Left, v2 Right)
	{
		v2 Result;
		
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v2i SubtractV2i(v2i Left, v2i Right)
	{
		v2i Result;
		
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v3 SubtractV3(v3 Left, v3 Right)
	{
		v3 Result;
		
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		Result.Z = Left.Z - Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v3i SubtractV3i(v3i Left, v3i Right)
	{
		v3i Result;
		
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		Result.Z = Left.Z - Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v4 SubtractV4(v4 Left, v4 Right)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_sub_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		Result.Z = Left.Z - Right.Z;
		Result.W = Left.W - Right.W;
#endif
		
		return (Result);
	}
	
	
	MATH_INLINE v4i SubtractV4i(v4i Left, v4i Right)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_sub_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		Result.Z = Left.Z - Right.Z;
		Result.W = Left.W - Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v2 MultiplyV2(v2 Left, v2 Right)
	{
		v2 Result;
		
		Result.X = Left.X * Right.X;
		Result.Y = Left.Y * Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v2i MultiplyV2i(v2i Left, v2i Right)
	{
		v2i Result;
		
		Result.X = Left.X * Right.X;
		Result.Y = Left.Y * Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v2 MultiplyV2f(v2 Left, r32 Right)
	{
		v2 Result;
		
		Result.X = Left.X * Right;
		Result.Y = Left.Y * Right;
		
		return (Result);
	}
	
	MATH_INLINE v2i MultiplyV2ii(v2i Left, s32 Right)
	{
		v2i Result;
		
		Result.X = Left.X * Right;
		Result.Y = Left.Y * Right;
		
		return (Result);
	}
	
	MATH_INLINE v3 MultiplyV3(v3 Left, v3 Right)
	{
		v3 Result;
		
		Result.X = Left.X * Right.X;
		Result.Y = Left.Y * Right.Y;
		Result.Z = Left.Z * Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v3i MultiplyV3i(v3i Left, v3i Right)
	{
		v3i Result;
		
		Result.X = Left.X * Right.X;
		Result.Y = Left.Y * Right.Y;
		Result.Z = Left.Z * Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v3 MultiplyV3f(v3 Left, r32 Right)
	{
		v3 Result;
		
		Result.X = Left.X * Right;
		Result.Y = Left.Y * Right;
		Result.Z = Left.Z * Right;
		
		return (Result);
	}
	
	MATH_INLINE v3i MultiplyV3ii(v3i Left, s32 Right)
	{
		v3i Result;
		
		Result.X = Left.X * Right;
		Result.Y = Left.Y * Right;
		Result.Z = Left.Z * Right;
		
		return (Result);
	}
	
	MATH_INLINE v4 MultiplyV4(v4 Left, v4 Right)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_mul_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X * Right.X;
		Result.Y = Left.Y * Right.Y;
		Result.Z = Left.Z * Right.Z;
		Result.W = Left.W * Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4i MultiplyV4i(v4i Left, v4i Right)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_mul_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X * Right.X;
		Result.Y = Left.Y * Right.Y;
		Result.Z = Left.Z * Right.Z;
		Result.W = Left.W * Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4 MultiplyV4f(v4 Left, r32 Right)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		__m128 Scalar = _mm_set1_ps(Right);
		Result.InternalComponentsSSE = _mm_mul_ps(Left.InternalComponentsSSE, Scalar);
#else
		Result.X = Left.X * Right;
		Result.Y = Left.Y * Right;
		Result.Z = Left.Z * Right;
		Result.W = Left.W * Right;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4i MultiplyV4ii(v4i Left, s32 Right)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		__m128 Scalar = _mm_set1_ps((r32)Right);
		Result.InternalComponentsSSE = _mm_mul_ps(Left.InternalComponentsSSE, Scalar);
#else
		Result.X = Left.X * Right;
		Result.Y = Left.Y * Right;
		Result.Z = Left.Z * Right;
		Result.W = Left.W * Right;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v2 DivideV2(v2 Left, v2 Right)
	{
		v2 Result;
		
		Result.X = Left.X / Right.X;
		Result.Y = Left.Y / Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v2i DivideV2i(v2i Left, v2i Right)
	{
		v2i Result;
		
		Result.X = Left.X / Right.X;
		Result.Y = Left.Y / Right.Y;
		
		return (Result);
	}
	
	MATH_INLINE v2 DivideV2f(v2 Left, r32 Right)
	{
		v2 Result;
		
		Result.X = Left.X / Right;
		Result.Y = Left.Y / Right;
		
		return (Result);
	}
	
	MATH_INLINE v2i DivideV2ii(v2i Left, s32 Right)
	{
		v2i Result;
		
		Result.X = Left.X / Right;
		Result.Y = Left.Y / Right;
		
		return (Result);
	}
	
	MATH_INLINE v3 DivideV3(v3 Left, v3 Right)
	{
		v3 Result;
		
		Result.X = Left.X / Right.X;
		Result.Y = Left.Y / Right.Y;
		Result.Z = Left.Z / Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v3 DivideV3f(v3 Left, r32 Right)
	{
		v3 Result;
		
		Result.X = Left.X / Right;
		Result.Y = Left.Y / Right;
		Result.Z = Left.Z / Right;
		
		return (Result);
	}
	
	MATH_INLINE v3i DivideV3i(v3i Left, v3i Right)
	{
		v3i Result;
		
		Result.X = Left.X / Right.X;
		Result.Y = Left.Y / Right.Y;
		Result.Z = Left.Z / Right.Z;
		
		return (Result);
	}
	
	MATH_INLINE v3i DivideV3ii(v3i Left, s32 Right)
	{
		v3i Result;
		
		Result.X = Left.X / Right;
		Result.Y = Left.Y / Right;
		Result.Z = Left.Z / Right;
		
		return (Result);
	}
	
	MATH_INLINE v4 DivideV4(v4 Left, v4 Right)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_div_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X / Right.X;
		Result.Y = Left.Y / Right.Y;
		Result.Z = Left.Z / Right.Z;
		Result.W = Left.W / Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4 DivideV4f(v4 Left, r32 Right)
	{
		v4 Result;
		
#ifdef _MATH__USE_SSE
		__m128 Scalar = _mm_set1_ps(Right);
		Result.InternalComponentsSSE = _mm_div_ps(Left.InternalComponentsSSE, Scalar);
#else
		Result.X = Left.X / Right;
		Result.Y = Left.Y / Right;
		Result.Z = Left.Z / Right;
		Result.W = Left.W / Right;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4i DivideV4i(v4i Left, v4i Right)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		Result.InternalComponentsSSE = _mm_div_ps(Left.InternalComponentsSSE, Right.InternalComponentsSSE);
#else
		Result.X = Left.X / Right.X;
		Result.Y = Left.Y / Right.Y;
		Result.Z = Left.Z / Right.Z;
		Result.W = Left.W / Right.W;
#endif
		
		return (Result);
	}
	
	MATH_INLINE v4i DivideV4ii(v4i Left, s32 Right)
	{
		v4i Result;
		
#ifdef _MATH__USE_SSE
		__m128 Scalar = _mm_set1_ps((r32)Right);
		Result.InternalComponentsSSE = _mm_div_ps(Left.InternalComponentsSSE, Scalar);
#else
		Result.X = Left.X / Right;
		Result.Y = Left.Y / Right;
		Result.Z = Left.Z / Right;
		Result.W = Left.W / Right;
#endif
		
		return (Result);
	}
	
	MATH_INLINE u8 EqualsV2(v2 Left, v2 Right)
	{
		u8 Result = (Left.X == Right.X && Left.Y == Right.Y);
		
		return (Result);
	}
	
	MATH_INLINE u8 EqualsV2i(v2i Left, v2i Right)
	{
		u8 Result = (Left.X == Right.X && Left.Y == Right.Y);
		return (Result);
	}
	
	MATH_INLINE u8 EqualsV3(v3 Left, v3 Right)
	{
		u8 Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z);
		
		return (Result);
	}
	
	MATH_INLINE u8 EqualsV3i(v3i Left, v3i Right)
	{
		u8 Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z);
		return (Result);
	}
	
	MATH_INLINE u8 EqualsV4(v4 Left, v4 Right)
	{
		u8 Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W);
		
		return (Result);
	}
	
	MATH_INLINE u8 EqualsV4i(v4i Left, v4i Right)
	{
		u8 Result = (Left.X == Right.X && Left.Y == Right.Y && Left.Z == Right.Z && Left.W == Right.W);
		return (Result);
	}
	
	MATH_INLINE r32 DotV2(v2 VecOne, v2 VecTwo)
	{
		r32 Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y);
		
		return (Result);
	}
	
	MATH_INLINE r32 DotV3(v3 VecOne, v3 VecTwo)
	{
		r32 Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z);
		
		return (Result);
	}
	
	MATH_INLINE r32 DotV4(v4 VecOne, v4 VecTwo)
	{
		r32 Result;
		
		// NOTE(zak): IN the future if we wanna check what version SSE is support
		// we can use _mm_dp_ps (4.3) but for now we will use the old way.
		// Or a r = _mm_mul_ps(v1, v2), r = _mm_hadd_ps(r, r), r = _mm_hadd_ps(r, r) for SSE3
#ifdef _MATH__USE_SSE
		__m128 SSEResultOne = _mm_mul_ps(VecOne.InternalComponentsSSE, VecTwo.InternalComponentsSSE);
		__m128 SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(2, 3, 0, 1));
		SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
		SSEResultTwo = _mm_shuffle_ps(SSEResultOne, SSEResultOne, _MM_SHUFFLE(0, 1, 2, 3));
		SSEResultOne = _mm_add_ps(SSEResultOne, SSEResultTwo);
		_mm_store_ss(&Result, SSEResultOne);
#else
		Result = (VecOne.X * VecTwo.X) + (VecOne.Y * VecTwo.Y) + (VecOne.Z * VecTwo.Z) + (VecOne.W * VecTwo.W);
#endif
		
		return (Result);
	}
	
	MATH_INLINE v3 Cross(v3 VecOne, v3 VecTwo)
	{
		v3 Result;
		
		Result.X = (VecOne.Y * VecTwo.Z) - (VecOne.Z * VecTwo.Y);
		Result.Y = (VecOne.Z * VecTwo.X) - (VecOne.X * VecTwo.Z);
		Result.Z = (VecOne.X * VecTwo.Y) - (VecOne.Y * VecTwo.X);
		
		return (Result);
    }
    
    MATH_INLINE v2 FastNormalizeV2(v2 A)
	{
		return MultiplyV2f(A, RSquareRootF(DotV2(A, A)));
	}
	
	MATH_INLINE v3 FastNormalizeV3(v3 A)
	{
		return MultiplyV3f(A, RSquareRootF(DotV3(A, A)));
	}
	
	MATH_INLINE v4 FastNormalizeV4(v4 A)
	{
		return MultiplyV4f(A, RSquareRootF(DotV4(A, A)));
	}
	
	/*
	 * Unary vector operations
	 */
	
	MATH_INLINE r32 LengthSquaredV2(v2 A)
	{
		r32 Result = DotV2(A, A);
		
		return(Result);
	}
	
	MATH_INLINE r32 LengthSquaredV3(v3 A)
	{
		r32 Result = DotV3(A, A);
		
		return (Result);
	}
	
	MATH_INLINE r32 LengthSquaredV4(v4 A)
	{
		r32 Result = DotV4(A, A);
		
		return (Result);
	}
	
	MATH_INLINE r32 LengthV2(v2 A)
	{
		r32 Result = SquareRootF(LengthSquaredV2(A));
		
		return (Result);
	}
	
	MATH_INLINE r32 LengthV3(v3 A)
	{
		r32 Result = SquareRootF(LengthSquaredV3(A));
		
		return (Result);
	}
	
	MATH_INLINE r32 LengthV4(v4 A)
	{
		r32 Result = SquareRootF(LengthSquaredV4(A));
		
		return(Result);
	}
	
	MATH_INLINE v2 NormalizeV2(v2 A)
	{
		v2 Result = {0};
		
		r32 VectorLength = LengthV2(A);
		
		/* NOTE(kiljacken): We need a zero check to not divide-by-zero */
		if (VectorLength != 0.0f)
		{
			Result.X = A.X * (1.0f / VectorLength);
			Result.Y = A.Y * (1.0f / VectorLength);
		}
		
		return (Result);
	}
	
	MATH_INLINE v3 NormalizeV3(v3 A)
	{
		v3 Result = {0};
		
		r32 VectorLength = LengthV3(A);
		
		/* NOTE(kiljacken): We need a zero check to not divide-by-zero */
		if (VectorLength != 0.0f)
		{
			Result.X = A.X * (1.0f / VectorLength);
			Result.Y = A.Y * (1.0f / VectorLength);
			Result.Z = A.Z * (1.0f / VectorLength);
		}
		
		return (Result);
	}
	
	MATH_INLINE v4 NormalizeV4(v4 A)
	{
		v4 Result = {0};
		
		r32 VectorLength = LengthV4(A);
		
		/* NOTE(kiljacken): We need a zero check to not divide-by-zero */
		if (VectorLength != 0.0f)
		{
			r32 Multiplier = 1.0f / VectorLength;
			
#ifdef _MATH__USE_SSE
			__m128 SSEMultiplier = _mm_set1_ps(Multiplier);
			Result.InternalComponentsSSE = _mm_mul_ps(A.InternalComponentsSSE, SSEMultiplier);
#else
			Result.X = A.X * Multiplier;
			Result.Y = A.Y * Multiplier;
			Result.Z = A.Z * Multiplier;
			Result.W = A.W * Multiplier;
#endif
		}
		
		return (Result);
	}
	
	
	/*
	 * SSE stuff
	 */
	
#ifdef _MATH__USE_SSE
	MATH_INLINE __m128 LinearCombineSSE(__m128 Left, m4 Right)
	{
		__m128 Result;
		Result = _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x00), Right.Rows[0]);
		Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0x55), Right.Rows[1]));
		Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xaa), Right.Rows[2]));
		Result = _mm_add_ps(Result, _mm_mul_ps(_mm_shuffle_ps(Left, Left, 0xff), Right.Rows[3]));
		
		return (Result);
	}
#endif
	
	
	/*
	 * Matrix functions
	 */
	
	MATH_INLINE m4 M4(void)
	{
		m4 Result = {0};
		
		return (Result);
	}
	
	MATH_INLINE m4 M4d(r32 Diagonal)
	{
		m4 Result = M4();
		
		Result.Components[0][0] = Diagonal;
		Result.Components[1][1] = Diagonal;
		Result.Components[2][2] = Diagonal;
		Result.Components[3][3] = Diagonal;
		
		return (Result);
	}
	
#ifdef _MATH__USE_SSE
	MATH_INLINE m4 Transpose(m4 Matrix)
	{
		m4 Result = Matrix;
		
		_MM_TRANSPOSE4_PS(Result.Rows[0], Result.Rows[1], Result.Rows[2], Result.Rows[3]);
		
		return (Result);
	}
#else
	EXTERN m4 Transpose(m4 Matrix);
#endif
	
#ifdef _MATH__USE_SSE
	MATH_INLINE m4 AddM4(m4 Left, m4 Right)
	{
		m4 Result;
		
		Result.Rows[0] = _mm_add_ps(Left.Rows[0], Right.Rows[0]);
		Result.Rows[1] = _mm_add_ps(Left.Rows[1], Right.Rows[1]);
		Result.Rows[2] = _mm_add_ps(Left.Rows[2], Right.Rows[2]);
		Result.Rows[3] = _mm_add_ps(Left.Rows[3], Right.Rows[3]);
		
		return (Result);
	}
#else
	EXTERN m4 AddM4(m4 Left, m4 Right);
#endif
	
#ifdef _MATH__USE_SSE
	MATH_INLINE m4 SubtractM4(m4 Left, m4 Right)
	{
		m4 Result;
		
		Result.Rows[0] = _mm_sub_ps(Left.Rows[0], Right.Rows[0]);
		Result.Rows[1] = _mm_sub_ps(Left.Rows[1], Right.Rows[1]);
		Result.Rows[2] = _mm_sub_ps(Left.Rows[2], Right.Rows[2]);
		Result.Rows[3] = _mm_sub_ps(Left.Rows[3], Right.Rows[3]);
		
		return (Result);
	}
#else
	EXTERN m4 SubtractM4(m4 Left, m4 Right);
#endif
	
	EXTERN m4 MultiplyM4(m4 Left, m4 Right);
	
#ifdef _MATH__USE_SSE
	MATH_INLINE m4 MultiplyM4f(m4 Matrix, r32 Scalar)
	{
		m4 Result;
		
		__m128 SSEScalar = _mm_set1_ps(Scalar);
		Result.Rows[0] = _mm_mul_ps(Matrix.Rows[0], SSEScalar);
		Result.Rows[1] = _mm_mul_ps(Matrix.Rows[1], SSEScalar);
		Result.Rows[2] = _mm_mul_ps(Matrix.Rows[2], SSEScalar);
		Result.Rows[3] = _mm_mul_ps(Matrix.Rows[3], SSEScalar);
		
		return (Result);
	}
#else
	EXTERN m4 MultiplyM4f(m4 Matrix, r32 Scalar);
#endif
	
	EXTERN v4 MultiplyM4ByV4(m4 Matrix, v4 Vector);
	
#ifdef _MATH__USE_SSE
	MATH_INLINE m4 DivideM4f(m4 Matrix, r32 Scalar)
	{
		m4 Result;
		
		__m128 SSEScalar = _mm_set1_ps(Scalar);
		Result.Rows[0] = _mm_div_ps(Matrix.Rows[0], SSEScalar);
		Result.Rows[1] = _mm_div_ps(Matrix.Rows[1], SSEScalar);
		Result.Rows[2] = _mm_div_ps(Matrix.Rows[2], SSEScalar);
		Result.Rows[3] = _mm_div_ps(Matrix.Rows[3], SSEScalar);
		
		return (Result);
	}
#else
	EXTERN m4 DivideM4f(m4 Matrix, r32 Scalar);
#endif
    
    MATH_INLINE void M4Inverse(m4& DstMatrix, const m4& SrcMatrix)
    {
        typedef r32 Float4x4[4][4];
        const Float4x4& M = *((const Float4x4*) SrcMatrix.Components);
        Float4x4 Result;
        r32 Det[4];
        Float4x4 Tmp;
        
        Tmp[0][0]	= M[2][2] * M[3][3] - M[2][3] * M[3][2];
        Tmp[0][1]	= M[1][2] * M[3][3] - M[1][3] * M[3][2];
        Tmp[0][2]	= M[1][2] * M[2][3] - M[1][3] * M[2][2];
        
        Tmp[1][0]	= M[2][2] * M[3][3] - M[2][3] * M[3][2];
        Tmp[1][1]	= M[0][2] * M[3][3] - M[0][3] * M[3][2];
        Tmp[1][2]	= M[0][2] * M[2][3] - M[0][3] * M[2][2];
        
        Tmp[2][0]	= M[1][2] * M[3][3] - M[1][3] * M[3][2];
        Tmp[2][1]	= M[0][2] * M[3][3] - M[0][3] * M[3][2];
        Tmp[2][2]	= M[0][2] * M[1][3] - M[0][3] * M[1][2];
        
        Tmp[3][0]	= M[1][2] * M[2][3] - M[1][3] * M[2][2];
        Tmp[3][1]	= M[0][2] * M[2][3] - M[0][3] * M[2][2];
        Tmp[3][2]	= M[0][2] * M[1][3] - M[0][3] * M[1][2];
        
        Det[0]		= M[1][1]*Tmp[0][0] - M[2][1]*Tmp[0][1] + M[3][1]*Tmp[0][2];
        Det[1]		= M[0][1]*Tmp[1][0] - M[2][1]*Tmp[1][1] + M[3][1]*Tmp[1][2];
        Det[2]		= M[0][1]*Tmp[2][0] - M[1][1]*Tmp[2][1] + M[3][1]*Tmp[2][2];
        Det[3]		= M[0][1]*Tmp[3][0] - M[1][1]*Tmp[3][1] + M[2][1]*Tmp[3][2];
        
        r32 Determinant = M[0][0]*Det[0] - M[1][0]*Det[1] + M[2][0]*Det[2] - M[3][0]*Det[3];
        const r32	RDet = 1.0f / Determinant;
        
        Result[0][0] =  RDet * Det[0];
        Result[0][1] = -RDet * Det[1];
        Result[0][2] =  RDet * Det[2];
        Result[0][3] = -RDet * Det[3];
        Result[1][0] = -RDet * (M[1][0]*Tmp[0][0] - M[2][0]*Tmp[0][1] + M[3][0]*Tmp[0][2]);
        Result[1][1] =  RDet * (M[0][0]*Tmp[1][0] - M[2][0]*Tmp[1][1] + M[3][0]*Tmp[1][2]);
        Result[1][2] = -RDet * (M[0][0]*Tmp[2][0] - M[1][0]*Tmp[2][1] + M[3][0]*Tmp[2][2]);
        Result[1][3] =  RDet * (M[0][0]*Tmp[3][0] - M[1][0]*Tmp[3][1] + M[2][0]*Tmp[3][2]);
        Result[2][0] =  RDet * (M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                                M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
                                M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]));
        Result[2][1] = -RDet * (M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
                                M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
                                M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]));
        Result[2][2] =  RDet * (M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
                                M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
                                M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1]));
        Result[2][3] = -RDet * (M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
                                M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
                                M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1]));
        Result[3][0] = -RDet * (M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                                M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
                                M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]));
        Result[3][1] =  RDet * (M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
                                M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
                                M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]));
        Result[3][2] = -RDet * (M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
                                M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
                                M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]));
        Result[3][3] =  RDet * (M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
                                M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
                                M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1]));
        
        memcpy(DstMatrix.Components, &Result, 16*sizeof(r32));
    }
	
	
	/*
	 * Common graphics transformations
	 */
	
	MATH_INLINE m4 Orthographic(r32 Left, r32 Right, r32 Bottom, r32 Top, r32 Near, r32 Far)
	{
		m4 Result = M4();
		
		Result.Components[0][0] = 2.0f / (Right - Left);
		Result.Components[1][1] = 2.0f / (Top - Bottom);
		Result.Components[2][2] = 2.0f / (Near - Far);
		Result.Components[3][3] = 1.0f;
		
		Result.Components[3][0] = (Left + Right) / (Left - Right);
		Result.Components[3][1] = (Bottom + Top) / (Bottom - Top);
		Result.Components[3][2] = (Far + Near) / (Near - Far);
		
		return (Result);
	}
	
	MATH_INLINE m4 Perspective(r32 FOV, r32 AspectRatio, r32 Near, r32 Far)
	{
        m4 Result = M4();
        
#if 0
		
		r32 TanThetaOver2 = TanF(FOV * (PI32 / 360.0f));
		
		Result.Components[0][0] = 1.0f / TanThetaOver2;
		Result.Components[1][1] = AspectRatio / TanThetaOver2;
		Result.Components[2][3] = -1.0f;
		Result.Components[2][2] = (Near + Far) / (Near - Far);
		Result.Components[3][2] = (2.0f * Near * Far) / (Near - Far);
		Result.Components[3][3] = 0.0f;
#else
        // NOTE: Made Perspective use vertical FOV instead of horizontal FOV for consistency with other graphics APIs.
        
        // See https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml
        r32 Cotangent = 1.0f / TanF(FOV * (PI32 / 360.0f));
        
        Result.Components[0][0] = Cotangent / AspectRatio;
        Result.Components[1][1] = Cotangent;
        Result.Components[2][3] = -1.0f;
        Result.Components[2][2] = (Near + Far) / (Near - Far);
        Result.Components[3][2] = (2.0f * Near * Far) / (Near - Far);
        Result.Components[3][3] = 0.0f;
#endif
		return (Result);
	}
	
	MATH_INLINE m4 M4Translate(v3 Translation)
	{
		m4 Result = M4d(1.0f);
		
		Result.Components[3][0] = Translation.X;
		Result.Components[3][1] = Translation.Y;
		Result.Components[3][2] = Translation.Z;
		
		return (Result);
	}
	
	EXTERN m4 M4Rotate(r32 Angle, v3 Axis);
	
	MATH_INLINE m4 M4Scale(v3 Scale)
	{
		m4 Result = M4d(1.0f);
		
		Result.Components[0][0] = Scale.X;
		Result.Components[1][1] = Scale.Y;
		Result.Components[2][2] = Scale.Z;
		
		return (Result);
	}
	
    EXTERN m4 LookAt(v3 Eye, v3 Center, v3 Up);
	
	
	/*
	 * Quat operations
	 */
	
	MATH_INLINE quat Quat(r32 X, r32 Y, r32 Z, r32 W)
	{
		quat Result;
		
		Result.X = X;
		Result.Y = Y;
		Result.Z = Z;
		Result.W = W;
		
		return (Result);
	}
	
	MATH_INLINE quat QuatV4(v4 Vector)
	{
		quat Result;
		
		Result.X = Vector.X;
		Result.Y = Vector.Y;
		Result.Z = Vector.Z;
		Result.W = Vector.W;
		
		return (Result);
	}
	
	MATH_INLINE quat AddQuat(quat Left, quat Right)
	{
		quat Result;
		
		Result.X = Left.X + Right.X;
		Result.Y = Left.Y + Right.Y;
		Result.Z = Left.Z + Right.Z;
		Result.W = Left.W + Right.W;
		
		return (Result);
	}
	
	MATH_INLINE quat SubtractQuat(quat Left, quat Right)
	{
		quat Result;
		
		Result.X = Left.X - Right.X;
		Result.Y = Left.Y - Right.Y;
		Result.Z = Left.Z - Right.Z;
		Result.W = Left.W - Right.W;
		
		return (Result);
	}
	
	MATH_INLINE quat MultiplyQuat(quat Left, quat Right)
	{
		quat Result;
		
		Result.X = (Left.X * Right.W) + (Left.Y * Right.Z) - (Left.Z * Right.Y) + (Left.W * Right.X);
		Result.Y = (-Left.X * Right.Z) + (Left.Y * Right.W) + (Left.Z * Right.X) + (Left.W * Right.Y);
		Result.Z = (Left.X * Right.Y) - (Left.Y * Right.X) + (Left.Z * Right.W) + (Left.W * Right.Z);
		Result.W = (-Left.X * Right.X) - (Left.Y * Right.Y) - (Left.Z * Right.Z) + (Left.W * Right.W);
		
		return (Result);
	}
	
	MATH_INLINE quat MultiplyQuatF(quat Left, r32 Multiplicative)
	{
		quat Result;
		
		Result.X = Left.X * Multiplicative;
		Result.Y = Left.Y * Multiplicative;
		Result.Z = Left.Z * Multiplicative;
		Result.W = Left.W * Multiplicative;
		
		return (Result);
	}
	
	MATH_INLINE quat DivideQuatF(quat Left, r32 Dividend)
	{
		quat Result;
		
		Result.X = Left.X / Dividend;
		Result.Y = Left.Y / Dividend;
		Result.Z = Left.Z / Dividend;
		Result.W = Left.W / Dividend;
		
		return (Result);
	}
	
	EXTERN quat InverseQuat(quat Left);
	
	MATH_INLINE r32 DotQuat(quat Left, quat Right)
	{
		r32 Result = (Left.X * Right.X) + (Left.Y * Right.Y) + (Left.Z * Right.Z) + (Left.W * Right.W);
		
		return (Result);
	}
	
	MATH_INLINE quat NormalizeQuat(quat Left)
	{
		quat Result;
		
		r32 Length = SquareRootF(DotQuat(Left, Left));
		Result = DivideQuatF(Left, Length);
		
		return (Result);
	}
	
	MATH_INLINE quat NLerp(quat Left, r32 Time, quat Right)
	{
		quat Result;
		
		Result.X = Lerp(Left.X, Time, Right.X);
		Result.Y = Lerp(Left.Y, Time, Right.Y);
		Result.Z = Lerp(Left.Z, Time, Right.Z);
		Result.W = Lerp(Left.W, Time, Right.W);
		
		Result = NormalizeQuat(Result);
		
		return (Result);
	}
	
	EXTERN quat Slerp(quat Left, r32 Time, quat Right);
	EXTERN m4 QuatToM4(quat Left);
	EXTERN quat QuatFromAxisAngle(v3 Axis, r32 AngleOfRotation);
	
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

MATH_INLINE r32 Length(v2 A)
{
    r32 Result = LengthV2(A);
    
    return (Result);
}

MATH_INLINE r32 Length(v3 A)
{
    r32 Result = LengthV3(A);
    
    return (Result);
}

MATH_INLINE r32 Length(v4 A)
{
    r32 Result = LengthV4(A);
    
    return (Result);
}

MATH_INLINE r32 LengthSquared(v2 A)
{
    r32 Result = LengthSquaredV2(A);
    
    return (Result);
}

MATH_INLINE r32 LengthSquared(v3 A)
{
    r32 Result = LengthSquaredV3(A);
    
    return (Result);
}

MATH_INLINE r32 LengthSquared(v4 A)
{
    r32 Result = LengthSquaredV4(A);
    
    return (Result);
}

MATH_INLINE v2 Normalize(v2 A)
{
    v2 Result = NormalizeV2(A);
    
    return (Result);
}

MATH_INLINE v3 Normalize(v3 A)
{
    v3 Result = NormalizeV3(A);
    
    return (Result);
}

MATH_INLINE v4 Normalize(v4 A)
{
    v4 Result = NormalizeV4(A);
    
    return (Result);
}

MATH_INLINE quat Normalize(quat A)
{
    quat Result = NormalizeQuat(A);
	
    return (Result);
}

MATH_INLINE r32 Dot(v2 VecOne, v2 VecTwo)
{
    r32 Result = DotV2(VecOne, VecTwo);
    
    return (Result);
}

MATH_INLINE r32 Dot(v3 VecOne, v3 VecTwo)
{
    r32 Result = DotV3(VecOne, VecTwo);
    
    return (Result);
}

MATH_INLINE r32 Dot(v4 VecOne, v4 VecTwo)
{
    r32 Result = DotV4(VecOne, VecTwo);
    
    return (Result);
}

MATH_INLINE r32 Dot(quat QuatOne, quat QuatTwo)
{
    r32 Result = DotQuat(QuatOne, QuatTwo);
	
    return (Result);
}

MATH_INLINE v2 Add(v2 Left, v2 Right)
{
    v2 Result = AddV2(Left, Right);
    
    return (Result);
}

MATH_INLINE v3 Add(v3 Left, v3 Right)
{
    v3 Result = AddV3(Left, Right);
    
    return (Result);
}

MATH_INLINE v4 Add(v4 Left, v4 Right)
{
    v4 Result = AddV4(Left, Right);
    
    return (Result);
}

MATH_INLINE v2i Addi(v2i Left, v2i Right)
{
    v2i Result = AddV2i(Left, Right);
    
    return (Result);
}

MATH_INLINE v3i Addi(v3i Left, v3i Right)
{
    v3i Result = AddV3i(Left, Right);
    
    return (Result);
}

MATH_INLINE v4i Addi(v4i Left, v4i Right)
{
    v4i Result = AddV4i(Left, Right);
    
    return (Result);
}

MATH_INLINE m4 Add(m4 Left, m4 Right)
{
	m4 Result = AddM4(Left, Right);
	
	return (Result);
}

MATH_INLINE quat Add(quat Left, quat Right)
{
	quat Result = AddQuat(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 Subtract(v2 Left, v2 Right)
{
	v2 Result = SubtractV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 Subtract(v3 Left, v3 Right)
{
	v3 Result = SubtractV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 Subtract(v4 Left, v4 Right)
{
	v4 Result = SubtractV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i Subtract(v2i Left, v2i Right)
{
	v2i Result = SubtractV2i(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i Subtract(v3i Left, v3i Right)
{
	v3i Result = SubtractV3i(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i Subtract(v4i Left, v4i Right)
{
	v4i Result = SubtractV4i(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 Subtract(m4 Left, m4 Right)
{
	m4 Result = SubtractM4(Left, Right);
	
	return (Result);
}

MATH_INLINE quat Subtract(quat Left, quat Right)
{
	quat Result = SubtractQuat(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 Multiply(v2 Left, v2 Right)
{
	v2 Result = MultiplyV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 Multiply(v2 Left, r32 Right)
{
	v2 Result = MultiplyV2f(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 Multiply(v3 Left, v3 Right)
{
	v3 Result = MultiplyV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 Multiply(v3 Left, r32 Right)
{
	v3 Result = MultiplyV3f(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 Multiply(v4 Left, v4 Right)
{
	v4 Result = MultiplyV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 Multiply(v4 Left, r32 Right)
{
	v4 Result = MultiplyV4f(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 Multiply(m4 Left, m4 Right)
{
	m4 Result = MultiplyM4(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 Multiply(m4 Left, r32 Right)
{
	m4 Result = MultiplyM4f(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 Multiply(m4 Matrix, v4 Vector)
{
	v4 Result = MultiplyM4ByV4(Matrix, Vector);
	
	return (Result);
}

MATH_INLINE quat Multiply(quat Left, quat Right)
{
	quat Result = MultiplyQuat(Left, Right);
	
	return (Result);
}

MATH_INLINE quat Multiply(quat Left, r32 Right)
{
	quat Result = MultiplyQuatF(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 Divide(v2 Left, v2 Right)
{
	v2 Result = DivideV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 Divide(v2 Left, r32 Right)
{
	v2 Result = DivideV2f(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 Divide(v3 Left, v3 Right)
{
	v3 Result = DivideV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 Divide(v3 Left, r32 Right)
{
	v3 Result = DivideV3f(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 Divide(v4 Left, v4 Right)
{
	v4 Result = DivideV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 Divide(v4 Left, r32 Right)
{
	v4 Result = DivideV4f(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 Divide(m4 Left, r32 Right)
{
	m4 Result = DivideM4f(Left, Right);
	
	return (Result);
}

MATH_INLINE quat Divide(quat Left, r32 Right)
{
	quat Result = DivideQuatF(Left, Right);
	
	return (Result);
}

MATH_INLINE u8 Equals(v2 Left, v2 Right)
{
	u8 Result = EqualsV2(Left, Right);
	
	return (Result);
}

MATH_INLINE u8 Equals(v3 Left, v3 Right)
{
	u8 Result = EqualsV3(Left, Right);
	
	return (Result);
}

MATH_INLINE u8 Equals(v4 Left, v4 Right)
{
	u8 Result = EqualsV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 operator+(v2 Left, v2 Right)
{
	v2 Result = AddV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i operator+(v2i Left, v2i Right)
{
	v2i Result = AddV2i(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 operator+(v3 Left, v3 Right)
{
	v3 Result = AddV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i operator+(v3i Left, v3i Right)
{
	v3i Result = AddV3i(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 operator+(v4 Left, v4 Right)
{
	v4 Result = AddV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i operator+(v4i Left, v4i Right)
{
	v4i Result = AddV4i(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 operator+(m4 Left, m4 Right)
{
	m4 Result = AddM4(Left, Right);
	
	return (Result);
}

MATH_INLINE quat operator+(quat Left, quat Right)
{
	quat Result = AddQuat(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 operator-(v2 Left, v2 Right)
{
	v2 Result = SubtractV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i operator-(v2i Left, v2i Right)
{
	v2i Result = SubtractV2i(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 operator-(v3 Left, v3 Right)
{
	v3 Result = SubtractV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i operator-(v3i Left, v3i Right)
{
	v3i Result = SubtractV3i(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 operator-(v4 Left, v4 Right)
{
	v4 Result = SubtractV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i operator-(v4i Left, v4i Right)
{
	v4i Result = SubtractV4i(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 operator-(m4 Left, m4 Right)
{
	m4 Result = SubtractM4(Left, Right);
	
	return (Result);
}

MATH_INLINE quat operator-(quat Left, quat Right)
{
	quat Result = SubtractQuat(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 operator*(v2 Left, v2 Right)
{
	v2 Result = MultiplyV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i operator*(v2i Left, v2i Right)
{
	v2i Result = MultiplyV2i(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 operator*(v3 Left, v3 Right)
{
	v3 Result = MultiplyV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i operator*(v3i Left, v3i Right)
{
	v3i Result = MultiplyV3i(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 operator*(v4 Left, v4 Right)
{
	v4 Result = MultiplyV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i operator*(v4i Left, v4i Right)
{
	v4i Result = MultiplyV4i(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 operator*(m4 Left, m4 Right)
{
	m4 Result = MultiplyM4(Left, Right);
	
	return (Result);
}

MATH_INLINE quat operator*(quat Left, quat Right)
{
	quat Result = MultiplyQuat(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 operator*(v2 Left, r32 Right)
{
	v2 Result = MultiplyV2f(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 operator*(v3 Left, r32 Right)
{
	v3 Result = MultiplyV3f(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 operator*(v4 Left, r32 Right)
{
	v4 Result = MultiplyV4f(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i operator*(v2i Left, s32 Right)
{
	v2i Result = MultiplyV2ii(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i operator*(v3i Left, s32 Right)
{
	v3i Result = MultiplyV3ii(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i operator*(v4i Left, s32 Right)
{
	v4i Result = MultiplyV4ii(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 operator*(m4 Left, r32 Right)
{
	m4 Result = MultiplyM4f(Left, Right);
	
	return (Result);
}

MATH_INLINE quat operator*(quat Left, r32 Right)
{
	quat Result = MultiplyQuatF(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 operator*(r32 Left, v2 Right)
{
	v2 Result = MultiplyV2f(Right, Left);
	
	return (Result);
}

MATH_INLINE v3 operator*(r32 Left, v3 Right)
{
	v3 Result = MultiplyV3f(Right, Left);
	
	return (Result);
}

MATH_INLINE v4 operator*(r32 Left, v4 Right)
{
	v4 Result = MultiplyV4f(Right, Left);
	
	return (Result);
}

MATH_INLINE v2i operator*(s32 Left, v2i Right)
{
	v2i Result = MultiplyV2ii(Right, Left);
	
	return (Result);
}

MATH_INLINE v3i operator*(s32 Left, v3i Right)
{
	v3i Result = MultiplyV3ii(Right, Left);
	
	return (Result);
}

MATH_INLINE v4i operator*(s32 Left, v4i Right)
{
	v4i Result = MultiplyV4ii(Right, Left);
	
	return (Result);
}

MATH_INLINE m4 operator*(r32 Left, m4 Right)
{
	m4 Result = MultiplyM4f(Right, Left);
	
	return (Result);
}

MATH_INLINE quat operator*(r32 Left, quat Right)
{
	quat Result = MultiplyQuatF(Right, Left);
	
	return (Result);
}

MATH_INLINE v4 operator*(m4 Matrix, v4 Vector)
{
	v4 Result = MultiplyM4ByV4(Matrix, Vector);
	
	return (Result);
}

MATH_INLINE v3 operator-(v3 Left)
{
	return Left * -1.f;
}

MATH_INLINE v3i operator-(v3i Left)
{
	return Left * -1;
}

MATH_INLINE v2 operator/(v2 Left, v2 Right)
{
	v2 Result = DivideV2(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i operator/(v2i Left, v2i Right)
{
	v2i Result = DivideV2i(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 operator/(v3 Left, v3 Right)
{
	v3 Result = DivideV3(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 operator/(v4 Left, v4 Right)
{
	v4 Result = DivideV4(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 operator/(v2 Left, r32 Right)
{
	v2 Result = DivideV2f(Left, Right);
	
	return (Result);
}

MATH_INLINE v3 operator/(v3 Left, r32 Right)
{
	v3 Result = DivideV3f(Left, Right);
	
	return (Result);
}

MATH_INLINE v4 operator/(v4 Left, r32 Right)
{
	v4 Result = DivideV4f(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i operator/(v3i Left, v3i Right)
{
	v3i Result = DivideV3i(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i operator/(v4i Left, v4i Right)
{
	v4i Result = DivideV4i(Left, Right);
	
	return (Result);
}

MATH_INLINE v2i operator/(v2i Left, s32 Right)
{
	v2i Result = DivideV2ii(Left, Right);
	
	return (Result);
}

MATH_INLINE v3i operator/(v3i Left, s32 Right)
{
	v3i Result = DivideV3ii(Left, Right);
	
	return (Result);
}

MATH_INLINE v4i operator/(v4i Left, s32 Right)
{
	v4i Result = DivideV4ii(Left, Right);
	
	return (Result);
}

MATH_INLINE m4 operator/(m4 Left, r32 Right)
{
	m4 Result = DivideM4f(Left, Right);
	
	return (Result);
}

MATH_INLINE quat operator/(quat Left, r32 Right)
{
	quat Result = DivideQuatF(Left, Right);
	
	return (Result);
}

MATH_INLINE v2 &operator+=(v2 &Left, v2 Right)
{
	return (Left = Left + Right);
}

MATH_INLINE v3 &operator+=(v3 &Left, v3 Right)
{
	return (Left = Left + Right);
}

MATH_INLINE v4 &operator+=(v4 &Left, v4 Right)
{
	return (Left = Left + Right);
}

MATH_INLINE v2i &operator+=(v2i &Left, v2i Right)
{
	return (Left = Left + Right);
}

MATH_INLINE v3i &operator+=(v3i &Left, v3i Right)
{
	return (Left = Left + Right);
}

MATH_INLINE v4i &operator+=(v4i &Left, v4i Right)
{
	return (Left = Left + Right);
}

MATH_INLINE m4 &operator+=(m4 &Left, m4 Right)
{
	return (Left = Left + Right);
}

MATH_INLINE quat &operator+=(quat &Left, quat Right)
{
	return (Left = Left + Right);
}

MATH_INLINE v2 &operator-=(v2 &Left, v2 Right)
{
	return (Left = Left - Right);
}

MATH_INLINE v3 &operator-=(v3 &Left, v3 Right)
{
	return (Left = Left - Right);
}

MATH_INLINE v4 &operator-=(v4 &Left, v4 Right)
{
	return (Left = Left - Right);
}

MATH_INLINE v2i &operator-=(v2i &Left, v2i Right)
{
	return (Left = Left - Right);
}

MATH_INLINE v3i &operator-=(v3i &Left, v3i Right)
{
	return (Left = Left - Right);
}

MATH_INLINE v4i &operator-=(v4i &Left, v4i Right)
{
	return (Left = Left - Right);
}

MATH_INLINE m4 &operator-=(m4 &Left, m4 Right)
{
	return (Left = Left - Right);
}

MATH_INLINE quat &operator-=(quat &Left, quat Right)
{
	return (Left = Left - Right);
}

MATH_INLINE v2 &operator*=(v2 &Left, v2 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v3 &operator*=(v3 &Left, v3 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v4 &operator*=(v4 &Left, v4 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v2 &operator*=(v2 &Left, r32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v3 &operator*=(v3 &Left, r32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v4 &operator*=(v4 &Left, r32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v2i &operator*=(v2i &Left, v2i Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v3i &operator*=(v3i &Left, v3i Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v4i &operator*=(v4i &Left, v4i Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v2i &operator*=(v2i &Left, s32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v3i &operator*=(v3i &Left, s32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v4i &operator*=(v4i &Left, s32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE m4 &operator*=(m4 &Left, r32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE quat &operator*=(quat &Left, r32 Right)
{
	return (Left = Left * Right);
}

MATH_INLINE v2 &operator/=(v2 &Left, v2 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v3 &operator/=(v3 &Left, v3 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v4 &operator/=(v4 &Left, v4 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v2 &operator/=(v2 &Left, r32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v3 &operator/=(v3 &Left, r32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v4 &operator/=(v4 &Left, r32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v2i &operator/=(v2i &Left, v2i Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v3i &operator/=(v3i &Left, v3i Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v4i &operator/=(v4i &Left, v4i Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v2i &operator/=(v2i &Left, s32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v3i &operator/=(v3i &Left, s32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE v4i &operator/=(v4i &Left, s32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE m4 &operator/=(m4 &Left, r32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE quat &operator/=(quat &Left, r32 Right)
{
	return (Left = Left / Right);
}

MATH_INLINE u8 operator==(v2 Left, v2 Right)
{
	return EqualsV2(Left, Right);
}

MATH_INLINE u8 operator==(v2i Left, v2i Right)
{
	return EqualsV2i(Left, Right);
}

MATH_INLINE u8 operator==(v3 Left, v3 Right)
{
	return EqualsV3(Left, Right);
}

MATH_INLINE u8 operator==(v3i Left, v3i Right)
{
	return EqualsV3i(Left, Right);
}

MATH_INLINE u8 operator==(v4 Left, v4 Right)
{
	return EqualsV4(Left, Right);
}

MATH_INLINE u8 operator==(v4i Left, v4i Right)
{
	return EqualsV4i(Left, Right);
}

MATH_INLINE u8 operator!=(v2 Left, v2 Right)
{
	return !EqualsV2(Left, Right);
}

MATH_INLINE u8 operator!=(v2i Left, v2i Right)
{
	return !EqualsV2i(Left, Right);
}

MATH_INLINE u8 operator!=(v3 Left, v3 Right)
{
	return !EqualsV3(Left, Right);
}

MATH_INLINE u8 operator!=(v3i Left, v3i Right)
{
	return !EqualsV3i(Left, Right);
}

MATH_INLINE u8 operator!=(v4 Left, v4 Right)
{
	return !EqualsV4(Left, Right);
}

MATH_INLINE u8 operator!=(v4i Left, v4i Right)
{
	return !EqualsV4i(Left, Right);
}

#endif /* __cplusplus */

#ifdef __clang__
#pragma GCC diagnostic pop
#endif

#endif /* _MATH_H */

#ifdef _MATH_IMPLEMENTATION

r32 Power(r32 Base, s32 Exponent)
{
	r32 Result = 1.0f;
	r32 Mul = Exponent < 0 ? 1.f / Base : Base;
	u32 X = Exponent < 0 ? -Exponent : Exponent;
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

#ifndef _MATH__USE_SSE
m4 Transpose(m4 Matrix)
{
	m4 Result;
	
	s32 Columns;
	for(Columns = 0; Columns < 4; ++Columns)
	{
		s32 Rows;
		for(Rows = 0; Rows < 4; ++Rows)
		{
			Result.Components[Rows][Columns] = Matrix.Components[Columns][Rows];
		}
	}
	
	return (Result);
}
#endif

#ifndef _MATH__USE_SSE
m4 AddM4(m4 Left, m4 Right)
{
	m4 Result;
	
	s32 Columns;
	for(Columns = 0; Columns < 4; ++Columns)
	{
		s32 Rows;
		for(Rows = 0; Rows < 4; ++Rows)
		{
			Result.Components[Columns][Rows] = Left.Components[Columns][Rows] + Right.Components[Columns][Rows];
		}
	}
	
	return (Result);
}
#endif

#ifndef _MATH__USE_SSE
m4 SubtractM4(m4 Left, m4 Right)
{
	m4 Result;
	
	s32 Columns;
	for(Columns = 0; Columns < 4; ++Columns)
	{
		s32 Rows;
		for(Rows = 0; Rows < 4; ++Rows)
		{
			Result.Components[Columns][Rows] = Left.Components[Columns][Rows] - Right.Components[Columns][Rows];
		}
	}
	
	return (Result);
}
#endif

m4 MultiplyM4(m4 Left, m4 Right)
{
	m4 Result;
	
#ifdef _MATH__USE_SSE
	
	Result.Rows[0] = LinearCombineSSE(Right.Rows[0], Left);
	Result.Rows[1] = LinearCombineSSE(Right.Rows[1], Left);
	Result.Rows[2] = LinearCombineSSE(Right.Rows[2], Left);
	Result.Rows[3] = LinearCombineSSE(Right.Rows[3], Left);
	
#else
	s32 Columns;
	for(Columns = 0; Columns < 4; ++Columns)
	{
		s32 Rows;
		for(Rows = 0; Rows < 4; ++Rows)
		{
			r32 Sum = 0;
			s32 CurrentMatrice;
			for(CurrentMatrice = 0; CurrentMatrice < 4; ++CurrentMatrice)
			{
				Sum += Left.Components[CurrentMatrice][Rows] * Right.Components[Columns][CurrentMatrice];
			}
			
			Result.Components[Columns][Rows] = Sum;
		}
	}
#endif
	
	return (Result);
}

#ifndef _MATH__USE_SSE
m4 MultiplyM4f(m4 Matrix, r32 Scalar)
{
	m4 Result;
	
	s32 Columns;
	for(Columns = 0; Columns < 4; ++Columns)
	{
		s32 Rows;
		for(Rows = 0; Rows < 4; ++Rows)
		{
			Result.Components[Columns][Rows] = Matrix.Components[Columns][Rows] * Scalar;
		}
	}
	
	return (Result);
}
#endif

v4 MultiplyM4ByV4(m4 Matrix, v4 Vector)
{
	v4 Result;
	
#ifdef _MATH__USE_SSE
	Result.InternalComponentsSSE = LinearCombineSSE(Vector.InternalComponentsSSE, Matrix);
#else
	s32 Columns, Rows;
	for(Rows = 0; Rows < 4; ++Rows)
	{
		r32 Sum = 0;
		for(Columns = 0; Columns < 4; ++Columns)
		{
			Sum += Matrix.Components[Columns][Rows] * Vector.Components[Columns];
		}
		
		Result.Components[Rows] = Sum;
	}
#endif
	
	return (Result);
}

#ifndef _MATH__USE_SSE
m4 DivideM4f(m4 Matrix, r32 Scalar)
{
	m4 Result;
	
	s32 Columns;
	for(Columns = 0; Columns < 4; ++Columns)
	{
		s32 Rows;
		for(Rows = 0; Rows < 4; ++Rows)
		{
			Result.Components[Columns][Rows] = Matrix.Components[Columns][Rows] / Scalar;
		}
	}
	
	return (Result);
}
#endif

m4 M4Rotate(r32 Angle, v3 Axis)
{
	m4 Result = M4d(1.0f);
	
	Axis = NormalizeV3(Axis);
	
	r32 SinTheta = SinF(ToRadians(Angle));
	r32 CosTheta = CosF(ToRadians(Angle));
	r32 CosValue = 1.0f - CosTheta;
	
	Result.Components[0][0] = (Axis.X * Axis.X * CosValue) + CosTheta;
	Result.Components[0][1] = (Axis.X * Axis.Y * CosValue) + (Axis.Z * SinTheta);
	Result.Components[0][2] = (Axis.X * Axis.Z * CosValue) - (Axis.Y * SinTheta);
	
	Result.Components[1][0] = (Axis.Y * Axis.X * CosValue) - (Axis.Z * SinTheta);
	Result.Components[1][1] = (Axis.Y * Axis.Y * CosValue) + CosTheta;
	Result.Components[1][2] = (Axis.Y * Axis.Z * CosValue) + (Axis.X * SinTheta);
	
	Result.Components[2][0] = (Axis.Z * Axis.X * CosValue) + (Axis.Y * SinTheta);
	Result.Components[2][1] = (Axis.Z * Axis.Y * CosValue) - (Axis.X * SinTheta);
	Result.Components[2][2] = (Axis.Z * Axis.Z * CosValue) + CosTheta;
	
	return (Result);
}

m4 LookAt(v3 Eye, v3 Center, v3 Up)
{
	m4 Result;
	
	v3 F = NormalizeV3(SubtractV3(Center, Eye));
	v3 S = NormalizeV3(Cross(F, Up));
	v3 U = Cross(S, F);
	
	Result.Components[0][0] = S.X;
	Result.Components[0][1] = U.X;
	Result.Components[0][2] = -F.X;
	Result.Components[0][3] = 0.0f;
	
	Result.Components[1][0] = S.Y;
	Result.Components[1][1] = U.Y;
	Result.Components[1][2] = -F.Y;
	Result.Components[1][3] = 0.0f;
	
	Result.Components[2][0] = S.Z;
	Result.Components[2][1] = U.Z;
	Result.Components[2][2] = -F.Z;
	Result.Components[2][3] = 0.0f;
	
	Result.Components[3][0] = -DotV3(S, Eye);
	Result.Components[3][1] = -DotV3(U, Eye);
	Result.Components[3][2] = DotV3(F, Eye);
	Result.Components[3][3] = 1.0f;
	
	return (Result);
}

quat InverseQuat(quat Left)
{
	quat Conjugate;
	quat Result;
	r32 Norm = 0;
	r32 NormSquared = 0;
	
	Conjugate.X = -Left.X;
	Conjugate.Y = -Left.Y;
	Conjugate.Z = -Left.Z;
	Conjugate.W = Left.W;
	
	Norm = SquareRootF(DotQuat(Left, Left));
	NormSquared = Norm * Norm;
	
	Result.X = Conjugate.X / NormSquared;
	Result.Y = Conjugate.Y / NormSquared;
	Result.Z = Conjugate.Z / NormSquared;
	Result.W = Conjugate.W / NormSquared;
	
	return (Result);
}

quat Slerp(quat Left, r32 Time, quat Right)
{
	quat Result;
	quat QuatLeft;
	quat QuatRight;
	
	r32 Cos_Theta = DotQuat(Left, Right);
	r32 Angle = ACosF(Cos_Theta);
	
	r32 S1 = SinF((1.0f - Time) * Angle);
	r32 S2 = SinF(Time * Angle);
	r32 Is = 1.0f / SinF(Angle);
	
	QuatLeft = MultiplyQuatF(Left, S1);
	QuatRight = MultiplyQuatF(Right, S2);
	
	Result = AddQuat(QuatLeft, QuatRight);
	Result = MultiplyQuatF(Result, Is);
	
	return (Result);
}

m4 QuatToM4(quat Left)
{
	m4 Result;
	Result = M4d(1);
	
	quat NormalizedQuat = NormalizeQuat(Left);
	
	r32 XX, YY, ZZ,
	XY, XZ, YZ,
	WX, WY, WZ;
	
	XX = NormalizedQuat.X * NormalizedQuat.X;
	YY = NormalizedQuat.Y * NormalizedQuat.Y;
	ZZ = NormalizedQuat.Z * NormalizedQuat.Z;
	XY = NormalizedQuat.X * NormalizedQuat.Y;
	XZ = NormalizedQuat.X * NormalizedQuat.Z;
	YZ = NormalizedQuat.Y * NormalizedQuat.Z;
	WX = NormalizedQuat.W * NormalizedQuat.X;
	WY = NormalizedQuat.W * NormalizedQuat.Y;
	WZ = NormalizedQuat.W * NormalizedQuat.Z;
	
	Result.Components[0][0] = 1.0f - 2.0f * (YY + ZZ);
	Result.Components[0][1] = 2.0f * (XY + WZ);
	Result.Components[0][2] = 2.0f * (XZ - WY);
	
	Result.Components[1][0] = 2.0f * (XY - WZ);
	Result.Components[1][1] = 1.0f - 2.0f * (XX + ZZ);
	Result.Components[1][2] = 2.0f * (YZ + WX);
	
	Result.Components[2][0] = 2.0f * (XZ + WY);
	Result.Components[2][1] = 2.0f * (YZ - WX);
	Result.Components[2][2] = 1.0f - 2.0f * (XX + YY);
	
	return (Result);
}

quat QuatFromAxisAngle(v3 Axis, r32 AngleOfRotation)
{
	quat Result;
	
	v3 RotatedVector;
	
	r32 AxisNorm = 0;
	r32 SineOfRotation = 0;
	
	AxisNorm = SquareRootF(DotV3(Axis, Axis));
	SineOfRotation = SinF(AngleOfRotation / 2.0f);
	RotatedVector = MultiplyV3f(Axis, SineOfRotation);
	
	Result.W = CosF(AngleOfRotation / 2.0f);
	Result.XYZ = DivideV3f(RotatedVector, AxisNorm);
	
	return (Result);
}

enclosed s32 Ceil(const r32 V)
{
	s32 Result = (s32)V;
	Result += (V > Result) ? 1 : 0;
	return Result;
}

enclosed s64 Ceil(const r64 V)
{
	s64 Result = (s64)V;
	Result += (V > Result) ? 1 : 0;
	return Result;
}

enclosed s32 Floor(const r32 V)
{
	s32 Result = (s32)V;
	Result -= (V > Result) ? 1 : 0;
	return Result;
}

enclosed s64 Floor(const r64 V)
{
	s64 Result = (s64)V;
	Result -= (V > Result) ? 1 : 0;
	return Result;
}


enclosed v2 V2()
{
	v2 R = {0.f, 0.f};
	return R;
}

enclosed v2i V2i()
{
	v2i R = {0, 0};
	return R;
}

enclosed v3 V3()
{
	v3 R = {0.f, 0.f, 0.f};
	return R;
}

enclosed v3i V3i()
{
	v3i R = {0, 0, 0};
	return R;
}

enclosed v4 V4()
{
	v4 R = {0.f, 0.f, 0.f, 0.f};
	return R;
}

enclosed v4i V4i()
{
	v4i R = {0, 0, 0, 0};
	return R;
}

enclosed m4 M4(r32 V)
{
	m4 R = {
		V, V, V, V,
		V, V, V, V,
		V, V, V, V,
		V, V, V, V
	};
	return R;
}

#define KNOT_MATH_H
#endif
