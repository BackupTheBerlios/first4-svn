TEMPLATE =  app
QT +=   gui \
  core \
  sql
CONFIG +=   qt \
  warn_on \
  console \
  debug
DESTDIR =   bin
OBJECTS_DIR =   build
MOC_DIR =   build
UI_DIR =   build
FORMS =   ui/mainfrm.ui \
  ui/loginfrm.ui \
  ui/cfgfrm.ui \
  ui/aboutfrm.ui \
  ui/newdbfrm.ui \
  ui/newdatatabfrm.ui \
  ui/addrfrm.ui \
  ui/datafrm.ui \
  ui/progfrm.ui \
  ui/dataeditfrm.ui \
  ui/printfrm.ui \
  ui/addrselectfrm.ui \
  ui/ordersfrm.ui \
  ui/orderseditfrm.ui \
  ui/stockselfrm.ui \
  ui/invfrm.ui \
  ui/invnewfrm.ui \
  ui/cmntfrm.ui \
  ui/docopenfrm.ui \
  ui/doceditfrm.ui
HEADERS =   src/mainfrm.h \
  src/vars.h \
  src/cfgfrm.h \
  src/aboutfrm.h \
  src/newdbfrm.h \
  src/newdatatabfrm.h \
  src/addrfrm.h \
  src/datafrm.h \
  src/procfrm.h \
  src/dataeditfrm.h \
  src/loginfrm.h \
  src/printfrm.h \
  src/addrselectfrm.h \
  src/ordersfrm.h \
  src/orderseditfrm.h \
  src/stockselfrm.h \
  src/invfrm.h \
  src/invnewfrm.h \
  src/progfrm.h \
  src/cmntfrm.h \
  src/docopenfrm.h \
  src/doceditfrm.h
SOURCES =   src/main.cpp \
  src/mainfrm.cpp \
  src/vars.cpp \
  src/cfgfrm.cpp \
  src/aboutfrm.cpp \
  src/newdbfrm.cpp \
  src/newdatatabfrm.cpp \
  src/addrfrm.cpp \
  src/datafrm.cpp \
  src/procfrm.cpp \
  src/dataeditfrm.cpp \
  src/loginfrm.cpp \
  src/printfrm.cpp \
  src/addrselectfrm.cpp \
  src/ordersfrm.cpp \
  src/orderseditfrm.cpp \
  src/stockselfrm.cpp \
  src/invfrm.cpp \
  src/invnewfrm.cpp \
  src/progfrm.cpp \
  src/cmntfrm.cpp \
  src/docopenfrm.cpp \
  src/doceditfrm.cpp
TRANSLATIONS =   langfiles/de.ts \
  langfiles/it.ts
RESOURCES =   ui/first.qrc
