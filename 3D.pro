#QMAKE_CXXFLAGS += -Og -ggdb3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
#QMAKE_CXXFLAGS += -O0 -ggdb3
QMAKE_CXXFLAGS += -O3 -ffast-math
CONFIG += c++17 #+= debug
TARGET        = a.out
HEADERS       = helper_functions.h \
                defines.h \
                grid.h \
                io.h \
                mainwindow.h \
                matrix_operations.h \
                mytime.h \
                painter.h \
                structs_and_stuff.h \
                surface.h \
                system_builder.h \
                system_solver.h \
                thread_info.h \
                window.h
SOURCES       = main.cpp \
    grid.cpp \
                helper_functions.cpp \
    io.cpp \
    long_member_functions.cpp \
    mainwindow.cpp \
    matrix_operations.cpp \
    mytime.cpp \
    painter.cpp \
    surface.cpp \
    system_builder.cpp \
    system_solver.cpp \
    thread_info.cpp \
                trapfpe.cpp \
    window.cpp \
    window_gui_stuff.cpp

QT += widgets
QT += opengl
QT += gui
