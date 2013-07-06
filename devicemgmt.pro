
QT          += core
QT          -= gui
QT          += xml
QT          += xmlpatterns


TARGET       = devicemgmt
CONFIG      += console
CONFIG      -= app_bundle

TEMPLATE     = app

INCLUDEPATH += /opt/local/include

linux {
    LIBS        += -lboost_system
}

macx {
    #sudo port install boost +universal-python27
    LIBS        += -L/opt/local/lib -lboost_system-mt -lboost_serialization-mt
}

SOURCES     += \
    src/main.cpp \
    src/udpreceiver.cpp \
    app.cpp \
    onv.cpp \
    src/udpsender.cpp \
    src/tcpasyncclient.cpp \
    device/getsystemdateandtime.cpp \
    device/envelope.cpp \
    device/body.cpp \
    helper/xmlhelper.cpp

HEADERS     += \
    src/udpreceiver.h \
    app.h \
    onv.h \
    src/udpsender.h \
    src/tcpasyncclient.h \
    device/getsystemdateandtime.h \
    device/envelope.h \
    device/body.h \
    helper/xmlhelper.h

OTHER_FILES += \
    xml/device.GetSystemDateAndTime.xml \
    xml/discover.xml


