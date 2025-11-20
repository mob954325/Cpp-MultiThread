// 스레드 작업 함수에게 참조 매개변수 넘기기

#include <iostream>
#include <thread>

using namespace std;

// value에 add만큼 더하는 함수
void modifyValue(int& value, int add)
{
	value += add;
}

int main()
{
	int myValue = 100;

	std::cout << "초기값 : " << myValue << "\n";

	thread t1(modifyValue, ref(myValue), 123);
	t1.join();

	std::cout << "작업 후 : " << myValue << "\n"; // 223
}

/// thread 생성자는 기본적으로 인자를 복사합니다 함수가 참조(&)로 받아도
/// 스레드에 값을 그냥 전달하면 복사가 되어 원본값을 수정할 수 없습니다.
/// 참조로 넘기려면 반드시 std::ref를 사용해야합니다.