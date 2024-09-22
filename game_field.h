#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QTimer>

#include "game.h"

class GameField : public QWidget {
    Q_OBJECT
public:
    explicit GameField(QWidget *parent = nullptr);
    void set_game(Game* game);
    void set_game_running(bool state);
private:
    Game* game_ = nullptr;
    bool game_is_running_ = false;
    QBrush current_brush_;
    int cur_line_width_ = 1;
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
};

#endif
