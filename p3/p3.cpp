#include <iostream>
#include <cstring>
#include <utility>
#include <limits>
#include <new>


struct recs {
     int k;
     char *str;
     void inverse();
};

void recs::inverse() {
     char* l = str + std::strlen(str) - 1;
     char* b = str;
     while (b < l)
	  std::swap(*b++, *l--);
}

class read_buf {
     std::istream& s;
     char *buf;
     size_t sz, nsz;
     static constexpr int initial_sz = 10;
     static constexpr double gr = 1.5;
     void grow();
public:
     read_buf(std::istream& is)
	  :s {is}, buf {nullptr}, sz {0}, nsz {initial_sz} {}
     ~read_buf() { std::free(buf); }
     char *getline(std::size_t &len);
     
};

void read_buf::grow() {
     char *p = (char *)std::realloc(buf, nsz);
     if (!p)
	  throw std::bad_alloc();
     buf = p;
     sz = nsz;
     nsz *= gr;
}

char* read_buf::getline(std::size_t& len) {
     std::size_t p;
     char ch;
     for (p = 0; s.get(ch) && ch != '\n'; p++) {
	  if (sz == p)
	       grow();
	  buf[p] = ch;
     }
     buf[p] = '\0';
     len = p;
     return buf;
}

int main()
{
     read_buf buf(std::cin);
     int num;
     if (!(std::cin >> num))
	  return 1;
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

     recs *a = new recs[num];
     for (int i = 0; i < num; i++) {
	  a[i].k = i;
	  std::size_t len;
	  char *p = buf.getline(len);
	  a[i].str = new char[len+1];
	  std::strcpy(a[i].str, p);
     }
     int k;
     if (!(std::cin >> k) || 0 > k || k >= num)
	  return 1;
     a[k].inverse();

     for (int i = 0; i < num; i++) {
	  std::cout << a[i].k << '\t' << a[i].str << std::endl;
	  delete[] a[i].str;
     }

     delete[] a;
}
