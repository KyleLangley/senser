/* senser_types.h : June 13th 2020 5:02 pm */

#if !defined(SENSER_TYPES_H)

#include <cstdio>
#include "stdint.h"

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float r32;
typedef double r64;

#define enclosed static
#define local_persist static 
#define global_variable static 

#define Kilobytes(Value) Value * 1024
#define Megabytes(Value) Kilobytes(Value) * 1024
#define Gigabytes(Value) Megabytes(Value) * 1024
#define Terabytes(Value) Gigabytes(Value) * 1024

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include <timeapi.h>

struct window_params
{
    WNDCLASS Class;
    HWND Handle;
    HDC DeviceContext;
    MSG Message;
    HGLRC RenderContext;
    u8 Running;
};

global_variable window_params WindowParams;

enclosed const r64 FPS_TARGET = 60.f;
enclosed const r64 FRAME_UPDATE_RATE = 1.f / FPS_TARGET;

struct timing_params
{
    LARGE_INTEGER StartTime;
    LARGE_INTEGER EndTime;
    LARGE_INTEGER Frequency;
};

global_variable timing_params TimingParams;

struct timing
{
    r64 GameSeconds;
    r64 FPS;
    r64 DeltaTime;
    u8 SleepIsGranular;
};

global_variable timing Timing;

#define _MATH_IMPLEMENTATION
#include "senser_math.h"

#include "senser_gl.h"
#include "senser_gl.cpp"

enclosed u8* Allocate(const s32 Size)
{
    return (u8*)VirtualAlloc(nullptr, Size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
}

enclosed u8 Deallocate(u8* Ptr)
{
    return VirtualFree(Ptr, 0, MEM_RELEASE);
}

#define SENSER_TYPES_H
#endif
