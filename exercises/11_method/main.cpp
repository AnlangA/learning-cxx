#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        if (i < cached) {
            return cache[i]; // 如果已缓存，直接返回
        }
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2]; // 计算并缓存
        }
        cached = i + 1; // 更新已缓存的数量
        return cache[i];
    }

    Fibonacci() : cached(2) { // 初始化缓存结构体
        cache[0] = 0;
        cache[1] = 1;
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体，使计算正确
    Fibonacci fib; // 创建 Fibonacci 对象
    fib.get(0); // 预先计算并缓存第一个 Fibonacci 数
    fib.get(1); // 预先计算并缓存第二个 Fibonacci 数
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
