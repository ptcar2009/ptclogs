include .version
export

IDIR=inc
CC=g++

ODIR=obj
SDIR=src
BDIR=bin
SHAREDDIR=$(BDIR)/shared
STATICDIR=$(BDIR)/static

SHARED_NAME=libptclogs.so
SO_NAME=$(SHARED_NAME).$(MAJOR)
SO_FULLNAME= $(SO_NAME).$(MINOR).$(PATCH)

CFLAGS=-I$(IDIR) -Wall
LFLAGS=
SFLAGS= -fPIC
SOFLAGS=-I$(IDIR) -Wl,-soname,$(SO_NAME)

_DEPS = ptclogs/driver/idriver.hpp ptclogs/driver/console_driver.hpp ptclogs/driver/json_driver.hpp ptclogs/fields.hpp ptclogs/logs.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =  fields.o driver.o console_driver.o json_driver.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
LIB = $(patsubst %,$(STATICDIR)/%,$(_OBJ))
SHAREDLIB = $(patsubst %,$(SHAREDDIR)/%,$(_OBJ))


help:
	@echo "to install the SO library, run make install."
	@echo "to build a static library, run make static/build. It will be compiled into the bin/static folder."

install: $(DEPS) shared/build
	@echo "installing the library"
	sudo cp $(SHAREDDIR)/$(SO_FULLNAME) /usr/lib
	sudo chmod 755 /usr/lib/$(SO_FULLNAME)
	sudo rm /usr/lib/$(SHARED_NAME)
	sudo ln -s /usr/lib/$(SO_FULLNAME) /usr/lib/$(SHARED_NAME) 2>/dev/null 
	@echo "installing the headers"
	sudo mkdir -p /usr/include/ptclogs
	sudo cp inc/ptclogs/* /usr/include/ptclogs -r


$(STATICDIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(STATICDIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(LFLAGS)
static/build: $(LIB)
	ar rcs $(STATICDIR)/libptclogs.a $<

$(SHAREDDIR)/%.o: $(SDIR)/%.cpp
	@mkdir -p $(SHAREDDIR)
	$(CC) -c -o $@ $< $(LFLAGS) $(CFLAGS) $(SFLAGS)
shared/build: $(SHAREDLIB)
	gcc -shared $^ $(SOFLAGS) -o $(SHAREDDIR)/$(SO_FULLNAME)

.PHONY: clean


clean:
	rm -rf $(BDIR)/* *~ core $(INCDIR)/*~ 
$(ODIR)/%.o:
