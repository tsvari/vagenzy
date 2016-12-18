TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../../source/backOffice/messageServer/main.cpp


unix:!macx: LIBS += -lzmq

HEADERS += \
    ../../../source/global/message_globals.h
