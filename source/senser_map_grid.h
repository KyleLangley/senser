/* senser_map_grid.h : June 19th 2020 8:25 pm */

#if !defined(SENSER_MAP_GRID_H)

enclosed const s32 GRID_COUNT_X = 30;
enclosed const s32 GRID_COUNT_Y = 20;

enclosed s32 SnapToGrid(const s32 V, const u8 Y);

global_variable s32 GRID_SIZE;

#define SENSER_MAP_GRID_H
#endif
