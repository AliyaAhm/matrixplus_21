#include "gtest/gtest.h"
#include "s21_matrix_oop.h"

//Проверяем базовый конструктор класса S21Matrix.
//Он создает объект tests с помощью конструктора по умолчанию
//и затем проверяет, что количество строк и столбцов в объекте
// tests равно 0 с помощью функций GetRows() и GetCols().
TEST(test_class, basic_constructor) {
  S21Matrix tests;
  EXPECT_EQ(tests.GetRows(), 0);
  EXPECT_EQ(tests.GetCols(), 0);
}

//Проверяем базовый конструктор
//класса S21Matrix и также проверяет, что при доступе к элементу
//матрицы с недопустимыми индексами выбрасывается исключение.

TEST(test_class, basic_constructor_1) {
  S21Matrix tests;
  EXPECT_EQ(tests.GetRows(), 0);
  EXPECT_EQ(tests.GetCols(), 0);
  EXPECT_ANY_THROW(tests(2, 2));
}

//Проверяем конструктор S21Matrix(int rows_, int cols_);
//Проверяем конструктор класса S21Matrix,
//который принимает количество строк и столбцов в качестве аргументов.
//Он создает объект tests с указанными размерами и затем проверяет,
//что количество строк и столбцов в объекте tests соответствует
//ожидаемым значениям.
TEST(test_class, rc_constructor) {
  S21Matrix tests(78, 320);
  EXPECT_EQ(tests.GetRows(), 78);
  EXPECT_EQ(tests.GetCols(), 320);
}

//Проверяем конструктор копирования S21Matrix(const S21Matrix& other);
//создаем объект tests с заданными размерами, а затем создает объект copy
//с использованием копирующего конструктора и передает в него объект tests.
//Далее тест проверяет, что количество строк и столбцов в объекте copy
//соответствует ожидаемым значениям.
TEST(test_class, copy_constructor) {
  S21Matrix tests(12, 12);
  S21Matrix copy(tests);

  EXPECT_EQ(copy.GetCols(), 12);
  EXPECT_EQ(copy.GetRows(), 12);
}

//Проверяем конструктор перемещения
TEST(test_class, move_constructor) {
  S21Matrix tests(12, 12);
  S21Matrix moved(std::move(tests));

  EXPECT_EQ(tests.GetCols(), 0);
  EXPECT_EQ(tests.GetRows(), 0);
  EXPECT_EQ(moved.GetCols(), 12);
  EXPECT_EQ(moved.GetRows(), 12);
}

TEST(test_class, square_brackets_operator) {
  S21Matrix tests(7, 10);
  EXPECT_EQ(tests(0, 0), 0.0);

  tests(0, 1) = 78.0;
  EXPECT_EQ(tests(0, 1), 78.0);

  tests(2, 6) = 32.0;
  EXPECT_EQ(tests(2, 6), 32.0);
}

// operator =
TEST(test_overload, equal_lvalue) {
  S21Matrix tests;
  S21Matrix tests_1(3, 3);
  tests_1(1, 2) = 3.0;
  tests_1(2, 2) = 2.0;

  tests = tests_1;

  EXPECT_EQ(tests.GetRows(), 3);
  EXPECT_EQ(tests.GetCols(), 3);
  EXPECT_EQ(tests(1, 2), 3.0);
  EXPECT_EQ(tests(2, 2), 2.0);
}

TEST(test_overload, equal_rvalue) {
  S21Matrix tests;
  S21Matrix tests_1(2, 2);

  tests = std::move(tests_1);

  EXPECT_EQ(tests.GetRows(), 2);
  EXPECT_EQ(tests.GetCols(), 2);
}

TEST(test_functional, equality_matrix) {
  S21Matrix tests(2, 2);
  S21Matrix tests_1(2, 2);

  ASSERT_TRUE(tests == tests_1);
}

