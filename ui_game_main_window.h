#ifndef UI_GAME_MAIN_WINDOW_H
#define UI_GAME_MAIN_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "game_field.h"

QT_BEGIN_NAMESPACE

class Ui_GameMainWindow {
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    GameField *field;
    QWidget *options;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_7;
    QPushButton *load_button;
    QLabel *info;
    QPushButton *reset_button;
    QGridLayout *gridLayout;
    QGroupBox *to_born_box;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QCheckBox *b_zero;
    QCheckBox *b_one;
    QCheckBox *b_two;
    QCheckBox *b_three;
    QCheckBox *b_four;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *b_five;
    QCheckBox *b_six;
    QCheckBox *b_seven;
    QCheckBox *b_eight;
    QGroupBox *to_survive_box;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *s_zero;
    QCheckBox *s_one;
    QCheckBox *s_two;
    QCheckBox *s_three;
    QCheckBox *s_four;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *s_five;
    QCheckBox *s_six;
    QCheckBox *s_seven;
    QCheckBox *s_eight;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *speed_box;
    QPushButton *play_button;
    QPushButton *stop_button;
    QStatusBar *statusbar;
    QButtonGroup *to_survive_buttons;
    QButtonGroup *to_born_buttons;

    void setupUi(QMainWindow *GameMainWindow);
    void retranslateUi(QMainWindow *GameMainWindow);
};

namespace Ui {
    class GameMainWindow: public Ui_GameMainWindow {};
}

QT_END_NAMESPACE

#endif
