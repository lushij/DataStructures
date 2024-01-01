#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = { 2,69,67,34,24};
    std::vector<int> record = { 2, 69 };

    // 创建一个新的 vector 用于存放 arr 中比 record 多的元素
    std::vector<int> remain;

    // 使用 std::set_difference 算法找到 arr 中相对于 record 的差异
    std::set_difference(arr.begin(), arr.end(), record.begin(), record.end(), std::back_inserter(remain));

    // 打印 remain 中的元素
    std::cout << "remain: ";
    for (int num : remain) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
