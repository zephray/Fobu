TARGET := firmware
ODIR ?= build
OBJODIR := $(ODIR)/obj

# A simple variant is to prefix commands with $(Q) - that's useful
# for commands that shall be hidden in non-verbose mode.
#
#	$(Q)ln $@ :<
#
# To put more focus on warnings, be less verbose as default
# Use 'make V=1' to see the full commands
ifeq ("$(origin V)", "command line")
	BUILD_VERBOSE = $(V)
else
	BUILD_VERBOSE = 0
endif

ifeq ($(BUILD_VERBOSE),1)
	Q =
else
	Q = @
endif

# Do not print "Entering directory ...",
# but we want to display it when entering to the output directory
# so that IDEs/editors are able to understand relative filenames.
MAKEFLAGS += --no-print-directory

# Cross compiling and selecting different set of gcc/bin-utils
# ---------------------------------------------------------------------------
#
# CROSS_COMPILE specify the prefix used for all executables used
# during compilation. Only gcc and related bin-utils executables
# are prefixed with $(CROSS_COMPILE).
# CROSS_COMPILE can be set on the command line
# make CROSS_COMPILE=ia64-linux-
# Alternatively CROSS_COMPILE can be set in the environment.
# Default value for CROSS_COMPILE is empty
CROSS_COMPILE ?=

# Make variables (CC, etc...)
AS		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)gcc
CC		= $(CROSS_COMPILE)gcc
CXX		= $(CC)
AR		= $(CROSS_COMPILE)ar
NM		= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump
SIZE	= $(CROSS_COMPILE)size

# File System Utilities
MKDIR	= mkdir -p
RM		= rm -f
MV		= mv -f

LDFILES	:=
LIBS	:= -lpthread -lSDL

CPUFLAGS :=

COMMONFLAGS := \
	-g3 -O1 \
	-Wuninitialized \
	-Wextra \
	-Wall \

CCFLAGS := \
	-std=gnu11

CPPFLAGS := \
	-std=c++1y \
	-fno-rtti \
	-fno-exceptions

LDFLAGS := \
	-Wl,-Map="$(ODIR)/$(TARGET).map" \
	-Wl,--gc-sections

# Include LVGL
LVGL_DIR := ./middlewares
LVGL_DIR_NAME := lvgl

include $(LVGL_DIR)/$(LVGL_DIR_NAME)/lvgl.mk

#******************************************************************************
# Header File
INCLUDES += \
	-I ./ \
	-I ./applications/home \
	-I ./middlewares/freertos/include \
	-I ./middlewares/freertos/portable/GCC/Linux \
	-I ./middlewares/id3v2lib \
	-I ./middlewares/lvgl \
	-I ./middlewares/minimp3 \
	-I ./middlewares/tjpgd \
	-I ./services \
	-I ./target/linux

#******************************************************************************
# C File
CSRCS += \
	./applications/home/assets.c \
	./applications/home/home.c \
	./middlewares/freertos/croutine.c \
	./middlewares/freertos/event_groups.c \
	./middlewares/freertos/list.c \
	./middlewares/freertos/queue.c \
	./middlewares/freertos/stream_buffer.c \
	./middlewares/freertos/tasks.c \
	./middlewares/freertos/timers.c \
	./middlewares/freertos/portable/MemMang/heap_4.c \
	./middlewares/freertos/portable/GCC/Linux/port.c \
	./middlewares/id3v2lib/frame.c \
	./middlewares/id3v2lib/header.c \
	./middlewares/id3v2lib/id3v2lib.c \
	./middlewares/id3v2lib/types.c \
	./middlewares/id3v2lib/utils.c \
	./middlewares/tjpgd/tjpgd.c \
	./services/decoder.c \
	./services/gui.c \
	./services/waveheader.c \
	./target/linux/main.c \
	./target/linux/os_audio.c \
	./target/linux/os_display.c \
	./target/linux/os_filesystem.c \
	./target/linux/os_input.c \
	./osmain.c

#******************************************************************************
# CPP File
CPPSRCS +=

#******************************************************************************
# ASM File (*.S)
ASRCS +=

#******************************************************************************
# ASM File (*.s)
ASRCs +=

