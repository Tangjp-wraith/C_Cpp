#include <cstddef>
#include <iostream>
#include <vector>

// incr order
void bubble_sort(std::vector<int>& arr) {
  if (arr.size() <= 1) {
    return;
  }
  for (size_t i = 0; i < arr.size() - 1; ++i) {
    size_t curr_pos = i;
    for (size_t j = arr.size() - 1; j > curr_pos; --j) {
      if (arr[j] < arr[j - 1]) {
        std::swap(arr[j], arr[j - 1]);
      }
    }
  }
}

void selection_sort(std::vector<int>& arr) {
  if (arr.size() <= 1) {
    return;
  }
  for (size_t i = 0; i < arr.size() - 1; ++i) {
    size_t target_pos = i;
    size_t smallest_pos = target_pos;
    for (size_t j = arr.size() - 1; j > target_pos; --j) {
      if (arr[j] < arr[smallest_pos]) {
        smallest_pos = j;
      }
    }
    std::swap(arr[smallest_pos], arr[target_pos]);
  }
}

void insertion_sort(std::vector<int>& arr) {
  if (arr.size() <= 1) {
    return;
  }
  for (size_t i = 0; i < arr.size() - 1; ++i) {
    for (size_t j = i; j > 0; --j) {
      if (arr[j] < arr[j - 1]) {
        std::swap(arr[j], arr[j - 1]);
      } else {
        break;
      }
    }
  }
}

void print(std::vector<int>& arr) {
  for (auto num : arr) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
}

int main() {
  {
    std::vector<int> arr = {3, 2, 1, 4, 5};
    bubble_sort(arr);
    print(arr);
  }
  {
    std::vector<int> arr = {3, 2, 1, 4, 5};
    selection_sort(arr);
    print(arr);
  }
  {
    std::vector<int> arr = {3, 2, 1, 4, 5};
    insertion_sort(arr);
    print(arr);
  }
}