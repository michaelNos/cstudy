/*
 * File name: matrix_ext.cc
 * Date:      2016/12/30 19:47
 * Author:    Jan Faigl
 */

#include <cstdlib>

#include "matrix_ext.h"

void MatrixExt::setIdentity(void)
{
   for (int r = 0; r < rows(); ++r) {
      for (int c = 0; c < cols(); ++c) {
         (*this)(r, c) = (r == c) ? 1.0 : 0.0;
      }
   }
}

Matrix MatrixExt::operator*(const Matrix &m2)
{
   Matrix m3(rows(), m2.cols());
   for (int r = 0; r < rows(); ++r) {
      for (int c = 0; c < m2.cols(); ++c) {
         m3(r, c) = 0.0;
         for (int k = 0; k < cols(); ++k) {
            m3(r, c) += (*this)(r, k) * m2(k, c);
         }
      }
   }
   return m3;
}

void MatrixExt::fillRandom(void)
{ 
   for (int r = 0; r < rows(); ++r) {
      for (int c = 0; c < cols(); ++c) {
         (*this)(r, c) = (rand() % 100) / 10.0;
         if (rand() % 100 > 50) {
            (*this)(r, c) *= -1.0;
         }
      }
   }
}
