#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
static int func(int param) {
    static int static_ = 0; // 初始化为0
    return static_++; // 返回当前值并自增
}

int main(int argc, char **argv) {
    // TODO: 将下列 `?` 替换为正确的数字
    ASSERT(func(5) == 0, "static variable value incorrect");
    ASSERT(func(4) == 1, "static variable value incorrect");
    ASSERT(func(3) == 2, "static variable value incorrect");
    ASSERT(func(2) == 3, "static variable value incorrect");
    ASSERT(func(1) == 4, "static variable value incorrect");
    return 0;
}
