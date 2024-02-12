#include <thread>
#include <iostream>

using namespace std;

int sum = 0;

void f()
{
    for (int i {0}; i < 1'000'000; ++i)
    {
        sum += 1;
    }
}

int main()
{
    thread t1 {f};
    thread t2 {f};

    t1.join();
    t2.join();

    cout << sum << endl;
}
