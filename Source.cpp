#include <iostream>
#include <memory>
#include "MyString.h"
#include <vector>
#include <algorithm>


using namespace std;

//Phan Nhật Vinh
//1712914 - 17CTT7
//Thư viện MyString (dựa theo thư viện string chuẩn C++11)
//Nguồn tham khảo: http://www.cplusplus.com/reference/string/string/


//Member functions

MyString::MyString()
{
	Data = new char[MyString::_STRING_SIZE];
	reservedSize = MyString::_STRING_SIZE;
	len = 0;
	this->Data[len] = '\0';
}

MyString::MyString(const MyString& String)
{
	this->len = String.len;
	this->Data = new char[String.reservedSize];
	this->reservedSize = String.reservedSize;
	for (int i = 0; i < len; i++)
	{
		this->Data[i] = String.Data[i];
	}
	this->Data[len] = '\0';
}

MyString::MyString(const MyString& String, size_t viTri, size_t chieuDai)
{
	if (chieuDai == MyString::npos)
	{
		if (viTri < String.len)
		{
			this->len = String.len - viTri;
			this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
			this->Data = new char[this->reservedSize];
			int j = 0;
			for (int i = viTri; i < String.len; i++)
			{
				this->Data[j] = String.Data[i];
				j++;
			}
		}
		else if (viTri == String.len)
		{
			this->len = 0;
			this->reservedSize = MyString::_STRING_SIZE;
			this->Data = new char[reservedSize];
		}
		else
		{
			this->len = 0;
			this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
			this->Data = new char[this->reservedSize];
		}
	}
	else if (chieuDai != MyString::npos)
	{
		if (viTri == String.len)
		{
			this->len = 0;
			this->reservedSize = MyString::_STRING_SIZE;
			this->Data = new char[reservedSize];
		}
		else if (viTri + chieuDai <= String.len)
		{
			this->len = chieuDai;
			this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
			this->Data = new char[this->reservedSize];
			int j = viTri;
			for (int i = 0; i < this->len; i++)
			{
				this->Data[i] = String.Data[j];
				j++;
			}
		}
		else
		{
			if (viTri >= String.len)
			{
				abort();
			}
			if (chieuDai > String.len)
			{
				this->len = String.len - viTri;
				this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
				this->Data = new char[this->reservedSize];
				int j = viTri;
				for (int i = 0; i < this->len; i++)
				{
					this->Data[i] = String.Data[j];
					j++;
				}
			}
		}
	}
	this->Data[len] = '\0';
}

MyString::MyString(const char* data)
{
	int len = 0;
	while (data[len] != '\0')
	{
		len++;
	}
	this->len = len;
	this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
	Data = new char[reservedSize];
	for (int i = 0; i < len; i++)
	{
		Data[i] = data[i];
	}
	this->Data[len] = '\0';
}

MyString::MyString(const char* data, size_t soKiTu)
{
	int l = 0;
	int j = 0;
	while (data[j] != '\0')
	{
		l++;
		j++;
	}
	if (l >= soKiTu)
	{
		this->len = soKiTu;
		this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
		this->Data = new char[reservedSize];
		for (int i = 0; i < soKiTu; i++)
		{
			this->Data[i] = data[i];
		}
	}
	else
	{
		this->len = soKiTu;
		this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(soKiTu / (MyString::_STRING_SIZE + 1));
		this->Data = new char[reservedSize];
		int pos = 0;
		for (int i = 0; i < l; i++)
		{
			pos++;
			this->Data[i] = data[i];
		}
		this->Data[pos] = '\t';
		for (int i = pos + 1; i < soKiTu; i++)
		{
			this->Data[i] = '-';
		}
	}
	this->Data[len] = '\0';
}

MyString::MyString(size_t kichThuoc, char kiTu)
{
	this->len = kichThuoc;
	this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
	this->Data = new char[reservedSize];
	for (int i = 0; i < this->len; i++)
	{
		this->Data[i] = kiTu;
	}
	this->Data[len] = '\0';
}

template <class InputIterator>
MyString::MyString(InputIterator first, InputIterator last)
{
	InputIterator it;
	int l = 0;
	for (it = first; it != last; it++)
	{
		l++;
	}
	this->len = l;
	this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
	this->Data = new char[this->reservedSize];
	int pos = 0;
	for (it = first; it != last; it++)
	{
		this->Data[pos] = (*it);
		pos++;
	}
	this->Data[len] = '\0';
}

MyString::MyString(initializer_list<char> list)
{
	int l = 0;
	this->len = 0;
	this->reservedSize = MyString::_STRING_SIZE;
	this->Data = new char[this->reservedSize];
	initializer_list<char>::iterator it;
	for (it = list.begin(); it != list.end(); it++)
	{
		(*this) = (*this) + (*it);
	}
	this->Data[len] = '\0';
}