TEST(test_functional, equality_matrix_1) {
  S21Matrix tests(3, 4);
  S21Matrix tests_1;

  tests.GetMatrix()[0][1] = 23.0;
  tests_1 = tests;

  ASSERT_TRUE(tests == tests_1);
}

TEST(test_functional, sum_matrix) {
  S21Matrix tests(2, 2);
  S21Matrix tests_1(2, 2);

  tests(0, 0) = 1.0;
  tests_1(0, 0) = 1.0;

  tests(1, 1) = 1.0;
  tests_1(1, 1) = 1.0;

  tests.SumMatrix(tests_1);

  EXPECT_EQ(tests(0, 0), 2);
  EXPECT_EQ(tests(1, 1), 2);
}

TEST(test_functional, operator_overload_matrix) {
  S21Matrix tests_0(2, 2);
  S21Matrix tests_1(2, 2);

  tests_0(0, 0) = 1;
  tests_0(0, 1) = 1;
  tests_0(1, 0) = 1;
  tests_0(1, 1) = 1;

  tests_1(0, 0) = 2;
  tests_1(0, 1) = 1;
  tests_1(1, 0) = 1;
  tests_1(1, 1) = 3;

  tests_0 = tests_0 + tests_1;

  EXPECT_EQ(tests_0(0, 0), 3);
  EXPECT_EQ(tests_1(1, 1), 3);
}

TEST(test_functional, eq_operator_overload_matrix) {
  S21Matrix tests(2, 2);
  S21Matrix tests_1(2, 2);

  tests(0, 0) = 1;
  tests_1(0, 0) = 2;

  tests(1, 1) = 1;
  tests_1(1, 1) = 1;

  tests += tests + tests_1;

  EXPECT_EQ(tests(0, 0), 4);
  EXPECT_EQ(tests_1(1, 1), 1);
}

TEST(test_functional, sub_matrix_0) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A.SubMatrix(B), std::runtime_error);
}

TEST(test_functional, sub_matrix_0_1) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 4);
  EXPECT_THROW(A.SubMatrix(B), std::invalid_argument);
}

TEST(test_functional, sub_matrix) {
  S21Matrix tests(2, 2);
  S21Matrix tests_1(2, 2);

  tests(0, 0) = 1;
  tests_1(0, 0) = 2;

  tests(1, 1) = 1;
  tests_1(1, 1) = 1;

  tests.SubMatrix(tests_1);

  EXPECT_EQ(tests(0, 0), -1);
  EXPECT_EQ(tests(1, 1), 0);
}

TEST(test_functional, eq_sub_matrix) {
  S21Matrix tests(2, 2);
  S21Matrix tests_1(2, 2);

  tests(0, 0) = 1;
  tests_1(0, 0) = 2;

  tests(1, 1) = 1;
  tests_1(1, 1) = 1;

  tests -= tests_1;

  EXPECT_EQ(tests(0, 0), -1);
  EXPECT_EQ(tests(1, 1), 0);
}

TEST(test_functional, sub_operator_overload) {
  S21Matrix tests_0(2, 2);
  S21Matrix tests_1(2, 2);

  tests_0(0, 0) = 1;
  tests_0(0, 1) = 1;
  tests_0(1, 0) = 1;
  tests_0(1, 1) = 1;

  tests_1(0, 0) = 2;
  tests_1(0, 1) = 1;
  tests_1(1, 0) = 1;
  tests_1(1, 1) = 3;

  tests_0 = tests_0 - tests_1;

  EXPECT_EQ(tests_0(0, 0), -1);
  EXPECT_EQ(tests_0(1, 1), -2);
}

TEST(test_functional, mul_matrix) {
  int rows = 2;
  int cols = 3;

  S21Matrix tests(rows, cols);
  S21Matrix tests_1(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      tests(i, j) = c++;
    }

    for (int i = 0, c = 7; i < cols; i++) {
      for (int j = 0; j < rows; j++) {
        tests_1(i, j) = c++;
      }
    }
  }

  tests.MulMatrix(tests_1);

  S21Matrix result(2, 2);
  result(0, 0) = 58;
  result(0, 1) = 64;
  result(1, 0) = 139;
  result(1, 1) = 154;

  ASSERT_TRUE(tests.EqMatrix(result));
}

