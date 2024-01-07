#include "s21_matrix_oop.h"

// базовый конструктор
S21Matrix::S21Matrix() : rows_(0), cols_(0) { matrix_ = nullptr; }

// параметризированный конструктор
S21Matrix::S21Matrix(int inrows, int incols) : rows_(inrows), cols_(incols) {
  matrix_ = nullptr;
  AllocateMemory(rows_, cols_);
}

// конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = nullptr;
  AllocateMemory(other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&other) : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

// деструктор
S21Matrix::~S21Matrix() { DeallocateMemory(); }

// операторы
S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result = *this;
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (matrix_ != nullptr) {
    DeallocateMemory();
  }
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  }

  DeallocateMemory();
  rows_ = other.rows_;
  cols_ = other.cols_;
  AllocateMemory(rows_, cols_);

  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

double S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || col >= cols_ || row >= rows_) {
    throw std::out_of_range("Invalid rows or/and columns!");
  }
  return matrix_[row][col];
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 0 || col < 0 || col >= cols_ || row >= rows_) {
    throw std::out_of_range("Invalid rows or/and columns!");
  }
  return matrix_[row][col];
}

int S21Matrix::GetCols() const { return cols_; }

int S21Matrix::GetRows() const { return rows_; }

double **S21Matrix::GetMatrix() const { return matrix_; }

void S21Matrix::AllocateMemory(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;
  if (matrix_ == nullptr &&
      (((rows_ == 0) && (cols_ > 0)) || ((rows_ > 0) && (cols_ == 0)))) {
    AllocateMatrix();
  } else if ((rows_ < 1 || cols_ < 1) && !matrix_) {
    throw std::invalid_argument("Invalid rows or/and columns!_2");
  } else {
    AllocateMatrix();
  }
}

void S21Matrix::AllocateMatrix() {
  FreeMemory();
  matrix_ = new double *[rows_];
  if (matrix_ == nullptr) {
    throw std::bad_alloc();
  }
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
    if (matrix_[i] == nullptr) {
      throw std::bad_alloc();
    }
  }
}

void S21Matrix::DeallocateMemory() {
  FreeMemory();
  rows_ = 0;
  cols_ = 0;
}

void S21Matrix::FreeMemory() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

//функция для сравнения двух матриц
bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool res = true;
  if (&other == this || other.matrix_ == nullptr || matrix_ == nullptr) {
    throw std::invalid_argument("Matrix is not exist");
  }
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(other.matrix_[i][j] - matrix_[i][j]) > epsilon) {
          res = false;
        }
      }
    }
  } else {
    res = false;
  }
  return res;
}

//Функция для добавления матрицы к текущей (исключительные ситуации разные
//размеры матрицы)
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}

//Функция для вычитания матрицы из текущий(исключительные систуации - разные
//размеры матрицы)
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Different matrix size");
  }
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::runtime_error("Matrix_ is nullptr");
  }

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
}

//Функция умножения текущей матрицы на число
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

//Функция умножения текущей матрицы на вторую матрицу
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the "
        "number "
        "of rows of the second matrix");
  }
  S21Matrix tmp_matrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      double sum = 0.0;
      for (int n = 0; n < cols_; n++) {
        sum += matrix_[i][n] * other.matrix_[n][j];
      }
      tmp_matrix.matrix_[i][j] = sum;
    }
  }
  *this = tmp_matrix;
}

//Создает новую транспонированную матрицу из текущей и возвращает ее.
S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);

  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      result.matrix_[i][j] = matrix_[j][i];
    }
  }

  return result;
}

//Вычисляет матрицу алгебраического сложения текущей и возвращает ее
//Алгебраическим дополнением элемента a[i][j] матрицы A называется число:
// A(ij)=(-1)^(i+j)*M(ij), где M(ij) - дополнительный минор, определитель
//матрицы, получающейся из исходной матрицы A путём вычёркивания i-й строки и
// j-го столбца.
//Матрица алгебраических дополнений состоит из таких алгебраических дополнений
//(посчитанных для каждого элемента матрицы)

S21Matrix S21Matrix::Minor(int inrows, int incols) const {
  int m_rows = 0;
  int m_cols = 0;

  S21Matrix result(rows_ - 1, cols_ - 1);
  if (rows_ != 1 || cols_ != 1 || matrix_ != nullptr) {
    for (int i = 0; i < GetRows(); i++) {
      if (i == inrows) {
        continue;
      }
      m_cols = 0;
      for (int j = 0; j < GetCols(); j++) {
        if (j == incols) {
          continue;
        }
        result.matrix_[m_rows][m_cols] = matrix_[i][j];
        m_cols++;
      }
      m_rows++;
    }
  } else {
    result = *this;
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::length_error("Error: matrix size is wrong");
  }
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else {
    for (int i = 0; i < cols_; i++) {
      S21Matrix minor = Minor(0, i);
      double minor_det = minor.Determinant();
      if (i % 2 == 0) {
        result += matrix_[0][i] * minor_det;
      } else {
        result -= matrix_[0][i] * minor_det;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (matrix_ == nullptr && rows_ < 1) {
    throw std::length_error("Matrix is empty");
  }
  if (cols_ != rows_) {
    throw std::invalid_argument("Matrix is not square");
  }
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    throw std::invalid_argument(
        "СalcComplements does not exist for matrix size 1х1");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double minor_det = 0.0;
      if (rows_ == 1 && cols_ == 1) {
        minor_det = matrix_[0][0];
      } else {
        minor_det = Minor(i, j).Determinant();
      }
      if ((i + j) % 2 == 0) {
        result.matrix_[i][j] = minor_det;
      } else {
        result.matrix_[i][j] = -minor_det;
      }
    }
  }
  return result;
}

//Обра́тная ма́трица — такая матрица при умножении которой на исходную матрицу
// A получается единичная матрица

S21Matrix S21Matrix::InverseMatrix() const {
  if (cols_ != rows_) {
    throw std::invalid_argument("Matrix is not square");
  }
  double det = Determinant();
  if (std::fabs(det) < epsilon) {
    throw std::logic_error("Мatrix is not invertible.");
  }
  S21Matrix inverse_tmp(rows_, cols_);
  if (rows_ == 1) {
    inverse_tmp.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements().Transpose();
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        inverse_tmp.matrix_[i][j] = tmp.matrix_[i][j] / det;
      }
    }
  }
  return inverse_tmp;
}

void S21Matrix::SetValue(int row, int col, double value) {
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    matrix_[row][col] = value;
  } else {
    std::cout << "Error: incorrect matrix element indices." << std::endl;
  }
}

void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 1) {
    throw std::invalid_argument("Rows is invalid");
  }
  if (rows_ != new_rows) {
    S21Matrix tmp(new_rows, cols_);
    int tmp_rows = 0;
    if (new_rows < rows_) {
      tmp_rows = new_rows;
    } else {
      tmp_rows = rows_;
    }
    for (int i = 0; i < tmp_rows; ++i) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = tmp;
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 1) {
    throw std::invalid_argument("Rows is invalid");
  }
  if (cols_ != new_cols) {
    S21Matrix tmp(rows_, new_cols);
    int tmp_cols = 0;
    if (new_cols < rows_) {
      tmp_cols = new_cols;
    } else {
      tmp_cols = cols_;
    }
    for (int i = 0; i < tmp_cols; ++i) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = tmp;
  }
}