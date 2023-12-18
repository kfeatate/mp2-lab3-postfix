#pragma once
#include <iostream>

const int MAX_STACK_SIZE = 100000000;

template <typename T>
class Stack {
private:
	T* begin; 
	T* end; 
	size_t sz; 
public:
	Stack() {
		sz = 1;
		begin = new T[sz];
		end = begin;
	}
	Stack(size_t _sz);
	Stack(const Stack& st);
	~Stack() {
		if (begin != NULL)
			delete[] begin;
	}
	void push(T elem);
	T top();
	void pop();
	bool empty();
	int size();
	bool operator==(const Stack& st);
	bool operator!=(const Stack& st);
	Stack<T>& operator=(const Stack& st);
	friend std::ostream& operator<<(std::ostream& ostr, const Stack<T>& st) {
		T* p = begin;
		int i = 0;
		while (p < end) {
			ostr << st.begin[i] << " ";
			p++;
			i++;
		}
		return ostr;
	}
};

template <typename T>
Stack<T>::Stack(size_t _sz) {
	if (sz = 0 || sz < 0) {
		throw "size < 0 or size = 0";
	}
	sz = _sz;
	begin = new T[sz];
	end = begin; 
}

template <typename T>
Stack<T>::Stack(const Stack& st) {
	sz = st.sz;
	begin = new T[sz];
	T* p = st.begin;
	int i = 0;
	while (p < st.end) {
		begin[i] = *p;
		i++;
		p++;
	}
	end = &begin[i];
}

template <typename T>
void Stack<T> ::push(T elem) {
	if (sz == (end - begin)) {
		T* tmp = new T[sz * 2];
		for (int i = 0; i < sz; i++) {
			tmp[i] = begin[i];
		}
		T* tmp1 = begin;
		begin = tmp;
		int k = sz;
		end = &begin[k];
		sz = sz * 2;
		delete[] tmp1;
	}
	*end = elem;
	end++;
}

template <typename T>
bool Stack<T>::empty() {
	if (end == begin) {
		return 1;
	}
	return 0;
}

template <typename T>
T Stack<T>::top() {
	if (empty()) {
		throw "stack is empty";
	}
	T* p = end;
	p--;
	return *p;
}

template <typename T>
void Stack<T>::pop() {
	if (empty()) {
		throw "stack is empty";
	}
	T* bufer = new T[sz];
	T* p = begin;
	T* p1 = end;
	p1--;
	int i = 0;
	while (p < p1) {
		bufer[i] = *p;
		p++;
		i++;
	}
	p = begin;
	begin = bufer;
	end = &bufer[i];
	delete[] p;
}

template <typename T>
int Stack<T>::size() {
	return sz;
}

template <typename T>
bool Stack<T>::operator==(const Stack& st) {
	if (sz != st.sz) {
		return false;
	}
	if ((end - begin) != (st.end - st.begin))  {
		return false;
	}
	T* p = begin;
	int i = 0;
	while( p < end ) {
		if (begin[i] != st.begin[i]) {
			return false;
		}
		p++;
		i++;
	}
	return true;
}

template <typename T>
bool Stack<T>::operator!=(const Stack& st) {
	if (sz != st.sz) {
		return true;
	}
	if ((end - begin) != (st.end - st.begin)) {
		return true;
	}
	T* p = begin;
	int i = 0;
	while ( p < end ) {
		if (begin[i] != st.begin[i]) {
			return true;
		}
		p++;
		i++;
	}
	return false;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& st) {
	if (this == &st) {
		return *this;
	}
	if (sz != st.sz) {
		sz = st.sz;
		T p = new T[st.sz];
		T* p1 = begin;
		begin = p;
		delete[] p1;
	}
	int i = 0;
	T* p = st.begin;
	while (p < st.end) {
		begin[i] = st.begin[i];
		i++;
		p++;
	}
	end = &begin[i];
}