MyString::~MyString()
{
	reservedSize = MyString::_STRING_SIZE;
	len = 0;
	this->Data = new char[len];
}

MyString& MyString::operator=(const MyString& String)
{
	MyString tempString = (*this);
	if (tempString == String)
	{
		return *this;
	}
	this->len = String.len;
	this->reservedSize = String.reservedSize;
	this->Data = new char[this->reservedSize];
	for (int i = 0; i < this->len; i++)
	{
		this->Data[i] = String.Data[i];
	}
	this->Data[len] = '\0';
	return *this;
}

MyString& MyString:: operator =(const char* String)
{
	int j = 0;
	int l = 0;
	while (String[j] != '\0')
	{
		l++;
		j++;
	}
	this->len = l;
	if (l > this->capacity())
	{
		this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
	}
	this->Data = new char[this->reservedSize];
	for (int i = 0; i < this->len; i++)
	{
		this->Data[i] = String[i];
	}
	this->Data[len] = '\0';
	return *this;
}

MyString& MyString:: operator= (char kiTu)
{
	this->len = 1;
	this->Data = new char[this->reservedSize];
	this->Data[0] = kiTu;
	this->Data[len] = '\0';
	return *this;
}

MyString& MyString:: operator= (initializer_list<char> list)
{
	MyString tempString(list);
	*this = tempString;
	this->Data[len] = '\0';
	return *this;
}

//Capacity

size_t MyString::size() const
{
	return len;
}

size_t MyString::length() const
{
	return this->len;
}

size_t MyString::max_size() const
{
	return INT_MAX * 2;
}

void MyString::resize(size_t newSize)
{
	size_t temp;
	temp = this->len;
	this->len = newSize;
	this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
	this->Data = (char*)realloc(this->Data, reservedSize); 
	if (newSize > temp)
	{
		for (int i = temp - 1; i < this->len; i++)
		{
			this->Data[i] = '\0';
		}
	}
	this->Data[len] = '\0';
}

void MyString::resize(size_t newSize, char c)
{
	this->Data = (char*)realloc(this->Data, newSize);
	if (newSize > this->len)
	{
		int j = this->len;
		while (j<newSize)
		{
			Data[j] = c;
			j++;
		}
	}
	this->len = newSize;
	this->Data[len] = '\0';
}

size_t MyString::capacity() const
{
	return this->reservedSize;
}

