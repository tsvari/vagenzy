TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../../../source/frontOffice/messageFromAppTest/main.cpp

unix:!macx: LIBS += -lzmq
