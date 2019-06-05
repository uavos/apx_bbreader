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

INCLUDEPATH += /home/pavel/sources/build-apx-release/packages/sdk/include
LIBS += -L/home/pavel/sources/build-apx-release/packages/sdk/lib \
    -lApxCore \
    -lApxData \
    -lApxGcs

FORMS += \
    bbreaderform.ui
