QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    JQCPUMonitor/jqcpumonitor.cpp \
    computerinfo.cpp \
    main.cpp \
    mainwindow.cpp \
    traymenu.cpp

HEADERS += \
    JQCPUMonitor/jqcpumonitor.h \
    JQCPUMonitor/jqcpumonitor.inc \
    computerinfo.h \
    mainwindow.h \
    traymenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/libusb-1.0.24/ -lusb-1.0

INCLUDEPATH += $$PWD/libusb-1.0.24
INCLUDEPATH += $$PWD/JQCPUMonitor
DEPENDPATH += $$PWD/libusb-1.0.24

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libusb-1.0.24/libusb-1.0.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/libusb-1.0.24/libusb-1.0.a

RESOURCES += \
    Resource.qrc
