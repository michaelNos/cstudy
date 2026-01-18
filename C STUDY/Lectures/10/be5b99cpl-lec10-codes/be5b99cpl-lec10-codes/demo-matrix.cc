#include <iostream>

#include <iomanip>

#include "matrix.h"

void print(const Matrix& m);

int main(void)
{
   int ret = 0;
   try {
      Matrix m1(3, 3);
      // m1.setValueAt(10.5, 2, 3);

      m1.fillRandom();
      std::cout << "Matrix m1" << std::endl;
      print(m1);

      Matrix *m2 = new Matrix(m1);
      Matrix *m3 = new Matrix(m2->rows(), m2->cols());
      std::cout << std::endl << "Matrix m2" << std::endl;
      print(*m2);
      m3->fillRandom();
      std::cout << std::endl << "Matrix m3" << std::endl;
      print(*m3);

      Matrix m4 = m1.sum(*m2); // copy constructor is used for the assignment operator
      std::cout << std::endl << "Matrix m4 = m1 + m2" << std::endl;
      print(m4);

      delete m2;
      delete m3;

      {
         std::cout << "\nMatrix demo using operators" << std::endl;
         Matrix m1(2, 2);
         Matrix m2(m1);
         m1.fillRandom();
         m2.fillRandom();

         std::cout << "Matrix m1" << std::endl << m1;
         std::cout << "\nMatrix m2" << std::endl << m2;
         std::cout << "\nMatrix m1 + m2" << std::endl << m1 + m2;
      }

   } catch (std::out_of_range& e) {
      std::cout << "ERROR: " << e.what() << std::endl;
      ret = -1;
   }
   return ret;
}

void print(const Matrix& m)
{
   std::cout << std::fixed << std::setprecision(1);
   for (int r = 0; r < m.rows(); ++r) {
      for (int c = 0; c < m.cols(); ++c) {
         std::cout << (c > 0 ? " " : "") << std::setw(4);
         std::cout << m.getValueAt(r, c);
      }
      std::cout << std::endl;
   }
}
