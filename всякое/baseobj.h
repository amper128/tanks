////////////////////////////////////////////////////////////////////////////////
// baseobj.h
// Kurilov Igor, Legionary group
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// Обявляем свою область имен
namespace legionary
{
// legionary::

// Не сортированый список
// Внимание! Код не является потоко-безопасным
template <class Type> class list
{
protected:
	// типы
	typedef Type *			t_ptr;	// указатель на данные
	typedef struct {
		void	*	pNext;
		void	*	pPrior;
		t_ptr		pData;
	}	t_listitem;					// структура для организации
									// связного списка
public:
	class iterator;
	friend class iterator;
	class iterator					// класс для перебора записей
	{
		friend class legionary::list;
	protected:
		t_listitem	*	m_pPosition; // указатель на текущий элемент цепочки
	public:
		iterator() { m_pPosition = 0; }
		~iterator() {}
		Type &amp; operator*() {	// оператор для получения данных (*iter)
			return *(m_pPosition-&gt;pData);
		}
		iterator&amp; operator++() { // для движения по списку вперед
			m_pPosition = (t_listitem*)m_pPosition-&gt;pNext;
			return (*this);
		}
		iterator&amp; operator--() { // для движения по списку назад
			m_pPosition = (t_listitem*)m_pPosition-&gt;pPrior;
			return (*this);
		}
		iterator&amp; operator=(const iterator&amp; iter) { // для движения присвоения
			m_pPosition = iter.m_pPosition;
			return (*this);
		}
		// проверка возможности перемещения
		bool valid() { return (m_pPosition!=0); } 
		bool last() { return (m_pPosition-&gt;pNext!=0); }
		bool first() { return (m_pPosition-&gt;pPrior!=0); }
	};
protected:
	// переменные
	t_ptr			m_pData;	// массив для данных
	t_listitem	*	m_pItems;	// массив для цепочек списка
	t_listitem	*	m_pCache;	// указатель на список резервных резерва
	t_listitem	*	m_pBegin;	// указатель на список данных (начало)
	t_listitem	*	m_pEnd;		// указатель на список данных (конец)
	iterator		m_Iterator; // используется в функциях, возращающих итератор
	// методы
	int	m_Size;				// кол-во элементов в списке
	int m_Capacity;			// кол-во зарезервированных элементов
public:
	// конструктор
	// nCapacity - максимальный объем списка
	list(int nCapacity) {
		m_Size = 0;
		m_Capacity = nCapacity;
		// резервируем память
		m_pData = new Type[m_Capacity];
		// изначально все элементы находятся в резерве
		m_pCache = m_pItems = new t_listitem[m_Capacity];
		m_pEnd = m_pBegin = 0;
		// связываем элементы списка в одну цепочку
		t_listitem *pLast = NULL;
		t_listitem *pCurrent = m_pCache;
		for(int n=0; n &lt; m_Capacity; n++, pCurrent++){
			pCurrent-&gt;pPrior = (void*)pLast;
			pCurrent-&gt;pData = m_pData + n;
			if(pLast!=0) pLast-&gt;pNext = (void*)pCurrent;
			pLast = pCurrent;
		}
		m_pCache[m_Capacity-1].pNext = 0;
	}
	// деструктор
	~list() {
		// освобохдаем память
		delete[] m_pData;
		delete[] m_pItems;
	}
	// добавление элемента в начало списка
	Type &amp; add_first() {
		// перемещаем элемент из резерва в начало списка
		t_listitem	*item = m_pCache;
		m_pCache = (t_listitem*)item-&gt;pNext;
		if(m_pCache!=0) m_pCache-&gt;pPrior = 0;
		if(m_pBegin==0) m_pEnd = item;
		else m_pBegin-&gt;pPrior = (void*)item;
		item-&gt;pNext = (void*)m_pBegin;
		m_pBegin = item;
		// приводим в соответствие количества элементов в списке и резерве
		m_Size++;
		m_Capacity--;
		return *(item-&gt;pData);
	}
	// добавление элемента в конец списка
	Type &amp; add_last() {
		// перемещаем элемент из резерва в конец списка
		t_listitem	*item = m_pCache;
		m_pCache = (t_listitem*)item-&gt;pNext;
		if(m_pCache!=0) m_pCache-&gt;pPrior = 0;
		if(m_pEnd==0) m_pBegin = item;
		else m_pEnd-&gt;pNext = (void*)item;
		item-&gt;pPrior = (void*)m_pEnd;
		item-&gt;pNext = 0;
		m_pEnd = item;
		// приводим в соответствие количества элементов в списке и резерве
		m_Size++;
		m_Capacity--;
		return *(item-&gt;pData);
	}
	// удаление всех элементов
	void clear() {
		if(m_pBegin!=0) {
			m_Capacity += m_Size;
			m_Size = 0;
			// присоединяем к концу списка начало резерва
			m_pEnd-&gt;pNext = (void*)m_pCache;
			m_pCache-&gt;pPrior = (void*)m_pEnd;
			// переносим начало списка в резерв
			m_pCache = m_pBegin;
			m_pEnd = m_pBegin = 0;
		}
	}
	// удаление одного элемента
	void remove(const iterator &amp; i) {
		if(i.m_pPosition-&gt;pPrior!=0) 
			((t_listitem*)(i.m_pPosition-&gt;pPrior))-&gt;pNext = i.m_pPosition-&gt;pNext;
		if(i.m_pPosition-&gt;pNext!=0) 
			((t_listitem*)(i.m_pPosition-&gt;pNext))-&gt;pPrior = i.m_pPosition-&gt;pPrior;
		if(i.m_pPosition==m_pBegin) m_pBegin = (t_listitem*)(i.m_pPosition-&gt;pNext);
		if(i.m_pPosition==m_pEnd) m_pEnd = (t_listitem*)(i.m_pPosition-&gt;pPrior);
		// приводим в соответствие количества элементов в списке и резерве
		m_Size--;
		m_Capacity++;
	}
	int size() { return m_Size; } // кол-во элементов в списке
	iterator &amp; begin() { // итератор на начало списка
		m_Iterator.m_pPosition = m_pBegin;
		return m_Iterator;
	}
	iterator &amp; end() { // итератор на конец списка
		m_Iterator.m_pPosition = m_pEnd;
		return m_Iterator;
	}
};

} // Конец области имен legionary
