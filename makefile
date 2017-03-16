#===============================================================================
# Base make file
#===============================================================================

#==========================================================
# Includes	
#==========================================================
include common.mk


#==========================================================
# Parameters	
#==========================================================

# Platforms directory
PLATFORMS_DIR = platforms

# Utilites directory
UTILS_DIR = utils

# Platform name
PLATFORM := $(firstword $(MAKECMDGOALS))

# Build mode 
BUILD_MODE := $(filter-out $(PLATFORM), $(MAKECMDGOALS))


#==========================================================
# Targets
#==========================================================

.PHONY: $(PLATFORM) help clean release debug all


$(PLATFORM):
	make --directory=$(PLATFORMS_DIR)/$(PLATFORM) $(BUILD_MODE)


help:
	@echo    Set platform name as make target
	@echo    Supported platforms:
	@echo        - portable - Default platform, pure C code;
	@echo


clean:
	$(RM) -f build

