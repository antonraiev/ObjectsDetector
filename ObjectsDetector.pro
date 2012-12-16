#-------------------------------------------------
#
# Project created by QtCreator 2012-12-16T13:12:55
#
#-------------------------------------------------

QT       += core gui network

LIBS += /usr/local/lib/libopencv_legacy.so
LIBS += /usr/local/lib/libopencv_ml.so
LIBS += /usr/local/lib/libopencv_calib3d.so
LIBS += /usr/local/lib/libopencv_nonfree.so
LIBS += /usr/local/lib/libopencv_contrib.so
LIBS += /usr/local/lib/libopencv_objdetect.so
LIBS += /usr/local/lib/libopencv_core.so
LIBS += /usr/local/lib/libopencv_photo.so
LIBS += /usr/local/lib/libopencv_features2d.so
LIBS += /usr/local/lib/libopencv_stitching.so
LIBS += /usr/local/lib/libopencv_flann.so
LIBS += /usr/local/lib/libopencv_ts.so
LIBS += /usr/local/lib/libopencv_gpu.so
LIBS += /usr/local/lib/libopencv_video.so
LIBS += /usr/local/lib/libopencv_highgui.so
LIBS += /usr/local/lib/libopencv_videostab.so
LIBS += /usr/local/lib/libopencv_imgproc.so

INCLUDEPATH += /usr/local/include/opencv
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObjectsDetector
TEMPLATE = app


SOURCES += main.cpp \
    camera/UsbCamera.cpp \
    camera/IPCamera.cpp \
    fuzzy/FuzzyGrid.cpp \
    tabs/VideoTab.cpp \
    tabs/MapTab.cpp \
    views/VideoView.cpp \
    MainWindow.cpp \
    cv/QtOpenCV.cpp \
    cv/CvSURF.cpp

HEADERS  += \
    MainWindow.h \
    resource.h \
    camera/UsbCamera.h \
    camera/IPCamera.h \
    camera/AbstractCamera.h \
    fuzzy/FuzzyGrid.h \
    tabs/VideoTab.h \
    tabs/MapTab.h \
    views/VideoView.h \
    cv/QtOpenCV.h \
    cv/CvSURF.h

RESOURCES += \
    resources.qrc

OTHER_FILES += \
    icon.rc
