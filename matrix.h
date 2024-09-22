#ifndef MATRIX_H
#define MATRIX_H
#include <cstddef>
#include <vector>
#include <memory>

enum class State: bool {
    DEAD,
    ALIVE,
};

class Matrix {
public:
    Matrix();
    Matrix(size_t width, size_t height, const bool* pattern);
    ~Matrix() = default;
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);
    void set_cell(State state, size_t i, size_t j);
    bool cell_is_alive(size_t i, size_t j) const;
    size_t get_height() const;
    size_t get_width() const;
private:
    static const size_t default_height = 20;
    static const size_t default_width = 20;
    size_t height_ = default_height;
    size_t width_ = default_width;
    std::vector<std::vector<State>> matrix_;
};

#endif
