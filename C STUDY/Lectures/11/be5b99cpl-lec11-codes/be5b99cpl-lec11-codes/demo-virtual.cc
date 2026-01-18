#include <iostream>

using namespace std;

class A {
   public:
      virtual void info() // virtual has to be specified 
      {
         cout << "Object of the class A" << endl;
      }
};

class B : public A {
   public:
      void info() 
      {
         cout << "Object of the class B" << endl;
      }
};


int main(void)
{
   A* a = new A();
   B* b = new B();
   a->info(); // calling method info() of the class A
   b->info(); // calling method info() of the class B
   a = b; // use the polymorphism of objects
   a->info(); // virtual method is the dynamic binding, method of the class B is called
   delete a;
   delete b;
   return 0;
}
