#QMAKE_CXXFLAGS += -Og -ggdb -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
QMAKE_CXXFLAGS += -O0 -ggdb
CONFIG += c++17 += debug
TARGET        = a.out
HEADERS       = helper_functions.h \
                defines.h \
                grid.h \
                io.h \
                matrix_operations.h \
                structs_and_stuff.h \
                system_builder.h \
                system_solver.h
SOURCES       = main.cpp \
    grid.cpp \
                helper_functions.cpp \
    io.cpp \
    long_member_functions.cpp \
    matrix_operations.cpp \
    system_builder.cpp \
    system_solver.cpp \
                trapfpe.cpp \

