######################################################################
# Automatically generated by qmake (3.1) Tue May 7 11:53:38 2024
######################################################################

TEMPLATE = app
TARGET = ../../Bible
INCLUDEPATH += .

LIBS += ../../third-party/cJSON/libcjson.a

INCLUDEPATH += ../../third-party

QT += widgets core gui

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060000 # disables all APIs deprecated in Qt 6.0.0 and earlier

# Input
HEADERS += gui-main.h

SOURCES += gui-main.cc

SOURCES += ../*.c
SOURCES += ../*.cc
