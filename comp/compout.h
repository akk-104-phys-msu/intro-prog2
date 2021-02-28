#ifndef COMPOUT_H
#define COMPOUT_H
#include <ostream>
#include <istream>
#include "comp.h"

std::ostream& operator<<(std::ostream& os, const Complex& x);
std::istream& operator>>(std::istream& os, Complex& x);
#endif
