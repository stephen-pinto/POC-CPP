#-------------------------------------------------
#
# Project created by QtCreator 2018-05-17T05:51:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SftpTransferClient
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    hash_generator.cpp \
    fs_scanner.cpp \
    generatehashform.cpp \
    fs_index_manager.cpp \
    test_unit_general.cpp

HEADERS += \
        mainwindow.h \
    ssl_test.h \
    hash_generator.h \
    fs_scanner.h \
    common.h \
    generatehashform.h \
    fs_index_manager.h \
    test_unit_general.h

FORMS += \
        mainwindow.ui \
    generatehashform.ui


win32: LIBS += -L"D:/Projects/ThirdPartyBuilds/PrebuiltBinaries/libssh2(openssl)/lib/" -llibssh2

INCLUDEPATH += $$PWD/'../../../../ThirdPartyBuilds/PrebuiltBinaries/libssh2(openssl)/include'
DEPENDPATH += $$PWD/'../../../../ThirdPartyBuilds/PrebuiltBinaries/libssh2(openssl)/include'

win32: LIBS += -L"D:/Projects/ThirdPartyBuilds/PrebuiltBinaries/openssl1.1.0/lib/" -llibssl
win32: LIBS += -L"D:/Projects/ThirdPartyBuilds/PrebuiltBinaries/openssl1.1.0/lib/" -llibcrypto

INCLUDEPATH += $$PWD/../../../../ThirdPartyBuilds/PrebuiltBinaries/openssl1.1.0/include
DEPENDPATH += $$PWD/../../../../ThirdPartyBuilds/PrebuiltBinaries/openssl1.1.0/include

win32: LIBS += -L"D:/Projects/ThirdPartyBuilds/PrebuiltBinaries/zlib1.2.8/lib/" -lzdll

INCLUDEPATH += $$PWD/../../../../ThirdPartyBuilds/PrebuiltBinaries/zlib1.2.8/include
DEPENDPATH += $$PWD/../../../../ThirdPartyBuilds/PrebuiltBinaries/zlib1.2.8/include
