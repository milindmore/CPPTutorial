#include<iostream>
using namespace std;
class b
{
public:
  b ()
  {
    cout << "\n Constructing base ";
  }
  virtual ~ b ()
  {
    cout << "\n Destructing base ";
  }
};

class d:public b
{
public:
  d ()
  {
    cout << "\n Constructing derived";
  }
   ~d ()
  {
    cout << "\n Destructing derived";
  }
};

class e:public d
{
public:
  e ()
  {
    cout << "\n Constructing E derived";
  }
   ~e ()
  {
    cout << "\n Destructing E derived";
  }
};

int
main (void)
{
  e *ederived = new e ();
  b *bptr = ederived;		// derived;
  delete bptr;
  //delete derived;
  return 0;
}
