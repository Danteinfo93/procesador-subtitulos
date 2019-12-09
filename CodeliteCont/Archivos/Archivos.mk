##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Archivos
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/dante/PROGRAMAS/CodeliteCont"
ProjectPath            := "/home/dante/PROGRAMAS/CodeliteCont/Archivos"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Dante
Date                   :=24/06/13
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
Objects=$(IntermediateDirectory)/MuestroArchivo$(ObjectSuffix) 

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
$(IntermediateDirectory)/MuestroArchivo$(ObjectSuffix): MuestroArchivo.c $(IntermediateDirectory)/MuestroArchivo$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/dante/PROGRAMAS/CodeliteCont/Archivos/MuestroArchivo.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/MuestroArchivo$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MuestroArchivo$(DependSuffix): MuestroArchivo.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/MuestroArchivo$(ObjectSuffix) -MF$(IntermediateDirectory)/MuestroArchivo$(DependSuffix) -MM "/home/dante/PROGRAMAS/CodeliteCont/Archivos/MuestroArchivo.c"

$(IntermediateDirectory)/MuestroArchivo$(PreprocessSuffix): MuestroArchivo.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MuestroArchivo$(PreprocessSuffix) "/home/dante/PROGRAMAS/CodeliteCont/Archivos/MuestroArchivo.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/MuestroArchivo$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MuestroArchivo$(DependSuffix)
	$(RM) $(IntermediateDirectory)/MuestroArchivo$(PreprocessSuffix)
	$(RM) $(OutputFile)


