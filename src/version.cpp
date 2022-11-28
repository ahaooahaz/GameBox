#include <time.h>
#include <string>
#include "version.h"

constexpr unsigned int str2int(const char* str, int h = 0) {
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

time_t compile_timestamp() {
    time_t timestamp;
    tm* lpCompileTime = new tm;
    char Mmm[4] = "Jan";
	sscanf(__DATE__, "%3s %d %d", Mmm,
				&lpCompileTime->tm_mday, &lpCompileTime->tm_year);
	lpCompileTime->tm_year -= 1900;
 
	switch (str2int(Mmm)) {
		case str2int("Jan"): lpCompileTime->tm_mon = 1; break;
		case str2int("Feb"): lpCompileTime->tm_mon = 2; break;
		case str2int("Mar"): lpCompileTime->tm_mon = 3; break;
		case str2int("Apr"): lpCompileTime->tm_mon = 4; break;
		case str2int("May"): lpCompileTime->tm_mon = 5; break;
		case str2int("Jun"): lpCompileTime->tm_mon = 6; break;
		case str2int("Jul"): lpCompileTime->tm_mon = 7; break;
		case str2int("Aug"): lpCompileTime->tm_mon = 8; break;
		case str2int("Sep"): lpCompileTime->tm_mon = 9; break;
		case str2int("Oct"): lpCompileTime->tm_mon = 10; break;
		case str2int("Nov"): lpCompileTime->tm_mon = 11; break;
		case str2int("Dec"): lpCompileTime->tm_mon = 12; break;
		default:lpCompileTime->tm_mon = 0;
	}
	sscanf(__TIME__, "%d:%d:%d", &lpCompileTime->tm_hour,
				&lpCompileTime->tm_min, &lpCompileTime->tm_sec);
	lpCompileTime->tm_isdst = lpCompileTime->tm_wday = lpCompileTime->tm_yday = 0;
    timestamp = mktime(lpCompileTime);
    delete lpCompileTime;
    return timestamp;
}


void version() {
    #if (defined VERSION_MAJOR) && (defined VERSION_MIDOR) && (defined VERSION_MINOR)
    printf("version: v%d.%d.%d\n", VERSION_MAJOR, VERSION_MIDOR, VERSION_MIDOR);
    #endif
    printf("compile timestamp: %ld\n", compile_timestamp());
    #ifdef VERSION_BRANCH
    printf("branch: %s\n", (char*)VERSION_BRANCH);
    #endif
    #ifdef VERSION_COMMIT
    printf("commit: %s\n", (char*)VERSION_COMMIT);
    #endif
}