#############################################################################
# Makefile for building: ObjectsDetector
# Generated by qmake (2.01a) (Qt 4.8.2) on: Sun Dec 16 14:48:56 2012
# Project:  ObjectsDetector.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/share/qt/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile ObjectsDetector.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt/mkspecs/linux-g++ -I. -I/usr/include/QtCore -I/usr/include/QtNetwork -I/usr/include/QtGui -I/usr/include -I/usr/local/include/opencv -I.
LINK          = g++
LFLAGS        = -Wl,-O1,--sort-common,--as-needed,-z,relro
LIBS          = $(SUBLIBS)  -L/usr/lib /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_ts.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_videostab.so /usr/local/lib/libopencv_imgproc.so -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		camera/UsbCamera.cpp \
		camera/IPCamera.cpp \
		fuzzy/FuzzyGrid.cpp \
		tabs/VideoTab.cpp \
		tabs/MapTab.cpp \
		views/VideoView.cpp \
		MainWindow.cpp \
		cv/QtOpenCV.cpp \
		cv/CvSURF.cpp moc_MainWindow.cpp \
		moc_FuzzyGrid.cpp \
		moc_VideoTab.cpp \
		moc_MapTab.cpp \
		moc_VideoView.cpp \
		qrc_resources.cpp
OBJECTS       = main.o \
		UsbCamera.o \
		IPCamera.o \
		FuzzyGrid.o \
		VideoTab.o \
		MapTab.o \
		VideoView.o \
		MainWindow.o \
		QtOpenCV.o \
		CvSURF.o \
		moc_MainWindow.o \
		moc_FuzzyGrid.o \
		moc_VideoTab.o \
		moc_MapTab.o \
		moc_VideoView.o \
		qrc_resources.o
DIST          = /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/debug.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/declarative_debug.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		ObjectsDetector.pro
QMAKE_TARGET  = ObjectsDetector
DESTDIR       = 
TARGET        = ObjectsDetector

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: ObjectsDetector.pro  /usr/share/qt/mkspecs/linux-g++/qmake.conf /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/debug.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/declarative_debug.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtNetwork.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile ObjectsDetector.pro
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/common/gcc-base.conf:
/usr/share/qt/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt/mkspecs/common/g++-base.conf:
/usr/share/qt/mkspecs/common/g++-unix.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/modules/qt_phonon.pri:
/usr/share/qt/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
/usr/share/qt/mkspecs/features/debug.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/declarative_debug.prf:
/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtNetwork.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile ObjectsDetector.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/ObjectsDetector1.0.0 || $(MKDIR) .tmp/ObjectsDetector1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/ObjectsDetector1.0.0/ && $(COPY_FILE) --parents MainWindow.h resource.h camera/UsbCamera.h camera/IPCamera.h camera/AbstractCamera.h fuzzy/FuzzyGrid.h tabs/VideoTab.h tabs/MapTab.h views/VideoView.h cv/QtOpenCV.h cv/CvSURF.h .tmp/ObjectsDetector1.0.0/ && $(COPY_FILE) --parents resources.qrc .tmp/ObjectsDetector1.0.0/ && $(COPY_FILE) --parents main.cpp camera/UsbCamera.cpp camera/IPCamera.cpp fuzzy/FuzzyGrid.cpp tabs/VideoTab.cpp tabs/MapTab.cpp views/VideoView.cpp MainWindow.cpp cv/QtOpenCV.cpp cv/CvSURF.cpp .tmp/ObjectsDetector1.0.0/ && (cd `dirname .tmp/ObjectsDetector1.0.0` && $(TAR) ObjectsDetector1.0.0.tar ObjectsDetector1.0.0 && $(COMPRESS) ObjectsDetector1.0.0.tar) && $(MOVE) `dirname .tmp/ObjectsDetector1.0.0`/ObjectsDetector1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/ObjectsDetector1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_MainWindow.cpp moc_FuzzyGrid.cpp moc_VideoTab.cpp moc_MapTab.cpp moc_VideoView.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_MainWindow.cpp moc_FuzzyGrid.cpp moc_VideoTab.cpp moc_MapTab.cpp moc_VideoView.cpp
moc_MainWindow.cpp: tabs/VideoTab.h \
		views/VideoView.h \
		camera/AbstractCamera.h \
		fuzzy/FuzzyGrid.h \
		tabs/MapTab.h \
		MainWindow.h
	/usr/bin/moc $(DEFINES) $(INCPATH) MainWindow.h -o moc_MainWindow.cpp