void MyString::reserve(size_t size)
{
	if (this->len == 0)
	{
		if (size > this->reservedSize)
		{
			this->reservedSize = MyString::_STRING_SIZE + ((size / MyString::_STRING_SIZE))*(MyString::_STRING_SIZE + 1);
			this->Data = (char*)realloc(this->Data, this->reservedSize);
		}
		else
		{
			if (size <= MyString::_STRING_SIZE)
			{
				this->reservedSize = MyString::_STRING_SIZE;
				this->Data = (char*)realloc(this->Data, this->reservedSize);
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		if (size >= this->reservedSize)
		{
			this->reservedSize = MyString::_STRING_SIZE + (size / MyString::_STRING_SIZE)*(MyString::_STRING_SIZE + 1);
			this->Data = (char*)realloc(this->Data, this->reservedSize);
		}
		else
		{
			return;
		}
	}
}

void MyString::clear()
{
	this->len = 0;
	this->Data = NULL;
}

bool MyString::empty()
{
	if (this->begin() != '\0')
	{
		return true;
	}
	else return false;
}

void MyString::shrink_to_fit()
{
	this->reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(this->len / (MyString::_STRING_SIZE + 1));
	this->Data = (char*)realloc(this->Data, this->reservedSize);
}

//Elements Access

char& MyString:: operator [](size_t viTri)
{
	if (viTri == this->len - 1)
	{
		return this->Data[len];
	}
	if (viTri > this->len - 1)
	{
		out_of_range err("Out of range!\n");
		throw err;
	}
	return this->Data[viTri];
}

const char& MyString:: operator[] (size_t viTri) const
{
	if (viTri >= this->len - 1)
	{
		return this->Data[len];
	}
	return this->Data[viTri];
}

char& MyString::at(size_t viTri)
{
	if (viTri >= this->len)
	{
		out_of_range err("Out of range!\n");
		throw err;
	}
	else
	{
		return (this->Data[viTri]);
	}
}

const char& MyString::at(size_t viTri) const
{
	if (viTri >= this->len)
	{
		out_of_range err("Out of range!\n");
		throw err;
	}
	else
	{
		return (this->Data[viTri]);
	}
}

char& MyString::back()
{
	return this->Data[len - 1];
}

const char& MyString::back() const
{
	return this->Data[len - 1];
}

char& MyString::front()
{
	return this->Data[0];
}

const char& MyString::front() const
{
	return this->Data[0];
}

//Iterator các loại

MyString::iterator MyString::begin()
{
	return (Data);
}

MyString::iterator MyString::end()
{
	if (len == 0)
	{
		return this->begin();
	}
	return Data + len;
}

MyString::reverse_iterator MyString::rbegin()
{
	return reverse_iterator(this->end());
}

MyString::reverse_iterator MyString::rend()
{
	return reverse_iterator(this->begin());
}

MyString::const_iterator MyString::cbegin() const
{
	return (Data);
}

MyString::const_iterator MyString::cend() const
{
	return (Data + len);
}

MyString::const_reverse_iterator MyString::crbegin() const
{
	return reverse_iterator(this->cend());
}

MyString::const_reverse_iterator MyString::crend() const
{
	return reverse_iterator(this->cbegin());
}

//Modifiers

MyString MyString:: operator += (const MyString& String)
{
	*this = *this + String;
	return (*this);
}

MyString& MyString:: operator+= (const char* s)
{
	MyString tempString(s);
	*this = *this + tempString;
	return *this;
}

MyString& MyString:: operator+= (char c)
{
	*this = *this + c;
	return *this;
}

MyString& MyString:: operator+= (initializer_list<char> il)
{
	MyString tempString(il);
	*this = *this + tempString;
	return *this;
}

MyString& MyString::append(const MyString& String)
{
	(*this) += String;
	return *this;
}

MyString& MyString::append(const MyString& String, size_t viTri, size_t chieuDai)
{
	MyString tempString(String, viTri, chieuDai);
	(*this) += tempString;
	return *this;
}

MyString& MyString::append(const char* String)
{
	(*this) += String;
	return *this;
}

MyString& MyString::append(const char* String, size_t chieuDai)
{
	MyString tempString(String, chieuDai);
	(*this) += tempString;
	return *this;
}

MyString& MyString::append(size_t chieuDai, char kiTu)
{
	MyString tempString(chieuDai, kiTu);
	(*this) += tempString;
	return *this;
}

template <class InputIterator>
MyString& MyString::append(InputIterator first, InputIterator last)
{
	MyString tempString(first, last);
	(*this) += tempString;
	return *this;
}

MyString& MyString::append(initializer_list<char> list)
{
	MyString tempString(list);
	(*this) += tempString;
	return *this;
}

void MyString::push_back(char c)
{
	*this = *this + c;
}

MyString& MyString::assign(const MyString& String)
{
	(*this) = String;
	return *this;
}

MyString& MyString::assign(const MyString& String, size_t viTri, size_t chieuDai)
{
	MyString tempString(String, viTri, chieuDai);
	(*this) = tempString;
	return *this;
}

MyString& MyString::assign(const char* String)
{
	(*this) = String;
	return *this;
}

MyString& MyString::assign(const char* String, size_t chieuDai)
{
	MyString tempString(String, chieuDai);
	(*this) = tempString;
	return *this;
}

MyString& MyString::assign(size_t chieuDai, char kiTu)
{
	MyString tempString(chieuDai, kiTu);
	(*this) = tempString;
	return *this;
}

template <class InputIterator>
MyString& MyString::assign(InputIterator first, InputIterator last)
{
	MyString tempString(first, last);
	(*this) = tempString;
	return *this;
}

MyString& MyString::assign(initializer_list<char> list)
{
	MyString tempString(list);
	(*this) = tempString;
	return *this;
}

MyString& MyString::insert(size_t viTri, const MyString& String)
{
	if (viTri > this->len)
	{
		abort();
	}
	MyString firstPart(*this, 0, viTri);
	MyString lastPart(*this, viTri);
	MyString tempString = firstPart + String + lastPart;
	*this = tempString;
	return *this;
}

MyString& MyString::insert(size_t viTri, const MyString& String, size_t viTriChuoiCon, size_t chieuDaiChuoiCon)
{
	if (viTri > this->len)
	{
		abort();
	}
	MyString firstPart(*this, 0, viTri);
	MyString lastPart(*this, viTri);
	MyString tempString(String, viTriChuoiCon, chieuDaiChuoiCon);
	*this = firstPart + tempString + lastPart;
	return *this;
}

MyString& MyString::insert(size_t viTri, const char* String)
{
	if (viTri > this->len)
	{
		abort();
	}
	MyString firstPart(*this, 0, viTri);
	MyString lastPart(*this, viTri);
	MyString tempString(String);
	*this = firstPart + tempString + lastPart;
	return *this;
}

MyString& MyString::insert(size_t viTri, const char* String, size_t chieuDai)
{
	if (viTri > this->len)
	{
		abort();
	}
	MyString firstPart(*this, 0, viTri);
	MyString lastPart(*this, viTri);
	MyString tempString(String, chieuDai);
	*this = firstPart + tempString + lastPart;
	return *this;
}

MyString& MyString::insert(size_t viTri, size_t chieuDai, char kiTu)
{
	if (viTri > this->len)
	{
		abort();
	}
	MyString firstPart(*this, 0, viTri);
	MyString lastPart(*this, viTri);
	MyString tempString(chieuDai, kiTu);
	*this = firstPart + tempString + lastPart;
	return *this;
}

MyString::iterator MyString::insert(iterator it, size_t kichThuoc, char kiTu)
{
	int l = 0;
	MyString::iterator tempIT = this->begin();
	while (tempIT != it)
	{
		l++;
		tempIT++;
	}
	MyString temp(*this, 0, l);
	MyString tempString(kichThuoc, kiTu);
	while (it != this->end())
	{
		tempString = tempString + *it;
		it++;
	}
	*this = temp + tempString;
	return this->begin() + l;
}

MyString::iterator MyString::insert(iterator it, char kiTu)
{
	int l = 0;
	MyString::iterator tempIT = this->begin();
	while (tempIT != it)
	{
		l++;
		tempIT++;
	}
	MyString temp(*this, 0, l);
	MyString tempString;
	tempString = tempString + kiTu;
	while (it != this->end())
	{
		tempString = tempString + *it;
		it++;
	}
	*this = temp + tempString;
	return this->begin() + l;
}

template <class InputIterator>
MyString::iterator MyString::insert(iterator it, InputIterator first, InputIterator last)
{
	int l = 0;
	MyString::iterator tempIT = this->begin();
	while (tempIT != it)
	{
		l++;
		tempIT++;
	}
	MyString temp(*this, 0, l);
	MyString tempString(first, last);
	while (it != this->end())
	{
		tempString = tempString + *it;
		it++;
	}
	*this = temp + tempString;
	return this->begin() + l;
}

MyString& MyString::insert(iterator it, initializer_list<char> list)
{
	int l = 0;
	MyString::iterator tempIT = this->begin();
	while (tempIT != it)
	{
		l++;
		tempIT++;
	}
	MyString temp(*this, 0, l);
	MyString tempString(list);
	while (it != this->end())
	{
		tempString = tempString + *it;
		it++;
	}
	*this = temp + tempString;
	return (*this);
}

MyString& MyString::erase(size_t viTri = 0, size_t chieuDai = npos)
{
	if (viTri == 0 && chieuDai == npos)
	{
		this->clear();
	}
	else
	{
		if (viTri + chieuDai < this->len)
		{
			MyString firstPart(*this, 0, viTri);
			MyString lastPart(*this, viTri + chieuDai);
			*this = firstPart + lastPart;
		}
		else
		{
			MyString firstPart(*this, 0, viTri);
			*this = firstPart;
		}
	}
	return *this;
}

MyString::iterator MyString::erase(iterator it)
{
	int l = 0;
	MyString::iterator tempIT = this->begin();
	while (tempIT != it)
	{
		l++;
		tempIT++;
	}
	MyString temp(*this, 0, l);
	MyString temp2(*this, l + 1);
	*this = temp + temp2;
	return this->begin() + l;
}

MyString::iterator MyString::erase(iterator first, iterator last)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	*this = tempString1 + tempString2;
	return this->begin() + left;
}

MyString& MyString::replace(size_t viTri, size_t chieuDai, const MyString& String)
{
	MyString tempString1(*this, 0, viTri);
	MyString tempString2(*this, viTri + chieuDai);
	*this = tempString1 + String + tempString2;
	return *this;
}

MyString& MyString::replace(iterator first, iterator last, const MyString& String)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	*this = tempString1 + String + tempString2;
	return *this;
}

