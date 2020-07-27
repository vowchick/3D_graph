#############################################################################
# Makefile for building: a.out
# Generated by qmake (3.1) (Qt 5.14.2)
# Project:  3D.pro
# Template: app
# Command: /usr/bin/qmake-qt5 -o Makefile 3D.pro
#############################################################################

MAKEFILE      = Makefile

EQ            = =

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O0 -ggdb -g -std=gnu++1z -Wall -Wextra -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I. -isystem /usr/include/qt5 -isystem /usr/include/qt5/QtGui -isystem /usr/include/qt5/QtCore -I. -I/../lib64/qt5/mkspecs/linux-g++
QMAKE         = /usr/bin/qmake-qt5
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /usr/bin/qmake-qt5 -install qinstall
QINSTALL_PROGRAM = /usr/bin/qmake-qt5 -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = a.out1.0.0
DISTDIR = /home/vowchicke/programms/3D_graph/.tmp/a.out1.0.0
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS) /usr/lib64/libQt5Gui.so /usr/lib64/libQt5Core.so -lGL -lpthread   
AR            = ar cqs
RANLIB        = 
SED           = sed
STRIP         = strip

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		delegator.cpp \
		grid.cpp \
		helper_functions.cpp \
		io.cpp \
		long_member_functions.cpp \
		matrix_operations.cpp \
		system_builder.cpp \
		system_solver.cpp \
		trapfpe.cpp 
OBJECTS       = main.o \
		delegator.o \
		grid.o \
		helper_functions.o \
		io.o \
		long_member_functions.o \
		matrix_operations.o \
		system_builder.o \
		system_solver.o \
		trapfpe.o
DIST          = /../lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/../lib64/qt5/mkspecs/qconfig.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/../lib64/qt5/mkspecs/features/qt_functions.prf \
		/../lib64/qt5/mkspecs/features/qt_config.prf \
		/../lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/../lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/../lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/../lib64/qt5/mkspecs/features/toolchain.prf \
		/../lib64/qt5/mkspecs/features/default_pre.prf \
		/../lib64/qt5/mkspecs/features/resolve_config.prf \
		/../lib64/qt5/mkspecs/features/default_post.prf \
		/../lib64/qt5/mkspecs/features/warn_on.prf \
		/../lib64/qt5/mkspecs/features/qt.prf \
		/../lib64/qt5/mkspecs/features/resources_functions.prf \
		/../lib64/qt5/mkspecs/features/resources.prf \
		/../lib64/qt5/mkspecs/features/moc.prf \
		/../lib64/qt5/mkspecs/features/unix/opengl.prf \
		/../lib64/qt5/mkspecs/features/unix/thread.prf \
		/../lib64/qt5/mkspecs/features/qmake_use.prf \
		/../lib64/qt5/mkspecs/features/file_copies.prf \
		/../lib64/qt5/mkspecs/features/testcase_targets.prf \
		/../lib64/qt5/mkspecs/features/exceptions.prf \
		/../lib64/qt5/mkspecs/features/yacc.prf \
		/../lib64/qt5/mkspecs/features/lex.prf \
		3D.pro helper_functions.h \
		defines.h \
		delegator.h \
		grid.h \
		io.h \
		matrix_operations.h \
		structs_and_stuff.h \
		system_builder.h \
		system_solver.h main.cpp \
		delegator.cpp \
		grid.cpp \
		helper_functions.cpp \
		io.cpp \
		long_member_functions.cpp \
		matrix_operations.cpp \
		system_builder.cpp \
		system_solver.cpp \
		trapfpe.cpp
QMAKE_TARGET  = a.out
DESTDIR       = 
TARGET        = a.out


first: all
####### Build rules

