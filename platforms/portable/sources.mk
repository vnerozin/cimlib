#===============================================================================
# Sources make file
#===============================================================================

#==========================================================
# Library sources
#==========================================================

# Source files
C_SRC_LIB = \
	$(wildcard frm_math/*.c) \
	$(wildcard mem_oper/*.c) \
	$(wildcard sc_math/*.c) \
	$(wildcard vec_math/*.c)

# Include directories	
INCLUDES_LIB = \
	-I ../../common/inc \
	-I ../../test/inc
	
# Objects 
OBJS_LIB = $(C_SRC_LIB:.c=.o)


#==========================================================
# Library test sources
#==========================================================

# Source files
C_SRC_TEST = \
	$(wildcard ../../test/*.c)

# Include directories	
INCLUDES_TEST = \
	-I ../../test/inc \

# Objects 
OBJS_TEST = $(C_SRC_TEST:.c=.o)
