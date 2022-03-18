#include <time.h>
#include <stdbool.h>


static time_t timeRef;

void resetTimer()
{
    timeRef = time(NULL);       //henter sekunder siden 01.01.1970
}

bool checkTimer(int seconds)
{
    return (time(NULL)-timeRef >= seconds);
}