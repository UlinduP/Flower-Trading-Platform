#include <iostream>
using namespace std;
static int value = 100;
class Test
{
public:
    // Constructor
    Test()
    {
        cout << "This is constructor" << endl;
    }

    // Member function
    void print()
    {
        cout << "This is print function." << endl;
        cout << "Value: " << value << endl;
    }

    // Destructor
    ~Test()
    {
        cout << "This is destructor" << endl;
    }

     // Default initialization of value
};

class Test2
{
public:
    // Constructor
    Test2()
    {
        cout << "This is Test2 constructor" << endl;
    }

    // Member function
    void print()
    {
        cout << "This is Test2 print function." << endl;
        cout << "Value: " << ++value << endl;
    }

    // Destructor
    ~Test2()
    {
        cout << "This is Test2 destructor" << endl;
    }
};

int main()
{
    Test2 t2; // No need for {} here, use default constructor
    t2.print();

    return 0; // Added a return statement
}
