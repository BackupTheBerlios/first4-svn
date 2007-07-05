TEMPLATE =   app
DESTDIR =   bin
DEPENDPATH =   src \
  ui
INCLUDEPATH =   src \
  ui
CONFIG +=   qt \
  warn_on \
  thread \
  console \
  debug
QT +=   gui \
  core \
  sql
OBJECTS_DIR =   build/first4/obj
MOC_DIR =   build/first4/moc
UI_DIR =   build/first4/ui
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
  ui/doceditfrm.ui \
  ui/doccompletefrm.ui \
  ui/docopendraftfrm.ui \
  ui/vatshowfrm.ui \
  ui/doceditposition.ui \
  ui/procedurefrm.ui \
  ui/procedureeditfrm.ui \
  ui/proceduretask.ui
HEADERS =   src/mainfrm.h \
  src/vars.h \
  src/cfgfrm.h \
  src/aboutfrm.h \
  src/newdbfrm.h \
  src/newdatatabfrm.h \
  src/addrfrm.h \
  src/datafrm.h \
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
  src/doceditfrm.h \
  src/doccompletefrm.h \
  src/docopendraftsfrm.h \
  src/vatshowfrm.h \
  src/doceditposition.h \
  src/procedurefrm.h \
  src/procedureeditfrm.h \
  src/proceduretask.h
SOURCES =   src/main.cpp \
  src/mainfrm.cpp \
  src/vars.cpp \
  src/cfgfrm.cpp \
  src/aboutfrm.cpp \
  src/newdbfrm.cpp \
  src/newdatatabfrm.cpp \
  src/addrfrm.cpp \
  src/datafrm.cpp \
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
  src/doceditfrm.cpp \
  src/doccompletefrm.cpp \
  src/docopendraftsfrm.cpp \
  src/vatshowfrm.cpp \
  src/doceditposition.cpp \
  src/procedurefrm.cpp \
  src/procedureeditfrm.cpp \
  src/proceduretask.cpp
TRANSLATIONS =   langfiles/de.ts \
  langfiles/it.ts
RESOURCES =   ui/first.qrc
