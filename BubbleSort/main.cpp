#include <iostream>
#include <algorithm>

struct Point {
  int x = 0;
  int y = 0;

  Point() = default;
  Point(int _x, int _y) : x(_x), y(_y) {}
  bool operator<(const Point& other);
};

bool Point::operator<(const Point& other) {
  if (x == other.x) {
    return y < other.y;
  }
  return x < other.x;
}

// Вариант 1. Использует оператор <
void BubbleSort(Point* array, int size) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - i - 1; ++j) {
      if (array[j + 1] < array[j]) std::swap(array[j], array[j + 1]);
    }
  }
}

// Вариант 2. Использует функцию сравнения
void BubbleSort(Point* array, int size,
    bool (*compare)(const Point&, const Point&)) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - i - 1; ++j) {
      if (compare(array[j + 1], array[j])) std::swap(array[j], array[j + 1]);
    }
  }
}

// Вариант 3. Использует все что угодно, что имеет ().
template<class Compare>
void BubbleSort2(Point* array, int size, const Compare& compare) {
  for (int i = 0; i < size - 1; ++i) {
    for (int j = 0; j < size - i - 1; ++j) {
      if (compare(array[j + 1], array[j])) std::swap(array[j], array[j + 1]);
    }
  }
}

bool CompareByDistanceFromZero(const Point& first, const Point& second) {
  return (first.x * first.x + first.y * first.y) <
         (second.x * second.x + second.y * second.y);
}

class CompareByDistanceFrom {
 public:
  explicit CompareByDistanceFrom(const Point& center) : center_(center) {}

  bool operator()(const Point& first, const Point& second) const {
    int first_x_diff = first.x - center_.x;
    int first_y_diff = first.y - center_.y;
    int second_x_diff = second.x - center_.x;
    int second_y_diff = second.y - center_.y;
    return (first_x_diff * first_x_diff + first_y_diff * first_y_diff) <
           (second_x_diff * second_x_diff + second_y_diff * second_y_diff);
  }

 private:
  Point center_;
};

int main() {
  Point array[5] = {Point(2, 2), Point(0, 2), Point(1, 1), Point(2, 0)};
  BubbleSort(array, 5);
  BubbleSort2(array, 5, CompareByDistanceFromZero);
  BubbleSort2(array, 5, CompareByDistanceFrom(Point(1, 3)));

  std::sort(array, array + 5, CompareByDistanceFrom(Point(1, 3)));

  Point center(1, 3);
  BubbleSort2(array, 5, [&center](const Point& first, const Point& second) {
    int first_x_diff = first.x - center.x;
    int first_y_diff = first.y - center.y;
    int second_x_diff = second.x - center.x;
    int second_y_diff = second.y - center.y;
    return (first_x_diff * first_x_diff + first_y_diff * first_y_diff) <
           (second_x_diff * second_x_diff + second_y_diff * second_y_diff);
  });

  for (const Point& point : array) {
    std::cout << "[" << point.x << ", " << point.y << "], ";
  }
  std::cout << std::endl << "Hello, World!" << std::endl;
  return 0;
}