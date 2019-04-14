#pragma once

template <class T>
class CMyStack
{
	T *buff;
	size_t len;
	size_t maxSize;
public:
	CMyStack();
	~CMyStack();
	void clear();
public:
	void push(T const& elem);
	void pop();
public:
	bool empty() const { return len == 0; }
	T const& GetTop() const { return buff[len - 1]; }
};

template <class T>
void CMyStack<T>::pop()
{
	len--;
}

template <class T>
void CMyStack<T>::push(T const& elem)
{
	if (len >= maxSize)
	{
		maxSize = maxSize + ((maxSize >> 1) > 1 ? (maxSize >> 1) : 1);
		T *tempBuff = new T[maxSize];
		memmove(tempBuff, buff, sizeof(T)* len);
		if (buff)
			delete[] buff;
		buff = tempBuff;
	}
	buff[len++] = elem;
}

template <class T>
void CMyStack<T>::clear()
{
	if (buff)
		delete[] buff;
	buff = NULL;
	len = maxSize = 0;
}

template <class T>
CMyStack<T>::~CMyStack()
{
	clear();
}

template <class T>
CMyStack<T>::CMyStack()
{
	buff = NULL;
	len = maxSize = 0;
}
