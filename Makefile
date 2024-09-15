INET_PROJ ?= $(HOME)/repos/omnetpp-samples/inet
INET_INCLUDE ?= $(INET_PROJ)/src
INET_LDPATH ?= $(INET_PROJ)/src
INET_LDFLAGS ?= -lINET

all: checkmakefiles
	cd src && $(MAKE)

clean: checkmakefiles
	cd src && $(MAKE) clean

cleanall: checkmakefiles
	cd src && $(MAKE) MODE=release clean
	cd src && $(MAKE) MODE=debug clean
	rm -f src/Makefile

makefiles:
	cd src && opp_makemake -f --deep -DINET_IMPORT -I../include --make-so -I$(INET_INCLUDE) -L$(INET_LDPATH) $(INET_LDFLAGS)

checkmakefiles:
	@if [ ! -f src/Makefile ]; then \
	echo; \
	echo '======================================================================='; \
	echo 'src/Makefile does not exist. Please use "make makefiles" to generate it!'; \
	echo '======================================================================='; \
	echo; \
	exit 1; \
	fi
