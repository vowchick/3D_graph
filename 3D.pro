QMAKE_CXXFLAGS += -Og -ggdb -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
CONFIG += c++17
TARGET        = a.out
HEADERS       = helper_functions.h \
                defines.h \
                grid.h \
                io.h \
                msr_matrix_builder.h \
                structs_and_stuff.h
SOURCES       = main.cpp \
    grid.cpp \
                helper_functions.cpp \
    io.cpp \
    long_member_functions.cpp \
    msr_matrix_builder.cpp \
                trapfpe.cpp \