MyString& MyString::replace(size_t viTri, size_t chieuDai, const MyString& String, size_t viTriChuoiCon, size_t chieuDaiChuoiCon)
{

	MyString tempString1(*this, 0, viTri);
	MyString tempString2(*this, viTri + chieuDai);
	MyString temp(String, viTriChuoiCon, chieuDaiChuoiCon);
	*this = tempString1 + temp + tempString2;
	return *this;
}

MyString& MyString::replace(size_t viTri, size_t chieuDai, const char* String)
{
	MyString tempString1(*this, 0, viTri);
	MyString tempString2(*this, viTri + chieuDai);
	*this = tempString1 + String + tempString2;
	return *this;
}

MyString& MyString::replace(iterator first, iterator last, const char* String)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	*this = tempString1 + String + tempString2;
	return *this;
}

MyString& MyString::replace(size_t viTri, size_t chieuDai, const char* String, size_t n)
{
	MyString tempString1(*this, 0, viTri);
	MyString tempString2(*this, viTri + chieuDai);
	MyString temp(String, n);
	*this = tempString1 + temp + tempString2;
	return *this;
}

MyString& MyString::replace(iterator first, iterator last, const char* String, size_t n)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	MyString tempS(String, n);
	*this = tempString1 + tempS + tempString2;
	return *this;
}

