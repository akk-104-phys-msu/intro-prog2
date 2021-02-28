#include <iostream>
#include <cstring>
#include <utility>

void reverse(char *m) {
     auto l = std::strlen(m);
     for (decltype(l) i = 0, j = l; i < j; i++, j--)
	  std::swap(m[i], m[j]);
}


int main()
{
     using std::cin, std::cout;
     int x;
     cin >> x;
     cout << x << std::endl;

     char c;
     while (cin && cin.get() != '\n');
     
     constexpr int len = 256;
     char ar[len];
     cin.getline(ar, len, '\n');
     reverse(ar);
     cout << ar << '\n';
     return 0;
}
