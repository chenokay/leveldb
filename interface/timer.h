#ifndef _UTIL_TIMER_
#define _UTIL_TIMER_

#include <time.h>
#include <errno.h>

namespace DOMOB_STL_CPP {

//
// �򵥵ļ�ʱ��
// ����start����Զ�ε���check��ÿ�ε���check��������ȡ����start����ǰ����ʱ
// ����clock_gettime(CLOCK_MONOTONIC, ...) ���������м�ʱ������������gettimeofday��
//       ��ʱʱ��ǵ�����ȱ�ݣ�������ּ�ʱ����쳣�����������ͬʱ��֤�˸߾��ȼ�ʱ
//       �ο���http://tdistler.com/2010/06/27/high-performance-timing-on-linux-windows
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
		// ���¿�ʼ��ʱ
		// 
		void restart()
		{
			clock_gettime(CLOCK_MONOTONIC, &_start_t);
			_check_t = _start_t;
		}

		//
		// �� start �� check ������ʱ�䣬�� nano second Ϊ��λ
		//
		long nsec_elapsed()
		{
			check();
			return (_check_t.tv_sec - _start_t.tv_sec) * 1000000000L +
				(_check_t.tv_nsec - _start_t.tv_nsec);
		}

		//
		// �� start �� check ������ʱ�䣬�� usec Ϊ��λ
		//
		long usec_elapsed()
		{
			return nsec_elapsed() / 1000L;
		}

		//
		// �� start �� check ������ʱ�䣬�� msec Ϊ��λ
		//
		long msec_elapsed()
		{
			return usec_elapsed() / 1000L;
		}

		//
		// �� start �� check ������ʱ�䣬�� sec Ϊ��λ
		//
		long sec_elapsed()
		{
			return msec_elapsed() / 1000l;
		}
	private:
		//
		// ��¼ʱ��㣬����ȡ�ô��ϴ� start �� check ֮�侭����ʱ��
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
