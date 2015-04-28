#include <boost/chrono.hpp>

#pragma once

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

