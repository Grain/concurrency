#include <thread>
#include <iostream>
#include <mutex>

using namespace std;

mutex m1;
mutex m2;

int i1 = 0;
int i2 = 0;

void f()
{
    for (int i {0}; i < 1'000'000; ++i)
    {
        {
            scoped_lock l1 {m1};
            i1 += 1;
        }
        {
            scoped_lock l2 {m2};
            i2 -= 1;
        }
    }
}

int main()
{
    jthread t1 {f};
    jthread t2 {f};
}
