#include "comp.h"
#include <cmath>

static constexpr double pi = 3.1415926535897932384626433;

double Complex::re_pol() const {
     return a * std::cos(b);
}

double Complex::im_pol() const {
     return a * std::sin(b);
}

double Complex::norm_dec() const {
     return std::hypot(a, b);
}

double Complex::arg_dec() const {
     if (a == 0 && b == 0)
	  return 0;
     else if (a == 0 && b > 0)
	  return pi/2;
     else if (a == 0 && b < 0)
	  return -pi/2;
     else
	  return std::atan2(b, a);
}

void Complex::arg_normalize() {
     b = std::fmod(b, 2*pi);
}

Complex Complex::conjugate() const {
     if (pol)
	  return Complex(a, pi - b, true);
     else
	  return Complex(a, -b);
}

Complex operator+(const Complex& x, const Complex& y) {
     return Complex(x.re() + y.re(), x.im() + y.im());
}

Complex operator-(const Complex& x, const Complex& y) {
     return Complex(x.re() + y.re(), x.im() + y.im());
}

Complex operator+(const Complex& x, double y) {
     return Complex(x.re()+y, x.im());
}
Complex operator+(double t, const Complex& x) {
     return x + t;
}

Complex operator*(const Complex& x, const Complex& y) {
     if (x.polar() && y.polar())
	  return Complex(x.norm()*y.norm(), x.arg()+y.arg(), true);
     else if (!x.polar() && !y.polar())
	  return Complex(x.re()*y.re()-x.im()*y.im(),
			 x.re()*y.im()+x.im()*y.re());
     else
	  return x.new_dec() * y.new_dec();
}

Complex operator/(const Complex& a, const Complex& b) {
     Complex x = b.inverse();
     return a*x;
}

Complex operator*(double k, const Complex& x) {
     if (x.polar())
	  return Complex(std::abs(k),
			 (k < 0 ? x.arg() + pi : x.arg()),
			 true);
     else
	  return Complex(k*x.re(), k*x.im());
}

Complex operator/(double k, const Complex& x) {
     return k*x.inverse();
}

Complex operator*(const Complex& x, double k) {
     return k*x;
}

Complex operator/(const Complex& x, double k) {
     return (1/k)*x;
}

bool near(const Complex& x, const Complex& y, double eps) {
     return (x-y).norm() < eps;
}

const Complex& Complex::operator+=(const Complex& y) {
     to_dec();
     Complex yd = y.new_dec();
     a += yd.a;
     b += yd.b;
     return *this;
}

const Complex& Complex::operator-=(const Complex& y) {
     to_dec();
     Complex yd = y.new_dec();
     a -= yd.a;
     b -= yd.b;
     return *this;
}

const Complex& Complex::operator*=(const Complex& y) {
     Complex t = *this * y;
     a = t.a;
     b = t.b;
     pol = t.pol;
     return *this;
}

const Complex& Complex::operator/=(const Complex& y) {
     Complex t = *this;
     *this = t / y;
     return *this;
}

const Complex& Complex::operator*=(double k) {
     if (pol && k > 0)
	  a *= k;
     else if (pol && k < 0) {
	  a *= -k, b += pi;
	  arg_normalize();
     } else if (pol && k == 0) {
	  a = b = 0;
     } else {
	  a *= k;
	  b *= k;
     }
     return *this;
}

const Complex& Complex::operator/=(double k) {
     double t = 1/k;
     return (*this *= t);
}
