QT += widgets
QT += core gui sql

CONFIG += c++17

SOURCES += \
    main.cpp \
    frmmain.cpp \
    statusdelegate.cpp \
    devicedialog.cpp \
    logindialog.cpp \
    authutils.cpp \
    userdialog.cpp

HEADERS += \
    frmmain.h \
    statusdelegate.h \
    devicedialog.h \
    logindialog.h \
    authutils.h \
    userdialog.h

FORMS += \
    frmmain.ui \
    devicedialog.ui \
    logindialog.ui \
    userdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
