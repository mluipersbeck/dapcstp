
#BOOST="C:\Users\maxre\Downloads\boost_1_65_1"
BOOST_LIB="$(BOOST)\lib64-msvc-14.1"
TK=vc141-mt-
BOOST_VER=1_65_1
STATIC_BOOST_LIBS=libboost_system-$(TK)$(BOOST_VER).lib libboost_program_options-$(TK)$(BOOST_VER).lib libboost_chrono-$(TK)$(BOOST_VER).lib libboost_timer-$(TK)$(BOOST_VER).lib libboost_filesystem-$(TK)$(BOOST_VER).lib

# assume Visual stuido paths are set, run from "VS2015 x64 Native Tools Command Prompt"

CXX = clang.exe
#%VCINSTALLDIR%\ClangC2\bin\amd64\clang.exe
EXE = dapcstp.exe
INCLUDES  = -I..\include -I$(BOOST)
LIBS      = -libpath:$(BOOST_LIB) ucrt.lib msvcrt.lib $(STATIC_BOOST_LIBS)
LDFLAGS   = -nologo -subsystem:console -nxcompat -dynamicbase
CXXFLAGS  = -O2 -fpic -fexceptions -fno-strict-aliasing -ffunction-sections -gline-tables-only -fomit-frame-pointer -fdata-sections -fno-ms-compatibility -fms-extensions -fno-short-enums -D_WIN32_WINNT=0x0601 -D_CONSOLE -DNDEBUG -DNOMINMAX -D_MT -D_DLL -D_CRT_SECURE_NO_WARNINGS
# -DBOOST_ALL_DYN_LINK
OBJS = ../src/bbnode.obj ../src/bbtree.obj ../src/bounds.obj ../src/cputime.obj ../src/heur.obj ../src/inst.obj ../src/main.obj ../src/options.obj ../src/prep.obj ../src/procstatus.obj ../src/sol.obj ../src/stats.obj ../src/timer.obj ../src/util.obj

all: ../$(EXE)

clean:
	-del ..\src\*.obj ..\$(EXE)

.cpp.obj:
	"$(CXX)" $(INCLUDES) $(CXXFLAGS) -o$@ -c $<

.rc.res:
	rc /nologo $<

../$(EXE): $(OBJS) resource.res
	link -out:$@ $(LDFLAGS) $(LIBS) $(OBJS) resource.res
