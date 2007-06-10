#/*
#*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
#*
#*   This program is free software; you can redistribute it and/or modify
#*   it under the terms of the GNU General Public License as published by
#*   the Free Software Foundation; either version 2 of the License, or (at
#*   your option) any later version.
#*
#*   This program is distributed in the hope that it will be useful, but
#*   WITHOUT ANY WARRANTY; without even the implied warranty of
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#*   GNU General Public License for more details.
#*
#*   You should have received a copy of the GNU General Public License
#*   along with this program; if not, write to the Free Software Foundation,
#*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#*/

# Qt 4 Settings
TEMPLATE = lib
DESTDIR = ../../bin/plugins
RESOURCES += res/docscannerplugin.qrc
CONFIG += debug thread warn_on qt plugin
QT += network sql xml

# Project Ui files
FORMS += ui/docscannerbase.ui

# Project Header
HEADERS += include/docscanner.h
HEADERS += include/docscannerplugin.h
HEADERS += include/plugininterface.h

# Project Source
SOURCES += src/docscanner.cpp
SOURCES += src/docscannerplugin.cpp

# Unix/Linux settings
unix{
  DEPENDPATH += include res src ui
  INCLUDEPATH += include ui

  TARGET = ../../bin/plugins/docscannerplugin
  #QMAKE_POST_LINK = strip -s ../../bin/plugins/libdocscannerplugin.so
  RCC_DIR = ../../build/docscannerplugin/unix/rcc
  MOC_DIR += ../../build/docscannerplugin/unix/moc
  OBJECTS_DIR += ../../build/docscannerplugin/unix/obj
  UI_DIR += ui
  LIBS += -L/usr/lib -lsanewidget
}

# Windows settings
win32{
  DEPENDPATH += include res src ui ../3rdparty ../3rdparty/twain
  INCLUDEPATH += include ui ../3rdparty ../3rdparty/twain

  TARGET = ../../bin/plugins/docscannerplugin  
  CONFIG += debug thread warn_on qt plugin
  RC_FILE = res/docscannerplugin.rc
  RCC_DIR = ../../build/docscannerplugin/win/rcc
  MOC_DIR += ../../build/docscannerplugin/win/moc
  OBJECTS_DIR += ../../build/docscannerplugin/win/obj
  UI_DIR += ../../build/docscannerplugin/win/ui  
  DEFINES -= UNICODE

  # 3rdpaty Source
  SOURCES += ../3rdparty/twain/dib.cpp
  SOURCES += ../3rdparty/twain/qtwain.cpp
  SOURCES += ../3rdparty/twain/qtwaininterface.cpp
  SOURCES += ../3rdparty/twain/qtwainsubstitute.cpp
  SOURCES += ../3rdparty/twain/twaincpp.cpp

  HEADERS += ../3rdparty/twain/dib.h
  HEADERS += ../3rdparty/twain/qtwain.h
  HEADERS += ../3rdparty/twain/qtwaininterface.h
  HEADERS += ../3rdparty/twain/qtwainsubstitute.h
  HEADERS += ../3rdparty/twain/stdafx.h
  HEADERS += ../3rdparty/twain/twain.h
  HEADERS += ../3rdparty/twain/twaincpp.h
}

# Mac settings
mac {
  DEPENDPATH += include res src ui
  INCLUDEPATH += include ui

  TARGET = ../../bin/plugins/docscannerplugin
  RCC_DIR = ../../build/docscannerplugin/mac/rcc
  MOC_DIR += ../../build/docscannerplugin/mac/moc
  OBJECTS_DIR += ../../build/docscannerplugin/mac/obj
  UI_DIR += ../../build/docscannerplugin/mac/ui
  LIBS += -L/usr/lib -lsanewidget
}