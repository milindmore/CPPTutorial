// ConsoleApplication12.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
struct A
{
    string str;

    A() :str("test") { cout <<endl<< " test constructor"; }
    A(const A& obj) : str(obj.str) { cout <<endl<< " copy constructor"; }
    A& operator=(const A& obj) 
    {
        cout << " Copy Assigment operator";
        str = obj.str;
        return *this;
    }

    A(A&& obj) : str(move(obj.str)) { cout << endl << " Move constructor "; }
    
    A& operator=(A&& obj)  {
         str = move(obj.str);
         cout << endl << " Move Assigment operator ";
         return *this;
    }


};
void func(A& a)
{
    cout << " Value " << a.str;
}

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
   // A a;
   // A b=a;
   // b = a;
   // A c(move(a));
   // A d;
   // d = move(b);
   
    L l(1);
    L m(0);
    L k1{ 5, 6 };

    L k{ 'a', 'b' };


  
    
   //cout<<
    //func(a);
    getchar();
    //std::cout << "Hello World!\n";
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
