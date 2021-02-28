#include "compmath.h"
#include <cmath>
#include <vector>


static constexpr double pi = 3.1415926535897932384626433;
constexpr double eps = 1e-16;

static Complex sin_polar(const Complex& x) {
     const double r = x.norm();
     const double a = x.arg();
     double cr = r;
     double ca = a;
     std::vector<Complex> v;
     int i = 1;
     while (cr > eps) {
	  v.push_back(Complex(cr, ca, true));
	  cr *= - r / i / (i+1);
	  ca += a;
	  i += 2;
     }
     Complex res(0, 0);
     for (int k = v.size()-1; k >= 0; --k) {
	  v[k].to_dec();
	  res += v[k];
     }
     return res;
}

static Complex sin_decart(const Complex& x) {
     return std::sin(x.re())*std::cosh(x.im()) +
	  Complex(0,1)*std::sinh(x.im())*std::cos(x.re());
}

Complex sin(const Complex& x) {
     if (x.polar())
	  return sin_polar(x);
     else
	  return sin_decart(x);
}

Complex exp(const Complex& x) {
     Complex t(1, 0);
     Complex r(0, 0);
     int i = 0;
     while (t.norm() > eps) {
	  r += t;
	  i++;
	  t *= x/i;
     }
     return r;
}

Complex cos(const Complex& x) {
     Complex t(1, 0);
     Complex r(0, 0);
     int i = 0;
     while (t.norm() > eps) {
	  r += t;
	  t *= - x*x/i/(i+1);
	  i += 2;
     }
     return r;
}

Complex tan(const Complex& x) {
     return sin(x)/cos(x);
}

Complex cot(const Complex& x) {
     return cos(x)/sin(x);
}

Complex pow(const Complex& x, int n) {
     if (n < 0)
	  return pow(x.inverse(), n);
     Complex v = x;
     Complex a(1);
     while (n > 0) {
	  if (n % 2 == 0)
	       v *= v, n /= 2;
	  else
	       a *= v, n--;
     }
     return a;
}

Complex croot(const Complex& x, int n, int nr)
{
     return Complex(x.norm(), (x.arg()+2*pi*nr)/n, true);
}

Complex logz(const Complex& x) {
     return Complex(std::log(x.norm())) + Complex(0, x.arg());
}
