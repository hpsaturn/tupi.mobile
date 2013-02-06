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
           tuppalettedialog.h \
           tuppenpreviewcanvas.h \
           tupstrokesizedialog.h \
           tupopacitydialog.h \
           tupframe.h \
           tupabout.h

SOURCES += tupmainwindow.cpp \
           tupcanvas.cpp \
           tupserializer.cpp \
           tupnethandler.cpp \
           tuppathitem.cpp \
           tupsvg2qt.cpp \
           tupgraphicalgorithm.cpp \
           tupcolorwidget.cpp \
           tuppalettedialog.cpp \
           tuppenpreviewcanvas.cpp \
           tupstrokesizedialog.cpp \
           tupopacitydialog.cpp \
           tupframe.cpp \
           tupabout.cpp \
           main.cpp

!android {
HEADERS += tupmetadatadialog.h \
           tupbrushdialog.h
SOURCES += tupmetadatadialog.cpp \
           tupbrushdialog.cpp
}

android {
    SOURCES += tupbrushandroiddialog.cpp \
               tupmetadataandroiddialog.cpp \
               tupandroidintents.cpp
    HEADERS += tupbrushandroiddialog.h \
               tupmetadataandroiddialog.h \
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
