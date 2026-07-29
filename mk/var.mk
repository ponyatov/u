APP     = $(notdir $(CURDIR))
REL     = $(shell git rev-parse --short=4    HEAD)
BRANCH  = $(shell git rev-parse --abbrev-ref HEAD)
NOW     = $(shell date +%y%m%d)
PEPS    = E26,E302,E305,E401,E402,E701,E702
HW     ?= pc

ifeq ($(OS),Windows_NT)
	WS  = $(shell uname -o)
        OS  = win32
	EXE = .exe
else
	WS  = $(shell lsb_release -si)
        OS  = linux
	EXE =
endif

BINFILE = $(APP)_$(HW)_$(OS)_$(BRANCH)_$(NOW)
