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


#==========================================================
# Targets
#==========================================================

help:
	@echo    Set platform name as make target
	@echo    Supported platforms:
	@echo        - portable - Default platform, pure C code;
	@echo


all:
	make --directory=$(PLATFORMS_DIR)/portable release
	make --directory=$(PLATFORMS_DIR)/portable debug	


clean:
	$(RM) -f build
	

astyle:
	$(PYTHON) $(UTILS_DIR)/apply_astyle.py
	
	
release_code:
	$(PYTHON) $(UTILS_DIR)/fill_base_header.py
	$(PYTHON) $(UTILS_DIR)/fill_src_headers.py
	$(PYTHON) $(UTILS_DIR)/apply_astyle.py
 	

ifneq ($(MAKECMDGOALS), help)
ifneq ($(MAKECMDGOALS), all)
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), astyle)
ifneq ($(MAKECMDGOALS), release_code)

PLATFORM := $(firstword $(MAKECMDGOALS))

$(PLATFORM):
	make --directory=$(PLATFORMS_DIR)/$(PLATFORM) \
		$(filter-out $(PLATFORM), $(MAKECMDGOALS))

endif
endif
endif
endif
endif


.PHONY: $(PLATFORM) help
