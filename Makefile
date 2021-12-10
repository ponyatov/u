# \ var
# detect module/project name by current directory
MODULE  = $(notdir $(CURDIR))
# detect OS name (only Linux/MinGW)
OS      = $(shell uname -s)
# host machine architecture (for cross-compiling)
MACHINE = $(shell uname -m)
# current date in the `ddmmyy` format
NOW     = $(shell date +%d%m%y)
# release hash: four hex digits (for snapshots)
REL     = $(shell git rev-parse --short=4 HEAD)
# current git branch
BRANCH  = $(shell git rev-parse --abbrev-ref HEAD)
# your own private working branch name
SHADOW ?= shadow
# number of CPU cores (for parallel builds)
CORES   = $(shell grep processor /proc/cpuinfo| wc -l)
# / var

# \ metainfo
AUTHOR  = Dmitry Ponyatov
EMAIL   = dponyatov@gmail.com
GITHUB  = https://github.com/ponyatov
# / metainfo

# \ dir
# current (project) directory
CWD     = $(CURDIR)
# compiled/executable files (target dir)
BIN     = $(CWD)/bin
# documentation & external manuals download
DOC     = $(CWD)/doc
# libraries / scripts
LIB     = $(CWD)/lib
# source code (not for all languages, Rust/C/Java included)
SRC     = $(CWD)/src
# temporary/flags/generated files
TMP     = $(CWD)/tmp
# / dir

# \ tool
# http/ftp download
CURL    = curl -L -o
PY      = $(shell which python3)
PIP     = $(shell which pip3)
PEP     = $(shell which autopep8)
PYT     = $(shell which pytest)
# / tool

# \ src
Y   += $(MODULE).metaL.py metaL.py
S   += $(Y)
C   += $(shell find src -maxdepth 1 -type f -regex ".+\.c$$")
C   += $(shell find src -maxdepth 1 -type f -regex ".+\.cpp$$")
H   += $(shell find src -maxdepth 1 -type f -regex ".+\.h$$")
H   += $(shell find src -maxdepth 1 -type f -regex ".+\.hpp$$")
S   += $(C) $(H)
C   += tmp/$(MODULE).lexer.cpp tmp/$(MODULE).parser.cpp
H   += tmp/$(MODULE).parser.hpp
U   += $(shell find lib -maxdepth 1 -type f -regex ".+\.u$$")
S   += $(U)
# / src

# \ cfg
CFLAGS  += -O0 -g2 -I$(SRC) -I$(TMP)
# / cfg

# \ all

.PHONY: all
all: $(BIN)/$(MODULE)
	$(MAKE) tmp/format_cpp
	cat $(U) | $^

.PHONY: meta
meta: $(PY) $(MODULE).metaL.py
	$^
	$(MAKE) tmp/format_py

format: tmp/format_py tmp/format_cpp
tmp/format_py: $(Y)
	$(PEP) --ignore=E26,E302,E305,E401,E402,E701,E702 --in-place $? && touch $@
tmp/format_cpp: $(C) $(H) .astylerc
	astyle --options=.astylerc $(C) $(H) && touch $@
# / all

# \ rule
$(SRC)/%/README: $(GZ)/%.tar.gz
	cd src ;  zcat $< | tar x && touch $@
$(SRC)/%/README: $(GZ)/%.tar.xz
	cd src ; xzcat $< | tar x && touch $@
$(BIN)/$(MODULE): $(C) $(H)
	$(CXX) $(CFLAGS) -o $@ $(C) $(L) && size $@
tmp/%.lexer.cpp: src/%.lex
	flex -o $@ $<
tmp/%.parser.cpp: src/%.yacc
	bison -o $@ $<
# / rule

# \ doc

.PHONY: doxy
doxy:
	rm -rf docs ; doxygen doxy.gen 1>/dev/null

.PHONY: doc
doc:
# / doc

# \ install
.PHONY: install update
install: $(OS)_install doc gz
	$(MAKE) update
update: $(OS)_update
	$(PIP) install --user -U pip pytest autopep8

.PHONY: Linux_install Linux_update
Linux_install Linux_update:
ifneq (,$(shell which apt))
	sudo apt update
	sudo apt install -u `cat apt.txt apt.dev`
endif

# \ gz
.PHONY: gz
gz:
# / gz
# / install

# \ merge
MERGE  = Makefile README.md .gitignore apt.dev apt.txt doxy.gen $(S)
MERGE += .vscode bin doc lib src tmp

.PHONY: shadow
shadow:
	git push -v
	git checkout $@
	git pull -v

.PHONY: dev
dev:
	git push -v
	git checkout $@
	git pull -v
	git checkout $(SHADOW) -- $(MERGE)

.PHONY: release
release:
	git tag $(NOW)-$(REL)
	git push -v --tags
	$(MAKE) shadow

.PHONY: zip
ZIP = $(TMP)/$(MODULE)_$(BRANCH)_$(NOW)_$(REL).src.zip
zip:
	git archive --format zip --output $(ZIP) HEAD
	$(MAKE) doxy ; zip -r $(ZIP) docs
# / merge
