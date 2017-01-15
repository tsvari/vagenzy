TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../../../source/backOffice/messageServerTest/main.cpp \
    ../../../../source/backOffice/messageServer/zparser.cpp \
    ../../../../source/backOffice/messageServerTest/zparsertest.cpp \
    ../../../../source/backOffice/messageServer/addemployeetojob.cpp \
    ../../../../source/backOffice/messageServer/removeemployeefromjob.cpp \
    ../../../../source/backOffice/messageServer/removeemployee.cpp \
    ../../../../source/backOffice/messageServer/checkjob.cpp \
    ../../../../source/backOffice/messageServer/zvalidator.cpp \
    ../../../../source/backOffice/global/zbase.cpp \
    ../../../../source/backOffice/messageServer/zrpc.cpp \
    ../../../../source/backOffice/messageServerTest/zvalidatortest.cpp \
    ../../../../source/backOffice/messageServerTest/zrpctest.cpp \
    ../../../../source/backOffice/messageServerTest/addemployeetojobtest.cpp \
    ../../../../source/backOffice/messageServerTest/checkjobtest.cpp \
    ../../../../source/backOffice/messageServerTest/removeemployeefromjobtest.cpp \
    ../../../../source/backOffice/messageServerTest/removeemployeetest.cpp

HEADERS += \
    ../../../../source/backOffice/messageServer/zparser.h \
    ../../../../source/backOffice/messageServer/addemployeetojob.h \
    ../../../../source/backOffice/messageServer/removeemployeefromjob.h \
    ../../../../source/backOffice/messageServer/removeemployee.h \
    ../../../../source/backOffice/messageServer/checkjob.h \
    ../../../../source/backOffice/messageServer/zvalidator.h \
    ../../../../source/global/data_globals.h \
    ../../../../source/backOffice/global/zbase.h \
    ../../../../source/backOffice/global/data_globals.h \
    ../../../../source/global/message_globals.h \
    ../../../../source/backOffice/messageServer/zrpc.h \
    ../../../../source/backOffice/messageServerTest/basetestclass.hpp


unix:!macx: LIBS += -pthread
unix:!macx: LIBS += -lgtest
unix:!macx: LIBS += -lgmock
