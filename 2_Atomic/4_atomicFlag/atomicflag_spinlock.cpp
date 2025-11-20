#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

class Spinlock
{
private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
	void lock()
	{
		while (flag.test_and_set()) // true : 다른 스레드가 락을 잡고있음, false : 해당 스레드 락 잡기
		{
			std::this_thread::yield(); // cpu 양보하기 
		}
	}

	void unlock()
	{
		flag.clear(); // 상태 되돌리기
	}
};

Spinlock spinlock;
int shared_counter = 0;

void increment_with_spinlock() {
    for (int i = 0; i < 10000; ++i) {
        spinlock.lock();
        ++shared_counter;  // 보호된 영역
        spinlock.unlock();
    }
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment_with_spinlock);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "결과: " << shared_counter << "\n";  // 100000

    return 0;
}