#===============================================================================
# Platform specific make file
#===============================================================================

help:
	@echo    Supported make targets:
	@echo        - all     - Makes both debug and release builds;
	@echo        - release - Makes release build;
	@echo        - debug   - Makes debug build;
	@echo        - test    - Makes release build, with test code;
	@echo        - clean   - Cleans built platform;
	@echo


ifneq ($(MAKECMDGOALS), help)

#==========================================================
# Includes
#==========================================================
include sources.mk
include ../../common.mk


#==========================================================
# Build directories
#==========================================================
PLATFORM = portable
DEBUG_DIR = $(BUILD_DIR)/$(PLATFORM)/debug
RELEASE_DIR = $(BUILD_DIR)/$(PLATFORM)/release
TEST_DIR = $(BUILD_DIR)/$(PLATFORM)/test

# Redirect objects
OBJS_DEBUG = $(addprefix $(DEBUG_DIR)/, $(OBJS_LIB))
OBJS_RELEASE = $(addprefix $(RELEASE_DIR)/, $(OBJS_LIB))
OBJS_TEST_LIB = $(addprefix $(TEST_DIR)/, $(OBJS_TEST))


#==========================================================
# Compiler and linker parameters
#==========================================================

# Compiler
CC = gcc

# Debug
CFLAGS_DEBUG = -std=c99 -Wall -Wextra -pedantic -Werror -g -O0

# Release
CFLAGS_RELEASE = -std=c99 -Wall -Wextra -pedantic -Werror -g -O3


#==========================================================
# Targets
#==========================================================

.PHONY: all clean debug release test


all: debug release test


debug: $(OBJS_DEBUG)
	ar rc $(DEBUG_DIR)/$(TARGET_DEBUG) $(OBJS_DEBUG)

$(DEBUG_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS_DEBUG) $(INCLUDES_LIB) -c $<  -o $@


release: $(OBJS_RELEASE)
	ar rc $(RELEASE_DIR)/$(TARGET_RELEASE) $(OBJS_RELEASE)

$(RELEASE_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS_RELEASE) $(INCLUDES_LIB) -c $<  -o $@


test: test_release test_build test_exec


test_release: $(OBJS_RELEASE)
	ar rc $(RELEASE_DIR)/$(TARGET_RELEASE) $(OBJS_RELEASE)

$(RELEASE_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) -DCIMLIB_BUILD_TEST=1 $(CFLAGS_RELEASE) $(INCLUDES_LIB) -c $<  -o $@


test_build: $(OBJS_TEST_LIB)
	$(CC) $(OBJS_TEST_LIB) $(OBJS_RELEASE) -o $(TEST_DIR)/$(PLATFORM)

$(TEST_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) -DCIMLIB_BUILD_TEST_STANDALONE=1 -DCIMLIB_BUILD_TEST=1 \
		$(CFLAGS_RELEASE) $(INCLUDES_LIB) $(INCLUDES_TEST) -c $<  -o $@
	
test_exec:
	./$(TEST_DIR)/$(PLATFORM) $(PLATFORM)


clean:
	$(RM) $(DEBUG_DIR) $(RELEASE_DIR) $(TEST_DIR)

endif
