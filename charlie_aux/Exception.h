#ifndef _AUX_EXCEPTION_H_
#define _AUX_EXCEPTION_H_
#include "Chars.h"
namespace CharlieAux {
class Logs;
class Exception
{
private:
	Chars message;
public:
	Exception();
	Exception(Chars& Message);
	Exception(const wchar_t* Message);
	~Exception(void);
	Chars ToChars(void) const { return Exception::prefix + message; }
public:
	static Chars prefix;
};

} // namespace CharlieAux
#endif