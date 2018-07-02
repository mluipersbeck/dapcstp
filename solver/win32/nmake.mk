# This file is written for VS2017 Build Tools

# set boost installation path
# best to use a package from 
# https://sourceforge.net/projects/boost/files/boost-binaries/
#BOOST="$(USERPROFILE)\Downloads\boost_1_65_1"

# Path to boost libraries
BOOST_LIB="$(BOOST)\lib64-msvc-14.1"

# boost library toolkit prefix (Visual Studio 14.1, Multi Threaded)
!IFDEF DEBUG_BUILD
TK=vc141-mt-gd-
!ELSE
TK=vc141-mt-
!ENDIF

# boost library version
BOOST_VER=1_65_1

# static boost libs, boost cant set the correct
# flags for clang, so they have to be specified manually
STATIC_BOOST_LIBS= \
	libboost_system-$(TK)$(BOOST_VER).lib \
	libboost_program_options-$(TK)$(BOOST_VER).lib \
	libboost_chrono-$(TK)$(BOOST_VER).lib \
	libboost_timer-$(TK)$(BOOST_VER).lib \
	libboost_filesystem-$(TK)$(BOOST_VER).lib

# assume Visual studio paths are set, run from "VS2017 x64 Native Tools Command Prompt"
CXX       = clang
INCLUDES  = -I..\include

!IFDEF DEBUG_BUILD
EXE       = dapcstp_d.exe
LIBS      = ucrtd.lib msvcrtd.lib $(STATIC_BOOST_LIBS)
LDFLAGS   = -nologo -subsystem:console -nxcompat -dynamicbase -debug:full
!ELSE
EXE       = dapcstp.exe
LIBS      = ucrt.lib msvcrt.lib $(STATIC_BOOST_LIBS)
LDFLAGS   = -nologo -subsystem:console -nxcompat -dynamicbase
!ENDIF

!IFDEF DEBUG_BUILD
CXXFLAGS  = -O0 -g3 -fpic -fexceptions
DEFINES   = -D_MD -D_DLL -D_DEBUG
!ELSE
# optimize, use relocatable objects (exe is always relocatable), enable C++ exceptions
CXXFLAGS  = -Ofast -fpic -fexceptions
# Multi Threaded, use Dynamic Linked Runtime
DEFINES   = -D_MT -D_DLL
# compatiblility with linux
DEFINES   = $(DEFINES) -DNDEBUG
!ENDIF

# compatible with Windows 7+ API (especially PSAPIv2)
DEFINES   = $(DEFINES) -D_WIN32_WINNT=0x0601
# do not use min/max macro in windows.h, it conflicts with <limits>
DEFINES   = $(DEFINES) -DNOMINMAX
# Do not warn about funtions like sprintf and sscanf
DEFINES   = $(DEFINES) -D_CRT_SECURE_NO_WARNINGS

# NMake has no Glog discovery of files, so specifiy them manualy
OBJS = ../src/bbnode.obj ../src/bbtree.obj ../src/bounds.obj ../src/cputime.obj \
	../src/heur.obj ../src/inst.obj ../src/main.obj ../src/options.obj ../src/prep.obj \
	../src/procstatus.obj ../src/sol.obj ../src/stats.obj ../src/timer.obj ../src/util.obj

all: ../$(EXE)

clean:
	-del ..\src\*.obj ..\$(EXE)

.cpp.obj:
	@set INCLUDE=$(INCLUDE);$(BOOST)
	$(CXX) $(INCLUDES) $(CXXFLAGS) $(DEFINES) -o$@ -c $<

.rc.res:
	rc -nologo $(INCLUDES) $(DEFINES) $<

../$(EXE): $(OBJS) resource.res
	@set LIB=$(LIB);$(BOOST_LIB)
	link -out:$@ $(LDFLAGS) $(LIBS) $(OBJS) resource.res
