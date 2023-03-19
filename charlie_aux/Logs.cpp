#include "Logs.h"
#include "Types.h"
#include "Chars.h"
#include "Exception.h"
#include "Time.h"
namespace CharlieAux {

Logs::Logs(void)
{
	file_name = NULL;
	log_stream = NULL;
}

Logs::~Logs(void)
{
	if(log_stream != NULL) fclose(log_stream);
	SAFE_DELETE(file_name);
}

void Logs::OpenLogsFile(Chars& file_name)
{
	if(log_stream != NULL) fclose(log_stream);
	if(_tfopen_s(&log_stream, file_name.GetChars(), L"a+, ccs=UTF-8") != 0) throw Exception();
}

void Logs::WriteLine(Level const level, const Chars& message)
{
	OutputMessage(message.GetChars());
	if(level > Debug && log_stream != NULL)
	{
		Chars prefix;
		if(level == Information) prefix = L"INFO";
		else if(level == Warning) prefix = L"WARN";
		else if(level == Error) prefix = L"ERROR";
		else prefix = L"???";
		Chars now; Time().GetChars(&now);
		_ftprintf_s(log_stream, L"%s%c%s%c%s\n", prefix.GetChars(), Separator, now.GetChars(), Separator, message.GetChars());
		fflush(log_stream);
	}
}

void Logs::WriteLine(Level const level, const wchar_t* message)
{
	return WriteLine(level, Chars(message));
}

void Logs::LogLastError(void)
{
	DWORD dwError = GetLastError();
	LPVOID lpMsgBuf;
	//HRESULT hr = HRESULT_FROM_WIN32(dwError);
	FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
			NULL,
			dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );
	OutputMessage((LPTSTR) lpMsgBuf);
	if(log_stream != NULL)
	{
		Chars now; Time().GetChars(&now);
		_ftprintf_s(log_stream, L"%s%c%s%c%s\n", L"ERROR", Separator, now.GetChars(), Separator, (LPTSTR) lpMsgBuf);
		fflush(log_stream);
	}
	LocalFree(lpMsgBuf);
}

void Logs::LogResult(HRESULT hr, const wchar_t* sMessage)
{
	size_t nBufSize = _tcslen(sMessage)+23;
	wchar_t* sBuf = new wchar_t[nBufSize];
	swprintf_s(sBuf, nBufSize, L"%s returned: 0x%x.", sMessage, hr);
	WriteLine(Error, sBuf);
	SAFE_DELETE(sBuf);
}

void Logs::OutputMessage(const wchar_t* sMessage)
{
	wide_debug_stream << L"Charlie3D: " << sMessage << L"\n";
	wide_debug_stream.flush();
}

void Logs::OutputMessage(const char* sMessage)
{
	ascii_debug_stream << "Charlie3D: " << sMessage << "\n";
	ascii_debug_stream.flush();
}

Logs* Logs::Instance = NULL;
void Logs::Create(void)
{
	Logs::Instance = new Logs();
}
void Logs::Destroy(void)
{
	SAFE_DELETE(Logs::Instance);
}

}