#ifndef COMP_H
#define COMP_H

class Complex {
private:
     bool pol;
     double a, b;
     double re_pol() const;
     double im_pol() const;
     double norm_dec() const;
     double arg_dec() const;
     void arg_normalize();
     static constexpr double pi = 3.1415926535897932384626433;

public:
     double re() const { return pol ? re_pol() : a; }
     double im() const { return pol ? im_pol() : b; }
     double norm() const { return pol ? a : norm_dec(); }
     double arg() const { return pol ? b : arg_dec(); }
     void to_pol() {
	  if (!pol) {
	       double x = norm_dec();
	       double y = arg_dec();
	       pol = true, a = x, b = y;
	  }
     }
     void to_dec() {
	  if (pol) {
	       double x = re_pol();
	       double y = im_pol();
	       pol = false, a = x, b = y;
	  }
     }
     Complex new_dec() const {
	  Complex t = *this;
	  t.to_dec();
	  return t;
     }
     Complex new_pol() const {
	  Complex t = *this;
	  t.to_pol();
	  return t;
     }
     Complex inverse() const {
	  if (pol)
	       return Complex(1/a, -b, true);
	  else {
	       double t = 1.0/(a*a+b*b);
	       return Complex(a/t, -b/t);
	  }
     }
     Complex operator-() const {
	  if (pol)
	       return Complex(a, b+pi, true);
	  else
	       return Complex(-a, -b);
     }
     Complex conjugate() const;
     bool polar() const { return pol; }
     Complex(double a, double b, bool pol=false) :pol {pol}, a{a}, b{b} {
	  if (pol)
	       arg_normalize();
     }
     Complex() { Complex(0,0); }
     Complex(double a) { Complex(a, 0); }
     const Complex& operator+=(const Complex&);
     const Complex& operator-=(const Complex&);
     const Complex& operator*=(const Complex&);
     const Complex& operator/=(const Complex&);
     const Complex& operator*=(double);
     const Complex& operator/=(double);

};

Complex conjugate(const Complex&);
Complex operator+(const Complex&, const Complex&);
Complex operator+(const Complex&, double);
Complex operator+(double, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator-(const Complex&, double);
Complex operator-(double, const Complex&);
Complex operator*(const Complex&, const Complex&);
Complex operator/(const Complex&, const Complex&);
Complex operator*(double, const Complex&);
Complex operator/(double, const Complex&);
Complex operator*(const Complex&, double);
Complex operator/(const Complex&, double);
bool near(const Complex&, const Complex&, double);

#endif
