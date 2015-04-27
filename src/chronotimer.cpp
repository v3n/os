#include "chronotimer.h"

/*	Example
ChronoTimer ct;
	ct.start();
	Sleep(1000);
	auto sec = ct.getTicks();
	std::cout << sec.count() << '\n';
	ct.stop();
*/
ChronoTimer::ChronoTimer()
{
	m_isStarted = false;
	m_start;
}

void ChronoTimer::start(){
	if (m_isStarted == false){
		m_isStarted = true;
		m_start = boost::chrono::high_resolution_clock::now();
	}
}

void ChronoTimer::stop(){
	m_isStarted = false;
	m_start = static_cast<boost::chrono::high_resolution_clock::time_point>(boost::chrono::high_resolution_clock::time_point::duration::zero());
}

void ChronoTimer::restart(){
	m_isStarted = true;
	m_start = boost::chrono::high_resolution_clock::now();
}

boost::chrono::nanoseconds ChronoTimer::getTicks(){
	if (m_isStarted == true){
		return boost::chrono::high_resolution_clock::now() - m_start;
	}
}
