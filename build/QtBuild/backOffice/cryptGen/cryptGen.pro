TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../../../source/backOffice/cryptGen/main.cpp

unix:!macx: LIBS += -lssl
