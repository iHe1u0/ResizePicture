QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17

QMAKE_CXXFLAGS += /MT

SOURCES += \
    file.cpp \
    imageinfodialog.cpp \
    imageutils.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    error.h \
    file.h \
    imageinfodialog.h \
    imageutils.h \
    mainwindow.h

FORMS += \
    imageinfodialog.ui \
    mainwindow.ui

LIBS += -L$$PWD/libs/ -lopencv_img_hash455
LIBS += -L$$PWD/libs/ -lopencv_world455

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
