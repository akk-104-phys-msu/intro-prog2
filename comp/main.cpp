#include <iostream>
#include "comp.h"
#include "compout.h"
#include "compmath.h"

int main()
{
     Complex x, y;
     int n;
     std::cin >> x >> y >> n;
     std::cout << x << '\t' << y << '\n';
     std::cout << "x + y = " << x+y << '\n';
     std::cout << "sin(x) = " << sin(x) << '\n';
     std::cout << "exp(x) = " << exp(x) << '\n';
     return 0;
}
