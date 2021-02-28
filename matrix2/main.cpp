#include "matrix2.h"
int main()
{
     Matrix2 m1;
     Matrix2 m2{1, 3, 1, 5};
     Matrix2 m3{m2};
     double n;
     
     std::cout << "m1 = " << m1 << '\n'
	       << "m2 = " << m2 << '\n';
     m1 = m2;
     std::cout << "m1 = " << m2 << '\n'
	       << "m1 != m2 == " << (m1 == m2) << std::endl;
     std::cout << "enter matrix [_,_;_,_]: " << std::flush;
     if (std::cin >> m1)
	  std::cerr << "input successful\n";
     else
	  std::cerr << "input failure\n";
     std::cout << "m1 = " << m1 << '\n'
	       << "m1*m2 = " << m1*m2 << '\n'
	       << "m1+m2 = " << m1+m2 << '\n'
	       << "5*m2 = " << 5.0 * m2 << '\n'
	       << "det(m1) = " << m1.det() << '\n';
     std::cout << "m1(1,1) = " << m1(1,1) << std::endl;
     std::cout << "enter number: " << std::flush;
     std::cin >> n;
     m1(1,1) = n;
     std::cout << "m1(1,1) = " << m1(1,1) << std::endl;
     std::cout << "enter number: " << std::flush;
     std::cin >> n;
     m1 *= n;
     std::cout << "m1 *= n = " << m1 << std::endl;
     std::cout << "m1 == m2 = " << (m1 == m2) << std::endl;
     std::cout << "m1 *= m2 = " << (m1 *= m2) << std::endl;
}
     
