//#undef new
//#undef delete

#include<stdlib.h>
//#include<iostream>

void* AllocateMemory(size_t arg_size, const char* arg_file, int arg_line);
void DeallocateMemory(void* arg_ptr);
void DumpMemoryAllocations();


inline void* operator new(size_t arg_size, const char* arg_file, int arg_line)
{
	//return malloc(arg_size);
	return AllocateMemory(arg_size, arg_file, arg_line);
}

inline void operator delete(void *arg_ptr) noexcept
{
	//free(arg_ptr);
	DeallocateMemory(arg_ptr);
}


