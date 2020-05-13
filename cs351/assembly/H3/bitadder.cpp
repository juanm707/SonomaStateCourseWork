#include <iostream>
#include <string>
using namespace std;

class Int128
{
    public:
        Int128(long long int highVal=0, unsigned long long int lowVal=0)
        {
            high = highVal;
            low = lowVal;
            overflow = false;
        }

        Int128 operator+(const Int128 & rhs)
        {
            Int128 sum;
            sum.high = high + rhs.high;
            sum.low = low + rhs.low;
            if (sum.low < low)
                ++sum.high;
            if (sum.high < high)
            {
                overflow = true;	
            }
            return sum;
        }

        void print()
        {
            cout << "High: " << high << endl;
            cout << "Low: " << low << endl;
        }
    private:
        long long int high;
        unsigned long long int low;
        bool overflow;
};

int main()
{
    // Test case 1:
    long long int bignum1 = strtoll("0x7fffffffffffffff", 0, 16);
    long long int bignum2 = strtoll("0xffffffffffffffff", 0, 16);

    // Test case 2:
    long long int  num1 = strtoll("0x7fffffffffffffff", 0, 16);
    long long int num2 = 0;
    long long int num3 = strtoll("0xffffffffffffffff", 0, 16);
    long long int num4 = 1;

    // Test case 2:
    long long int numba1 = strtoll("0x7fffffffffffffff", 0, 16);
    long long int numba2 = strtoll("0xffffffffffffffff", 0, 16);
    long long int numba3 = 1;

    // Test case 1:
    Int128 myNum(bignum1, bignum2);
    Int128 myNum2(bignum1, bignum2);
    Int128 myNum3 = myNum + myNum2;
    myNum3.print();

    // Test case 2:
    Int128 myNumber(num1, num2);
    Int128 myNumber2(num3, num4);
    Int128 myNumber3 = myNumber + myNumber2;
    myNumber3.print();

    // Test case 3:
    Int128 myNumba(numba1, numba2);
    Int128 myNumba2(numba2, numba3);
    Int128 myNumba3 = myNumba + myNumba2;
    myNumba3.print();


    return 0;
}
