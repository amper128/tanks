/*

	менеджер памяти, чтобы каждый раз ядро ОСи не трогать

*/

#include <system/memory_manager.h>
#include <cstdio>

inline CMemoryManager::MemBlock::MemBlock(void): m_size(defsize), m_remain(m_size), m_curr(0)
{
	m_block = new unsigned char[m_size];
	m_remain = m_size;
}

inline CMemoryManager::MemBlock::MemBlock(size_t theSize): m_size(defsize), m_block(0), m_curr(0)
{
	if(theSize > m_size) m_size = theSize;
	m_block = new unsigned char[m_size];
	m_remain = m_size;
}

CMemoryManager::MemBlock::~MemBlock(void)
{
	delete[] m_block;
}

inline const size_t CMemoryManager::MemBlock::size(void) const
{
	return m_size;
}

inline const size_t CMemoryManager::MemBlock::remaining(void) const
{
	return m_remain;
}

inline void* CMemoryManager::MemBlock::allocate(size_t bytes)
{
	if ((m_block == NULL) || (bytes > m_remain))
		return 0;
	void *memory = m_block + m_curr;
	m_curr += bytes;
	m_remain -= bytes;
	return memory;
}

//CMemoryManager
inline void CMemoryManager::addBlock(size_t blockSize)
{
	if(blockSize > CMemoryManager::MemBlock::defsize)
		m_blocks.push_back(new CMemoryManager::MemBlock(blockSize));
	else m_blocks.push_back(new CMemoryManager::MemBlock());
}

void* CMemoryManager::allocate(size_t bytes)
{
	void *memory = 0;
	try
	{
	//try to find free cell
		std::queue<CMemoryManager::MemEntry> que = m_freeEntrys[bytes];
		if(!que.empty())
		{
			memory = que.front().ptr;
			que.pop();
		}
		if(!memory)
		{
			if(m_blocks.empty()) addBlock(bytes);
			if((*(m_blocks.end()-1))->remaining() < bytes)
				addBlock(bytes);
			memory = (*(m_blocks.end()-1))->allocate(bytes);
		}
	}
	catch( char * str )
	{
		//ну вобщем тут ошибко
		printf("Error блеать!!!\n");
	}
	return memory;
}

void CMemoryManager::deallocate(void* space, size_t bytes)
{
	m_freeEntrys[bytes].push(CMemoryManager::MemEntry(space, bytes));
}

void CMemoryManager::mrproper(void)
{
	std::map<size_t, std::queue<CMemoryManager::MemEntry> >::iterator mit = m_freeEntrys.begin();
	for(; mit!=m_freeEntrys.end(); ++mit)
	{
		while(!(mit->second.empty()))
		mit->second.pop();
	}

	std::vector<CMemoryManager::MemBlock*>::iterator vit = m_blocks.begin();
	for(; vit!=m_blocks.end(); ++vit)
	{
		delete (*vit);
	}
	m_blocks.clear();
}

CMemoryManager::~CMemoryManager(void)
{
	mrproper();
}
