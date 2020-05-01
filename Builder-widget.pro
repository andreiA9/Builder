QT += core gui widgets


CONFIG += c++11


SOURCES += \
    BuilderModule.cpp \
    GccInterpreter.cpp \
    main.cpp \
    Applicationwindow.cpp


HEADERS += \
    Applicationwindow.h \
    BuilderModule.h \
    GccInterpreter.h


FORMS += \
    Applicationwindow.ui


RESOURCES += \
    resources.qrc


installFiles.path = $$OUT_PWD/Sources
installFiles.files = \
    $$PWD/Resources/Sources/* \
    $$PWD/Resources/Sources-inclusion/*
INSTALLS += installFiles


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
