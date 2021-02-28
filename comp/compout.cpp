#include "compout.h"
#include <ios>
std::ostream& operator<<(std::ostream& os, const Complex& x) {
     if (x.polar())
	  return os << '(' << x.norm() << ';' << x.arg() << ')';
     else
	  return os << '(' << x.re() << ',' << x.im() << ')';
}

std::istream& operator>>(std::istream& is, Complex& x) {
     char c;
     double a, b;
     if (is >> c && c == '(' && is >> a &&
	 is >> c && is >> b) {
	  if (c == ',')
	       x = Complex(a, b);
	  else if (c == ';')
	       x = Complex(a, b, true);
	  else
	       is.setstate(std::ios::failbit);
     } else
	  is.setstate(std::ios::failbit);
     if (!(is >> c && c == ')'))
	  is.setstate(std::ios::failbit);

     return is;
}
