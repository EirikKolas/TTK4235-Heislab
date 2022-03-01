#include <time.h>
#include <stdbool.h>

static int msTimer = 0;

void sleep()
{
    nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
}

void updateTimer()
{
    msTimer += 20; //milliseconds
}

void resetTimer()
{
    msTimer = 0;
}

bool checkTimer(int milliseconds)
{
    if (msTimer >= milliseconds)
    {
        return true;
    }
    return false;
    
}

