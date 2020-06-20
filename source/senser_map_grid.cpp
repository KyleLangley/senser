/* senser_map_grid.cpp : June 19th 2020 8:25 pm */

enclosed void InitMapGrid(const s32 Width, const s32 Height)
{
    const s32 Size = sizeof(v3i) * ((Width * GRID_SIZE) + (Height * GRID_SIZE));
    GridMapping = (v3i*)Allocate(Size);
    
    s32 GridIdx = 0;
    for(s32 WidthIndex = 0; WidthIndex < Width; ++WidthIndex)
    {
        for(s32 HeightIndex = 0; HeightIndex < Height; ++HeightIndex)
        {
            GridMapping[GridIdx++] = V3i(WidthIndex * GRID_SIZE, HeightIndex * GRID_SIZE, 0);
        }
    }
}

