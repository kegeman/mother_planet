#ifndef _AUX_CHARS_H_
#define _AUX_CHARS_H_
namespace CharlieAux {
class Exception;

class Chars
{
private:
	wchar_t* chars;
	int length;

public:
	Chars(void);
	~Chars(void);
	Chars(const wchar_t* string);
	Chars(const char* string);
	Chars(const Chars& x);

	inline const wchar_t* GetChars() const;
	const int GetLength() const;
	inline const size_t GetSize() const;

	Chars& operator= (const Chars& x);
	Chars& operator= (const wchar_t* x);
	Chars operator+ (const Chars& x) const;
	Chars operator+ (unsigned short x) const;
	Chars operator+ (unsigned int x) const;
	Chars operator+ (signed int x) const;
	Chars operator+ (unsigned long x) const;
	Chars& operator+= (const Chars& x);
	bool operator== (const Chars& x) const;
	bool operator== (const wchar_t* x) const;

	int CompareTo(const Chars& x) const;
	int CompareTo(const wchar_t* x) const;
public:
	static const wchar_t* Empty;
};

} // namespace CharlieAux
#endif