TEMPLATE = lib
DESTDIR = ../../bin/plugins
RESOURCES += resources/images/first4_cashpoint.qrc
CONFIG += debug \
 thread \
 warn_on \
 qt \
 plugin
QT += gui sql core
TARGET = ../../bin/plugins/first4_cashpoint
INCLUDEPATH += src ui
DEPENDPATH += resources src ui
UI_DIR = build/first4_cashpoint/ui
unix {
 MOC_DIR =  build/first4_cashpoint/unix/moc
 OBJECTS_DIR =  build/first4_cashpoint/unix/obj
}
win32 {
 MOC_DIR =  build/first4_cashpoint/win/moc
 OBJECTS_DIR =  build/first4_cashpoint/win/obj
}
mac {
 MOC_DIR =  build/first4_cashpoint/mac/moc
 OBJECTS_DIR =  build/first4_cashpoint/mac/obj
}
HEADERS += src/cashpointplugin.h src/plugininterface.h src/cashpoint_main.h src/stockselfrm.h
SOURCES += src/cashpointplugin.cpp src/cashpoint_main.cpp src/stockselfrm.cpp
FORMS += ui/cashpoint.ui ui/stockselfrm.ui
