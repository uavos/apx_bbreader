QT += quick widgets positioning sql

TARGET = apx_bbreader
TEMPLATE = lib

CONFIG += plugin c++14 silent

DESTDIR = bin
OBJECTS_DIR = obj
UI_DIR = $$OBJECTS_DIR
MOC_DIR = $$OBJECTS_DIR
target.path = ~/Документы/UAVOS/Plugins/
INSTALLS += target

SOURCES += \
    EscReader.cpp \
    bbreaderform.cpp \
    bbreaderplugin.cpp

HEADERS += \
    EscReader.h \
    bbreaderform.h \
    bbreaderplugin.h \
    escaped.h \
    node.h

INCLUDEPATH += /opt/apx_sdk/include/ApxGcs
INCLUDEPATH += /opt/apx_sdk/include/ApxCore
INCLUDEPATH += /opt/apx_sdk/include/ApxData
INCLUDEPATH += /opt/apx_sdk/include/ApxShared/
LIBS += -L/opt/apx_sdk/lib \
    -lApxCore \
    -lApxData \
    -lApxGcs

FORMS += \
    bbreaderform.ui
