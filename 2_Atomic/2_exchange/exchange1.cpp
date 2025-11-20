#include <iostream>
#include <vector>
#include <atomic>
#include <thread>

using namespace std;

atomic<int> task_id{ 100 };

void worker()
{
	int prev = task_id.exchange(0);
	if (prev == 100)
	{
		cout << this_thread::get_id() << " : 성공 !\n";
	}
	else
	{
		cout << this_thread::get_id() << " : 실패...\n";
	}
}

int main()
{
	vector<thread> threads;
	for (int i = 0; i < 10; i++)
	{
		threads.emplace_back(worker);
	}

	for (auto& e : threads)
	{
		e.join();
	}
}