QT       += core gui
QT       += multimedia
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    difficulty.cpp \
    gamearea.cpp \
    main.cpp \
    mainwindow.cpp \
    rankingdialog.cpp \
    registerdialog.cpp \
    sudoku.cpp

HEADERS += \
    difficulty.h \
    gamearea.h \
    mainwindow.h \
    rankingdialog.h \
    registerdialog.h \
    sudoku.h

FORMS += \
    difficulty.ui \
    mainwindow.ui \
    rankingdialog.ui \
    registerdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