MyString& MyString::replace(size_t viTri, size_t chieuDai, size_t n, char kiTu)
{
	MyString tempString1(*this, 0, viTri);
	MyString tempString2(*this, viTri + chieuDai);
	MyString temp(n, kiTu);
	*this = tempString1 + temp + tempString2;
	return *this;
}

MyString& MyString::replace(iterator first, iterator last, size_t n, char kiTu)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	MyString tempS(n, kiTu);
	*this = tempString1 + tempS + tempString2;
	return *this;
}

template <class InputIterator>
MyString& MyString::replace(iterator first, iterator last, InputIterator i1, InputIterator i2)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	MyString tempS(i1, i2);
	*this = tempString1 + tempS + tempString2;
	return *this;
}

MyString& MyString::replace(iterator first, iterator last, initializer_list<char> list)
{
	int left = 0;
	int right = 0;
	int temp = 0;
	MyString::iterator it = this->begin();
	while (it != last)
	{
		if (it == first)
		{
			left = temp;
		}
		temp++;
		it++;
	}
	right = temp;
	MyString tempString1(*this, 0, left);
	MyString tempString2(*this, right);
	MyString tempS(list);
	*this = tempString1 + tempS + tempString2;
	return *this;
}

void MyString::swap(MyString& String)
{
	MyString temp(String);
	String = *this;
	*this = temp;
}

void MyString::pop_back()
{
	MyString temp(*this, 0, this->len - 1);
	*this = temp;
}

//String Operations

const char* MyString::c_str() const
{
	return (*this).Data;
}

const char* MyString::data() const
{
	return this->Data;
}

size_t MyString::copy(char* String, size_t chieuDai, size_t viTri) const
{
	if (viTri == 0)
	{

		if (chieuDai <= this->len)
		{
			for (int i = 0; i < chieuDai; i++)
			{
				String[i] = this->Data[i];
			}
			return chieuDai;
		}
		else
		{
			for (int i = 0; i < this->len; i++)
			{
				String[i] = this->Data[i];
			}
			return this->len;
		}
	}
	else
	{
		if (viTri + chieuDai < this->len)
		{
			int j = 0;
			for (int i = viTri; i < viTri + chieuDai; i++)
			{
				String[j] = this->Data[i];
				j++;
			}
			return j;
		}
		else
		{
			int j = 0;
			for (int i = viTri; i < this->len; i++)
			{
				String[j] = this->Data[i];
				j++;
			}
			return j;
		}
	}
}

size_t MyString::find(const MyString& String, size_t viTri) const
{
	if (String.len > this->len)
	{
		return npos;
	}
	if (viTri == 0)
	{
		int count = this->len - String.len + 1;
		for (int i = 0; i < count; i++)
		{
			MyString compString(*this, i, String.len);
			if (compString == String)
			{
				return i;
			}
		}
		return npos;
	}
	else
	{
		if (viTri >= this->len)
		{
			return npos;
		}
		int count = this->len - viTri - 1;
		for (int i = viTri; i < count; i++)
		{
			MyString compString(*this, i, String.len);
			if (compString == String)
			{
				return i;
			}
		}
		return npos;
	}
}

size_t MyString::find(const char* String, size_t viTri) const
{
	int j = 0;
	int l = 0;
	while (String[j] != '\0')
	{
		j++;
		l++;
	}
	if (viTri == 0)
	{
		int count = this->len - l + 1;
		for (int i = 0; i < count; i++)
		{
			MyString compString(*this, i, l);
			if (compString == String)
			{
				return i;
			}
		}
		return npos;
	}
	else
	{
		if (viTri >= this->len)
		{
			return npos;
		}
		int count = this->len - viTri - 1;
		for (int i = viTri; i < count; i++)
		{
			MyString compString(*this, i, l);
			if (compString == String)
			{
				return i;
			}
		}
		return npos;
	}
}

size_t MyString::find(const char* String, size_t viTri, size_t soKiTu) const
{
	MyString temp(String, soKiTu);
	int result = this->find(temp, viTri);
	return result;
}

size_t MyString::find(char kiTu, size_t viTri) const
{
	MyString temp(1, kiTu);
	size_t result = this->find(temp, viTri);
	return result;
}

size_t MyString::rfind(const MyString& String, size_t viTri) const
{
	if (viTri == npos)
	{
		int startPos = this->len - String.len;
		for (int i = startPos; i >= 0; i--)
		{
			MyString compString(*this, i, String.len);
			if (compString == String)
			{
				return i;
			}
		}
		return npos;
	}
	else
	{
		if (viTri >= this->len)
		{
			return npos;
		}
		for (int i = this->len - String.len; i >= viTri; i--)
		{
			MyString compString(*this, i, String.len);
			if (compString == String)
			{
				return i;
			}
		}
		return npos;
	}
}

size_t MyString::rfind(const char* String, size_t viTri) const
{
	MyString tempString(String);
	return this->rfind(tempString, viTri);
}

