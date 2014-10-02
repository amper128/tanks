////////////////////////////////////////////////////////////////////////////////
// baseobj.h
// Kurilov Igor, Legionary group
////////////////////////////////////////////////////////////////////////////////
#pragma once

////////////////////////////////////////////////////////////////////////////////
// �������� ���� ������� ����
namespace legionary
{
// legionary::

// �� ������������ ������
// ��������! ��� �� �������� ������-����������
template <class Type> class list
{
protected:
	// ����
	typedef Type *			t_ptr;	// ��������� �� ������
	typedef struct {
		void	*	pNext;
		void	*	pPrior;
		t_ptr		pData;
	}	t_listitem;					// ��������� ��� �����������
									// �������� ������
public:
	class iterator;
	friend class iterator;
	class iterator					// ����� ��� �������� �������
	{
		friend class legionary::list;
	protected:
		t_listitem	*	m_pPosition; // ��������� �� ������� ������� �������
	public:
		iterator() { m_pPosition = 0; }
		~iterator() {}
		Type &amp; operator*() {	// �������� ��� ��������� ������ (*iter)
			return *(m_pPosition-&gt;pData);
		}
		iterator&amp; operator++() { // ��� �������� �� ������ ������
			m_pPosition = (t_listitem*)m_pPosition-&gt;pNext;
			return (*this);
		}
		iterator&amp; operator--() { // ��� �������� �� ������ �����
			m_pPosition = (t_listitem*)m_pPosition-&gt;pPrior;
			return (*this);
		}
		iterator&amp; operator=(const iterator&amp; iter) { // ��� �������� ����������
			m_pPosition = iter.m_pPosition;
			return (*this);
		}
		// �������� ����������� �����������
		bool valid() { return (m_pPosition!=0); } 
		bool last() { return (m_pPosition-&gt;pNext!=0); }
		bool first() { return (m_pPosition-&gt;pPrior!=0); }
	};
protected:
	// ����������
	t_ptr			m_pData;	// ������ ��� ������
	t_listitem	*	m_pItems;	// ������ ��� ������� ������
	t_listitem	*	m_pCache;	// ��������� �� ������ ��������� �������
	t_listitem	*	m_pBegin;	// ��������� �� ������ ������ (������)
	t_listitem	*	m_pEnd;		// ��������� �� ������ ������ (�����)
	iterator		m_Iterator; // ������������ � ��������, ����������� ��������
	// ������
	int	m_Size;				// ���-�� ��������� � ������
	int m_Capacity;			// ���-�� ����������������� ���������
public:
	// �����������
	// nCapacity - ������������ ����� ������
	list(int nCapacity) {
		m_Size = 0;
		m_Capacity = nCapacity;
		// ����������� ������
		m_pData = new Type[m_Capacity];
		// ���������� ��� �������� ��������� � �������
		m_pCache = m_pItems = new t_listitem[m_Capacity];
		m_pEnd = m_pBegin = 0;
		// ��������� �������� ������ � ���� �������
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
	// ����������
	~list() {
		// ����������� ������
		delete[] m_pData;
		delete[] m_pItems;
	}
	// ���������� �������� � ������ ������
	Type &amp; add_first() {
		// ���������� ������� �� ������� � ������ ������
		t_listitem	*item = m_pCache;
		m_pCache = (t_listitem*)item-&gt;pNext;
		if(m_pCache!=0) m_pCache-&gt;pPrior = 0;
		if(m_pBegin==0) m_pEnd = item;
		else m_pBegin-&gt;pPrior = (void*)item;
		item-&gt;pNext = (void*)m_pBegin;
		m_pBegin = item;
		// �������� � ������������ ���������� ��������� � ������ � �������
		m_Size++;
		m_Capacity--;
		return *(item-&gt;pData);
	}
	// ���������� �������� � ����� ������
	Type &amp; add_last() {
		// ���������� ������� �� ������� � ����� ������
		t_listitem	*item = m_pCache;
		m_pCache = (t_listitem*)item-&gt;pNext;
		if(m_pCache!=0) m_pCache-&gt;pPrior = 0;
		if(m_pEnd==0) m_pBegin = item;
		else m_pEnd-&gt;pNext = (void*)item;
		item-&gt;pPrior = (void*)m_pEnd;
		item-&gt;pNext = 0;
		m_pEnd = item;
		// �������� � ������������ ���������� ��������� � ������ � �������
		m_Size++;
		m_Capacity--;
		return *(item-&gt;pData);
	}
	// �������� ���� ���������
	void clear() {
		if(m_pBegin!=0) {
			m_Capacity += m_Size;
			m_Size = 0;
			// ������������ � ����� ������ ������ �������
			m_pEnd-&gt;pNext = (void*)m_pCache;
			m_pCache-&gt;pPrior = (void*)m_pEnd;
			// ��������� ������ ������ � ������
			m_pCache = m_pBegin;
			m_pEnd = m_pBegin = 0;
		}
	}
	// �������� ������ ��������
	void remove(const iterator &amp; i) {
		if(i.m_pPosition-&gt;pPrior!=0) 
			((t_listitem*)(i.m_pPosition-&gt;pPrior))-&gt;pNext = i.m_pPosition-&gt;pNext;
		if(i.m_pPosition-&gt;pNext!=0) 
			((t_listitem*)(i.m_pPosition-&gt;pNext))-&gt;pPrior = i.m_pPosition-&gt;pPrior;
		if(i.m_pPosition==m_pBegin) m_pBegin = (t_listitem*)(i.m_pPosition-&gt;pNext);
		if(i.m_pPosition==m_pEnd) m_pEnd = (t_listitem*)(i.m_pPosition-&gt;pPrior);
		// �������� � ������������ ���������� ��������� � ������ � �������
		m_Size--;
		m_Capacity++;
	}
	int size() { return m_Size; } // ���-�� ��������� � ������
	iterator &amp; begin() { // �������� �� ������ ������
		m_Iterator.m_pPosition = m_pBegin;
		return m_Iterator;
	}
	iterator &amp; end() { // �������� �� ����� ������
		m_Iterator.m_pPosition = m_pEnd;
		return m_Iterator;
	}
};

} // ����� ������� ���� legionary
