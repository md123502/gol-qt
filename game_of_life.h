#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H
#include <array>
#include <string>
#include <memory>

#include "game.h"
#include "matrix.h"

constexpr size_t possible_neighbours_number = 9;

struct Rules {
    std::array<bool, possible_neighbours_number> to_born;
    std::array<bool, possible_neighbours_number> to_stay_alive;
};

class GameOfLife: public Game {
public:
    GameOfLife();
    ~GameOfLife() = default;
    void next_step() override;
    bool initialize_game(std::string filename) override;
    void reset() override;
    bool check_rule(RuleTypeId rule_type_id, size_t id) override;
    void set_rule(bool state, RuleTypeId rule_type_id, size_t id) override;
    CellState cell_state(size_t i, size_t j) override;
    void set_cell(CellState state, size_t i, size_t j) override;
    size_t matrix_height() const override;
    size_t matrix_width() const override;
private:
    Matrix matrix_;
    Rules rules_;

    void set_default_rules();
    void set_default_matrix();
    bool is_to_born(size_t number);
    void set_to_born(bool state, size_t number);
    bool is_to_stay_alive(size_t number);
    void set_to_stay_alive(bool state, size_t number);
};

#endif
