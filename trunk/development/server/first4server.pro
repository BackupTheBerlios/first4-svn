CONFIG += qt \
 thread \
 debug \
 warn_on
DESTDIR = bin
HEADERS = src/server.h
INCLUDEPATH = src 
QT += core sql network
SOURCES = src/main.cpp \
 src/server.cpp
TARGET = first4server
TEMPLATE = app
MOC_DIR =  build/unix/moc
OBJECTS_DIR =  build/unix/obj
