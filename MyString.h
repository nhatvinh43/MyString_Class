#ifndef _MYSTRING_H
#define _MYSTRING_H
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

class MyString
{

private:
	char* Data;
	size_t len;
	size_t reservedSize;
	static const size_t _STRING_SIZE = 15;

public:

	class iterator :public std::iterator<std::random_access_iterator_tag, char>
	{
	private:
		friend class MyString;
		iterator(char* c) :ch(c) {}
		char* ch;
	public:
		iterator() :ch(NULL){}
		iterator(const iterator& it) : ch(it.ch) {}

		char& operator*()
		{
			return *ch;
		}
		iterator operator + (int pos)
		{
			return ch + pos;
		}
		iterator operator - (int pos)
		{
			return ch - pos;
		}
		iterator& operator++()
		{
			ch = ch + 1;
			return *this;
		}
		iterator& operator--()
		{
			ch = ch - 1;
			return *this;
		}
		iterator& operator+=(int pos)
		{
			ch = ch + pos;
			return *this;
		}
		iterator& operator-=(int pos)
		{
			ch = ch - pos;
			return *this;
		}
		bool operator==(const iterator& rhs)
		{
			return ch == rhs.ch;
		}
		bool operator!=(const iterator& rhs)
		{
			return ch != rhs.ch;
		}
	};

	static const size_t npos = -1;

	typedef iterator iterator;

	typedef const iterator const_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	typedef const std::reverse_iterator<iterator> const_reverse_iterator;

	typedef char value_type;
	typedef char_traits<char> traits_type;
	typedef allocator<char> allocator_type;
	typedef char& reference;
	typedef const char& const_reference;
	typedef char* pointer;
	typedef const char* const_pointer;
	typedef MyString::iterator iterator;
	typedef const MyString::iterator const_iterator;
	typedef MyString::reverse_iterator reverse_iterator;
	typedef MyString::const_reverse_iterator const_reverse_iterator;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;

	//Member functions
	MyString();
	MyString(const MyString&);
	MyString(const MyString&, size_t, size_t len = npos);
	MyString(const char*);
	MyString(const char*, size_t);
	MyString(size_t, char);
	template <class InputIterator>
	MyString(InputIterator, InputIterator);
	MyString(initializer_list<char>);
	~MyString();
	MyString& operator =(const MyString&);
	MyString& operator =(const char*);
	MyString& operator= (char);
	MyString& operator= (initializer_list<char>);

	//Iterators các loại
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_iterator cbegin() const;
	const_iterator cend() const;
	const_reverse_iterator crbegin() const;
	const_reverse_iterator crend() const;

	//Capacity
	size_t size() const;
	size_t length() const;
	size_t max_size() const;
	void resize(size_t);
	void resize(size_t, char);
	size_t capacity() const;
	void reserve(size_t n = 0);
	void clear();
	bool empty();
	void shrink_to_fit();

	//Elements access
	char& operator [](size_t);
	const char& operator[] (size_t) const;
	char& at(size_t);
	const char& at(size_t) const;
	char& back();
	const char& back() const;
	char& front();
	const char& front() const;

	//Modifiers
	MyString operator += (const MyString&);
	MyString& operator+= (const char* s);
	MyString& operator+= (char c);
	MyString& operator+= (initializer_list<char> il);

	MyString& append(const MyString&);
	MyString& append(const MyString&, size_t, size_t);
	MyString& append(const char*);
	MyString& append(const char* s, size_t);
	MyString& append(size_t, char);
	template <class InputIterator>
	MyString& append(InputIterator, InputIterator);
	MyString& append(initializer_list<char>);

	void push_back(char c);

	MyString& assign(const MyString&);
	MyString& assign(const MyString&, size_t, size_t);
	MyString& assign(const char*);
	MyString& assign(const char*, size_t);
	MyString& assign(size_t, char);
	template <class InputIterator>
	MyString& assign(InputIterator, InputIterator);
	MyString& assign(initializer_list<char>);

	MyString& insert(size_t, const MyString&);
	MyString& insert(size_t, const MyString&, size_t, size_t);
	MyString& insert(size_t, const char*);
	MyString& insert(size_t, const char*, size_t);
	MyString& insert(size_t, size_t, char);
	MyString::iterator insert(iterator, size_t, char);
	MyString::iterator insert(iterator, char);
	template <class InputIterator>
	MyString::iterator insert(iterator, InputIterator, InputIterator);
	MyString& insert(iterator p, initializer_list<char> il);

