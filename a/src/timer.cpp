#include "timer.h"

timer::timer()
{
    //ctor
    startedAt =0;
    pausedAt =0;
    paused = false;
    started = false;
}

timer::~timer()
{
    //dtor
}
bool timer::isStarted()
{
    return started;
}

bool timer::isStopped()
{
    return !started;
}

bool timer::isPaused()
{
    return paused;

}

void timer::pause()
{
    if(paused || !started)
        return;
    paused =true;
    pausedAt = clock();
}

void timer::resume()
{
    if(!paused) return;
    paused = false;
    startedAt +=clock()-pausedAt;
}

void timer::stop()
{
    started = false;
}
void timer::start()
{
    if(started)return;
    started  =true;
    paused = false;
    startedAt = clock();
}

void timer::reset()
{
    paused = false;
    startedAt= clock();
}

clock_t timer::getTicks()
{
    if(!started)return 0;

    if(paused)return pausedAt - startedAt;
    return clock() - startedAt;
}