a.out:  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: 3D.pro /../lib64/qt5/mkspecs/linux-g++/qmake.conf /../lib64/qt5/mkspecs/features/spec_pre.prf \
		/usr/lib64/qt5/mkspecs/common/unix.conf \
		/usr/lib64/qt5/mkspecs/common/linux.conf \
		/usr/lib64/qt5/mkspecs/common/sanitize.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base.conf \
		/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf \
		/usr/lib64/qt5/mkspecs/common/g++-base.conf \
		/usr/lib64/qt5/mkspecs/common/g++-unix.conf \
		/../lib64/qt5/mkspecs/qconfig.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri \
		/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri \
		/../lib64/qt5/mkspecs/features/qt_functions.prf \
		/../lib64/qt5/mkspecs/features/qt_config.prf \
		/../lib64/qt5/mkspecs/linux-g++/qmake.conf \
		/../lib64/qt5/mkspecs/features/spec_post.prf \
		.qmake.stash \
		/../lib64/qt5/mkspecs/features/exclusive_builds.prf \
		/../lib64/qt5/mkspecs/features/toolchain.prf \
		/../lib64/qt5/mkspecs/features/default_pre.prf \
		/../lib64/qt5/mkspecs/features/resolve_config.prf \
		/../lib64/qt5/mkspecs/features/default_post.prf \
		/../lib64/qt5/mkspecs/features/warn_on.prf \
		/../lib64/qt5/mkspecs/features/qt.prf \
		/../lib64/qt5/mkspecs/features/resources_functions.prf \
		/../lib64/qt5/mkspecs/features/resources.prf \
		/../lib64/qt5/mkspecs/features/moc.prf \
		/../lib64/qt5/mkspecs/features/unix/opengl.prf \
		/../lib64/qt5/mkspecs/features/unix/thread.prf \
		/../lib64/qt5/mkspecs/features/qmake_use.prf \
		/../lib64/qt5/mkspecs/features/file_copies.prf \
		/../lib64/qt5/mkspecs/features/testcase_targets.prf \
		/../lib64/qt5/mkspecs/features/exceptions.prf \
		/../lib64/qt5/mkspecs/features/yacc.prf \
		/../lib64/qt5/mkspecs/features/lex.prf \
		3D.pro
	$(QMAKE) -o Makefile 3D.pro
/../lib64/qt5/mkspecs/features/spec_pre.prf:
/usr/lib64/qt5/mkspecs/common/unix.conf:
/usr/lib64/qt5/mkspecs/common/linux.conf:
/usr/lib64/qt5/mkspecs/common/sanitize.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base.conf:
/usr/lib64/qt5/mkspecs/common/gcc-base-unix.conf:
/usr/lib64/qt5/mkspecs/common/g++-base.conf:
/usr/lib64/qt5/mkspecs/common/g++-unix.conf:
/../lib64/qt5/mkspecs/qconfig.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_accessibility_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_concurrent.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_concurrent_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_core.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_core_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_dbus.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_dbus_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_edid_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_egl_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eglfs_kms_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eglfsdeviceintegration_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_fb_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_glx_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_gui.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_gui_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_input_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_kms_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_linuxaccessibility_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_network.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_network_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_opengl.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_opengl_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_openglextensions_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_platformcompositor_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_printsupport.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_printsupport_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_service_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_sql.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_sql_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_testlib.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_testlib_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_theme_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_widgets.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_widgets_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xkbcommon_support_private.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xml.pri:
/../lib64/qt5/mkspecs/modules/qt_lib_xml_private.pri:
/../lib64/qt5/mkspecs/features/qt_functions.prf:
/../lib64/qt5/mkspecs/features/qt_config.prf:
/../lib64/qt5/mkspecs/linux-g++/qmake.conf:
/../lib64/qt5/mkspecs/features/spec_post.prf:
.qmake.stash:
/../lib64/qt5/mkspecs/features/exclusive_builds.prf:
/../lib64/qt5/mkspecs/features/toolchain.prf:
/../lib64/qt5/mkspecs/features/default_pre.prf:
/../lib64/qt5/mkspecs/features/resolve_config.prf:
/../lib64/qt5/mkspecs/features/default_post.prf:
/../lib64/qt5/mkspecs/features/warn_on.prf:
/../lib64/qt5/mkspecs/features/qt.prf:
/../lib64/qt5/mkspecs/features/resources_functions.prf:
/../lib64/qt5/mkspecs/features/resources.prf:
/../lib64/qt5/mkspecs/features/moc.prf:
/../lib64/qt5/mkspecs/features/unix/opengl.prf:
/../lib64/qt5/mkspecs/features/unix/thread.prf:
/../lib64/qt5/mkspecs/features/qmake_use.prf:
/../lib64/qt5/mkspecs/features/file_copies.prf:
/../lib64/qt5/mkspecs/features/testcase_targets.prf:
/../lib64/qt5/mkspecs/features/exceptions.prf:
/../lib64/qt5/mkspecs/features/yacc.prf:
/../lib64/qt5/mkspecs/features/lex.prf:
3D.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile 3D.pro

