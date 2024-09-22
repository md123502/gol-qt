#include "game_field.h"

#include <QVector>
#include <QLine>
#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include "game.h"

GameField::GameField(QWidget *parent) : QWidget(parent) {
    current_brush_ = QBrush(Qt::white);
}

void GameField::set_game(Game* game) {
    assert(nullptr != game);
    game_ = game;
}

void GameField::set_game_running(bool state) {
    game_is_running_ = state;
}

void GameField::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    int field_height = height();
    int field_width = width();
    QRect area = event->rect();
    struct coords {
        int x1;
        int y1;
        int x2;
        int y2;
    } area_coords;
    area.getCoords(&area_coords.x1, &area_coords.y1, &area_coords.x2,
                            &area_coords.y2);
    QPen pen = QPen(Qt::black);
    pen.setCosmetic(true);
    painter.setPen(pen);
    cur_line_width_ = painter.pen().width();
    if ((area.width() == field_width) &&
            (area.height() == field_height)) {
        size_t rows_num = game_->matrix_height();
        size_t columns_num = game_->matrix_width();
        size_t cell_height = field_height / rows_num;
        size_t cell_width = field_width / columns_num;
        QVector<QLine> lines_to_draw;
        for (size_t i = 0; i <= rows_num; ++i) {
            lines_to_draw.append(QLine(0, i * cell_height,
                                       cell_width * columns_num,
                                       i * cell_height));
        }
        for (size_t i = 0; i <= columns_num; ++i) {
            lines_to_draw.append(QLine(i * cell_width, 0, i * cell_width,
                                       cell_height * rows_num));
        }
        painter.drawLines(lines_to_draw);
        for (size_t i = 0; i < rows_num; ++i) {
            for (size_t j = 0; j < columns_num; ++j) {
                painter.fillRect(cell_width * j + cur_line_width_,
                                 cell_height * i + cur_line_width_,
                                 cell_width - 2 * cur_line_width_,
                                 cell_height - 2 * cur_line_width_,
                                 //multiplying pen_width is necessary
                                 //because we do not want to erase
                                 //neither first line nor second
                                 (CellState::ALIVE == (game_->cell_state(i, j)))
                                 ? QBrush(Qt::black) : QBrush(Qt::white));
            }
        }
    }
    else {
        //supposed to be a cell
        painter.fillRect(area_coords.x1, area_coords.y1, area.width(),
                         area.height(), current_brush_);
    }
}

void GameField::mousePressEvent(QMouseEvent *event) {
    if (!game_is_running_) {
        int field_height = height();
        int field_width = width();
        size_t rows_num = game_->matrix_height();
        size_t columns_num = game_->matrix_width();
        size_t cell_height = field_height / rows_num;
        size_t cell_width = field_width / columns_num;
        QPoint press_position = event->pos();
        size_t column_pressed = press_position.x() / cell_width;
        size_t row_pressed = press_position.y() / cell_height;
        if ((column_pressed >= columns_num) || (row_pressed >= rows_num)) {
            return;
        }
        bool dying = (CellState::ALIVE == (game_->cell_state(row_pressed,
                                                            column_pressed)));
        game_->set_cell((dying ? CellState::DEAD : CellState::ALIVE),
                        row_pressed, column_pressed);
        current_brush_ = QBrush(dying ? Qt::white : Qt::black);
        QRect area_to_update = QRect(
                    column_pressed * cell_width + cur_line_width_,
                    row_pressed * cell_height + cur_line_width_,
                    cell_width - 2 * cur_line_width_,//multiplying pen_width is
                                                     //necessary because we do
                                                     //not want to erase
                                                     //neither first line nor
                                                     //second
                    cell_height - 2 * cur_line_width_);
        update(area_to_update);
    }
}
