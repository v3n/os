#pragma once

#ifdef __APPLE__
#include <boost/chrono.hpp>
#elif _WIN32
#include <boost\chrono.hpp>
#endif

class ChronoTimer
{
public:
	ChronoTimer();
	void start();
	void stop();
	void restart();
	boost::chrono::nanoseconds getTicks();
private:
	float m_isStarted;
	boost::chrono::high_resolution_clock::time_point m_start;
	
};

