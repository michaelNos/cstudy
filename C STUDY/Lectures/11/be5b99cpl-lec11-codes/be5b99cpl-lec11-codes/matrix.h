#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <ostream>

class Matrix {

   public:
      Matrix(int rows, int cols);
      Matrix(const Matrix &m);
      ~Matrix();

      inline int rows(void) const { return ROWS; }
      inline int cols(void) const { return COLS; }

      double getValueAt(int r, int c) const;
      void setValueAt(double v, int r, int c);

      void fillRandom(void);

      Matrix sum(const Matrix &m2);

      Matrix operator+(const Matrix &m2);

      Matrix& operator=(const Matrix &m);
      double& operator()(int r, int c);
      double operator()(int r, int c) const;

   private:
      inline double& at(int r, int c) const
      {
         return vals[COLS * r + c];
      }
   private:
      const int ROWS;
      const int COLS;
      double *vals;
};

std::ostream& operator<<(std::ostream& out, const Matrix& m);

#endif
