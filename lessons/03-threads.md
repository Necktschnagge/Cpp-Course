# Some further nice features of modern C++

## Lambda Functions:
#### doc
https://en.cppreference.com/w/cpp/language/lambda

#### syntax
[_captures_]\(_params_\){_body_}

#### examples
```
#include<iostream>
#include<vector>
...

int x = 7;
int y = 9;

std::function<void(int, std::ostream&)> write_int = [](int x, std::ostream& os){ os << x; };
auto sum = [](int a, int b){ rerturn a + b; };
auto add_x = [x](int z){ return z + x;}
auto increment_x{ [&x](int increment){ x += i; } };

auto some_sum = sum(add_x(4),9);
increment_x(some_sum);
std::cout << x; // what is the result?
```

#### Use lambdas together with the algorithm library

https://en.cppreference.com/w/cpp/algorithm

```
auto v = std::vector<int>({ 1,2,4,5,6,6,9,8,7 });
std::remove_if(v.begin(),v.end(), [](int x){ return static_cast<bool>(x % 2); }); // what is happening here?
std::transform(v.begin(),v.end(),v.begin(), [](int x){ return x - 1; } );
std::cout << std::accumulate(v.begin(), v.end(),0, [](int x, int y){ return 10*x + y; });

```

## Smart Pointer

Never need to care about deleting abjects behind pointers if the object is shared between various places of usage in code.

https://en.cppreference.com/w/cpp/memory/unique_ptr
https://en.cppreference.com/w/cpp/memory/shared_ptr
https://en.cppreference.com/w/cpp/memory/weak_ptr


## Threads
https://en.cppreference.com/w/cpp/thread/thread

```
using namespace std::literals::chrono_literals;

auto michael = std::thread([](){
  std::cout << "Hello\n";
  std::this_thread::sleep_for(2s);
  std::cout << "2s later\n";
  std::cout << "My name is Michael and now I start walking home.\n"
  std::this_thread::sleep_for(10s);
  std::cout << "Oh, I am at the door.\n"
}); // thread immediately starts running it's code.

std::cout << "Hello\n";
std::this_thread::sleep_for(1s);
std::cout << "1s later\n";
std::this_thread::sleep_for(3s);
std::cout << "Oh, when will Michael come home? Let's wait for him:\n";

michael.join(); // wait for a thread to finish its execution.
std::cout << "Hi, Michael!\n";
// Can Michael answer here?
```

Use mutexes if two threads want to use objects concurrently. Be aware of race conditions, competition of threads and deadlocks. Find solutions to be deadlock-free. To avoid deadlocks, you may also consider using `std::atomic<...>`.

https://en.cppreference.com/w/cpp/thread/mutex

https://en.cppreference.com/w/cpp/atomic/atomic

# Challenge Task

Write a function `void primes(unsigned long long upperbound, std::ostream& os);` that outputs all prime numbers in natural order that are less or equal upperbound. So e.g. `primes(7,std::cout);` should write
```
2
3
5
7
```
to the console.

Your solution should work at least for `2000 <= upperbound <= 1'000'000'000`. But it would be nice if it also works for greater bounds as well as trivial ones. (The upperbound of upperbound was adjusted since an example solution was written that could do the job except writing output for `200'000` in less than 1 second. )

Use threads to speed up. You may also consider using the algorithm library mentioned earlier on this page and its ExecutionPolicies to achieve parallel computing:
https://stackoverflow.com/questions/39954678/difference-between-execution-policies-and-when-to-use-them

To measure the performance of your code it will be compiled with g++ on Windows and executed afterwards on an Intel processor: https://www.intel.de/content/www/de/de/products/processors/core/i9-processors/i9-9900k.html There will be 16GB RAM available at least.

Bonus tasks:
* Also open a file to write the primes into it (of course, not inside the primes function). Use the "class" `std::ofstream`. http://www.cplusplus.com/reference/fstream/ofstream/
* Write a function `std::chrono::duration<...> duration_of(const std::function<void()>& f);` that calls a function and returns the time interval that executing the function took. Of course, have a look at what chrono offers you to measure time.
* Write a checker that opens a file and checks that it contains a valid list of prime numbers as produced by function `primes`.

To determine the winner the same code for time measurement and opening a file will be applied to all the `primes` functions written by students, just to make sure that all variants are measured under equal conditions.

# What are your interests for the last C++ lesson?

Ever heard of 
* constexpr
* exceptions and `noexcept`
* templates
* perfect forwarding
* iterators
* ...
?

If you have special interests, please let me know. (Use email, report an issue on this github site, ...)

