/* senser_map_serialize.h : June 29th 2020 11:50 pm */

#if !defined(SENSER_MAP_SERIALIZE_H)

#include <direct.h>
#define GetCurrentDir _getcwd
#define MAX_WINDOWS_PATH_LENGTH MAX_PATH

#define SERIALIZE_MAP_VALUE_TOKEN "%d,"

enclosed char* GetWorkingDirectory();
enclosed char* GetRelativeDirectoryFromName(const char* DirectoryName);
enclosed char* GetContentDirectory();
enclosed char* GetMapDirectory();
enclosed char* GetSourceDirectory();

enclosed u8 WriteMapFile(const char* FileName, quad_position*& Buffer, const s32 BufferCount);
enclosed void OpenMapFile(const char* FileName, quad_position*& Buffer);

#define SENSER_MAP_SERIALIZE_H
#endif