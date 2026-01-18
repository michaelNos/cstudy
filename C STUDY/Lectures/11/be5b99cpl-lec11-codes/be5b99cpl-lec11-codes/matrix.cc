#include <stdexcept>
#include <cstdlib>
#include <ostream>
#include <iomanip>

#include "matrix.h"

Matrix::Matrix(int rows, int cols) : ROWS(rows), COLS(cols)
{
   vals = new double[ROWS * COLS];
}

Matrix::Matrix(const Matrix &m) : ROWS(m.ROWS), COLS(m.COLS)
{  // copy constructor 
   vals = new double[ROWS * COLS];
   for (int i = 0; i < ROWS * COLS; ++i) {
      vals[i] = m.vals[i];
   }
}

Matrix::~Matrix()
{
   delete[] vals;
}

double Matrix::getValueAt(int r, int c) const
{
   if (r < 0 or r >= ROWS or c < 0 or c >= COLS) {
      throw std::out_of_range("Out of range at Matrix::getValueAt");
   }
   return at(r, c);
}

void Matrix::setValueAt(double v, int r, int c)
{
   if (r < 0 or r >= ROWS or c < 0 or c >= COLS) {
      throw std::out_of_range("Out of range at Matrix::setValueAt");
   }
   at(r, c) = v;
}

void Matrix::fillRandom(void)
{
   for (int r = 0; r < ROWS; ++r) {
      for (int c = 0; c < COLS; ++c) {
         at(r, c) = (rand() % 100) / 10.0;
      }
   }
  /* for (int i = 0; i < ROWS * COLS; ++i) {
      vals[i] = (rand() % 100) / 10.0;
   }*/
}

Matrix Matrix::sum(const Matrix &m2)
{
   if (ROWS != m2.ROWS or COLS != m2.COLS) {
      throw std::invalid_argument("Matrix dimensions do not match at Matrix::sum");
   }
   Matrix ret(ROWS, COLS);
   for (int i = 0; i < ROWS * COLS; ++i) {
      ret.vals[i] = vals[i] + m2.vals[i];
   }
   return ret;
}

Matrix Matrix::operator+(const Matrix &m2)
{
   return sum(m2);
}

Matrix& Matrix::operator=(const Matrix &m)
{
   if (this != &m) { // to avoid overwriting itself
      if (ROWS != m.ROWS or COLS != m.COLS) {
         throw std::out_of_range("Cannot assign matrix with different dimensions");
      }
      for (int i = 0; i < ROWS * COLS; ++i) {
         vals[i] = m.vals[i];
      }
   }
   return *this;
}

double& Matrix::operator()(int r, int c)
{
   return at(r, c);
}

double Matrix::operator()(int r, int c) const 
{
   return at(r, c);
}

std::ostream& operator<<(std::ostream& out, const Matrix& m)
{
   if (out) {
      out << std::fixed << std::setprecision(1);
      for (int r = 0; r < m.rows(); ++r) {
         for (int c = 0; c < m.cols(); ++c) {
            out << (c > 0 ? " " : "") << std::setw(4);
            out << m.getValueAt(r, c);
         }
         out << std::endl;
      }
   }
   return out;
}