	MyString& erase(size_t, size_t);
	MyString::iterator erase(iterator);
	MyString::iterator erase(iterator, iterator);

	MyString& replace(size_t, size_t, const MyString&);
	MyString& replace(iterator, iterator, const MyString&);
	MyString& replace(size_t, size_t, const MyString&, size_t, size_t);
	MyString& replace(size_t, size_t, const char*);
	MyString& replace(iterator, iterator, const char*);
	MyString& replace(size_t, size_t, const char*, size_t);
	MyString& replace(iterator, iterator, const char* s, size_t);
	MyString& replace(size_t, size_t, size_t, char);
	MyString& replace(iterator, iterator, size_t, char);
	template <class InputIterator>
	MyString& replace(iterator, iterator, InputIterator, InputIterator);
	MyString& replace(iterator, iterator, initializer_list<char>);

	void swap(MyString&);
	void pop_back();

	//String operations
	const char* c_str() const;
	const char* data() const;
	allocator<char> get_allocator() const;
	size_t copy(char*, size_t, size_t pos = 0) const;

	size_t find(const MyString&, size_t = 0) const;
	size_t find(const char*, size_t = 0) const;
	size_t find(const char*, size_t, size_t) const;
	size_t find(char, size_t pos = 0) const;

	size_t rfind(const MyString&, size_t pos = npos) const;
	size_t rfind(const char*, size_t pos = npos) const;
	size_t rfind(const char*, size_t, size_t) const;
	size_t rfind(char, size_t pos = npos) const;

	size_t find_first_of(const MyString& , size_t pos = 0) const ;
	size_t find_first_of(const char* , size_t pos = 0) const;
	size_t find_first_of(const char* , size_t pos, size_t ) const;
	size_t find_first_of(char , size_t pos = 0) const ;

	size_t find_last_of(const MyString&, size_t pos = npos) const;
	size_t find_last_of(const char* , size_t pos = npos) const;
	size_t find_last_of(const char* , size_t, size_t ) const;
	size_t find_last_of(char , size_t pos = npos) const;

	size_t find_first_not_of(const MyString&, size_t pos = 0) const;
	size_t find_first_not_of(const char* , size_t pos = 0) const;
	size_t find_first_not_of(const char* , size_t , size_t ) const;
	size_t find_first_not_of(char , size_t pos = 0) const;

	size_t find_last_not_of(const MyString& , size_t pos = npos) const;
	size_t find_last_not_of(const char* , size_t pos = npos) const;
	size_t find_last_not_of(const char* , size_t , size_t ) const;
	size_t find_last_not_of(char , size_t pos = npos) const;

	MyString substr(size_t pos = 0, size_t len = npos) const;

	int compare(const MyString&) const;
	int compare(size_t, size_t, const MyString&) const;
	int compare(size_t, size_t, const MyString&, size_t, size_t) const;
	int compare(const char* ) const;
	int compare(size_t , size_t , const char* ) const;
	int compare(size_t , size_t , const char* , size_t ) const;

	//Non-member function overloads
	friend MyString operator + (const MyString&, const MyString&);
	friend MyString operator+ (const MyString& trai, const char*   phai);
	friend MyString operator+ (const char*   trai, const MyString& phai);
	friend MyString operator+ (const MyString& trai, char          phai);
	friend MyString operator+ (char          trai, const MyString& phai);

	friend bool operator ==(const MyString&, const MyString&);
	friend bool operator ==(const char*, const MyString&);
	friend bool operator ==(const MyString&, const char*);

	friend bool operator !=(const MyString&, const MyString&);
	friend bool operator !=(const char*, const MyString&);
	friend bool operator !=(const MyString&, const char*);

	friend bool operator <=(const MyString&, const MyString&);
	friend bool operator <=(const char*, const MyString&);
	friend bool operator <=(const MyString&, const char*);

	friend bool operator >=(const MyString&, const MyString&);
	friend bool operator >=(const char*, const MyString&);
	friend bool operator >=(const MyString&, const char*);

	friend bool operator <(const MyString&, const MyString&);
	friend bool operator <=(const char*, const MyString&);
	friend bool operator <=(const MyString&, const char*);

	friend bool operator >(const MyString&, const MyString&);
	friend bool operator >(const char*, const MyString&);
	friend bool operator >(const MyString&, const char*);

	friend void swap(MyString& , MyString& );

	friend istream& operator >> (istream& is, MyString& String);
	friend ostream& operator <<(ostream& os, const MyString& String);

	friend istream& getline(istream& , MyString& , char );
	friend istream& getline(istream& , MyString& );
};
#endif