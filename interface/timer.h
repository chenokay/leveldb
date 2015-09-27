#ifndef _UTIL_TIMER_
#define _UTIL_TIMER_

#include <time.h>
#include <errno.h>

namespace DOMOB_STL_CPP {

//
// 简单的计时器
// 调用start后可以多次调用check，每次调用check，都可以取到从start到当前的用时
// 采用clock_gettime(CLOCK_MONOTONIC, ...) 函数来进行计时，这样避免了gettimeofday的
//       计时时间非单调的缺陷，避免出现计时结果异常的情况发生，同时保证了高精度计时
//       参考：http://tdistler.com/2010/06/27/high-performance-timing-on-linux-windows
//             http://blog.habets.pp.se/2010/09/gettimeofday-should-never-be-used-to-measure-time
//
class Timer
{
	public:
		Timer()
		{
			clear();
			restart();
		}

		void clear()
		{
			_start_t.tv_sec = 0;
			_start_t.tv_nsec = 0;
			_check_t.tv_sec = 0;
			_check_t.tv_nsec = 0;
		}

		// 
		// 重新开始计时
		// 
		void restart()
		{
			clock_gettime(CLOCK_MONOTONIC, &_start_t);
			_check_t = _start_t;
		}

		//
		// 从 start 到 check 经过的时间，以 nano second 为单位
		//
		long nsec_elapsed()
		{
			check();
			return (_check_t.tv_sec - _start_t.tv_sec) * 1000000000L +
				(_check_t.tv_nsec - _start_t.tv_nsec);
		}

		//
		// 从 start 到 check 经过的时间，以 usec 为单位
		//
		long usec_elapsed()
		{
			return nsec_elapsed() / 1000L;
		}

		//
		// 从 start 到 check 经过的时间，以 msec 为单位
		//
		long msec_elapsed()
		{
			return usec_elapsed() / 1000L;
		}

		//
		// 从 start 到 check 经过的时间，以 sec 为单位
		//
		long sec_elapsed()
		{
			return msec_elapsed() / 1000l;
		}
	private:
		//
		// 记录时间点，用于取得从上次 start 到 check 之间经过的时间
		//
		void check()
		{
			clock_gettime(CLOCK_MONOTONIC, &_check_t);
		}

		struct timespec _start_t;  // the beginning time
		struct timespec _check_t;  // the check point time
};

}  // end namespace

#endif
