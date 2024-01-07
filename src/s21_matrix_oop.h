#ifndef CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_
#define CPP1_S21_MATRIXPLUS_S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

constexpr double epsilon = 1e-7;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int inrows, int incols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix &operator=(S21Matrix &&other) noexcept;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  bool operator==(const S21Matrix &other) const;
  double operator()(int row, int col) const;
  double &operator()(int row, int col);
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  int GetCols() const;
  int GetRows() const;
  void SetRows(int new_rows);
  void SetCols(int new_cols);
  void SetValue(int row, int col, double value);
  double **GetMatrix() const;

 private:
  int rows_, cols_;
  double **matrix_;
  void AllocateMemory(int inrows, int incols);
  void DeallocateMemory();
  void FreeMemory();
  void AllocateMatrix();
  S21Matrix Minor(int rows_in, int cols_in) const;
};

#endif