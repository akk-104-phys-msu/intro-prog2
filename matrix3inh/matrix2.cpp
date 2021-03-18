#include "matrix2.h"
#include <limits>
#include <cstring>
#include <ios>

static const char *bad_ind_msg = "bad index to matrix";

const char* Matrix2::bad_index::what() const
{
     return bad_ind_msg;
}

double& Matrix2::operator()(int i, int j)
{
     if (0 <= i && i < dim &&
	 0 <= j && j < dim)
	  return vals[i][j];
     throw bad_index(bad_ind_msg);
}

const double& Matrix2::operator()(int i, int j) const
{
     if (0 <= i && i < dim &&
	 0 <= j && j < dim)
	  return vals[i][j];
     throw bad_index(bad_ind_msg);
}

Matrix2& Matrix2::operator=(const Matrix2& m)
{
     if (this != &m)
	  std::memcpy((void*)vals, (void*)m.vals, sizeof m.vals);
     return *this;
}

Matrix2::Matrix2(double a, double b, double c, double d)
{
     vals[0][0] = a;
     vals[0][1] = b;
     vals[1][0] = c;
     vals[1][1] = d;
}

Matrix2::Matrix2(const Matrix2& m)
{
     if (this != &m)
	  std::memcpy((void*)vals, (void*)m.vals, sizeof m.vals);
}

Matrix2::Matrix2()
{
     std::memset((void*)vals, 0, sizeof vals);
}

Matrix2::~Matrix2() {}

double Matrix2::det() const
{
     return vals[0][0]*vals[1][1] - vals[1][0]*vals[0][1];
}

Matrix2& Matrix2::operator+=(const Matrix2& m)
{
     for (int i = 0; i < dim; i++)
	  for (int j = 0; j < dim; j++)
	       vals[i][j] += m.vals[i][j];
     return *this;
}

Matrix2& Matrix2::operator*=(const Matrix2& m)
{
     double temp[dim][dim];
     std::memset((void*)temp, 0, sizeof temp);
     for (int i = 0; i < dim; i++)
	  for (int j = 0; j < dim; j++)
	       for (int k = 0; k < dim; k++)
		    temp[i][j] += vals[i][k]*m.vals[k][j];
     std::memcpy((void*)vals, (void*)temp, sizeof temp);
     return *this;
}

std::ostream& operator<<(std::ostream& os, const Matrix2& m)
{
     return os << '[' << m(0,0) << ", " << m(0,1)
	       << "; " << m(1,0) << ", " << m(1,1)
	       << "]";
}

std::istream& operator>>(std::istream& is, Matrix2& m)
{
     const auto& fail = std::ios_base::failbit;
     char ch;
     double t[Matrix2::dim][Matrix2::dim] = {0,0,0,0};
     if (!(is >> ch) || ch != '[' || !(is >> t[0][0]) ||
	 !(is >> ch) || ch != ',' || !(is >> t[0][1]) ||
	 !(is >> ch) || ch != ';' || !(is >> t[1][0]) ||
	 !(is >> ch) || ch != ',' || !(is >> t[1][1]) ||
	 !(is >> ch) || ch != ']') {
	  is.setstate(fail);
     }
     for (int i = 0; i < Matrix2::dim; i++)
	  for (int j = 0; j < Matrix2::dim; j++)
	       m(i, j) = t[i][j];
     return is;
     
}

bool Matrix2::operator==(const Matrix2& m) const
{
     bool r = true;
     for (int i = 0; r && i < dim; i++)
	  for (int j = 0; r && j < dim; j++)
	       r = r && vals[i][j] == m.vals[i][j];
     return r;
}

bool Matrix2::operator!=(const Matrix2& m) const
{
     return !(*this == m);
}

Matrix2 operator+(const Matrix2& m1, const Matrix2& m2)
{
     Matrix2 m3{m1};
     m3 += m2;
     return m3;
}

Matrix2& Matrix2::operator*=(double k)
{
     for (int i = 0; i < dim; i++)
	  for (int j = 0; j < dim; j++)
	       vals[i][j] *= k;
     return *this;
}

Matrix2 operator*(const Matrix2& a, const Matrix2& b)
{
     Matrix2 m;
     for (int i = 0; i < Matrix2::dim; i++)
	  for (int j = 0; j < Matrix2::dim; j++)
	       for (int k = 0; k < Matrix2::dim; k++)
		    m(i, j) += a(i, k) * b(k, j);
     return m;
}

Matrix2 operator*(double k, const Matrix2& x)
{
     Matrix2 m{x};
     for (int i = 0; i < Matrix2::dim; i++)
	  for (int j = 0; j < Matrix2::dim; j++)
	       m(i, j) *= k;
     return m;
}

void Matrix2::print() const {
     std::cout << *this << std::endl;
}
