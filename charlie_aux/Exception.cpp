#include "Exception.h"
#include "Logs.h"
namespace CharlieAux {
Chars Exception::prefix = Chars( L"EXCEPTION: " );

Exception::Exception() : message()
{
	CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Error, Exception::prefix);
}

Exception::Exception(Chars& Message) : message(Message)
{
	CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Error, Exception::prefix + message);
}

Exception::Exception(const wchar_t* Message) : message(Message)
{
	CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Error, Exception::prefix + message);
}

Exception::~Exception(void)
{
}

} // namespace CharlieAux