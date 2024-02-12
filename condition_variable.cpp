#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <optional>
#include <chrono>

using namespace std;

optional<int> val;
condition_variable cond; // used to wait for val to have a value
mutex m; // protects val

void consume()
{
    while (true)
    {
        unique_lock lock {m};
        while (!val.has_value())
            cond.wait(lock);

        cerr << this_thread::get_id() << ": " << *val << "\n";
        val = nullopt;
    }
}

int main()
{
    thread c1 {consume};
    thread c2 {consume};

    for (int i {0}; ; ++i)
    {
        {
            scoped_lock lock {m};
            val = i;
            cond.notify_all();
        }
        this_thread::sleep_for(1s);
    }
}
