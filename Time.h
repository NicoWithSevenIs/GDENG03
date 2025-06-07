#pragma once

#include <chrono>
#include <ctime>

class Time
{

	public:
		static void initialize();
		static double getDeltaTime();

	private:
		Time(){}
		~Time(){}
		Time(Time const&){}
		Time& operator=(Time const&){}

		static Time* instance;

		std::chrono::system_clock::time_point start;
		std::chrono::system_clock::time_point end;

		double delta_time = 0.0;

		static void LogFrameStart();
		static void LogFrameEnd();

		friend class Window;

};

