#ifndef GAME_H
#define GAME_H
#include <array>
#include <string>
#include <memory>

enum class RuleTypeId: bool {
    TO_BORN,
    TO_SURVIVE
};

enum class CellState: bool {
    DEAD,
    ALIVE,
};

class Game {
public:
    Game() = default;
    virtual ~Game() = default;
    virtual void next_step() = 0;
    virtual bool initialize_game(std::string filename) = 0;
    virtual void reset() = 0;
    virtual bool check_rule(RuleTypeId rule_type_id, size_t id) = 0;
    virtual void set_rule(bool state, RuleTypeId rule_type_id, size_t id) = 0;
    virtual CellState cell_state(size_t i, size_t j) = 0;
    virtual void set_cell(CellState state, size_t i, size_t j) = 0;
    virtual size_t matrix_height() const = 0;
    virtual size_t matrix_width() const = 0;
};

#endif
