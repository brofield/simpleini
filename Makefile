PREFIX?=	/usr/local

help:
	@echo This makefile is just for the test program \(use \"make clean all test\"\)
	@echo Just include the SimpleIni.h header file to use it.

install:
	mkdir -p $(DESTDIR)$(PREFIX)/include/
	install -C -m 644 SimpleIni.h $(DESTDIR)$(PREFIX)/include/

TOPTARGETS := all clean test

SUBDIRS := tests

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)
