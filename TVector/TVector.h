#pragma once
#include <iostream>
using namespace std;

template <typename TVector>
class VectorIterator
{
public:
	using ValueType = typename TVector::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	VectorIterator(PointerType ptr) : m_Ptr(ptr) { };
	VectorIterator& operator ++()
	{
		m_Ptr++;
		return *this;
	}
	VectorIterator& operator --()
	{
		m_Ptr--;
		return *this;
	}
	VectorIterator& operator ++(int)
	{
		VectorIterator iterator = *this;
		++(*this);
		return iterator;
	}
	VectorIterator& operator --(int)
	{
		VectorIterator iterator = *this;
		--(*this);
		return iterator;
	}
	ReferenceType operator [](int index)
	{
		return *(m_Ptr + index);
	}
	PointerType operator ->()
	{
		return m_Ptr;
	}
	ReferenceType operator *()
	{
		return *m_Ptr;
	}
	bool operator ==(const VectorIterator& other) const
	{
		return m_Ptr == other.m_Ptr;
	}
	bool operator !=(const VectorIterator& other) const
	{
		return !(*this == other);
	}
private:
	PointerType m_Ptr;
};

template <typename T>
class TVector
{
private:
	T* m_data;
	size_t m_size = 0;
	size_t m_capacity = 0;
	void Allocate(size_t memory);
public:
	using ValueType = T;
	using Iterator = VectorIterator<TVector<T>>;
public:
	TVector();	
	void PushBack(T& data);
	void PushBack(T&& data);
	void PopBack();
	inline size_t Size();
	void Clear();
	Iterator begin();
	Iterator end();
	T& Front();
	T& Back();
	T& At(size_t index);
	~TVector();
	
	template <typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_size >= m_capacity)
		{
			Allocate(m_capacity + m_capacity / 2);
		}
		new (&m_data[m_size++]) T(std::forward<Args>(args)...);
		return m_data[m_size];
	}

	T& operator[](size_t index)
	{
		return m_data[index];
	}

	void Print()
	{
		cout << "===========================" << endl;
		for (size_t i = 0; i < m_size; ++i)
		{
			cout << m_data[i] << endl;
		}
		cout << "===========================" << endl;
	}
};

template <typename T>
TVector<T>::TVector()
{
	Allocate(3);
}


template <typename T>
void TVector<T>::Allocate(size_t newCapacity)
{
	T* new_data = (T*)::operator new (newCapacity * sizeof(T));
	for (size_t i = 0; i < m_size; ++i)
	{
		new_data[i] = std::move(m_data[i]);
	}
	::operator delete(m_data, m_capacity * sizeof(T));
	m_data = new_data;
	m_capacity = newCapacity;
}

template <typename T>
void TVector<T>::PushBack(T& data)
{
	if (m_size >= m_capacity)
	{
		Allocate(m_capacity + m_capacity / 2);
	}
	m_data[m_size++] = data;
}

template <typename T>
void TVector<T>::PushBack(T&& data)
{
	if (m_size >= m_capacity)
	{
		Allocate(m_capacity + m_capacity / 2);
	}
	m_data[m_size++] = std::move(data);
}

template <typename T>
void TVector<T>::PopBack()
{
	m_data[--m_size].~T();
}

template <typename T>
inline size_t TVector<T>::Size()
{
	return m_size;
}

template <typename T>
void TVector<T>::Clear()
{
	for (size_t i = 0; i < m_size; i++)
	{
		m_data[i].~T();
		m_size = 0;
	}
}

template <typename T>
TVector<T>::~TVector()
{
	Clear();
	::operator delete(m_data, m_capacity * sizeof(T));
}

template <typename T>
typename TVector<T>::Iterator TVector<T>::begin()
{
	return Iterator(m_data);
}

template <typename T>
typename TVector<T>::Iterator TVector<T>::end()
{
	return Iterator(m_data + m_size);
}

template <typename T>
T& TVector<T>::Front()
{
	//return *m_data;
	return *this->begin();
}

template <typename T>
T& TVector<T>::Back()
{
	return *--this->end();
}

template <typename T>
T& TVector<T>::At(size_t index)
{
	return m_data[index];
}