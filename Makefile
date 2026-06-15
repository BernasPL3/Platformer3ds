#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error Please set DEVKITARM in your environment)
endif

TOPDIR ?= $(CURDIR)

include $(DEVKITARM)/3ds_rules

APP_TITLE       := MonkeyDS
APP_DESCRIPTION := Platformer for Nintendo 3DS
APP_AUTHOR      := BernardoGames

TARGET      := MonkeyDS
BUILD       := build
SOURCES     := source
INCLUDES    := include
GRAPHICS    := gfx
ROMFS       := romfs

ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS := -g -Wall -O2 -mword-relocations \
          -ffunction-sections \
          $(ARCH)

CFLAGS += $(INCLUDE) -D__3DS__

CXXFLAGS := $(CFLAGS) -std=gnu++17 -fno-rtti -fno-exceptions

ASFLAGS := -g $(ARCH)

LDFLAGS = -specs=3dsx.specs -g $(ARCH)

LIBS := -lcitro2d -lcitro3d -lctru -lm

LIBDIRS := $(CTRULIB)

include $(DEVKITARM)/base_tools
