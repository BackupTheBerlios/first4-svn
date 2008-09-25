CONFIG += plugin \
 qt \
 thread \
 warn_on \
 debug
DESTDIR = bin
FORMS = ui/aboutfrm.ui \
 ui/accountsfrm.ui \
 ui/addrfrm.ui \
 ui/addrselectfrm.ui \
 ui/cfgfrm.ui \
 ui/cmntfrm.ui \
 ui/dataeditfrm.ui \
 ui/datafrm.ui \
 ui/dbwizzardfrm.ui \
 ui/doccompletefrm.ui \
 ui/doceditfrm.ui \
 ui/doceditposition.ui \
 ui/docopendraftfrm.ui \
 ui/docopenfrm.ui \
 ui/invfrm.ui \
 ui/invnewfrm.ui \
 ui/loginfrm.ui \
 ui/mainfrm.ui \
 ui/newdatatabfrm.ui \
 ui/orderseditfrm.ui \
 ui/ordersfrm.ui \
 ui/printfrm.ui \
 ui/procedureeditfrm.ui \
 ui/procedurefrm.ui \
 ui/proceduresearch.ui \
 ui/proceduretask.ui \
 ui/progfrm.ui \
 ui/stockselfrm.ui \
 ui/vatshowfrm.ui \
 ui/accountseditfrm.ui \
 ui/accountscomplfrm.ui \
 ui/accountsimpexpfrm.ui \
 ui/msgfrm.ui \
 ui/msgeditfrm.ui \
 ui/templateeditfrm.ui \
 ui/dbupdatefrm.ui \
 ui/loginconfserversfrm.ui \
 ui/addrimpexpfrm.ui \
 ui/dataimpexpfrm.ui
HEADERS = src/aboutfrm.h \
 src/accountsfrm.h \
 src/addrfrm.h \
 src/addrselectfrm.h \
 src/cfgfrm.h \
 src/cmntfrm.h \
 src/dataeditfrm.h \
 src/datafrm.h \
 src/dbwizzardfrm.h \
 src/doccompletefrm.h \
 src/doceditfrm.h \
 src/doceditposition.h \
 src/docopendraftsfrm.h \
 src/docopenfrm.h \
 src/invfrm.h \
 src/invnewfrm.h \
 src/loginfrm.h \
 src/mainfrm.h \
 src/newdatatabfrm.h \
 src/orderseditfrm.h \
 src/ordersfrm.h \
 src/printfrm.h \
 src/procedureeditfrm.h \
 src/procedurefrm.h \
 src/proceduresearch.h \
 src/proceduretask.h \
 src/progfrm.h \
 src/stockselfrm.h \
 src/vars.h \
 src/vatshowfrm.h \
 src/accountseditfrm.h \
 src/accountscomplfrm.h \
 src/accountsimpexpfrm.h \
 src/msgfrm.h \
 src/msgeditfrm.h \
 src/templateeditfrm.h \
 src/dbupdatefrm.h \
 src/loginconfserversfrm.h \
 src/addrimpexpfrm.h \
 src/dataimpexpfrm.h \
 src/plugininterface.h
INCLUDEPATH = src ui
QT += core gui sql
SOURCES = src/aboutfrm.cpp \
 src/accountsfrm.cpp \
 src/addrfrm.cpp \
 src/addrselectfrm.cpp \
 src/cfgfrm.cpp \
 src/cmntfrm.cpp \
 src/dataeditfrm.cpp \
 src/datafrm.cpp \
 src/dbwizzardfrm.cpp \
 src/doccompletefrm.cpp \
 src/doceditfrm.cpp \
 src/doceditposition.cpp \
 src/docopendraftsfrm.cpp \
 src/docopenfrm.cpp \
 src/invfrm.cpp \
 src/invnewfrm.cpp \
 src/loginfrm.cpp \
 src/main.cpp \
 src/mainfrm.cpp \
 src/newdatatabfrm.cpp \
 src/orderseditfrm.cpp \
 src/ordersfrm.cpp \
 src/printfrm.cpp \
 src/procedureeditfrm.cpp \
 src/procedurefrm.cpp \
 src/proceduresearch.cpp \
 src/proceduretask.cpp \
 src/progfrm.cpp \
 src/stockselfrm.cpp \
 src/vars.cpp \
 src/vatshowfrm.cpp \
 src/accountseditfrm.cpp \
 src/accountscomplfrm.cpp \
 src/accountsimpexpfrm.cpp \
 src/msgfrm.cpp \
 src/msgeditfrm.cpp \
 src/templateeditfrm.cpp \
 src/dbupdatefrm.cpp \
 src/loginconfserversfrm.cpp \
 src/addrimpexpfrm.cpp \
 src/dataimpexpfrm.cpp
RESOURCES = resources/images/first4.qrc
TARGET = first4
TEMPLATE = app
UI_DIR = build/first4/ui
TRANSLATIONS = resources/translations/de.ts resources/translations/it.ts
mac {
 MOC_DIR =  build/first4/mac/moc
 OBJECTS_DIR =  build/first4/mac/obj
}
unix {
 MOC_DIR =  build/first4/unix/moc
 OBJECTS_DIR =  build/first4/unix/obj
 target.path +=  /opt/first4/bin/
 INSTALLS =  target
}
win32 {
 MOC_DIR =  build/first4/win/moc
 OBJECTS_DIR =  build/first4/win/obj
 RC_FILE =  first4.rc
}
