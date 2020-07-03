/* senser_types.h : June 13th 2020 5:02 pm */

#if !defined(SENSER_TYPES_H)

#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS
#endif

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

#define Assert(Exp) if(!(Exp)) {*(int *)0 = 0;}

/*
enclosed const char* SizingNames[4] = {"Kilobytes", "Megabytes", "Gigabytes", "Terabytes"};
enclosed void GetSize(const s32 Value, char*& Out)
{
    s32 Sizing = 0;
    s32 NewValue = Value % 1024;
    if(NewValue % 1024 > 1024)
    {
        Sizing++;
        Count++;
        GetSize(NewValue, Out);
    }
    
    sprintf(&Out[0], "%d %s.%d\n", Count, SizingNames[Sizing], NewValue);
}
*/

#ifdef WINDOWS
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include "stdlib.h"

enclosed u8* Allocate(const s32 Size)
{
    return (u8*)VirtualAlloc(nullptr, Size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

enclosed u8* Reallocate(u8* Ptr, const s32 Size)
{
    return (u8*)VirtualAlloc(Ptr, Size, MEM_COMMIT, PAGE_READWRITE);
}

enclosed u8 Deallocate(u8* Ptr)
{
    return VirtualFree(Ptr, 0, MEM_RELEASE);
}

#include <timeapi.h>

#define STB_DEFINE
#include "stb/stb.h"

#define _MATH_IMPLEMENTATION
#include "senser_math.h"

struct window_params
{
    WNDCLASS Class;
    HWND Handle;
    HDC DeviceContext;
    MSG Message;
    HGLRC RenderContext;
    u8 Running;
    POINT CursorPoint;
    
    v2i Dimensions;
};

global_variable window_params WindowParams;

enclosed const r64 FPS_TARGET = 90.f;
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

#include "senser_map_grid.h"
#include "senser_map_grid.cpp"

#include "senser_gl.h"
#include "senser_map_serialize.cpp"
#include "senser_gl.cpp"

#define SENSER_TYPES_H
#endif
