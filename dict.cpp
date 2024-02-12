#include <thread>
#include <iostream>
#include <map>

using namespace std;

map<int, int> n;

void f()
{
    for (int i {0}; i < 100'000; ++i)
    {
        n[i] = i + 1;
    }
}

int main()
{
    thread t1 {f};
    thread t2 {f};

    t1.join();
    t2.join();

    cout << n.size();
}
