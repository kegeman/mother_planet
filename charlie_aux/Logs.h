#pragma once
#include "Win32.h"
#include <ostream>
#include <sstream>

namespace CharlieAux {

template<class CharT, class TraitsT = std::char_traits<CharT> >
class basic_dostream : public std::basic_ostream<CharT, TraitsT>
{
public:
    basic_dostream() : std::basic_ostream<CharT, TraitsT>
                (new std::basic_stringbuf<CharT, TraitsT>()) {}
};

typedef basic_dostream<char>    adebugstream; // ASCII
typedef basic_dostream<wchar_t> wdebugstream; // WIDE

//////////////////////////////////////////////////////////////////////
#if defined(LOGGING)
#ifndef LOG
#define LOG(x)			{ CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Information, x); }
#endif
#ifndef LOGD
#define LOGD(x)			{ CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Debug, x); }
#endif
#ifndef LOGW
#define LOGW(x)			{ CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Warning, x); }
#endif
#ifndef LOGE
#define LOGE(x)			{ CharlieAux::Logs::Instance->WriteLine(CharlieAux::Logs::Error, x); }
#endif
#ifndef LLE
#define LLE()           { CharlieAux::Logs::Instance->LogLastError(); }
#endif
#ifndef LR
#define LR(x)			{ hr = (x); if( FAILED(hr) ) { CharlieAux::Logs::Instance->LogResult( hr, L#x); } }
#endif
#else
#ifndef LOG
#define LOG(x)			{}
#endif
#ifndef LOGD
#define LOGD(x)			{}
#endif
#ifndef LOGW
#define LOGW(x)			{}
#endif
#ifndef LOGE
#define LOGE(x)			{}
#endif
#ifndef LLE
#define LLE()			{}
#endif
#ifndef LR
#define LR(x)			{ hr = (x); }
#endif
#endif
//////////////////////////////////////////////////////////////////////
class Chars;

class Logs
{
public:
	enum Level { Debug, Information, Warning, Error };
private:
	wchar_t* file_name;
	FILE* log_stream;
public:
	Logs(void);
	~Logs(void);
	void OpenLogsFile(Chars& file_name);
	void WriteLine(Level const level, const Chars& message);
	void WriteLine(Level const level, const wchar_t* message);
	void LogLastError(void);
	void LogResult(HRESULT hr, const wchar_t* sMessage);
private:
	adebugstream ascii_debug_stream;
	wdebugstream wide_debug_stream;
	void OutputMessage(const wchar_t* sMessage);
	void OutputMessage(const char* sMessage);
public:
	static Logs* Instance;
	static void Create(void);
	static void Destroy(void);
	static const wchar_t Separator = L';';
};

} // namespace CharlieAux