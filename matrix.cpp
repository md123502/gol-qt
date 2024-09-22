#include "matrix.h"

#include <cassert>
#include <algorithm>

Matrix::Matrix() {
    matrix_ = std::vector<std::vector<State>>(default_height,
                  std::vector<State>(default_width, State::DEAD));
}

Matrix::Matrix(size_t width, size_t height, const bool* pattern) {
    matrix_ = std::vector<std::vector<State>>(height);
    height_ = height;
    width_ = width;
    for (size_t i = 0; i < height_; ++i) {
        std::vector<State> cur_row(width);
        for (size_t j = 0; j < width_; ++j) {
            cur_row[j] = ((true == pattern[width * i + j]) ? State::ALIVE :
                                                             State::DEAD);
        }
        matrix_[i] = cur_row;
    }
}

Matrix::Matrix(const Matrix& other) {
    width_ = other.width_;
    height_ = other.height_;
    matrix_ = std::vector<std::vector<State>>(other.matrix_);
}

Matrix::Matrix(Matrix&& other) {
    width_ = other.width_;
    height_ = other.height_;
    matrix_ = std::move(other.matrix_);
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    width_ = other.width_;
    height_ = other.height_;
    matrix_ = std::vector<std::vector<State>>(other.matrix_);
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) {
    if (this == &other) {
        return *this;
    }
    height_ = other.height_;
    other.height_ = 0;
    width_ = other.width_;
    other.width_ = 0;
    matrix_ = std::move(other.matrix_);
    return *this;
}

void Matrix::set_cell(State state, size_t i, size_t j) {
    assert(i < matrix_.size());
    assert(j < matrix_[i].size());
    matrix_[i][j] = state;
}

bool Matrix::cell_is_alive(size_t i, size_t j) const {
    assert(i < matrix_.size());
    assert(j < matrix_[i].size());
    return (State::ALIVE == matrix_[i][j]);
}

size_t Matrix::get_height() const {
    return height_;
}

size_t Matrix::get_width() const {
    return width_;
}
