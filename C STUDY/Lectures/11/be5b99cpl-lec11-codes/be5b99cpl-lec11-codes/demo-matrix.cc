#include <iostream>

#include <iomanip>

#include "matrix.h"

void setIdentity(Matrix& matrix);

int main(void)
{
   int ret = 0;
   Matrix m1(2, 2);
   std::cout << "Matrix m1 -- init values: " << std::endl << m1;
   setIdentity(m1);
   std::cout << "Matrix m1 -- identity: " << std::endl << m1;
   return ret;
}

void setIdentity(Matrix& matrix)
{
   for (int r = 0; r < matrix.rows(); ++r) {
      for (int c = 0; c < matrix.cols(); ++c) {
         matrix(r, c) = (r == c) ? 1.0 : 0.0;
      }
   }
}