TEST(test_functional_mul_matrix, eq_mul_matrix) {
  int rows = 2;
  int cols = 3;

  S21Matrix tests(rows, cols);
  S21Matrix tests_1(cols, rows);
  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      tests(i, j) = c++;
    }
  }

  for (int i = 0, c = 7; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      tests_1(i, j) = c++;
    }
  }

  tests *= tests_1;

  S21Matrix result(2, 2);
  result(0, 0) = 58;
  result(0, 1) = 64;
  result(1, 0) = 139;
  result(1, 1) = 154;

  ASSERT_TRUE(tests.EqMatrix(result));
}

TEST(test_functional, eq_mul_operator_num) {
  int rows = 2;
  int cols = 3;

  S21Matrix tests(rows, cols);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      tests(i, j) = c++;
    }
  }
  tests *= 2;

  S21Matrix result(2, 3);
  result(0, 0) = 2;
  result(0, 1) = 4;
  result(0, 2) = 6;
  result(1, 0) = 8;
  result(1, 1) = 10;
  result(1, 2) = 12;

  ASSERT_TRUE(tests.EqMatrix(result));
}

TEST(test_functional, mul_operator) {
  int rows = 2;
  int cols = 3;

  S21Matrix tests(rows, cols);
  S21Matrix tests_1(cols, rows);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      tests(i, j) = c++;
    }
  }

  for (int i = 0, c = 7; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      tests_1(i, j) = c++;
    }
  }

  tests = tests * tests_1;
  S21Matrix result(2, 2);
  result(0, 0) = 58;
  result(0, 1) = 64;
  result(1, 0) = 139;
  result(1, 1) = 154;

  ASSERT_TRUE(tests.EqMatrix(result));
}

TEST(test_functional, mul_operator_num) {
  int rows = 2;
  int cols = 3;

  S21Matrix tests(rows, cols);

  for (int i = 0, c = 1; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      tests(i, j) = c++;
    }
  }
  tests = tests * 2;

  S21Matrix result(2, 3);
  result(0, 0) = 2;
  result(0, 1) = 4;
  result(0, 2) = 6;
  result(1, 0) = 8;
  result(1, 1) = 10;
  result(1, 2) = 12;

  ASSERT_TRUE(tests.EqMatrix(result));
}

TEST(test_functional, transpose) {
  int rows = 2;
  int cols = 3;

  S21Matrix tests(rows, cols);
  S21Matrix tests_1(cols, rows);
  double c = 1.0;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      c += 1.0;
      tests(i, j) = c;
      tests_1(j, i) = c;
    }
  }
  //  std::cout << "tests" << tests.GetRows() << " " << tests.GetCols() <<
  //  std::endl;
  // std::cout << "tests_1" << tests_1.GetRows() << " " << tests_1.GetCols() <<
  // std::endl;
  tests = tests.Transpose();

  ASSERT_TRUE(tests == tests_1);
}

//исключение
TEST(test_functional, determinant) {
  S21Matrix tests(2, 3);

  EXPECT_ANY_THROW(tests.Determinant());
}

TEST(test_functional, determinant_zero) {
  int size = 5;
  S21Matrix tests(5, 5);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      tests(i, j) = j;
    }
  }
  ASSERT_NEAR(0, tests.Determinant(), epsilon);
}

TEST(test_functional, determinant_5) {
  int size = 5;
  S21Matrix tests(size, size);

  tests(0, 1) = 6;
  tests(0, 2) = -2;
  tests(0, 3) = -1;
  tests(0, 4) = 5;
  tests(1, 3) = -9;
  tests(1, 4) = -7;
  tests(2, 1) = 15;
  tests(2, 2) = 35;
  tests(3, 1) = -1;
  tests(3, 2) = -11;
  tests(3, 3) = -2;
  tests(3, 4) = 1;
  tests(4, 0) = -2;
  tests(4, 1) = -2;
  tests(4, 2) = 3;
  tests(4, 4) = -2;

  double result = tests.Determinant();
  ASSERT_NEAR(result, 2480, epsilon);
}

