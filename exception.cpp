#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

int sum = 0;
mutex m; // protects sum

void f()
{
    for (int i {0}; i < 1'000'000; ++i)
    {
        try
        {
            m.lock();
            sum += 1;
            throw 1;
            m.unlock();
        }
        catch (...)
        {
        }
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
