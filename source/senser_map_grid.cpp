/* senser_map_grid.cpp : June 19th 2020 8:25 pm */

enclosed s32 SnapToGrid(const s32 V)
{
    return (V / GRID_SIZE) * GRID_SIZE;
}