TEST(test_functional, determinant_3) {
  int size = 3;
  S21Matrix tests(size, size);

  tests(0, 0) = 2;
  tests(0, 1) = 3;
  tests(0, 2) = 1;
  tests(1, 0) = 7;
  tests(1, 1) = 4;
  tests(1, 2) = 1;
  tests(2, 0) = 9;
  tests(2, 1) = -2;
  tests(2, 2) = 1;

  double result = tests.Determinant();
  ASSERT_NEAR(result, -32, epsilon);
}

TEST(test_functional, determinant_2) {
  int size = 2;
  S21Matrix tests(size, size);

  tests(0, 0) = -5;
  tests(0, 1) = -4;
  tests(1, 0) = -2;
  tests(1, 1) = -3;

  double result = tests.Determinant();
  ASSERT_NEAR(result, 7, epsilon);
}

TEST(test_functional, complements_throw) {
  S21Matrix tests(3, 12);
  EXPECT_ANY_THROW(tests.CalcComplements());
}

TEST(test_functional, complements_3) {
  int size = 3;
  S21Matrix tests(size, size);
  S21Matrix tests_1(size, size);

  tests(0, 0) = 0;
  tests(0, 1) = 10;
  tests(0, 2) = -20;
  tests(1, 0) = 4;
  tests(1, 1) = -14;
  tests(1, 2) = 8;
  tests(2, 0) = -8;
  tests(2, 1) = -2;
  tests(2, 2) = 4;

  tests_1(0, 0) = 1;
  tests_1(0, 1) = 2;
  tests_1(0, 2) = 3;
  tests_1(1, 0) = 0;
  tests_1(1, 1) = 4;
  tests_1(1, 2) = 2;
  tests_1(2, 0) = 5;
  tests_1(2, 1) = 2;
  tests_1(2, 2) = 1;

  S21Matrix result = tests_1.CalcComplements();
  ASSERT_TRUE(result == tests);
}

TEST(test_functional, complements_3_1) {
  int size = 3;
  S21Matrix tests(size, size);
  S21Matrix tests_1(size, size);

  tests(0, 0) = 1.0;
  tests(0, 1) = 2.0;
  tests(0, 2) = 3.0;
  tests(1, 0) = 0.0;
  tests(1, 1) = 4.0;
  tests(1, 2) = 2.0;
  tests(2, 0) = 5.0;
  tests(2, 1) = 2.0;
  tests(2, 2) = 1.0;

  tests_1(0, 0) = 0.0;
  tests_1(0, 1) = 10.0;
  tests_1(0, 2) = -20.0;
  tests_1(1, 0) = 4.0;
  tests_1(1, 1) = -14.0;
  tests_1(1, 2) = 8.0;
  tests_1(2, 0) = -8.0;
  tests_1(2, 1) = -2.0;
  tests_1(2, 2) = 4.0;

  S21Matrix result = tests.CalcComplements();
  ASSERT_TRUE(result == tests_1);
}

TEST(test_functional, complements_3_2) {
  int size = 3;
  S21Matrix tests(size, size);
  S21Matrix tests_1(size, size);

  tests(0, 0) = 1;
  tests(0, 1) = 2;
  tests(0, 2) = 3;
  tests(1, 1) = 4;
  tests(1, 2) = 2;
  tests(2, 0) = 5;
  tests(2, 1) = 2;
  tests(2, 2) = 1;

  tests_1(0, 1) = 10;
  tests_1(0, 2) = -20;
  tests_1(1, 0) = 4;
  tests_1(1, 1) = -14;
  tests_1(1, 2) = 8;
  tests_1(2, 0) = -8;
  tests_1(2, 1) = -2;
  tests_1(2, 2) = 4;

  S21Matrix result = tests.CalcComplements();
  ASSERT_TRUE(result == tests_1);
}

