# Microsoft Developer Studio Generated NMAKE File, Based on path_set.dsp
!IF "$(CFG)" == ""
CFG=path_set - Win32 Debug
!MESSAGE No configuration specified. Defaulting to path_set - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "path_set - Win32 Release" && "$(CFG)" != "path_set - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "path_set.mak" CFG="path_set - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "path_set - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "path_set - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "path_set - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\path_set.exe"


CLEAN :
	-@erase "$(INTDIR)\path_set.obj"
	-@erase "$(INTDIR)\path_set.res"
	-@erase "$(INTDIR)\UpdatePathVariable.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\path_set.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\path_set.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\path_set.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\path_set.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=shared.lib setargv.obj kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\path_set.pdb" /machine:I386 /out:"$(OUTDIR)\path_set.exe" 
LINK32_OBJS= \
	"$(INTDIR)\path_set.obj" \
	"$(INTDIR)\UpdatePathVariable.obj" \
	"$(INTDIR)\path_set.res"

"$(OUTDIR)\path_set.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "path_set - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\path_set.exe" "$(OUTDIR)\path_set.bsc"


CLEAN :
	-@erase "$(INTDIR)\path_set.obj"
	-@erase "$(INTDIR)\path_set.res"
	-@erase "$(INTDIR)\path_set.sbr"
	-@erase "$(INTDIR)\UpdatePathVariable.obj"
	-@erase "$(INTDIR)\UpdatePathVariable.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\path_set.bsc"
	-@erase "$(OUTDIR)\path_set.exe"
	-@erase "$(OUTDIR)\path_set.ilk"
	-@erase "$(OUTDIR)\path_set.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\path_set.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\path_set.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\path_set.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\path_set.sbr" \
	"$(INTDIR)\UpdatePathVariable.sbr"

"$(OUTDIR)\path_set.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=sharedd.lib setargv.obj kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\path_set.pdb" /debug /machine:I386 /out:"$(OUTDIR)\path_set.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\path_set.obj" \
	"$(INTDIR)\UpdatePathVariable.obj" \
	"$(INTDIR)\path_set.res"

"$(OUTDIR)\path_set.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("path_set.dep")
!INCLUDE "path_set.dep"
!ELSE 
!MESSAGE Warning: cannot find "path_set.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "path_set - Win32 Release" || "$(CFG)" == "path_set - Win32 Debug"
SOURCE=.\path_set.cpp

!IF  "$(CFG)" == "path_set - Win32 Release"


"$(INTDIR)\path_set.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "path_set - Win32 Debug"


"$(INTDIR)\path_set.obj"	"$(INTDIR)\path_set.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\UpdatePathVariable.cpp

!IF  "$(CFG)" == "path_set - Win32 Release"


"$(INTDIR)\UpdatePathVariable.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "path_set - Win32 Debug"


"$(INTDIR)\UpdatePathVariable.obj"	"$(INTDIR)\UpdatePathVariable.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\path_set.rc

"$(INTDIR)\path_set.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

