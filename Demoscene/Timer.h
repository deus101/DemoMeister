#ifndef _TIMER_H_
#define _TIMER_H_

//#include <sys/timeb.h>
//#include <time.h>

#ifdef _WIN32
#include <sys/timeb.h>
#include <time.h>
#endif


/** \brief A very basic timer class, suitable for FPS counters etc. 
 *  
 */
class Timer
{
    
public:
	Timer(): startTime_(getCurrentTime() ) {};

	/** Report the elapsed time in seconds (it will return a double,
	 *  so the fractional part is subsecond part). */
	double elapsed() const { return getCurrentTime() - startTime_; };

	/** Restart the timer. */
	void restart() { startTime_ = getCurrentTime(); };

	/** Return the current time as number of elapsed seconds of this day. */
	double static getCurrentTime() {
		struct timeb ts;
		ftime(&ts);
		return (ts.time + 0.001*ts.millitm);
    };

private:
    double startTime_;
    
};
#endif // _TIMER_H_
