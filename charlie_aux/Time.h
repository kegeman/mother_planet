#ifndef _AUX_TIME_H_
#define _AUX_TIME_H_
#include "Win32.h"
namespace CharlieAux {

class Chars;

class Time
{
private:
	__time32_t total_seconds;
public:
	Time(void);
	~Time(void);
	void GetLocalTime(struct tm* const time_struct) const;
	void GetChars(Chars* const chars) const;
};

} // namespace CharlieAux
#endif