#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = { 2,69,67,34,24};
    std::vector<int> record = { 2, 69 };

    // ����һ���µ� vector ���ڴ�� arr �б� record ���Ԫ��
    std::vector<int> remain;

    // ʹ�� std::set_difference �㷨�ҵ� arr ������� record �Ĳ���
    std::set_difference(arr.begin(), arr.end(), record.begin(), record.end(), std::back_inserter(remain));

    // ��ӡ remain �е�Ԫ��
    std::cout << "remain: ";
    for (int num : remain) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
