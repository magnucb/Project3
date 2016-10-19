TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

unix {
    LIBS += -lblas -llapack -larmadillo
} else {
LIBS += -LC:/Armadillo/ -larmadillo
LIBS += -LC:/Armadillo/examples/lib_win64 -llapack_win64_MT -lblas_win64_MT
INCLUDEPATH += C:/Armadillo/include
}

SOURCES += main.cpp \
    celestialbody.cpp \
    solarsystem.cpp \
    vec3.cpp \
    euler.cpp \
    verlet.cpp

HEADERS += \
    celestialbody.h \
    solarsystem.h \
    vec3.h \
    euler.h \
    verlet.h

