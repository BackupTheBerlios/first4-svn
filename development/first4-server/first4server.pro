CONFIG += qt \
 thread \
 debug \
 warn_on
DESTDIR = bin
HEADERS = src/first4server.h \
 src/first4thread.h 
INCLUDEPATH = src 
QT += core sql network xml
SOURCES = src/main.cpp \
 src/first4server.cpp \
 src/first4thread.cpp
TARGET = first4server
TEMPLATE = app
MOC_DIR =  build/unix/moc
OBJECTS_DIR =  build/unix/obj
