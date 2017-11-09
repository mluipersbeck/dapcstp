
BOOST="C:\Users\maxre\Downloads\boost_1_65_1"
BOOST_LIB="$(BOOST)\lib64-msvc-14.0"

# assume Visual stuido paths are set, run from "VS2015 x64 Native Tools Command Prompt"

CXX = %VCINSTALLDIR%\ClangC2\bin\amd64\clang.exe
EXE = dapcstp.exe
INCLUDES  = -I..\include -I$(BOOST)
LIBS      = -libpath:$(BOOST_LIB) msvcrt.lib ucrt.lib kernel32.lib boost_system-vc140-mt-1_65_1.lib boost_filesystem-vc140-mt-1_65_1.lib boost_program_options-vc140-mt-1_65_1.lib boost_timer-vc140-mt-1_65_1.lib
LDFLAGS   = -nologo /MACHINE:X64 -subsystem:console /NXCOMPAT /DYNAMICBASE
CXXFLAGS  = -fpic -O2 -DBOOST_ALL_DYN_LINK -D_WIN32_WINNT=0x0601 -D_CONSOLE -DNDEBUG -DNOMINMAX -D_MT -D_DLL -D_CRT_SECURE_NO_WARNINGS -fno-strict-aliasing -ffunction-sections -gline-tables-only -fomit-frame-pointer -fdata-sections -fno-ms-compatibility -fexceptions

OBJS = ../src/bbnode.obj ../src/bbtree.obj ../src/bounds.obj ../src/cputime.obj ../src/heur.obj ../src/inst.obj ../src/main.obj ../src/options.obj ../src/prep.obj ../src/procstatus.obj ../src/sol.obj ../src/stats.obj ../src/timer.obj ../src/util.obj

all: ../$(EXE)

clean:
	-del ..\src\*.obj ..\$(EXE)

.cpp.obj:
	"$(CXX)" $(INCLUDES) $(CXXFLAGS) -o$@ -c $< -fms-extensions -fno-short-enums

.rc.res:
	rc /nologo $<

../$(EXE): $(OBJS) resource.res
	link -out:$@ $(LDFLAGS) $(LIBS) $(OBJS) resource.res
