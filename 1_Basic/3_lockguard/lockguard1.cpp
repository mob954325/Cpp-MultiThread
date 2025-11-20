/// 레이스 컨디션 해결하기
/// 각 스레드가 공유자원을 100000번씩 증가시켜 총 200000이 나오도록 출력하기

#include <iostream>
#include <vector>
#include <mutex>

using namespace std;

int counter = 0; // 공유 자원 counter
mutex mtx; // 임계영역 설정을 위한 std::뮤텍스 

void Increment()
{
	for (int i = 0; i < 100000; i++)
	{
		{
			lock_guard<mutex> lock(mtx); // lock
			counter++;
		}	// lock 자동해제
	}
}

int main()
{
	cout << "counter : " << counter << "\n";

	thread t1(Increment);
	thread t2(Increment);
	t1.join();
	t2.join();

	cout << "after : " << counter << "\n";
}