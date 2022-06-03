QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += core5compat

CONFIG += c++17 file_copies

CONFIG(debug, debug|release) {
    resources.files = $$PWD/etc
	resources.path = $$OUT_PWD/debug/
	opencv.files = $$PWD/etc/dll/opencv_world500d.dll
	opencv.path = $$OUT_PWD/debug/
} else {
    resources.files = $$PWD/etc
	resources.path = $$OUT_PWD/release/
	opencv.files = $$PWD/etc/dll/opencv_world500.dll
	opencv.path = $$OUT_PWD/release/
}
COPIES += resources opencv

# QMAKE_CXXFLAGS += /MT

SOURCES += \
    aboutdialog.cpp \
    cropwindow.cpp \
    file.cpp \
    imageinfodialog.cpp \
    imageutils.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    aboutdialog.h \
    cropwindow.h \
    error.h \
    file.h \
    imageinfodialog.h \
    imageutils.h \
    mainwindow.h

FORMS += \
    aboutdialog.ui \
    cropwindow.ui \
    imageinfodialog.ui \
    mainwindow.ui

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/libs/ -lopencvd
} else {
    LIBS += -L$$PWD/libs/ -lopencv
}

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    etc/dll/opencv_world500.dll \
    etc/dll/opencv_world500d.dll \
    etc/haarcascades/haarcascade_eye.xml \
    etc/haarcascades/haarcascade_eye_tree_eyeglasses.xml \
    etc/haarcascades/haarcascade_frontalcatface.xml \
    etc/haarcascades/haarcascade_frontalcatface_extended.xml \
    etc/haarcascades/haarcascade_frontalface_alt.xml \
    etc/haarcascades/haarcascade_frontalface_alt2.xml \
    etc/haarcascades/haarcascade_frontalface_alt_tree.xml \
    etc/haarcascades/haarcascade_frontalface_default.xml \
    etc/haarcascades/haarcascade_fullbody.xml \
    etc/haarcascades/haarcascade_lefteye_2splits.xml \
    etc/haarcascades/haarcascade_licence_plate_rus_16stages.xml \
    etc/haarcascades/haarcascade_lowerbody.xml \
    etc/haarcascades/haarcascade_profileface.xml \
    etc/haarcascades/haarcascade_righteye_2splits.xml \
    etc/haarcascades/haarcascade_russian_plate_number.xml \
    etc/haarcascades/haarcascade_smile.xml \
    etc/haarcascades/haarcascade_upperbody.xml \
    etc/icon/ic_zoom.ico \
    etc/lbpcascades/lbpcascade_frontalcatface.xml \
    etc/lbpcascades/lbpcascade_frontalface.xml \
    etc/lbpcascades/lbpcascade_frontalface_improved.xml \
    etc/lbpcascades/lbpcascade_profileface.xml \
    etc/lbpcascades/lbpcascade_silverware.xml \
    etc/licenses/SoftFloat-COPYING.txt \
    etc/licenses/ade-LICENSE \
    etc/licenses/ffmpeg-license.txt \
    etc/licenses/ffmpeg-readme.txt \
    etc/licenses/ippicv-EULA.rtf \
    etc/licenses/ippicv-readme.htm \
    etc/licenses/ippicv-third-party-programs.txt \
    etc/licenses/ippiw-EULA.rtf \
    etc/licenses/ippiw-support.txt \
    etc/licenses/ippiw-third-party-programs.txt \
    etc/licenses/ittnotify-LICENSE.BSD \
    etc/licenses/ittnotify-LICENSE.GPL \
    etc/licenses/libjpeg-turbo-LICENSE.md \
    etc/licenses/libjpeg-turbo-README.ijg \
    etc/licenses/libjpeg-turbo-README.md \
    etc/licenses/libopenjp2-LICENSE \
    etc/licenses/libopenjp2-README.md \
    etc/licenses/libpng-LICENSE \
    etc/licenses/libpng-README \
    etc/licenses/libtiff-COPYRIGHT \
    etc/licenses/opencl-headers-LICENSE.txt \
    etc/licenses/openexr-AUTHORS.ilmbase \
    etc/licenses/openexr-AUTHORS.openexr \
    etc/licenses/openexr-LICENSE \
    etc/licenses/protobuf-LICENSE \
    etc/licenses/protobuf-README.md \
    etc/licenses/quirc-LICENSE \
    etc/licenses/zlib-README
