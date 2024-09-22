#include "game_main_window.h"

#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QString>
#include <string>

#include "game.h"
#include "ui_game_main_window.h"

GameMainWindow::GameMainWindow(Game* cur_game, QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::GameMainWindow) {
    assert(nullptr != cur_game);
    ui->setupUi(this);
    timer_ = new QTimer(this);
    game_ = cur_game;
    ui->field->set_game(cur_game);
    QObject::connect(timer_, &QTimer::timeout, this,
                     &GameMainWindow::on_timeout);
    QObject::connect(ui->to_born_buttons, &QButtonGroup::idClicked, this,
                     &GameMainWindow::rule_to_born_checkbox_clicked);
    QObject::connect(ui->to_survive_buttons, &QButtonGroup::idClicked, this,
                     &GameMainWindow::rule_to_survive_checkbox_clicked);
    set_checkboxes_states();
}

GameMainWindow::~GameMainWindow() {
    delete ui;
    delete timer_;
}

void GameMainWindow::on_timeout() {
    game_->next_step();
    ui->field->repaint();
}

void GameMainWindow::on_load_button_clicked() {
    //following is needed to stop ongoing game if it was not stopped explicitly
    timer_->stop();
    enable_checkboxes();
    ui->field->set_game_running(false);

    QString qstring_filename = QFileDialog::getOpenFileName();
    std::string filename = qstring_filename.toStdString();
    if (!game_->initialize_game(filename)) {
        ui->info->setText(QString("Error!"));
    }
    else {
        ui->info->setText(QString());
        ui->field->repaint();
    }
}

int interval_for_timer(int speed) {
    return 1000 / speed;
}

void GameMainWindow::on_play_button_clicked() {
    disable_checkboxes();
    ui->field->set_game_running(true);//in order to inform ui->field

    int speed = ui->speed_box->value();
    timer_->start(interval_for_timer(speed));
}

void GameMainWindow::on_stop_button_clicked() {
    timer_->stop();
    enable_checkboxes();
    ui->field->set_game_running(false);

    ui->field->repaint();
}

void GameMainWindow::on_reset_button_clicked() {
    timer_->stop();
    enable_checkboxes();
    ui->field->set_game_running(false);

    game_->reset();
    set_checkboxes_states();
    ui->field->repaint();
}

void GameMainWindow::rule_to_born_checkbox_clicked(int id) {
    size_t actual_id_of_rule = abs(id + 2);//buttons id's are negative by default
    game_->set_rule(ui->to_born_buttons->button(id)->isChecked(),
                    RuleTypeId::TO_BORN, actual_id_of_rule);
}

void GameMainWindow::rule_to_survive_checkbox_clicked(int id) {
    size_t actual_id_of_rule = abs(id + 2);
    game_->set_rule(ui->to_survive_buttons->button(id)->isChecked(),
                    RuleTypeId::TO_SURVIVE, actual_id_of_rule);
}

void GameMainWindow::set_checkboxes_states() {
    for (int i = -2; i > -11 /*buttons id's are negative by default*/; --i) {
        size_t actual_id_of_rule = abs(i + 2);
        ui->to_born_buttons->button(i)->
                setChecked(game_->check_rule(RuleTypeId::TO_BORN,
                                             actual_id_of_rule));
    }
    for (int i = -2; i > -11; --i) {
        size_t actual_id_of_rule = abs(i + 2);
        ui->to_survive_buttons->button(i)->
                setChecked(game_->check_rule(RuleTypeId::TO_SURVIVE,
                                             actual_id_of_rule));
    }
}

void GameMainWindow::disable_checkboxes() {
    for (int i = -2; i > -11 /*buttons id's are negative by default*/; --i) {
        ui->to_born_buttons->button(i)-> setEnabled(false);
    }
    for (int i = -2; i > -11; --i) {
        ui->to_survive_buttons->button(i)-> setEnabled(false);
    }
}

void GameMainWindow::enable_checkboxes() {
    for (int i = -2; i > -11 /*buttons id's are negative by default*/; --i) {
        ui->to_born_buttons->button(i)-> setEnabled(true);
    }
    for (int i = -2; i > -11; --i) {
        ui->to_survive_buttons->button(i)-> setEnabled(true);
    }
}

void GameMainWindow::on_speed_box_valueChanged(int new_speed) {
    if (timer_->isActive()) {
        timer_->start(interval_for_timer(new_speed));
    }
}
