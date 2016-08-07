#include <map>
#include "debug.h"
#include "memory_manager.h"

#undef new
#undef delete


class MemoryAllocation
{
public:
	MemoryAllocation(){}
	size_t mSize;
	const char* mFile;
	int mLine;
};

class MemoryManager
{
public:
	MemoryManager(){}
	~MemoryManager(){}

	void addMemoryAllocation(MemoryAllocation *arg_mem, size_t arg_loc)
	{
		mMemoryMap[arg_loc] = arg_mem;
	}
	void removeMemoryAllocation(void* arg_ptr)
	{
		mMemoryMap[reinterpret_cast<size_t>(arg_ptr)] = 0;
	}
	void dumpMemoryAllocations()
	{

		LOG_INFO() << "Dumping memory information";
		LOG_INFO() << "size ** filenam ** line number";

		if(mMemoryMap.empty())
			return;

		std::map<size_t, MemoryAllocation*>::iterator it;
		for(it = mMemoryMap.begin(); it != mMemoryMap.end(); it++)
		{
			MemoryAllocation *m = it->second;;
			if(!m)
				continue; // nothing
			LOG_INFO() << m->mSize << " ** File: " << m->mFile << " ** Line: " << m->mLine;
		}
	}
private:
	std::map<size_t, MemoryAllocation*> mMemoryMap;
};

MemoryManager memoryManager;

void* AllocateMemory(size_t arg_size, const char* arg_file, int arg_line)
{
	void* location = malloc(arg_size);
	MemoryAllocation *mem = new MemoryAllocation();
	mem->mSize = arg_size;
	mem->mFile = arg_file;
	mem->mLine = arg_line; 
	memoryManager.addMemoryAllocation(mem, reinterpret_cast<size_t>(location));
	return location;
}

void DeallocateMemory(void* arg_ptr)
{
	memoryManager.removeMemoryAllocation(arg_ptr);
	free(arg_ptr);
}

void DumpMemoryAllocations()
{
	memoryManager.dumpMemoryAllocations();
}

#define new new(__FILE__,__LINE__)

#define delete delete