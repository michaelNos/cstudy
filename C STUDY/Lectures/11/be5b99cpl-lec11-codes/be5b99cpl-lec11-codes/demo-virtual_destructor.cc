#include <iostream>

using namespace std;

class Base {
   public:
      Base(int capacity) {
         cout << "Base::Base -- allocate data" << endl;
         int *data = new int[capacity];
      }
      virtual ~Base() {
         cout << "Base::~Base -- release data" << endl;
      }
   protected:
      int *data;
};

class Derived : public Base {
   public:
      Derived(int capacity) : Base(capacity) {
         cout << "Derived::Derived -- allocate data2" << endl;
         int *data2 = new int[capacity];
      }
      ~Derived() {
         cout << "Derived::~Derived -- release data2" << endl;
         int *data2;
      }
   protected:
      int *data2;
};

int main(void)
{
   { 
      cout << "Using Derived " << endl;
      Derived *object = new Derived(1000000);
      delete object;
      cout << endl;
   }
   {
      cout << "Using Base" << endl;
      Base *object = new Derived(1000000);
      delete object;
   }
   return 0;
}
