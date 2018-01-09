#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;
using namespace std;

cpp_int Factorial(int num)
{
    cpp_int fact = 1;
    for(int i=num; i>1; --i)
    {
        fact *= i;
    }

    return fact;
}

int main(int argc, char const *argv[])
{
    int p = 5000;
    cpp_int prime = 1;
    prime <<= p;
    prime--;

    int i = 3;
    cpp_int a = 1;
    cpp_int b;
    for (int j = 1; j < p; j++) {

        a *= a;
        b = a >> p;
        a &= prime;
        a += b;

        a *= i;

        b = a >> p;
        a &= prime;
        a += b;
    }

    cout << (a ==1 || a == prime - 1) << endl;
    return 0;
}