#-------------------------------------------------
#
# Project created by QtCreator 2015-06-02T12:15:42
#
#-------------------------------------------------

QT       += core gui\
            sql\
            network\


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MSO
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

include(Services.pri)
include(SQLTable.pri)

RESOURCES += \
    resource.qrc

RC_FILE = MSO.rc

TRANSLATIONS =  MSO_ru.ts
