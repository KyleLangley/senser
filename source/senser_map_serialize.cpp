/* senser_map_serialize.cpp : June 29th 2020 11:52 pm */

#include "senser_map_serialize.h"

enclosed u8 WriteMapFile(const char* FileName, quad_position*& Buffer, const s32 BufferCount)
{
    
    if(Buffer != nullptr && FileName != nullptr)
    {
        const s32 MapTokenValueLength = strlen(SERIALIZE_MAP_VALUE_TOKEN);
        
        char* WriteBuffer = (char*)Allocate(Megabytes(10));
        char* WriteBufferTempPtr = WriteBuffer;
        
        for(s32 BufferIndex = 0; BufferIndex < BufferCount; ++BufferIndex)
        {
            if(quad_position* QuadPosition = &Buffer[BufferIndex])
            {
                if(QuadPosition->Used)
                {
                    char* Temp = WriteBufferTempPtr;
                    sprintf(Temp, SERIALIZE_MAP_VALUE_TOKEN, QuadPosition->Position.X, QuadPosition->Position.Y, QuadPosition->Used);
                    WriteBufferTempPtr += strlen(Temp);
                }
            }
        }
        
        const s32 WrittenSize = WriteBufferTempPtr - WriteBuffer;
        WriteBuffer = (char*)Reallocate((u8*)WriteBuffer, WrittenSize);
        
        DWORD Error = GetLastError();
        
        if(const s32 FileNameLength = strlen(FileName))
        {
            if(char* Content = GetContentDirectory())
            {
                memcpy(&Content[strlen(Content)], FileName, strlen(FileName));
                
                if(FILE* MapFile = fopen(Content, "w+"))
                {
                    fwrite(WriteBuffer, sizeof(char), WrittenSize, MapFile);
                    fclose(MapFile);
                    
                    printf("Successfully wrote file %s with size of %d bytes.\n", Content, WrittenSize);
                    return true;
                }
            }
        }
    }
    return false;
}

enclosed void OpenMapFile()
{
}

enclosed char* GetWorkingDirectory()
{
    char* Dir = (char*)Allocate(MAX_WINDOWS_PATH_LENGTH);
    GetCurrentDir(Dir, MAX_WINDOWS_PATH_LENGTH);
    return Dir;
}

enclosed char* GetRelativeDirectoryFromName(const char* DirectoryName)
{
    char* Dir = GetWorkingDirectory();
    if(char* Ptr = strstr(Dir, "\\build"))
    {
        memset(&Dir[Ptr - Dir], 0, MAX_WINDOWS_PATH_LENGTH - (s32)(Ptr - Dir));
        memcpy(&Dir[Ptr - Dir], DirectoryName, strlen(DirectoryName));
    }
    return Dir;
}

enclosed char* GetContentDirectory()
{
    return GetRelativeDirectoryFromName("\\content\\");
}

enclosed char* GetMapDirectory()
{
    return GetRelativeDirectoryFromName("\\content\\map\\");
}

enclosed char* GetSourceDirectory()
{
    return GetRelativeDirectoryFromName("\\source\\");
}

