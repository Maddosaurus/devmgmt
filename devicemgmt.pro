
QT          += core
QT          -= gui
QT          += xml
QT          += xmlpatterns

#CONFIG  += qxt
#QXT     += core gui


TARGET       = devicemgmt
CONFIG      += console
CONFIG      -= app_bundle

TEMPLATE     = app

INCLUDEPATH += /opt/local/include
INCLUDEPATH += /usr/local/Qxt/include
INCLUDEPATH += /usr/local/Qxt/include/QxtCore
INCLUDEPATH += /usr/local/Qxt/include/QxtWeb

linux {
    LIBS        += -lboost_system -lboost_serialization
}

macx {
    #sudo port install boost +universal-python27
    LIBS        += -L/opt/local/lib -lboost_system-mt -lboost_serialization-mt
}

SOURCES     += \
    src/main.cpp \
    src/communication/udpreceiver.cpp \
    src/app.cpp \
    src/onv.cpp \
    src/communication/udpsender.cpp \
    src/communication/tcpasyncclient.cpp \
    src/device/getsystemdateandtime.cpp \
    src/device/envelope.cpp \
    src/device/body.cpp \
    src/helper/xmlhelper.cpp \
    src/helper/usertokenhelper.cpp

HEADERS     += \
    src/communication/udpreceiver.h \
    src/app.h \
    src/onv.h \
    src/communication/udpsender.h \
    src/communication/tcpasyncclient.h \
    src/device/getsystemdateandtime.h \
    src/device/envelope.h \
    src/device/body.h \
    src/helper/xmlhelper.h \
    src/helper/usertokenhelper.h

OTHER_FILES += \
    xml/device.GetSystemDateAndTime.xml \
    xml/discover.xml \
    xml/getUsers.xml


