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
DEPENDPATH += include res src ../../src ui ../../3rdparty
INCLUDEPATH += include ../../src
RESOURCES += res/chipcardplugin.qrc
CONFIG += debug thread warn_on qt plugin
QT += xml network

# Project Ui files
FORMS += ui/chipcardbase.ui

# Project Header
HEADERS += include/chipcard.h
HEADERS += include/chipcardplugin.h
HEADERS += src/plugininterface.h

# Project Source
SOURCES += src/chipcard.cpp
SOURCES += src/chipcardplugin.cpp

# Core - 3rdparty Source/Header
HEADERS += ../3rdparty/Base64.h
HEADERS += ../3rdparty/XMLPreferences.h
HEADERS += ../3rdparty/XMLWriter.h

SOURCES += ../3rdparty/Base64.cpp
SOURCES += ../3rdparty/XMLPreferences.cpp
SOURCES += ../3rdparty/XMLWriter.cpp

# Unix/Linux settings
unix{
  TARGET = ../../bin/plugins/chipcardplugin
  #QMAKE_POST_LINK = strip -s ../../bin/plugins/libchipcardplugin.so
  RCC_DIR = ../../build/chipcardplugin/unix/rcc
  MOC_DIR += ../../build/chipcardplugin/unix/moc
  OBJECTS_DIR += ../../build/chipcardplugin/unix/obj
  UI_DIR += ui
}

# Windows settings
win32{
  TARGET = ../../bin/plugins/searchplugin  
  CONFIG += debug thread warn_on qt plugin
  RC_FILE = res/chipcardplugin.rc
  RCC_DIR = ../../build/chipcardplugin/win/rcc
  MOC_DIR += ../../build/chipcardplugin/win/moc
  OBJECTS_DIR += ../../build/chipcardplugin/win/obj
  UI_DIR += ../../build/chipcardplugin/win/ui  
}

# Mac settings
mac {
  TARGET = ../../bin/plugins/chipcardplugin
  RCC_DIR = ../../build/chipcardplugin/mac/rcc
  MOC_DIR += ../../build/chipcardplugin/mac/moc
  OBJECTS_DIR += ../../build/chipcardplugin/mac/obj
  UI_DIR += ../../build/chipcardplugin/mac/ui
}