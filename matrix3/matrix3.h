#ifndef MATRIX3_H
#define MATRIX3_H
#include <utility>
#include <iostream>
#include <vector>
#include "matrix2.h"
class Matrix3 {
public:
     static constexpr int dim = 3;
     static constexpr double eps = 1e-16;
private:
     Matrix2 m22;
     double *c2, *r2, *l;
public:
     class bad_index {};
     Matrix3();
     Matrix3(const Matrix3&);
     Matrix3(const std::vector<double>&);
     Matrix3(const std::initializer_list<double>&);
     ~Matrix3();
     Matrix3& operator=(const Matrix3&);
     double& operator()(int, int);
     const double& operator()(int, int) const;
     double det() const;
     double spur() const;
     Matrix3& operator+=(const Matrix3&);
     Matrix3& operator*=(double);
     Matrix3& operator*=(const Matrix3&);
     bool operator==(const Matrix3&) const;
};

Matrix3 operator+(const Matrix3&, const Matrix3&);
Matrix3 operator*(double, const Matrix3&);
Matrix3 operator*(const Matrix3&, const Matrix3&);
bool operator!=(const Matrix3&, const Matrix3&);
std::ostream& operator<<(std::ostream&, const Matrix3&);
std::istream& operator>>(std::istream&, Matrix3&);
#endif
