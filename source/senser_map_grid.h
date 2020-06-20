/* senser_map_grid.h : June 19th 2020 8:25 pm */

#if !defined(SENSER_MAP_GRID_H)

enclosed const s32 GRID_SIZE = 32;

enclosed void InitMapGrid(const s32 Width, const s32 Height);

local_persist v3i* GridMapping;

#define SENSER_MAP_GRID_H
#endif
