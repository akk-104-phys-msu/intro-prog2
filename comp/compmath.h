#ifndef COMPMATH_H
#define COMPMATH_H

#include "comp.h"

Complex sin(const Complex& x);
Complex cos(const Complex& x);
Complex tan(const Complex& x);
Complex cot(const Complex& x);

Complex exp(const Complex& x);
Complex pow(const Complex& x, int n);
Complex croot(const Complex& x, int n, int nr);
Complex logz(const Complex& x);
#endif
