// ConsoleApplication12.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Here is sample program of initilizer list using generic teplate T


#include <iostream>
#include <string>
using namespace std;

struct L   {
    L(int) { cout << endl << "Initilize 0"; }
    L(int, int)   { cout << endl << "Initilize 1";  }
    L(int, int, int)   { cout << endl << "Initilize 2";  }
    template <typename T>   L(std::initializer_list<T> il) { cout << endl << "Initilize IList";
    
    for (auto itm : il) {
        std::cout << endl << itm << " ";
    }
        
    }
};



int main()
{
   
    L l(1);
    L m(0);
    L k1{ 5, 6 };
    L k{ 'a', 'b' };

    getchar();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
