#include <iostream>
#include <thread>

using namespace std;

class ThreadGuard
{
	thread& refThread;

public:
	ThreadGuard(thread& ref) : refThread(ref) { };
	~ThreadGuard()
	{
		if (refThread.joinable())
		{
			cout << "ThreadGuard: 스레드 join() 시도...\n";
			refThread.join();
			cout << "ThreadGuard: 스레드 join() 완료\n";
		}
	}
};

void task()
{
	cout << "Task 시작됨, 2초간 작업 시작 \n";
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Task 종료됨\n";
}

int main()
{
	try
	{
		thread t(task);
		ThreadGuard tg(t);

		cout << "1초 대기 후 예외 발생\n";
		this_thread::sleep_for(chrono::seconds(1));
		throw std::runtime_error("고의 예외");
	}
	catch (exception& e)
	{
		cout << "Main : 예외 처리 " << e.what() << "\n";
	}
}