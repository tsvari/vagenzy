TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += MARKUP_STL

SOURCES += \
    ../../../../source/backOffice/messageServer/zparser.cpp \
    ../../../../source/backOffice/messageServer/addemployeetojob.cpp \
    ../../../../source/backOffice/messageServer/removeemployeefromjob.cpp \
    ../../../../source/backOffice/messageServer/removeemployee.cpp \
    ../../../../source/backOffice/messageServer/checkjob.cpp \
    ../../../../source/backOffice/messageServer/zvalidator.cpp \
    ../../../../source/backOffice/global/zbase.cpp \
    ../../../../source/backOffice/messageServer/zrpc.cpp \
    ../../../../source/backOffice/messageServer/configfile.cpp \
    ../../../../source/global/Markup.cpp \
    ../../../../source/backOffice/messageServer/dbjobsloader.cpp \
    ../../../../source/backOffice/messageServerTest/addemployeetojob_test.cpp \
    ../../../../source/backOffice/messageServerTest/checkjob_test.cpp \
    ../../../../source/backOffice/messageServerTest/removeemployeefromjob_test.cpp \
    ../../../../source/backOffice/messageServerTest/removeemployee_test.cpp \
    ../../../../source/backOffice/messageServerTest/zparser_test.cpp \
    ../../../../source/backOffice/messageServerTest/zrpc_test.cpp \
    ../../../../source/backOffice/messageServerTest/zvalidator_test.cpp \
    ../../../../source/backOffice/messageServerTest/main_test.cpp \
    ../../../../source/backOffice/messageServerTest/db_mock_fake_test.cpp

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
    ../../../../source/backOffice/messageServerTest/basetestclass.hpp \
    ../../../../source/backOffice/messageServer/configfile.h \
    ../../../../source/global/Markup.h \
    ../../../../source/backOffice/messageServer/dbjobsloader.h


unix:!macx: LIBS += -pthread
unix:!macx: LIBS += -lgtest
unix:!macx: LIBS += -lgmock
