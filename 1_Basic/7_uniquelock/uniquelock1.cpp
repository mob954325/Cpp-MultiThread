// std::unique_lock에서 std::defer_lock을 사용해 지연 잠금 설정하기

#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;

int main()
{
	auto flexible_lock_task = []()
		{
			unique_lock<mutex> lock(mtx, std::defer_lock);

			cout << this_thread::get_id() << " : 작업 수행 500ms\n";
			this_thread::sleep_for(chrono::milliseconds(500));

			lock.lock();
			cout << this_thread::get_id() << " : 임계영역 진입 200ms\n";
			this_thread::sleep_for(chrono::milliseconds(200));
			lock.unlock();

			cout << this_thread::get_id() << " : 임계영역 벗어남 300ms\n";
			this_thread::sleep_for(chrono::milliseconds(300));
		};

	thread t1(flexible_lock_task);
	thread t2(flexible_lock_task);

	t1.join();
	t2.join();
}