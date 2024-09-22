#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "game.h"
#include "ui_game_main_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GameMainWindow; }
QT_END_NAMESPACE

class GameMainWindow : public QMainWindow {
    Q_OBJECT

public:
    GameMainWindow(Game* cur_game, QWidget *parent = nullptr);
    ~GameMainWindow();

private slots:    
    void on_timeout();
    void on_load_button_clicked();
    void on_play_button_clicked();
    void on_stop_button_clicked();
    void on_reset_button_clicked();
    void rule_to_born_checkbox_clicked(int id);
    void rule_to_survive_checkbox_clicked(int id);
    void on_speed_box_valueChanged(int new_speed);
private:
    Ui::GameMainWindow* ui;
    QTimer* timer_;
    Game* game_;
    void set_checkboxes_states();
    void disable_checkboxes();
    void enable_checkboxes();
};
#endif
