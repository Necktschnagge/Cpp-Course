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










# Challenge Task

Write a function `void primes(unsigned long long upperbound, std::ostream& os);` that outputs all prime numbers in natural order that are less or equal upperbound. So e.g. `primes(7,std::cout);` should write
```
2
3
5
7
```
to the console.
Use threads to speed up. To measure the performance of your code it will be compiled with g++ on Windows and executed afterwards on an Intel processor: https://www.intel.de/content/www/de/de/products/processors/core/i9-processors/i9-9900k.html

Bonus tasks:
* Also open a file to write the primes into it (of course, not inside the primes function).
* Write a function `std::chrono::duration duration_of(const std::function<void()>& f);` that calls a function and returns the time interval that executing the function took.
* Write a checker that opens a file and checks that it contains a valid list of prime numbers as produced by function `primes`.

