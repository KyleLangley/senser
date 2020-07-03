/* senser_map_serialize.cpp : June 29th 2020 11:52 pm */

#include "senser_map_serialize.h"

enclosed u8 WriteMapFile(const char* FileName, quad_position*& Buffer, const s32 BufferCount)
{
    if(Buffer != nullptr && FileName != nullptr)
    {
        const s32 MapTokenValueLength = strlen(SERIALIZE_MAP_VALUE_TOKEN);
        
        char* WriteBuffer = (char*)Allocate(Megabytes(10));
        memset(WriteBuffer, 0, Megabytes(10));
        char* WriteBufferTempPtr = WriteBuffer;
        
        for(s32 BufferIndex = 0; BufferIndex < BufferCount; ++BufferIndex)
        {
            if(quad_position* QuadPosition = &Buffer[BufferIndex])
            {
                if(QuadPosition->Used)
                {
                    char* Temp = WriteBufferTempPtr;
                    Assert(QuadPosition->Position.X < WindowParams.Dimensions.Width);
                    Assert(QuadPosition->Position.Y < WindowParams.Dimensions.Height);
                    
                    sprintf(Temp, SERIALIZE_MAP_VALUE_TOKEN, QuadPosition->Position.X, QuadPosition->Position.Y, QuadPosition->Used);
                    WriteBufferTempPtr += strlen(Temp);
                }
            }
        }
        
        const s32 WrittenSize = WriteBufferTempPtr - WriteBuffer;
        if(WrittenSize <= 0)
        {
            printf("Tried to write file but there is nothing to write....\n");
            return false;
        }
        
        WriteBuffer = (char*)Reallocate((u8*)WriteBuffer, WrittenSize);
        
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

enclosed void OpenMapFile(const char* FileName, quad_position*& Buffer)
{
    if(FileName != nullptr && Buffer != nullptr)
    {
        if(const s32 FileNameLength = strlen(FileName))
        {
            if(char* Content = GetContentDirectory())
            {
                memcpy(&Content[strlen(Content)], FileName, strlen(FileName));
                
                if(FILE* Opened = fopen(Content, "r"))
                {
                    fseek(Opened, 0, SEEK_END);
                    const s32 OpenedSize = ftell (Opened);
                    fseek(Opened, 0, SEEK_SET);
                    
                    if(char* ReadBuffer = (char*)Allocate(OpenedSize))
                    {
                        const s32 ReadSize = fread(ReadBuffer, sizeof(char), OpenedSize, Opened);
                        if(ReadSize != OpenedSize)
                        {
                            printf("Opened filed but got unexpected size of %d. Expected %d.\n", ReadSize, OpenedSize);
                        }
                        
                        char* StartPtr = ReadBuffer;
                        char* Ptr = ReadBuffer;
                        while(*Ptr != 0)
                        {
                            if(*Ptr++ == ',')
                            {
                                char PositionBuffer[32];
                                memset(&PositionBuffer[0], 0, 32);
                                char* PositionBufferPtr = &PositionBuffer[0];
                                
                                while(StartPtr != Ptr)
                                {
                                    *PositionBufferPtr++ = *StartPtr;
                                    StartPtr++;
                                }
                                
                                char Start[16];
                                memset(&Start[0], 0, 16);
                                char End[16];
                                memset(&End[0], 0, 16);
                                char* StartPtr = &Start[0];
                                char* EndPtr = &End[0];
                                
                                u8 Split = false;
                                for(s32 Index = 0; Index < 32; ++Index)
                                {
                                    if(PositionBuffer[Index] == ',')
                                    {
                                        break;
                                    }
                                    
                                    if(PositionBuffer[Index] == '-')
                                    {
                                        Split = true;
                                        continue;
                                    }
                                    
                                    if(Split)
                                    {
                                        *EndPtr++ = PositionBuffer[Index];
                                    }
                                    else
                                    {
                                        *StartPtr++ = PositionBuffer[Index];
                                    }
                                }
                                
                                const s32 X = atoi(&Start[0]);
                                const s32 Y = atoi(&End[0]);
                                
                                AddToQuadPositions(V2i(X, Y));
                                
                                StartPtr = Ptr;
                            }
                        }
                    }
                }
            }
        }
    }
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

