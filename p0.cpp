#include <iostream>
#include <stdexcept>
class TriMat {
private:
     int lim;
     int* data;
public:
     class Row {
     private:
	  int base;
	  int len;
	  TriMat* obj;
     public:
	  Row(int b, int len, TriMat *o)
	       :base {b}, len {len}, obj {o} { }
	  int& operator[](int n) {
	       if (n >= len)
		    throw std::out_of_range {"column out of range"};
	       return obj->data[base + n];
	  }
	  int operator[](int n) const {
	       if (n >= len)
		    throw std::out_of_range {"column out of range"};
	       return obj->data[base + n];
	  }
     };
     class ConstRow {
     private:
	  int base;
	  int len;
	  const TriMat* obj;
     public:
	  ConstRow(int b, int len, const TriMat *o)
	       :base {b}, len {len}, obj {o} { }
	  int operator[](int n) const {
	       if (n >= len)
		    throw std::out_of_range {"column out of range"};
	       return obj->data[base + n];
	  }
     };
     int get_lim() const { return lim; }
     Row operator[](int row) {
	  if (row >= lim)
	       throw std::out_of_range {"row out of range"};
	  return Row(row*(row+1)/2, row+1, this);
     }
     ConstRow operator[](int row) const {
	  if (row >= lim)
	       throw std::out_of_range {"row out of range"};
	  return ConstRow(row*(row+1)/2, row+1, this);
     }
     TriMat(int limn = 10) {
	  lim = limn;
	  data = new int[lim*(lim+1)/2];
	  if (!data)
	       throw std::runtime_error {"cannot allocate"};
     }
     ~TriMat() {
	  delete data;
     }
};

std::ostream& operator<<(std::ostream& out, const TriMat& m) {
     int n = m.get_lim();
     for (int i = 0; i < n; ++i) {
	  TriMat::ConstRow r = m[i];
	  for (int j = 0; j <= i; ++j)
	       out << r[j] << ' ';
	  out << std::endl;
     }
     return out;
}

int main() {
     constexpr int n = 8;
     TriMat m {8};
     for (int i = 0; i < n; ++i) {
	  TriMat::Row r = m[i];
	  for (int j = 0; j <= i; ++j)
	       r[j] = (i+1)*10 + j + 1;
     }
     std::cout << m;
     return 0;
}
