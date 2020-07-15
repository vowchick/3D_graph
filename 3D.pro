#QMAKE_CXXFLAGS += -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
CONFIG += c++17
TARGET        = a.out
HEADERS       = helper_functions.h \
                defines.h \
                io.h \
                matrix_operations.h 
SOURCES       = main.cpp \
                helper_functions.cpp \
    io.cpp \
                matrix_operations.cpp \
                trapfpe.cpp \

