#include "Chars.h"
#include "Types.h"
#include "Win32.h"
#include "Exception.h"
#include <cassert>
namespace CharlieAux {
const wchar_t* Chars::Empty = L"\n";

Chars::Chars(void)
{
	chars = const_cast<wchar_t*>( Chars::Empty );
	length = 0;
}

Chars::~Chars(void)
{
	if(chars != NULL && chars != Chars::Empty) delete chars;
}

Chars::Chars(const wchar_t* string)
{
	size_t size = _tcslen(string);
	size += 1;
	chars = new wchar_t[size];
	length = swprintf_s(chars, size, L"%s", string);
	if(length < 0) throw Exception(L"The Chars class constructor has failed!");
}

Chars::Chars(const char* string)
{
	size_t size = strlen(string);
	size += 1;
	chars = new wchar_t[size];
	length = swprintf_s(chars, size, L"%S", string);
	if(length < 0) throw Exception(L"The Chars class constructor has failed!");
}

Chars::Chars(const Chars& x)
{
	size_t size = x.GetSize();
	size += 1;
	this->chars = new wchar_t[size];
	this->length = swprintf_s(chars, size, L"%s", x.GetChars());
}

const wchar_t* Chars::GetChars() const { return chars; }

const int Chars::GetLength() const { return length; }

const size_t Chars::GetSize() const
{
	assert(length >= 0);
	return static_cast<size_t>(length);
}

Chars& Chars::operator= (const Chars& x)
{
	size_t size = x.GetSize();
	size += 1;
	if(chars != NULL && chars != Chars::Empty) delete this->chars;
	this->chars = new wchar_t[size];
	this->length = swprintf_s(this->chars, size, L"%s", x.GetChars());
	if(this->length < 0) throw Exception(L"The Chars class' operator '=' has failed!");
	return *this;
}

Chars& Chars::operator= (const wchar_t* x)
{
	size_t size = _tcslen(x);
	size += 1;
	if(chars != NULL && chars != Chars::Empty) delete this->chars;
	this->chars = new wchar_t[size];
	this->length = swprintf_s(this->chars, size, L"%s", x);
	if(this->length < 0) throw Exception(L"The Chars class' operator '=' has failed!");
	return *this;
}

Chars Chars::operator+ (const Chars& x) const
{
	size_t size = this->GetSize() + x.GetSize();
	size += 1;
	wchar_t* y = new wchar_t[size];
	int y_length = swprintf_s(y, size, L"%s%s", this->GetChars(), x.GetChars());
	if(y_length < 0) throw Exception(L"The Chars class' operator '+' has failed!");
	Chars z = Chars(y);
	delete[] y;
	return z;
}

Chars Chars::operator+ (unsigned short x) const
{
	size_t size = this->GetSize();
	size += 23;
	wchar_t* y = new wchar_t[size];
	int y_length = swprintf_s(y, size, L"%s%d", this->GetChars(), x);
	if(y_length < 0) throw Exception(L"The Chars class' operator '+' has failed!");
	Chars z = Chars(y);
	delete[] y;
	return z;
}

Chars Chars::operator+ (unsigned int x) const
{
	size_t size = this->GetSize();
	size += 23;
	wchar_t* y = new wchar_t[size];
	int y_length = swprintf_s(y, size, L"%s%u", this->GetChars(), x);
	if(y_length < 0) throw Exception(L"The Chars class' operator '+' has failed!");
	Chars z = Chars(y);
	delete[] y;
	return z;
}

Chars Chars::operator+ (signed int x) const
{
	size_t size = this->GetSize();
	size += 24;
	wchar_t* y = new wchar_t[size];
	int y_length = swprintf_s(y, size, L"%s%d", this->GetChars(), x);
	if(y_length < 0) throw Exception(L"The Chars class' operator '+' has failed!");
	Chars z = Chars(y);
	delete[] y;
	return z;
}

Chars Chars::operator+ (unsigned long x) const
{
	size_t size = this->GetSize();
	size += 23;
	wchar_t* y = new wchar_t[size];
	int y_length = swprintf_s(y, size, L"%s%d", this->GetChars(), x);
	if(y_length < 0) throw Exception(L"The Chars class' operator '+' has failed!");
	Chars z = Chars(y);
	delete[] y;
	return z;
}

Chars& Chars::operator+= (const Chars& x)
{
	size_t size = this->GetSize();
	size += 1;
	wchar_t* y = new wchar_t[size];
	this->length = swprintf_s(y, size, L"%s", this->GetChars());
	if(length < 0) throw Exception(L"The Chars class' operator '+=' has failed!");

	size = this->GetSize() + x.GetSize();
	size += 1;
	delete this->chars;
	this->chars = new wchar_t[size];
	this->length = swprintf_s(this->chars, size, L"%s%s", y, x.GetChars());
	if(length < 0) throw Exception(L"The Chars class' operator '+=' has failed!");

	delete[] y;
	return *this;
}

bool Chars::operator== (const Chars& x) const
{
	return this->CompareTo(x) == 0;
}

bool Chars::operator== (const wchar_t* x) const
{
	return this->CompareTo(x) == 0;
}

int Chars::CompareTo(const Chars& x) const
{
	return wcscmp(this->GetChars(), x.GetChars());
}

int Chars::CompareTo(const wchar_t* x) const
{
	return wcscmp(this->GetChars(), x);
}

} // namespace Charlie3D
