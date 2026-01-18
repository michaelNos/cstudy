#ifndef __MATRIX_EXT_H__
#define __MATRIX_EXT_H__

#include "matrix.h"

class MatrixExt : public Matrix {
   typedef Matrix Base;
   public:
   MatrixExt(int r, int c) : Base(r, c) {}

   void setIdentity(void);
   Matrix operator*(const Matrix &m2);
   void fillRandom(void);
};

#endif
