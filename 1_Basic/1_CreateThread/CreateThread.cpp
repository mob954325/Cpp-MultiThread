#include <iostream>
#include <vector>
#include <thread>

using namespace std;

int main()
{
	vector<int> datas;

	thread t1([&datas]() 
		{ 
			cout << "스레드 1초 대기 하기\n";
			this_thread::sleep_for(chrono::seconds(1));

			cout << "스레드 작업 시작 \n";
			datas.push_back(10);
			datas.push_back(20);
			datas.push_back(30);
		});
	t1.join();

	cout << "최종 벡터 내용 : ";
	for (const auto& e : datas) cout << e << " "; // 10 20 30
}