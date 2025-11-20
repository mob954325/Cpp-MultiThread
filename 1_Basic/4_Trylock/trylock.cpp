#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

std::timed_mutex tmtx;

void LongWork()
{
	tmtx.lock();
	this_thread::sleep_for(chrono::seconds(2)); // 2초동안 가짜 일하기
	tmtx.unlock();
}

void TryLock()
{
	bool isSuccess = tmtx.try_lock_for(chrono::milliseconds(500)); // 500ms 동안 뮤텍스 잠금 시도

	if (isSuccess)
	{
		cout << "Lock Acquired\n";
	}
	else
	{
		cout << "Timed out\n";
	}
}

int main()
{
	thread t1(LongWork);
	thread t2(TryLock);
	t1.join();
	t2.join(); // timed out
}