size_t MyString::rfind(const char* String, size_t viTri, size_t soKiTu) const
{
	MyString tempString(String, soKiTu);
	return this->rfind(tempString, viTri);
}

size_t MyString::rfind(char kiTu, size_t viTri) const
{
	MyString tempString(1, kiTu);
	return this->rfind(tempString, viTri);
}

size_t MyString::find_first_of(const MyString& String, size_t viTri) const
{
	vector <size_t> pos;
	for (int i = 0; i < String.len; i++)
	{
		char kiTu = String.Data[i];
		int result = this->find(kiTu, viTri);
		if (result != npos)
		{
			pos.push_back(result);
		}
	}
	if (pos.empty() == 0)
	{
		return *std::min_element(pos.begin(), pos.end());
	}
	else
	{
		return npos;
	}
}

size_t MyString::find_first_of(const char* String, size_t viTri) const
{
	MyString thisString(String);
	return this->find_first_of(thisString, viTri);
}

size_t MyString::find_first_of(const char* String, size_t viTri, size_t soKiTu) const
{
	MyString thisString(String, soKiTu);
	return this->find_first_of(thisString, viTri);
}

size_t MyString::find_first_of(char kiTu, size_t viTri) const
{
	return this->find(kiTu, viTri);
}

size_t MyString::find_last_of(const MyString& String, size_t viTri) const
{
	vector <size_t> pos;
	for (int i = 0; i < String.len; i++)
	{
		char kiTu = String.Data[i];
		int result = this->rfind(kiTu, viTri);
		if (result != npos)
		{
			pos.push_back(result);
		}
	}
	if (pos.empty() == 0)
	{
		return *std::max_element(pos.begin(), pos.end());
	}
	else
	{
		return npos;
	}
}

size_t MyString::find_last_of(const char* String, size_t viTri) const
{
	MyString tempString(String);
	return this->find_last_of(tempString, viTri);
}

size_t MyString::find_last_of(const char* String, size_t viTri, size_t soKiTu) const
{
	MyString tempString(String, soKiTu);
	return this->find_last_of(tempString, viTri);
}

size_t MyString::find_last_of(char kiTu, size_t viTri) const
{
	MyString tempString(1, kiTu);
	return this->find_last_of(tempString, viTri);
}

size_t MyString::find_first_not_of(const MyString& String, size_t viTri) const
{
	vector <size_t> pos;
	if (viTri >= this->len)
	{
		return npos;
	}
	for (int i = viTri; i < this->len; i++)
	{
		char kiTu = this->Data[i];
		int result = String.find(kiTu);
		if (result == npos)
		{
			pos.push_back(i);
		}
	}
	if (pos.empty() == 0)
	{
		return *std::min_element(pos.begin(), pos.end());
	}
	else
	{
		return npos;
	}
}

size_t MyString::find_first_not_of(const char* String, size_t viTri) const
{
	MyString tempString(String);
	return this->find_first_not_of(tempString, viTri);
}

size_t MyString::find_first_not_of(const char* String, size_t viTri, size_t soKiTu) const
{
	MyString tempString(String, soKiTu);
	return this->find_first_not_of(tempString, viTri);
}

size_t MyString::find_first_not_of(char kiTu, size_t viTri) const
{
	MyString tempString(1, kiTu);
	return this->find_first_not_of(tempString, viTri);
}

size_t MyString::find_last_not_of(const MyString& String, size_t viTri) const
{
	vector <size_t> pos;
	if (viTri == npos)
	{
		for (int i = 0; i < this->len; i++)
		{
			char kiTu = this->Data[i];
			int result = String.find(kiTu);
			if (result == npos)
			{
				pos.push_back(i);
			}
		}
	}
	else
	{
		for (int i = viTri; i < this->len; i++)
		{
			char kiTu = this->Data[i];
			int result = String.find(kiTu);
			if (result == npos)
			{
				pos.push_back(i);
			}
		}
	}
	if (pos.empty() == 0)
	{
		return *std::max_element(pos.begin(), pos.end());
	}
	else
	{
		return npos;
	}
}

size_t MyString::find_last_not_of(const char* String, size_t viTri) const
{
	MyString tempString(String);
	return this->find_last_not_of(tempString, viTri);
}

size_t MyString::find_last_not_of(const char* String, size_t viTri, size_t soKiTu) const
{
	MyString tempString(String, soKiTu);
	return this->find_last_not_of(tempString, viTri);
}

size_t MyString::find_last_not_of(char kiTu, size_t viTri) const
{
	MyString tempString(1, kiTu);
	return this->find_last_not_of(tempString, viTri);
}

MyString MyString::substr(size_t viTri, size_t chieuDai) const
{
	if (viTri == this->len)
	{
		MyString tempString;
		return tempString;
	}
	if (viTri > this->len)
	{
		out_of_range err("Out of range!\n");
		throw err;
	}
	MyString tempString(*this, viTri, chieuDai);
	return tempString;
}

