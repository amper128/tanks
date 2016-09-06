#pragma once

#include <vector>
#include <map>
#include <queue>

class CMemoryManager
{
	class MemBlock
	{
	public:
		enum { defsize = 64*1024*1024 };	//дефолтный размер = 32М

		MemBlock(void);

		MemBlock(size_t);
		~MemBlock(void);

		void* allocate(size_t);
		size_t size(void) const;

		size_t remaining(void) const;

		MemBlock(const MemBlock& cp);
		MemBlock& operator = (const MemBlock& cp);

	private:
		unsigned char* m_block;		//указатель на область памяти, где оно лежит
		size_t m_remain;	//скока еще свободно
		size_t m_size;		//какой размер блока вообще
		size_t m_curr;		//скока занято
	};

	//ячейка памяти
	struct MemEntry
	{
		size_t size;		//размер ячейки
		void* ptr;		//где лежит
		MemEntry(void* sp, size_t sz): size(sz), ptr(sp) {}
	};
private:
	CMemoryManager(const CMemoryManager&);
	CMemoryManager& operator = (const CMemoryManager&);

	std::vector<CMemoryManager::MemBlock*> m_blocks;
	std::map<size_t, std::queue<CMemoryManager::MemEntry> > m_freeEntrys;

	void addBlock(size_t);
public:
	CMemoryManager(void) { }
	~CMemoryManager(void);

	void* allocate(size_t);
	void deallocate(void*, size_t);

	void mrproper(void);
};
