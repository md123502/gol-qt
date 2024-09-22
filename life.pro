QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game_field.cpp \
    game_of_life.cpp \
    main.cpp \
    game_main_window.cpp \
    matrix.cpp \
    ui_game_main_window.cpp

HEADERS += \
    game.h \
    game_field.h \
    game_main_window.h \
    game_of_life.h \
	matrix.h \
    ui_game_main_window.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
