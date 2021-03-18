#ifndef MATRIX2_H
#define MATRIX2_H
#include <iostream>

class Matrix2 {
public:
     class bad_index {
	  const char *msg;
     public:
	  const char *what() const;
	  bad_index(const char *m) :msg {m} {}
     };
     
     static constexpr int dim = 2;
     double& operator()(int i, int j);
     const double& operator()(int i, int j) const;
     Matrix2(double a, double b, double c, double d);
     Matrix2(const Matrix2& m);
     Matrix2();
     ~Matrix2();
     double det() const;
     Matrix2& operator=(const Matrix2& m);
     Matrix2& operator+=(const Matrix2& m);
     Matrix2& operator*=(const Matrix2& m);
     Matrix2& operator*=(double k);
     bool operator==(const Matrix2& m) const;
     bool operator!=(const Matrix2& m) const;
     virtual void print() const;
private:
     double vals[dim][dim];
};
Matrix2 operator+(const Matrix2& a, const Matrix2& b);
Matrix2 operator*(const Matrix2& a, const Matrix2& b);
Matrix2 operator*(double k, const Matrix2& b);
std::ostream& operator<<(std::ostream& os, const Matrix2& m);
std::istream& operator>>(std::istream& is, Matrix2& m);
#endif
