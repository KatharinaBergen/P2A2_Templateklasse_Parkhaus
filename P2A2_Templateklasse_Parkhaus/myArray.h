/*
	Author: Kat Bergen

	Template class enables the innitialization of objects stored in an array of elements of type T

	v1 06.12.2020
*/

#ifndef MYARRAY_H
#define MYARRAY_H

#include <exception>
#include <iostream>
using std::cout;

template<class T, int N> class MyArray
{
public:
	// Standardkonstruktor, Kopierkonstruktor, Kopierzuweisung:
	// erstmal die generierte Funktionalitaet verwenden
	MyArray() : MyArray{ T{} }
	{ }

	MyArray(const T& t)
	{
		for (int i{}; i < N; ++i) elem[i] = t;
	}

	explicit MyArray(T t) : elem{}
	{
		for (int i{}; i < N; ++i) elem[i] = t;
	}


	MyArray(const MyArray<T, N>& r)
	{
		delete[] elem; //ADDED
		*this = r;
	}


	MyArray(std::initializer_list<T> in)
	{ 
		std::copy(in.begin(), in.end(), elem); 
	}


	MyArray& operator=(const MyArray<T, N>& r)
	{
		if (this == &r) return *this;
		for (int i{}; i < N; ++i) elem[i] = r.elem[i];
		return *this;
	}

	T& operator[](int n) {
		return elem[n];
	}
	const T& operator[](int n) const //Zugriff
	{
		return operator[](n);
	}

	T& at(int n) {
		if (n < 0 || N <= n) throw std::out_of_range{ "bad index" };
		return elem[n];
	}

	T* data(int n) {
		return &(elem[n]);
	}
	const T* data(int n) const // Zeiger auf ein Element
	{
		return data(n);
	} 

	int size() const { return N; }

	void fill(const T& val) { //CHANGED! FOLIE 41
		for (unsigned int i{}; i < N; ++i) elem[i] = val;
	}

	void printall()
	{
		for (unsigned int i{}; i < N; i++)
		{
			cout << this->at(i) << ", ";
		}
	}


private:
	T elem[N];
};

#endif // !MYARRAY_H