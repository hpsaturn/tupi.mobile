QT += xml network
RESOURCES = resources.qrc

# Enables debugging option  
DEFINES += TUP_DEBUG  

HEADERS += tupmainwindow.h \
           tupcanvas.h \
           tupserializer.h \
           tupnethandler.h \
           tuppathitem.h \
           tupsvg2qt.h \
           tupgraphicalgorithm.h \
           tupcolorwidget.h \
           tuppenpreviewcanvas.h \
           tupstrokesizedialog.h \
           tupopacitydialog.h \
           tupframe.h \
           tupcolordialog.h \
           tupcolorpalette.h \
           tupseparator.h \
           tupabout.h \
           tupslider.h \
    QtWebsocket/QWsSocket.h \
    QtWebsocket/QWsServer.h

SOURCES += tupmainwindow.cpp \
           tupcanvas.cpp \
           tupserializer.cpp \
           tupnethandler.cpp \
           tuppathitem.cpp \
           tupsvg2qt.cpp \
           tupgraphicalgorithm.cpp \
           tupcolorwidget.cpp \
           tuppenpreviewcanvas.cpp \
           tupstrokesizedialog.cpp \
           tupopacitydialog.cpp \
           tupframe.cpp \
           tupcolordialog.cpp \
           tupabout.cpp \
           tupcolorpalette.cpp \
           tupseparator.cpp \
           tupslider.cpp \
           main.cpp \
    QtWebsocket/QWsSocket.cpp \
    QtWebsocket/QWsServer.cpp

!android {
HEADERS += tupmetadatadialog.h \
           tuprgbeditor.h \
           tupbrushdialog.h
SOURCES += tupmetadatadialog.cpp \
           tuprgbeditor.cpp \
           tupbrushdialog.cpp
}

android {
    SOURCES += tupbrushandroiddialog.cpp \
               tupcolorandroidpalette.h \
               tupandroidintents.cpp
    HEADERS += tupbrushandroiddialog.h \
               tupcolorandroidpalette.cpp \
               tupandroidintents.h

OTHER_FILES += \
    android/AndroidManifest.xml \
    android/src/org/kde/necessitas/origo/QtActivity.java \
    android/src/org/kde/necessitas/origo/QtApplication.java \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-et/strings.xml \
    android/res/drawable/logo.png \
    android/res/drawable/icon.png \
    android/res/drawable-hdpi/icon.png \
    android/res/values-fr/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-es/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-rs/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-de/strings.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/values-ms/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-ro/strings.xml \
    android/version.xml \
    android/src/org/kde/necessitas/origo/QAndroidIntent.java
}

OTHER_FILES += \
    android/res/values-nb/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-fr/strings.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-et/strings.xml \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/version.xml \
    android/AndroidManifest.xml \
    android/res/drawable-mdpi/icon.png \
    android/res/values/libs.xml \
    android/res/drawable-hdpi/icon.png \
    android/res/drawable-ldpi/icon.png \
    android/res/drawable/icon.png \
    android/res/drawable/logo.png \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/version.xml \
    android/res/layout/poi_add_dialog.xml
