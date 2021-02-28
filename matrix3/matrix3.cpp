#include "matrix3.h"
#include <cstring>
Matrix3::Matrix3()
     :m22{}, c2(new double[Matrix2::dim] {0}),
      r2(new double[Matrix2::dim] {0}),
      l(new double(0))
{
}

Matrix3::~Matrix3()
{
     delete[] c2;
     delete[] r2;
     delete l;
}

const double& Matrix3::operator()(int i, int j) const
{
     if (0 <= i && i < Matrix2::dim &&
	 0 <= j && j < Matrix2::dim)
	  return m22(i, j);
     else if (0 <= i && i < Matrix2::dim && j == dim-1)
	  return r2[i];
     else if (0 <= j && j < Matrix2::dim && i == dim-1)
	  return c2[i];
     else if (i == dim-1 && j == dim-1)
	  return *l;
     else
	  throw bad_index {};
}

double& Matrix3::operator()(int i, int j)
{
     const Matrix3* m = (const Matrix3*) this;
     return (double&) m->operator()(i, j);
}

Matrix3::Matrix3(const std::initializer_list<double>& ls)
     :m22{}, c2(new double[Matrix2::dim] {0}),
      r2(new double[Matrix2::dim] {0}),
      l(new double(0))
{
     auto m = std::min<std::size_t>(dim*dim, ls.size());
     const auto* it {ls.begin()};
     for (std::size_t k = 0; k < m; k++)
	  operator()(k/dim, k%dim) = *it++;
}

Matrix3::Matrix3(const std::vector<double>& v)
     :m22{}, c2(new double[Matrix2::dim]{0}),
      r2(new double[Matrix2::dim]{0}),
      l(new double(0))
{
     auto m = std::min<std::size_t>(dim*dim, v.size());
     for (std::size_t k = 0; k < m; k++)
	  operator()(k/dim, k%dim) = v[k];
}

Matrix3::Matrix3(const Matrix3& m)
     :m22{m.m22},
      c2{new double[Matrix2::dim]},
      r2{new double[Matrix2::dim]},
      l{new double}
{
     std::memcpy(c2, m.c2, Matrix2::dim*sizeof(double));
     std::memcpy(r2, m.r2, Matrix2::dim*sizeof(double));
     *l = *m.l;
}

Matrix3& Matrix3::operator=(const Matrix3& m)
{
     if (&m != this) {
	  m22 = m.m22;
	  std::memcpy(c2, m.c2, Matrix2::dim*sizeof(double));
	  std::memcpy(r2, m.r2, Matrix2::dim*sizeof(double));
	  *l = *m.l;
     }
     return *this;
}
double Matrix3::det() const
{
     return *l*m22.det() - c2[1]*(m22(0,0)*r2[1] - m22(0, 1)*r2[0]) +
	  c2[0]*(m22(1,0) * r2[1] - r2[0]*m22(0,1));
}

double Matrix3::spur() const
{
     double x{0};
     for (int i = 0; i < Matrix3::dim; i++)
	  x += operator()(i,i);
     return x;
}

Matrix3& Matrix3::operator+=(const Matrix3& m)
{
     for (int i = 0; i < dim; i++)
	  for (int j = 0; j < dim; j++)
	       operator()(i, j) += m(i, j);
     return *this;
}

Matrix3& Matrix3::operator*=(double k)
{
     for (int i = 0; i < dim; i++)
	  for (int j = 0; j < dim; j++)
	       operator()(i, j) *= k;
     return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& m)
{
     Matrix3 temp {*this};
     *this = Matrix3();
     for (int i = 0; i < dim; i++)
	  for (int j = 0; j < dim; j++)
	       for (int k = 0; k < dim; k++)
		    operator()(i, j) += temp(i, k) * m(k, j);
     return *this;
}

static inline bool near(double a, double b, double eps)
{
     return std::abs(a-b) < eps*std::max(a, b);
}

bool Matrix3::operator==(const Matrix3& m) const
{
     bool eq = true;
     for (int i = 0; eq && i < Matrix3::dim; i++)
	  for (int j = 0; eq && j < Matrix3::dim; j++)
	       eq = eq && near((*this)(i,j), m(i, j), Matrix3::eps);
     return eq;
}

Matrix3 operator+(const Matrix3& a, const Matrix3& b)
{
     return Matrix3{a} += b;
}

Matrix3 operator*(double k, const Matrix3& a)
{
     return Matrix3{a} *= k;
}

Matrix3 operator*(const Matrix3& a, const Matrix3& b)
{
     return Matrix3{a} *= b;
}

bool operator!=(const Matrix3& a, const Matrix3& b)
{
     return !(a==b);
}

std::ostream& operator<<(std::ostream& os, const Matrix3& a)
{
     os << '[';
     for (int i = 0; i < Matrix3::dim; i++) {
	  for (int j = 0; j < Matrix3::dim; j++) {
	       os << a(i, j);
	       if (j != Matrix3::dim-1)
		    os << ", ";
	  }
	  if (i != Matrix3::dim-1)
	       os << "; ";
     }
     os << ']';
     return os;
	       
}
	   
std::istream& operator>>(std::istream& is, Matrix3& m)
{
     constexpr int len = Matrix3::dim*Matrix3::dim;
     std::vector<double> v(len);
     for (int i = 0; i < len; i++)
	  is >> v[i];
     
     m = Matrix3(v);
     return is;
}
