###################################################################################################
#
#	Test_QT5 Makefile
#


CXX					= g++
CONFIG				= Debug
USE32Bit			= 0

PRJ_NAME			= Test_QT5

MAKE_DIR			:= $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST))))
HOME_DIR			:= $(shell dirname $(MAKE_DIR))

SRC_DIR				= $(MAKE_DIR)/$(PRJ_NAME)
OBJ_DIR				= $(HOME_DIR)/Obj
BIN_DIR				= $(HOME_DIR)/Bin
EXT_DIR				= $(HOME_DIR)/Ext

############################################################################
#	Platform Architecture(32Bit/64Bit) Check

ifeq ($(USE32Bit),0)
	CXXFLAGS		+= -m64
	LDFLAGS			+= -m64
	BUILD_BIT		= 64
else
	CXXFLAGS		+= -m32
	LDFLAGS			+= -m32
	BUILD_BIT		= 32
endif

EXE_NAME		= $(PRJ_NAME)

############################################################################
#	Source Configuration(Debug/Release) Check

ifeq ($(CONFIG),Debug)
	CXXFLAGS		+= -g
	OBJ_DIR			:= $(OBJ_DIR)/Linux_Debug$(BUILD_BIT)/$(PRJ_NAME)
else
	OBJ_DIR			:= $(OBJ_DIR)/Linux_Release$(BUILD_BIT)/$(PRJ_NAME)
endif

############################################################################
#	Additional Path

#SRC_STDAFX			= $(SRC_DIR)/stdafx.cpp
#SRC_FILES			= $(shell find $(SRC_DIR) -name '*.cpp' ! -name 'stdafx.cpp')
# OBJ_STDAFX			= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_STDAFX))

# MOC_H_FILES			= $(SRC_DIR)/Test/Base/CH05/0501_main_window.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH05/0502_table_dialog.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH06/0601_validator.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH07/0701_test_editor.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH07/0702_dir.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH09/0901_timer.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH09/0902_thread.h
# MOC_H_FILES			+= $(SRC_DIR)/Test/Base/CH10/1001_move_event.h

MOC_H_FILES			= $(shell find $(SRC_DIR) -name '*.h' | xargs grep 'Q_OBJECT' | uniq | awk 'BEGIN{ORS=" ";FS=":"}{print $$1}')

MOC_CPP_FILES		= $(patsubst $(SRC_DIR)/%.h, $(OBJ_DIR)/%.moc.cpp, $(MOC_H_FILES))
MOC_OBJ_FILES		= $(patsubst $(OBJ_DIR)/%.moc.cpp, $(OBJ_DIR)/%.moc.o, $(MOC_CPP_FILES))

SRC_FILES			= $(shell find $(SRC_DIR)/Test -name '*.cpp')
SRC_FILES			+= $(SRC_DIR)/main.cpp

OBJ_FILES			= $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

# HEADER_FILES		= $(shell find $(SRC_DIR) -name '*.h')

# DEPEND_FILES		= $(patsubst %.o, %.d, $(OBJ_STDAFX))
DEPEND_FILES		+= $(patsubst %.o, %.d, $(OBJ_FILES))
# DEPEND_FILES		+= $(patsubst %.h, %.h.d, $(HEADER_FILES))

$(shell mkdir -p $(dir $(DEPEND_FILES)) >/dev/null)
$(shell mkdir -p $(dir $(MOC_OBJ_FILES)) >/dev/null)


############################################################################
#	Additional Compile/Link Flags

CXXFLAGS		= -Wall -t -std=c++11
CXXFLAGS		+= -Wno-unused-but-set-variable -Wno-unused-variable 
CXXFLAGS		+= -fPIC

CXXFLAGS		+= -I$(SRC_DIR)
CXXFLAGS		+= -I/usr/include/x86_64-linux-gnu/qt5

LDFLAGS			=
LDFLAGS			+= -L/usr/lib/x86_64-linux-gnu

LDLIBS		    = 
LDLIBS			+= -lQt5Core -lQt5Widgets -lQt5Gui

# OBJ_FILE_LISTS  += $(OBJ_STDAFX)
OBJ_FILE_LISTS	+= $(OBJ_FILES)
OBJ_FILE_LISTS	+= $(MOC_OBJ_FILES)


############################################################################

all : $(PRJ_NAME)

