#include "Time.h"

Time* Time::instance = nullptr;

void Time::initialize()
{
	instance = new Time();
}

double Time::getDeltaTime()
{
	return instance->delta_time;
}

void Time::LogFrameStart()
{
	instance->start = std::chrono::system_clock::now();
}

void Time::LogFrameEnd()
{
	instance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = instance->end - instance->start;

	instance->delta_time = elapsed.count();
}