int MyString::compare(const MyString& String) const
{
	if (*this == String)
	{
		return 0;
	}
	if (*this < String)
	{
		return -1;
	}
	if (*this> String)
	{
		return 1;
	}
}

int MyString::compare(size_t viTri, size_t chieuDai, const MyString& String) const
{
	if (viTri > this->len)
	{
		out_of_range err("Out of range!\n");
		throw err;
	}
	MyString comparedString(*this, viTri, chieuDai);
	return comparedString.compare(String);

}

int MyString::compare(size_t viTri, size_t chieuDai, const MyString& String, size_t viTriChuoiCon, size_t chieuDaiChuoiCon) const
{
	if (viTri >= this->len || viTriChuoiCon >= String.len)
	{
		out_of_range err("Out of range!\n");
		throw err;
	}
	MyString comparedString(*this, viTri, chieuDai);
	MyString comparingString(String, viTriChuoiCon, chieuDaiChuoiCon);
	return comparedString.compare(comparingString);
}

int MyString::compare(const char* String) const
{
	MyString comparingString(String);
	return this->compare(comparingString);
}

int MyString::compare(size_t viTri, size_t chieuDai, const char* String) const
{
	MyString comparedString(*this, viTri, chieuDai);
	return comparedString.compare(String);
}

int MyString::compare(size_t viTri, size_t chieuDai, const char* String, size_t soKiTu) const
{
	MyString comparedString(*this, viTri, chieuDai);
	MyString comparingString(String, soKiTu);
	return comparedString.compare(comparingString);
}

////Non-member function overloads

MyString operator + (const MyString& String1, const MyString& String2)
{
	MyString tempString;
	tempString.len = String1.len + String2.len;
	tempString.reservedSize = tempString._STRING_SIZE + (tempString._STRING_SIZE + 1)*(tempString.len / (tempString._STRING_SIZE + 1));
	tempString.Data = new char[tempString.reservedSize];
	int tempPos = 0;
	for (int i = 0; i < String1.len; i++)
	{
		tempString.Data[i] = String1.Data[i];
		tempPos = i;
	}
	tempPos++;
	if (String1.len == 0)
	{
		tempPos = 0;
	}
	for (int i = 0; i < String2.len; i++)
	{
		tempString.Data[tempPos] = String2.Data[i];
		tempPos++;
	}
	tempString.Data[tempString.len] = '\0';
	return tempString;
}

MyString operator+ (const MyString& trai, const char*  phai)
{
	int l = 0;
	int j = 0;
	MyString tempString;
	while (phai[j] != '\0')
	{
		j++;
		l++;
	}
	tempString.len = trai.len + l;
	tempString.reservedSize = tempString._STRING_SIZE + (tempString._STRING_SIZE + 1)*(tempString.len / (tempString._STRING_SIZE + 1));
	tempString.Data = new char[tempString.reservedSize];
	int k = 0;
	for (int i = 0; i < trai.len; i++)
	{
		tempString.Data[i] = trai.Data[i];
		k++;
	}
	for (int i = 0; i < l; i++)
	{
		tempString.Data[k] = phai[i];
		k++;
	}
	tempString.Data[tempString.len] = '\0';
	return tempString;
}

MyString operator+ (const char*   trai, const MyString& phai)
{
	MyString tempString(trai);
	int k = 0;
	tempString += phai;
	tempString.Data[tempString.len] = '\0';
	return tempString;
}

MyString operator+ (const MyString& trai, char          phai)
{
	MyString tempString(trai);
	tempString.len += 1;
	tempString.reservedSize = tempString._STRING_SIZE + (tempString._STRING_SIZE + 1)*(tempString.len / (tempString._STRING_SIZE + 1));
	tempString.Data = (char*)realloc(tempString.Data, tempString.reservedSize);
	tempString.Data[tempString.len - 1] = phai;
	tempString.Data[tempString.len] = '\0';
	return tempString;
}

MyString operator+ (char          trai, const MyString& phai)
{
	MyString tempString(1, trai);
	tempString += phai;
	tempString.Data[tempString.len] = '\0';
	return tempString;
}

bool operator ==(const MyString& String1, const MyString& String2)
{
	if (String1.len<String2.len || String1.len > String2.len)
	{
		return false;
	}
	for (int i = 0; i < String1.len; i++)
	{
		if (String1.Data[i] != String2.Data[i])
		{
			return false;
		}
	}
	return true;
}

bool operator ==(const char* String1, const MyString& String2)
{
	MyString tempString1(String1);
	return tempString1 == String2;
}

bool operator ==(const MyString& String1, const char* String2)
{
	MyString tempString2(String2);
	return String1 == tempString2;
}

bool  operator !=(const MyString& String1, const MyString& String2)
{
	return !(String1 == String2);
}

bool operator !=(const char* String1, const MyString& String2)
{
	MyString tempString1(String1);
	return tempString1 != String2;
}

