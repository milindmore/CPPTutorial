// Sample program of copy constructor copy assigment operator
// Move constructor , move assigment operator

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


int main()
{
    A a;
    A b=a;
    b = a;
    A c(move(a));
    A d;
    d = move(b);
   
    getchar();
   
}

