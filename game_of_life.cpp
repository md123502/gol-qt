#include "game_of_life.h"

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

GameOfLife::GameOfLife() {
    set_default_rules();
}

size_t count_neighbours(Matrix& matrix, size_t x, size_t y);

void GameOfLife::next_step() {
    Matrix result(matrix_);
    size_t matrix_height = matrix_.get_height();
    size_t matrix_width = matrix_.get_width();
    for (size_t i = 0; i < matrix_height; ++i) {
        for (size_t j = 0; j < matrix_width; ++j) {
            size_t neighbours_number = count_neighbours(matrix_, i, j);
            if (matrix_.cell_is_alive(i, j)) {
                if (!rules_.to_stay_alive[neighbours_number]) {
                    result.set_cell(State::DEAD, i, j);
                }
            }
            else {
                if (rules_.to_born[neighbours_number]) {
                    result.set_cell(State::ALIVE, i, j);
                }
            }
        }
    }
    matrix_ = std::move(result);
}

bool get_params(std::ifstream& input, size_t& width, size_t& height,
                Rules& rules);

bool read_pattern(std::ifstream& input, size_t width, size_t height,
                  bool* pattern);

bool GameOfLife::initialize_game(std::string filename) {
    std::ifstream input(filename.c_str());
    if (!input.is_open()) {
        return false;
    }
    size_t width_got = 0;
    size_t height_got = 0;
    Rules rules_got;
    for (size_t i = 0; i < possible_neighbours_number; ++i) {
        rules_got.to_born[i] = false;
    }
    for (size_t i = 0; i < possible_neighbours_number; ++i) {
        rules_got.to_stay_alive[i] = false;
    }
    if (!get_params(input, width_got, height_got, rules_got)) {
        return false;
    }
    bool* pattern = new bool[width_got * height_got];
    std::fill(pattern, pattern + width_got * height_got, false);
    if (!read_pattern(input, width_got, height_got, pattern)) {
        delete[] pattern;
        return false;
    }
    rules_.to_born = rules_got.to_born;
    rules_.to_stay_alive = rules_got.to_stay_alive;
    matrix_ = Matrix(width_got, height_got, pattern);
    delete[] pattern;
    return true;
}

void GameOfLife::reset() {
    set_default_matrix();
    set_default_rules();
}

void GameOfLife::set_default_rules() {
    for (size_t i = 0; i < possible_neighbours_number; ++i) {
        rules_.to_born[i] = false;
    }
    rules_.to_born[3] = true;
    for (size_t i = 0; i < possible_neighbours_number; ++i) {
        rules_.to_stay_alive[i] = false;
    }
    rules_.to_stay_alive[2] = true;
    rules_.to_stay_alive[3] = true;
}

bool GameOfLife::check_rule(RuleTypeId rule_type_id, size_t id) {
    assert(possible_neighbours_number > id);
    if (RuleTypeId::TO_BORN == rule_type_id) {
        return is_to_born(id);
    }
    else {
        return is_to_stay_alive(id);
    }
}

void GameOfLife::set_rule(bool state, RuleTypeId rule_type_id, size_t id) {
    assert(possible_neighbours_number > id);
    if (RuleTypeId::TO_BORN == rule_type_id) {
        set_to_born(state, id);
    }
    else {
        set_to_stay_alive(state, id);
    }
}

CellState GameOfLife::cell_state(size_t i, size_t j) {
    if (matrix_.cell_is_alive(i, j)) {
        return CellState::ALIVE;
    }
    else {
        return CellState::DEAD;
    }
}

void GameOfLife::set_cell(CellState state, size_t i, size_t j) {
    if (CellState::ALIVE == state) {
        matrix_.set_cell(State::ALIVE, i, j);
    }
    else {
        matrix_.set_cell(State::DEAD, i, j);
    }
}

size_t GameOfLife::matrix_height() const {
    return matrix_.get_height();
}

size_t GameOfLife::matrix_width() const {
    return matrix_.get_width();
}

void GameOfLife::set_default_matrix() {
    matrix_ = Matrix();
}

bool GameOfLife::is_to_born(size_t number) {
    assert(possible_neighbours_number > number);
    return rules_.to_born[number];
}

void GameOfLife::set_to_born(bool state, size_t number) {
    assert(possible_neighbours_number > number);
    rules_.to_born[number] = state;
}

bool GameOfLife::is_to_stay_alive(size_t number) {
    assert(possible_neighbours_number > number);
    return rules_.to_stay_alive[number];
}

void GameOfLife::set_to_stay_alive(bool state, size_t number) {
    assert(possible_neighbours_number > number);
    rules_.to_stay_alive[number] = state;
}

int toroidal_coord(const int range, const int coord) {
    return ((coord < 0) ? (range + coord) : (coord % range));
}

