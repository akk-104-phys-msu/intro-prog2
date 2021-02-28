#include <limits>
#include <iostream>
#include <new>

struct recs {
     int k;
     char str[256];
};

int main() try {
     int nums;
     std::cin >> nums;
     std::cin.ignore(std::numeric_limits<std:: streamsize>::max(), '\n');
     recs *array = new recs[nums];

     for (int i = 0; i < nums; i++) {
	  auto& x = array[i];
	  x.k = i;
	  std::cin.getline(x.str, sizeof x.str);
     }

     for (int i = nums-1; i >= 0; i--) {
	  auto& x = array[i];
	  std::cout << x.k << "  " << x.str << '\n';
     }
     delete[] array;
     return 0;
}
catch (const std::bad_alloc& x) {
     std::cerr << x.what() << std::endl;
}
