#include <atomic>
#include <iostream>

int main() {
    std::atomic<int> value{ 100 };

    int expected = 100;
    int desired = 200;

    if (value.compare_exchange_strong(expected, desired))
    {
        std::cout << "성공: " << value << "\n";
    }
    else
    {
        std::cout << "실패. 실제 값은: " << expected << "\n";
    }

    if (value.compare_exchange_strong(expected, 300)) // expected 값이 value로 갱신됨
    {
        std::cout << "성공\n";
    }
    else
    {
        std::cout << "실패. 실제 값은 : " << expected << "\n"; // 200; 
    }

    return 0;
}