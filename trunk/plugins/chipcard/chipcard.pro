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
DEPENDPATH += include res src ui ../../3rdparty
INCLUDEPATH += include 
RESOURCES += res/chipcardplugin.qrc
CONFIG += debug thread warn_on qt plugin
QT += network sql

# Project Ui files
FORMS += ui/chipcardbase.ui

# Project Header
HEADERS += include/chipcard.h
HEADERS += include/chipcardplugin.h
HEADERS += include/plugininterface.h

# Project Source
SOURCES += src/chipcard.cpp
SOURCES += src/chipcardplugin.cpp

# Unix/Linux settings
unix{
  TARGET = ../../bin/plugins/chipcardplugin
  #QMAKE_POST_LINK = strip -s ../../bin/plugins/libchipcardplugin.so
  RCC_DIR = ../../build/chipcardplugin/unix/rcc
  MOC_DIR += ../../build/chipcardplugin/unix/moc
  OBJECTS_DIR += ../../build/chipcardplugin/unix/obj
  UI_DIR += ui
  LIBS += -L/usr/lib -lchipcardc
}

# Windows settings
win32{
  TARGET = ../../bin/plugins/chipcardplugin  
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