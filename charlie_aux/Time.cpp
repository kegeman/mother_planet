#include "Time.h"
#include "Chars.h"
#include <cassert>
namespace CharlieAux {

Time::Time(void)
{
	_time32(&total_seconds);   // Get current time in seconds.
}

Time::~Time(void)
{
}

void Time::GetLocalTime(struct tm* const time_struct) const
{
	assert(time_struct != NULL);
	_localtime32_s(time_struct, &total_seconds);   // Convert time to struct tm form.
}

void Time::GetChars(Chars* const chars) const
{
	assert(chars != NULL);
	const size_t time_string_length = 26;
	wchar_t time_string[time_string_length];
	struct tm time_struct;
	GetLocalTime(&time_struct);
	swprintf_s(time_string,time_string_length,L"%04d-%02d-%02d %02d:%02d:%02d",time_struct.tm_year+1900,time_struct.tm_mon+1,time_struct.tm_mday,time_struct.tm_hour,time_struct.tm_min,time_struct.tm_sec);
	*chars = Chars(time_string);
}

}