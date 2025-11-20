// shared_mutex를 통해 여러 읽기와 쓰기 락 설정하기

#include <iostream>
#include <shared_mutex>
#include <map>
#include <string>

using namespace std;

shared_mutex smtx;

class Configuration
{
	map<string, int> settings;

public:
	// 읽기 함수
	int GetSetting(const string& key)
	{
		{
			shared_lock<shared_mutex> lock(smtx);
			cout << this_thread::get_id() << " : Read lock 획득\n";
			this_thread::sleep_for(chrono::milliseconds(100));
		}

		return settings.find(key)->second;
	}

	void SetSetting(const string& key, int value)
	{
		{
			unique_lock<shared_mutex> lock(smtx); // 하나의 스레드만 허용
			cout << this_thread::get_id() << " : Write lock 획득\n";		
			this_thread::sleep_for(chrono::milliseconds(500));
			settings[key] = value; // 데이터 저장하기
		}
	}
};

int main()
{
	auto config = make_unique<Configuration>();

	thread writer1([&config]() { config->SetSetting("Version", 1); });
	thread reader1([&config]() { config->GetSetting("Version"); });
	thread reader2([&config]() { config->GetSetting("Version"); });

	writer1.join();
	reader1.join();
	reader2.join();
}