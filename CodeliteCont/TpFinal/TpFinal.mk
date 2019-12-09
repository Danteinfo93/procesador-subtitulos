##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=TpFinal
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/dante/PROGRAMAS/CodeliteCont"
ProjectPath            := "/home/dante/PROGRAMAS/CodeliteCont/TpFinal"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Dante
Date                   :=01/11/13
CodeLitePath           :="/home/dante/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/Lista$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/iterador$(ObjectSuffix) $(IntermediateDirectory)/manipulador$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Lista$(ObjectSuffix): Lista.c $(IntermediateDirectory)/Lista$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/Lista.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/Lista$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Lista$(DependSuffix): Lista.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/Lista$(ObjectSuffix) -MF$(IntermediateDirectory)/Lista$(DependSuffix) -MM "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/Lista.c"

$(IntermediateDirectory)/Lista$(PreprocessSuffix): Lista.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Lista$(PreprocessSuffix) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/Lista.c"

$(IntermediateDirectory)/main$(ObjectSuffix): main.c $(IntermediateDirectory)/main$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/main.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/main.c"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/main.c"

$(IntermediateDirectory)/iterador$(ObjectSuffix): iterador.c $(IntermediateDirectory)/iterador$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/iterador.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/iterador$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/iterador$(DependSuffix): iterador.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/iterador$(ObjectSuffix) -MF$(IntermediateDirectory)/iterador$(DependSuffix) -MM "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/iterador.c"

$(IntermediateDirectory)/iterador$(PreprocessSuffix): iterador.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/iterador$(PreprocessSuffix) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/iterador.c"

$(IntermediateDirectory)/manipulador$(ObjectSuffix): manipulador.c $(IntermediateDirectory)/manipulador$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/manipulador.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/manipulador$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/manipulador$(DependSuffix): manipulador.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/manipulador$(ObjectSuffix) -MF$(IntermediateDirectory)/manipulador$(DependSuffix) -MM "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/manipulador.c"

$(IntermediateDirectory)/manipulador$(PreprocessSuffix): manipulador.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/manipulador$(PreprocessSuffix) "/home/dante/PROGRAMAS/CodeliteCont/TpFinal/manipulador.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/Lista$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Lista$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Lista$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/iterador$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/iterador$(DependSuffix)
	$(RM) $(IntermediateDirectory)/iterador$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/manipulador$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/manipulador$(DependSuffix)
	$(RM) $(IntermediateDirectory)/manipulador$(PreprocessSuffix)
	$(RM) $(OutputFile)


