﻿#include "../exercise.h"
#include <cstring>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape_[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    Tensor4D &operator+=(Tensor4D const &others) {
        // Check if broadcast is possible
        for (int i = 0; i < 4; ++i) {
            if (others.shape[i] != 1 && others.shape[i] != shape[i]) {
                throw std::runtime_error("Shapes are incompatible for broadcasting");
            }
        }

        // Perform broadcast addition
        unsigned int strides[4] = {1, 1, 1, 1};
        for (int i = 3; i > 0; --i) {
            strides[i - 1] = strides[i] * others.shape[i];
        }

        unsigned int total_size = 1;
        for (int i = 0; i < 4; ++i) {
            total_size *= shape[i];
        }

        for (unsigned int idx = 0; idx < total_size; ++idx) {
            unsigned int coord[4];
            unsigned int temp_idx = idx;
            for (int i = 3; i >= 0; --i) {
                coord[i] = temp_idx % shape[i];
                temp_idx /= shape[i];
            }

            unsigned int other_idx = 0;
            for (int i = 0; i < 4; ++i) {
                if (others.shape[i] != 1) {
                    other_idx += coord[i] * strides[i];
                }
            }

            data[idx] += others.data[other_idx];
        }

        return *this;
    }
};

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        // clang-format off
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        auto t0 = Tensor4D(shape, data);
        auto t1 = Tensor4D(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,

            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        // clang-format on
        unsigned int s1[]{1, 2, 3, 1};
        // clang-format off
        float d1[]{
            6,
            5,
            4,

            3,
            2,
            1};
        // clang-format on

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        // clang-format off
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,

            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // clang-format on
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};

        auto t0 = Tensor4D(s0, d0);
        auto t1 = Tensor4D(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
}
