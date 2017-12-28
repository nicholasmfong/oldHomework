TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    namedsquare.cpp \
    rectangle.cpp \
    point.cpp
QMAKE_CXXFLAGS += -std=c++0x

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    namedsquare.h \
    rectangle.h \
    point.h

