#include <iostream>

#include "matrix_ext.h"

using std::cout;

void setIdentity(Matrix& matrix);

int main(void)
{
   int ret = 0;
   MatrixExt m1(2, 1);
   m1(0, 0) = 3; m1(1, 0) = 5;

   MatrixExt m2(1, 2);
   m2(0, 0) = 1; m2(0, 1) = 2;

   cout << "Matrix m1:\n" << m1 << std::endl;
   cout << "Matrix m2:\n" << m2 << std::endl;
   cout << "m1 * m2 =\n" << m2 * m1 << std::endl;
   cout << "m2 * m1 =\n" << m1 * m2 << std::endl;
   
   { // demo setIdentity
      cout << "Using setIdentity for Matrix" << std::endl;
      setIdentity(m1);
      cout << "Matrix m1:\n" << m1 << std::endl;
   }

   {
      MatrixExt *m1 = new MatrixExt(3, 3);
      Matrix *m2 = new MatrixExt(3, 3);
      m1->fillRandom();
      m2->fillRandom();
      cout << "m1: MatrixExt as MatrixExt:\n" << *m1 << std::endl;
      cout << "m2: MatrixExt as Matrix:\n" << *m2 << std::endl;
      delete m1;
      delete m2;
   }

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
