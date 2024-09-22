#include <QApplication>

#include "game_main_window.h"
#include "game_of_life.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GameOfLife game;
    GameMainWindow game_window(&game);
    game_window.show();
    return app.exec();
}
