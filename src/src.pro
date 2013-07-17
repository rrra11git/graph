SOURCES += main.cpp \
 gr_view.cpp \
 n_graph.cpp \
 mw_ngraph.cpp \
 overlay.cpp \
 figuremy.cpp \
 node.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt \
 debug



TARGET = graph
DESTDIR = ../bin
HEADERS += gr_view.h \
 n_graph.h \
 mw_ngraph.h \
 overlay.h \
 figuremy.h \
 node.h

FORMS += mf_ngraph.ui

unix {
    UI_DIR = .ui
    MOC_DIR = .moc
    OBJECTS_DIR = .obj
}


CONFIG -= release

RESOURCES += res_pict.qrc