moc_FuzzyGrid.cpp: fuzzy/FuzzyGrid.h
	/usr/bin/moc $(DEFINES) $(INCPATH) fuzzy/FuzzyGrid.h -o moc_FuzzyGrid.cpp

moc_VideoTab.cpp: views/VideoView.h \
		camera/AbstractCamera.h \
		fuzzy/FuzzyGrid.h \
		tabs/VideoTab.h
	/usr/bin/moc $(DEFINES) $(INCPATH) tabs/VideoTab.h -o moc_VideoTab.cpp

moc_MapTab.cpp: fuzzy/FuzzyGrid.h \
		tabs/MapTab.h
	/usr/bin/moc $(DEFINES) $(INCPATH) tabs/MapTab.h -o moc_MapTab.cpp

moc_VideoView.cpp: camera/AbstractCamera.h \
		views/VideoView.h
	/usr/bin/moc $(DEFINES) $(INCPATH) views/VideoView.h -o moc_VideoView.cpp

compiler_rcc_make_all: qrc_resources.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_resources.cpp
qrc_resources.cpp: resources.qrc \
		img/photo_icon.jpg \
		img/scene_icon.png \
		img/video_icon.jpg \
		img/map_icon.png \
		img/toparrow.jpg \
		img/database_icon.png \
		img/bottomarrow.jpg \
		img/leftarrow.jpg \
		img/rightarrow.jpg \
		Resources/snapshot.wav
	/usr/bin/rcc -name resources resources.qrc -o qrc_resources.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: main.cpp MainWindow.h \
		tabs/VideoTab.h \
		views/VideoView.h \
		camera/AbstractCamera.h \
		fuzzy/FuzzyGrid.h \
		tabs/MapTab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

UsbCamera.o: camera/UsbCamera.cpp camera/UsbCamera.h \
		cv/CvSURF.h \
		cv/QtOpenCV.h \
		camera/AbstractCamera.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o UsbCamera.o camera/UsbCamera.cpp

IPCamera.o: camera/IPCamera.cpp camera/IPCamera.h \
		camera/AbstractCamera.h \
		cv/QtOpenCV.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o IPCamera.o camera/IPCamera.cpp

FuzzyGrid.o: fuzzy/FuzzyGrid.cpp fuzzy/FuzzyGrid.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FuzzyGrid.o fuzzy/FuzzyGrid.cpp

VideoTab.o: tabs/VideoTab.cpp tabs/VideoTab.h \
		views/VideoView.h \
		camera/AbstractCamera.h \
		fuzzy/FuzzyGrid.h \
		camera/IPCamera.h \
		cv/QtOpenCV.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VideoTab.o tabs/VideoTab.cpp

MapTab.o: tabs/MapTab.cpp tabs/MapTab.h \
		fuzzy/FuzzyGrid.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MapTab.o tabs/MapTab.cpp

VideoView.o: views/VideoView.cpp views/VideoView.h \
		camera/AbstractCamera.h \
		camera/IPCamera.h \
		cv/QtOpenCV.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o VideoView.o views/VideoView.cpp

MainWindow.o: MainWindow.cpp MainWindow.h \
		tabs/VideoTab.h \
		views/VideoView.h \
		camera/AbstractCamera.h \
		fuzzy/FuzzyGrid.h \
		tabs/MapTab.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow.o MainWindow.cpp

QtOpenCV.o: cv/QtOpenCV.cpp cv/QtOpenCV.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o QtOpenCV.o cv/QtOpenCV.cpp

CvSURF.o: cv/CvSURF.cpp cv/CvSURF.h \
		cv/QtOpenCV.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CvSURF.o cv/CvSURF.cpp

moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainWindow.o moc_MainWindow.cpp

moc_FuzzyGrid.o: moc_FuzzyGrid.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_FuzzyGrid.o moc_FuzzyGrid.cpp

moc_VideoTab.o: moc_VideoTab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_VideoTab.o moc_VideoTab.cpp

moc_MapTab.o: moc_MapTab.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MapTab.o moc_MapTab.cpp

moc_VideoView.o: moc_VideoView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_VideoView.o moc_VideoView.cpp

qrc_resources.o: qrc_resources.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_resources.o qrc_resources.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:
