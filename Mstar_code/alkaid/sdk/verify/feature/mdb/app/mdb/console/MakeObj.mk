
############################################################ source files.
SUBDIRS :=./src
INC     +=./inc

OUTPUT_DIR := ./obj/

############################################################ depnedent header files.
include $(DB_BUILD_TOP)/compile.mk
all: gen_obj
clean: clean_files