size_t count_neighbours(Matrix& matrix, size_t i, size_t j) {
    size_t result = 0;
    size_t height = matrix.get_height();
    size_t width = matrix.get_width();
    result += (matrix.cell_is_alive(toroidal_coord(height, i - 1),
                                    toroidal_coord(width, j - 1))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i - 1),
                                    toroidal_coord(width, j))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i - 1),
                                    toroidal_coord(width, j + 1))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i),
                                    toroidal_coord(width, j - 1))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i),
                                    toroidal_coord(width, j + 1))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i + 1),
                                    toroidal_coord(width, j - 1))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i + 1),
                                    toroidal_coord(width, j))) ? 1 : 0;
    result += (matrix.cell_is_alive(toroidal_coord(height, i + 1),
                                    toroidal_coord(width, j + 1))) ? 1 : 0;
    return result;
}

bool read_pattern(std::ifstream& input, size_t width, size_t height,
                  bool* pattern) {
    char sym = input.get();
    size_t i = 0;
    size_t j = 0;
    size_t j1 = 0;  //int number needs to be initialized as 0 and not 1 in order
    size_t number = 0;  //to work with not one-digit numbers starting with 1
    while ('!' != sym) {
        while (('$' != sym) && ('!' != sym)) {
            if ((isdigit(sym)) && (0 == number) && ('0' != sym)) { //First digit in number
                number = sym - '0';
                if (number > width) {
                    return false;
                }
            }
            else if ((isdigit(sym)) && (0 != number)) { //Not first digit, so number is not one-digit
                number = number * 10 + (sym - '0');
                if (number > width) {
                    return false;
                }
            }
            else if ('o' == sym) {  //Setting cells alive
                j1 = j + ((0 == number) ? 1 : number);
                while(j < j1) {
                    pattern[width * i + j] = true;
                    j++;
                }
                number = 0;
            }
            else if ('b' == sym) {  //Leaving cells dead
                j += ((0 == number) ? 1 : number);
                number = 0;
            }
            else {
                return false;
            }
            sym = input.get();
        }
        ++i;
        if (height <= i) {
            return false;
        }
        j = 0;
        if (0 != number) { //Digit was the last symbol in line
            return false;
        }
        if ('!' != sym) {
            sym = input.get();
        }
    }
    return true;
}

bool interpret_rules_in_numbers_as_arrays(size_t rule_to_born_as_number,
                                          size_t rule_to_stay_alive_as_number,
                                          Rules& rules) {
    while (0 < rule_to_born_as_number) {
        size_t cur_digit = rule_to_born_as_number % 10;
        if ((9 == cur_digit) || (true == rules.to_born[cur_digit])) {
            return false;
        }
        rules.to_born[cur_digit] = true;
        rule_to_born_as_number /= 10;
    }
    while (0 < rule_to_stay_alive_as_number) {
        size_t cur_digit = rule_to_stay_alive_as_number % 10;
        if ((9 == cur_digit) || (true == rules.to_stay_alive[cur_digit])) {
            return false;
        }
        rules.to_stay_alive[cur_digit] = true;
        rule_to_stay_alive_as_number /= 10;
    }
    return true;
}

bool parse_params_line(std::string& line, size_t& width, size_t& height,
                       Rules& rules) {
    std::stringstream cur_line(line);
    int cur_sym = ' ';
    std::string string_read;
    bool got_parameter = false;
    size_t rule_to_born_as_number = 0;
    size_t rule_to_stay_alive_as_number = 0;
    for (size_t i = 0; i < 4; ++i) {
        while (true) {
            cur_sym = cur_line.get();
            if (cur_line.eof()) {
                break;
            }
            if (!isdigit(cur_sym)) {
                string_read.push_back(cur_sym);
            }
            else {
                if (0 == i) {
                    if (std::string("x = ") == string_read) {
                        cur_line.unget();
                        cur_line >> width;
                        got_parameter = true;
                    }
                    break;
                }
                else if (1 == i) {
                    if (std::string(", y = ") == string_read) {
                        cur_line.unget();
                        cur_line >> height;
                        got_parameter = true;
                    }
                    break;
                }
                else if (2 == i) {
                    if (std::string(", rule = B") == string_read) {
                        cur_line.unget();
                        cur_line >> rule_to_born_as_number;
                        got_parameter = true;
                    }
                    break;
                }
                else if (3 == i) {
                    if (std::string("/S") == string_read) {
                        cur_line.unget();
                        cur_line >> rule_to_stay_alive_as_number;
                        got_parameter = true;
                    }
                    break;
                }
            }
        }
        if (!got_parameter) {
            return false;
        }
        got_parameter = false;
        string_read.clear();
    }
    if (!interpret_rules_in_numbers_as_arrays(rule_to_born_as_number,
                                              rule_to_stay_alive_as_number,
                                              rules)) {
        return false;
    }
    return true;
}

bool get_params(std::ifstream& input, size_t& width, size_t& height,
                Rules& rules) {
    while (!input.eof()) {
        std::string line;
        std::getline(input, line);
        if ('#' != line[0]) {
            if (!parse_params_line(line, width, height, rules)) {
                return false;
            }
            break;
        }
    }
    return true;
}
