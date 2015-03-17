# Target filename
#   All output files will start with this (TARGET.elf, TARGET.hex, etc.)
#   You can select this for your liking. Remember to run `make clean` before changing this value.
#TARGET := simpleled
TARGET := pre-project
# List of source files to be build (seperated by space)
#SRC := simpleled.c
SRC := pre-project.c
# On this course we will use arduino mega boards, so there is no need to change this
BOARD := arduino_mega2560
# yaamake defines following values based on BOARD (these values are required by avr-libc)
#  MCU   :=  atmega2560 # microcontroller, required by the compiler and avrdude
#  F_CPU :=  16MHz      # speed the processor is running (this is correct if you do not touch prescaler)
# Command `make info` outputs values used by yaamake

# Port the device is connected to
#   If for some reason the device doesn't appear as this device,
#   you can change it here or in the command line
#     `make program PORT=/dev/ttyACM0`
PORT := /dev/ttyACM0

# List macro defines here (-D for gcc)
#DEFS += -DFOOBAR="foo bar"
#DEFS += -DBAZ=baz

# Following will find and include yaamake makefiles, which defines lot of rules.
# Basically yaamake has generic implementation of rules show in Makefile.alternative.
# Purpose of yaamake is to make this project specific makefile as simple as possible.
# Yaamake is installed on computers in the exercise lab, but if you need it on your
#  computer get it from https://github.com/raphendyr/yaamake
# If you do not want or can't use yaamake, use the provided MAkefile.alternative instead.
include $(shell yaamake --include-path --require 1.1)

# run 'make help' for more information
