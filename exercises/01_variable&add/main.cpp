#include "../exercise.h"

// READ: 运算符 <https://zh.cppreference.com/w/cpp/language/expressions#.E8.BF.90.E7.AE.97.E7.AC.A6>

int main(int argc, char **argv) {
    // 定义变量 x
    int x = 5; // 可以根据需要修改 x 的值
    // 打印加法运算
    std::cout << x << " + " << x << " = " << x + x << std::endl;
    return 0;
}
