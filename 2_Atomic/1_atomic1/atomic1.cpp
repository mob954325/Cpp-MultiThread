#include <iostream>
#include <atomic>
#include <thread>

using namespace std;

atomic<int> value = 0; // 원자성을 보장해주는 객체

int main()
{
	thread t1([]() { for (int i = 0; i < 10; i++) value++; });
	thread t2([]() { for (int i = 0; i < 10; i++) value++; });
	
	t1.join();
	t2.join();


	cout << value; // 20
}