TEST(test_functional, inverse_3_3) {
  int size = 3;
  S21Matrix tests(size, size);
  S21Matrix tests_1(size, size);

  tests(0, 0) = 44300.0 / 367429.0;
  tests(0, 1) = -236300.0 / 367429.0;
  tests(0, 2) = 200360.0 / 367429.0;
  tests(1, 0) = 20600.0 / 367429.0;
  tests(1, 1) = 56000.0 / 367429.0;
  tests(1, 2) = -156483.0 / 367429.0;
  tests(2, 0) = 30900.0 / 367429.0;
  tests(2, 1) = 84000.0 / 367429.0;
  tests(2, 2) = -51010.0 / 367429.0;

  tests_1(0, 0) = 2.8;
  tests_1(0, 1) = 1.3;
  tests_1(0, 2) = 7.01;
  tests_1(1, 0) = -1.03;
  tests_1(1, 1) = -2.3;
  tests_1(1, 2) = 3.01;
  tests_1(2, 0) = 0;
  tests_1(2, 1) = -3;
  tests_1(2, 2) = 2;

  ASSERT_TRUE(tests_1.InverseMatrix() == tests);
}

TEST(test_functional, inverse_3_3_1) {
  int size = 3;
  S21Matrix tests(size, size);
  S21Matrix tests_1(size, size);

  tests(0, 0) = 1.0;
  tests(0, 1) = -1.0;
  tests(0, 2) = 1.0;
  tests(1, 0) = -38.0;
  tests(1, 1) = 41.0;
  tests(1, 2) = -34.0;
  tests(2, 0) = 27.0;
  tests(2, 1) = -29.0;
  tests(2, 2) = 24.0;

  tests_1(0, 0) = 2.0;
  tests_1(0, 1) = 5.0;
  tests_1(0, 2) = 7.0;
  tests_1(1, 0) = 6.0;
  tests_1(1, 1) = 3.0;
  tests_1(1, 2) = 4.0;
  tests_1(2, 0) = 5.0;
  tests_1(2, 1) = -2.0;
  tests_1(2, 2) = -3.0;

  ASSERT_TRUE(tests_1.InverseMatrix() == tests);
}

//Данный тест проверяет, что метод InverseMatrix() класса S21Matrix
//выбрасывает исключение при попытке вычислить обратную матрицу для
//матрицы m размером 2x3 и матрицы n размером 2x2.
TEST(test_functional, inverse_throw) {
  S21Matrix tests(2, 3);
  EXPECT_ANY_THROW(tests.InverseMatrix());

  S21Matrix tests_1(2, 2);
  EXPECT_ANY_THROW(tests_1.InverseMatrix());
}

//Данный тест проверяет, что метод InverseMatrix() класса S21Matrix
//правильно вычисляет обратную матрицу для матрицы m размером 1x1.
TEST(test_functional, inverse_1x1) {
  S21Matrix tests(1, 1);
  tests(0, 0) = 69.420;

  double expected = 1 / tests(0, 0);

  double result = tests.InverseMatrix()(0, 0);

  ASSERT_NEAR(expected, result, 1e-06);
}

TEST(test_functional, brackets_const) {
  const S21Matrix tests(3, 3);

  ASSERT_EQ(tests(0, 0), 0);
}

TEST(test_functional, set_rows) {
  S21Matrix tests;
  tests.SetRows(5);
  S21Matrix tests_1;
  tests_1.SetCols(5);

  EXPECT_EQ(tests.GetRows(), 5);
  EXPECT_EQ(tests.GetCols(), 0);
  EXPECT_EQ(tests_1.GetCols(), 5);
  EXPECT_EQ(tests_1.GetRows(), 0);
}

int main() {
  testing::InitGoogleTest();
  if (RUN_ALL_TESTS()) {
    std::cout << "Tests have failed " << std::endl;
  };
}