bool operator !=(const MyString& String1, const char* String2)
{
	MyString tempString2(String2);
	return String1 != tempString2;
}

bool  operator <=(const MyString& String1, const MyString& String2)
{
	int maxLen = max(String1.len, String2.len);
	for (int i = 0; i < maxLen; i++)
	{

		if (String1.Data[i]>String2.Data[i])
		{
			return false;
		}
		if (String1.Data[i] <= String2.Data[i])
		{
			return true;
		}
	}
	return false;
}

bool operator <=(const char* String1, const MyString& String2)
{
	MyString tempString1(String1);
	return tempString1 <= String2;
}

bool operator <=(const MyString& String1, const char* String2)
{
	MyString tempString2(String2);
	return String1 <= tempString2;
}

bool  operator >=(const MyString& String1, const MyString& String2)
{
	if (String1 > String2 || String1 == String2)
	{
		return true;
	}
	return false;
}

bool operator >=(const char* String1, const MyString& String2)
{
	MyString tempString1(String1);
	return tempString1 >= String2;
}

bool operator >=(const MyString& String1, const char* String2)
{
	MyString tempString2(String2);
	return String1 >= tempString2;
}

bool  operator <(const MyString& String1, const MyString& String2)
{
	return !(String1 >= String2);
}

bool operator <(const char* String1, const MyString& String2)
{
	MyString tempString1(String1);
	return tempString1 < String2;
}

bool operator <(const MyString& String1, const char* String2)
{
	MyString tempString2(String2);
	return String1 < tempString2;
}

bool  operator >(const MyString& String1, const MyString& String2)
{
	return !(String1 <= String2);
}

bool operator >(const char* String1, const MyString& String2)
{
	MyString tempString1(String1);
	return tempString1 > String2;
}

bool operator >(const MyString& String1, const char* String2)
{
	MyString tempString2(String2);
	return String1 > tempString2;
}

void swap(MyString& a, MyString& b)
{
	MyString temp = a;
	a = b;
	b = temp;
}

istream& getline(istream& is, MyString& String, char delim)
{
	char* tempString = new char;
	is.getline(tempString, MyString::npos, delim);
	int i = 0;
	int l = 0;
	while (tempString[i] != '\0')
	{
		i++;
		l++;
	}
	String.len = l;
	String.reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(String.len / (MyString::_STRING_SIZE + 1));
	String.Data = new char[String.reservedSize];
	for (int i = 0; i < l; i++)
	{
		String.Data[i] = tempString[i];
	}
	String.Data[String.len] = '\0';
	return is;
}

istream& getline(istream& is, MyString& String)
{
	char* tempString = new char;
	is.getline(tempString, MyString::npos);
	int i = 0;
	int l = 0;
	while (tempString[i] != '\0')
	{
		i++;
		l++;
	}
	String.len = l;
	String.reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(String.len / (MyString::_STRING_SIZE + 1));
	String.Data = new char[String.reservedSize];
	for (int i = 0; i < l; i++)
	{
		String.Data[i] = tempString[i];
	}
	String.Data[String.len] = '\0';
	return is;
}

istream& operator >> (istream& is, MyString& String)
{
	char* temp = new char;
	is >> temp;
	int l = 0;
	int j = 0;
	while (temp[j] != '\0')
	{
		j++;
		l++;
	}
	String.len = l;
	String.reservedSize = MyString::_STRING_SIZE + (MyString::_STRING_SIZE + 1)*(String.len / (MyString::_STRING_SIZE + 1));
	String.Data = new char[String.reservedSize];
	for (int i = 0; i < l; i++)
	{
		String.Data[i] = temp[i];
	}
	String.Data[String.len] = '\0';
	return is;
}

ostream& operator <<(ostream& os, const MyString& String)
{
	for (int i = 0; i < String.len; i++)
	{
		os << String.Data[i];
	}
	return os;
}

void main()
{
	{
		system("cls");
		cout << "  _______________________________________________________________\n";
		cout << " |                                                               |\n";
		cout << " |	   PHAN NHAT VINH - 1712914   -    MYSTRING CLASS        |\n";
		cout << " |             **********************************                |\n";
		cout << " |                                                               |\n";
		cout << " |                1/ Member functions                            |\n";
		cout << " |                2/ Iterators Methods                           |\n";
		cout << " |                3/ Capacity Methods                            |\n";
		cout << " |                4/ Element Access Methods                      |\n";
		cout << " |                5/ Modifiers                                   |\n";
		cout << " |                6/ String Operation Methods                    |\n";
		cout << " |                7/ Non-member Function Overloads               |\n";
		cout << " |                                                               |\n";
		cout << "  --------------------------------------------------------------- \n";

	}
	MyString welcome("  ---------------------HELLO WORLD!------------------------------");
	cout << welcome << endl;
	system("pause");
}