info : 
	@echo
	@echo '[INFO] $$(MAKE_DIR)			--> '$(MAKE_DIR)
	@echo '[INFO] $$(HOME_DIR)			--> '$(HOME_DIR)
	@echo '[INFO] $$(SRC_DIR)			--> '$(SRC_DIR)
	@echo '[INFO] $$(OBJ_DIR)			--> '$(OBJ_DIR)
	@echo '[INFO] $$(BIN_DIR)			--> '$(BIN_DIR)
	@echo '[INFO] $$(EXT_DIR)			--> '$(EXT_DIR)
	@echo
	@echo '[INFO] $$(CXXFLAGS)			--> '$(CXXFLAGS)
	@echo '[INFO] $$(LDFLAGS)			--> '$(LDFLAGS)
	@echo '[INFO] $$(LDLIBS)			--> '$(LDLIBS)
	@echo 
	@echo '[INFO] $$(MOC_H_FILES)		--> '$(MOC_H_FILES)
	@echo '[INFO] $$(MOC_CPP_FILES)		--> '$(MOC_CPP_FILES)
	@echo '[INFO] $$(MOC_OBJ_FILES)		--> '$(MOC_OBJ_FILES)
	@echo '[INFO] $$(SRC_FILES)			--> '$(SRC_FILES)
	@echo '[INFO] $$(OBJ_FILES)			--> '$(OBJ_FILES)


clean :
	@echo
	@echo ' [ $(PRJ_NAME) Clean Begin ] ##########################'
	rm -rf $(BIN_DIR)/$(EXE_NAME)
	rm -rf $(OBJ_DIR)
	@echo
	@echo ' [ $(PRJ_NAME) Clean End ] ############################'


$(PRJ_NAME) : init_prj uninit_prj
	

init_prj : 
	@echo && \
	echo '##########################################################' && \
	echo '#' && \
	echo '# $(PRJ_NAME) Build Begin ' && \
	echo '#' && \
	echo;


# compile_stdafx: $(OBJ_STDAFX)

# compile_obj_files: compile_stdafx

# compile_prj: compile_obj_files $(OBJ_FILE_LISTS)

compile_moc_files: $(MOC_CPP_FILES)

compile_prj: compile_moc_files $(OBJ_FILE_LISTS)

link_prj : compile_prj
	@echo
	@echo ' [ LINK ] '
	$(CXX) -o $(BIN_DIR)/$(EXE_NAME) $(OBJ_FILES) $(MOC_OBJ_FILES) $(LDFLAGS) $(LDLIBS) 
	@echo

uninit_prj : link_prj
	@echo
	@echo '#'
	@echo '# $(PRJ_NAME) Build End '
	@echo '#'
	@echo '##########################################################'
	@echo


# $(OBJ_STDAFX) : $(@:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.cpp) $(@:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.h)
# 	@echo '[ COMPILE(STDAFX) ]' $(@:$(OBJ_DIR)/%.o=%.cpp) 
# 	@$(CXX) $(CXXFLAGS) -MMD -o $@ -c $(@:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.cpp) $(LDFLAGS) $(LDLIBS) \
# 		-MT $@ -MD -MP -MF $(@:$(OBJ_DIR)/%.o=$(OBJ_DIR)/%.d)

$(OBJ_FILES) : $(@:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.cpp) $(@:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.h) 
	@echo '[ COMPILE ]' $(@:$(OBJ_DIR)/%.o=%.cpp) 
	@$(CXX) $(CXXFLAGS) -MMD -o $@ -c $(@:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.cpp) $(LDFLAGS) $(LDLIBS) \
		-MT $@ -MD -MP -MF $(@:$(OBJ_DIR)/%.o=$(OBJ_DIR)/%.d)
	
$(MOC_OBJ_FILES) : $(@:$(OBJ_DIR)/%.moc.o=$(OBJ_DIR)/%.moc.cpp) $(@:$(OBJ_DIR)/%.moc.o=$(SRC_DIR)/%.h) 
	@echo '[ COMPILE ]' $(@:$(OBJ_DIR)/%.moc.o=%.moc.cpp) 
	@$(CXX) $(CXXFLAGS) -o $@ -c $(@:$(OBJ_DIR)/%.moc.o=$(OBJ_DIR)/%.moc.cpp) $(LDFLAGS) $(LDLIBS) 

$(MOC_CPP_FILES) : $(@:$(OBJ_DIR)/%.moc.cpp=$(SRC_DIR)/%.h)
	@echo '[ QT_MOC ]' $(@:$(OBJ_DIR)/%.moc.cpp=$(SRC_DIR)/%.h)
	@moc -o $@ $(@:$(OBJ_DIR)/%.moc.cpp=$(SRC_DIR)/%.h)

-include $(DEPEND_FILES)

