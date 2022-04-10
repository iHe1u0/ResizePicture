QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS_RELEASE += /MT -MD

#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    file.cpp \
    main.cpp \
    mainwindow.cpp \
    resize.cpp

HEADERS += \
    error.h \
    file.h \
    mainwindow.h \
    resize.h

FORMS += \
    mainwindow.ui

LIBS += -LD:/OpenCV4/x64/vc17/lib/ -lopencv_img_hash455
LIBS += -LD:/OpenCV4/x64/vc17/lib/ -lopencv_world455

INCLUDEPATH += D:/OpenCV_4/OpenCV4/include
DEPENDPATH += D:/OpenCV_4/OpenCV4/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
