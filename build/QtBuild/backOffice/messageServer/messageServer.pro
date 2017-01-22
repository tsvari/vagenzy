TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEFINES += ELPP_NO_DEFAULT_LOG_FILE
DEFINES += PROJECT_NAME=\\\"msgSrv\\\"

SOURCES += \
    ../../../../source/backOffice/messageServer/main.cpp \
    ../../../../source/backOffice/messageServer/addemployeetojob.cpp \
    ../../../../source/backOffice/messageServer/checkjob.cpp \
    ../../../../source/backOffice/messageServer/configfile.cpp \
    ../../../../source/backOffice/messageServer/dbjobsloader.cpp \
    ../../../../source/backOffice/messageServer/removeemployee.cpp \
    ../../../../source/backOffice/messageServer/removeemployeefromjob.cpp \
    ../../../../source/backOffice/messageServer/zparser.cpp \
    ../../../../source/backOffice/messageServer/zrpc.cpp \
    ../../../../source/backOffice/messageServer/zvalidator.cpp \
    ../../../../source/backOffice/global/zbase.cpp

unix:!macx: LIBS += -lzmq

HEADERS += \
    ../../../../source/global/message_globals.h \
    ../../../../source/backOffice/messageServer/addemployeetojob.h \
    ../../../../source/backOffice/messageServer/checkjob.h \
    ../../../../source/backOffice/messageServer/configfile.h \
    ../../../../source/backOffice/messageServer/dbjobsloader.h \
    ../../../../source/backOffice/messageServer/jobregister.h \
    ../../../../source/backOffice/messageServer/removeemployee.h \
    ../../../../source/backOffice/messageServer/removeemployeefromjob.h \
    ../../../../source/backOffice/messageServer/zparser.h \
    ../../../../source/backOffice/messageServer/zrpc.h \
    ../../../../source/backOffice/messageServer/zvalidator.h \
    ../../../../source/backOffice/global/zbase.h \
    ../../../../source/backOffice/global/data_globals.h \
    ../../../../source/global/zmq_addon.hpp \
    ../../../../source/global/zmq.hpp

unix:!macx: LIBS += -lpthread