#******************************************************************************
# Binary resource (*)
BSRC +=

COMPONENT_OBJS :=	$(CSRCS:%.c=$(OBJODIR)/%.o) \
		$(CPPSRCS:%.cpp=$(OBJODIR)/%.o) \
		$(ASRCs:%.s=$(OBJODIR)/%.o) \
		$(ASRCS:%.S=$(OBJODIR)/%.o) \
		$(BSRC:%=$(OBJODIR)/%)

DEPS :=	$(CSRCS:%.c=$(OBJODIR)/%.d) \
		$(CPPSRCS:%.cpp=$(OBJODIR)/%.d) \
		$(ASRCs:%.s=$(OBJODIR)/%.d) \
		$(ASRCS:%.S=$(OBJODIR)/%.d)

OBJS :=	$(CSRCS:%.c=$(OBJODIR)/%.o) \
		$(CPPSRCS:%.cpp=$(OBJODIR)/%.o) \
		$(ASRCs:%.s=$(OBJODIR)/%.o) \
		$(ASRCS:%.S=$(OBJODIR)/%.o) \
		$(BSRC:%=$(OBJODIR)/%)

DEPS :=	$(CSRCS:%.c=$(OBJODIR)/%.d) \
		$(CPPSRCS:%.cpp=$(OBJODIR)/%.d) \
		$(ASRCs:%.s=$(OBJODIR)/%.d) \
		$(ASRCS:%.S=$(OBJODIR)/%.d)

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(MAKECMDGOALS),disasm)
ifdef DEPS
sinclude $(DEPS)
endif
endif
endif

$(OBJODIR)/%.o: %.c
	@echo [CC] $<
	$(Q)$(MKDIR) $(dir $@)
	$(Q)$(CC) -MT $@ -MMD -MP -MF $(OBJODIR)/$*.Td 	$(CPUFLAGS) $(COMMONFLAGS) $(CCFLAGS) $(INCLUDES) -c -o $@ $<
	$(Q)$(MV) $(OBJODIR)/$*.Td $(OBJODIR)/$*.d && touch $@

$(OBJODIR)/%.o: %.cpp
	@echo [CXX] $<
	$(Q)$(MKDIR) $(dir $@)
	$(Q)$(CXX) -MT $@ -MMD -MP -MF $(OBJODIR)/$*.Td $(CPUFLAGS) $(COMMONFLAGS) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<
	$(Q)$(MV) $(OBJODIR)/$*.Td $(OBJODIR)/$*.d && touch $@

$(OBJODIR)/%.o: %.s
	@echo [AS] $<
	$(Q)$(MKDIR) $(dir $@)
	$(Q)$(AS) $(CFLAGS) -M -o $(OBJODIR)/$*.d $<
	$(Q)$(AS) $(CFLAGS) -MMD -MP -MF $(OBJODIR)/$*.d -MT$@ -c -o $@ $<

$(OBJODIR)/%.o: %.S
	@echo [AS] $<
	$(Q)$(MKDIR) $(dir $@)
	$(Q)$(AS) $(CFLAGS) -M -o $(OBJODIR)/$*.d $<
	$(Q)$(AS) $(CFLAGS) -MMD -MP -MF $(OBJODIR)/$*.d -MT$@ -c -o $@ $<

$(OBJODIR)/%: %
	@echo [OBJCOPY] $<
	$(Q)$(MKDIR) $(dir $@)

#******************************************************************************
# Targets
#
PHONY += all
all: $(OBJS)
	$(Q)$(LD) $(CPUFLAGS) $(LDFLAGS) $(LDFILES) $(OBJS) $(LIBS) -o $(ODIR)/$(TARGET).elf
	@echo 'all finish'

PHONY += clean
clean:
	$(Q)$(RM) -r $(ODIR)
	@echo 'clean finish'

PHONY += listc
listc:
	@echo $(CSRCS) $(CPPSRCS) $(CASRCS)

# Declare the contents of the .PHONY variable as phony.  We keep that
# information in a variable so we can use it in if_changed and friends.
.PHONY: $(PHONY)

# Set default target
.DEFAULT_GOAL:= all