qmake_all: FORCE


all: Makefile a.out

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents $(DIST) $(DISTDIR)/
	$(COPY_FILE) --parents /../lib64/qt5/mkspecs/features/data/dummy.cpp $(DISTDIR)/
	$(COPY_FILE) --parents helper_functions.h defines.h delegator.h grid.h io.h matrix_operations.h structs_and_stuff.h system_builder.h system_solver.h $(DISTDIR)/
	$(COPY_FILE) --parents main.cpp delegator.cpp grid.cpp helper_functions.cpp io.cpp long_member_functions.cpp matrix_operations.cpp system_builder.cpp system_solver.cpp trapfpe.cpp $(DISTDIR)/


clean: compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


distclean: clean 
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) .qmake.stash
	-$(DEL_FILE) Makefile


####### Sub-libraries

mocclean: compiler_moc_header_clean compiler_moc_objc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_objc_header_make_all compiler_moc_source_make_all

check: first

benchmark: first

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_moc_predefs_make_all: moc_predefs.h
compiler_moc_predefs_clean:
	-$(DEL_FILE) moc_predefs.h
moc_predefs.h: /../lib64/qt5/mkspecs/features/data/dummy.cpp
	g++ -pipe -O0 -ggdb -g -std=gnu++1z -Wall -Wextra -dM -E -o moc_predefs.h /../lib64/qt5/mkspecs/features/data/dummy.cpp

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_moc_objc_header_make_all:
compiler_moc_objc_header_clean:
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_predefs_clean 

####### Compile

main.o: main.cpp system_builder.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h \
		grid.h \
		system_solver.h \
		matrix_operations.h \
		io.h \
		delegator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

delegator.o: delegator.cpp delegator.h \
		system_builder.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h \
		grid.h \
		system_solver.h \
		matrix_operations.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o delegator.o delegator.cpp

grid.o: grid.cpp grid.h \
		structs_and_stuff.h \
		defines.h \
		helper_functions.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o grid.o grid.cpp

helper_functions.o: helper_functions.cpp helper_functions.h \
		structs_and_stuff.h \
		defines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o helper_functions.o helper_functions.cpp

io.o: io.cpp io.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o io.o io.cpp

long_member_functions.o: long_member_functions.cpp system_builder.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h \
		grid.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o long_member_functions.o long_member_functions.cpp

matrix_operations.o: matrix_operations.cpp matrix_operations.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o matrix_operations.o matrix_operations.cpp

system_builder.o: system_builder.cpp system_builder.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h \
		grid.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o system_builder.o system_builder.cpp

system_solver.o: system_solver.cpp system_solver.h \
		matrix_operations.h \
		helper_functions.h \
		structs_and_stuff.h \
		defines.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o system_solver.o system_solver.cpp

trapfpe.o: trapfpe.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o trapfpe.o trapfpe.cpp

####### Install

install:  FORCE

uninstall:  FORCE

FORCE:

