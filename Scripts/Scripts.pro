TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

SOURCES += \
        Ising.cpp\
        main.cpp

HEADERS += \
    Ising.h

DISTFILES += \
    main