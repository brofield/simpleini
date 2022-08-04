PREFIX?=	/usr/local

TOPTARGETS := all clean test

SUBDIRS := tests

$(TOPTARGETS): help $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)

help:
	@echo This makefile must builds the automatic test harness
	@echo Just include the SimpleIni.h header file to use it in your own code.

install:
	mkdir -p $(DESTDIR)$(PREFIX)/include/
	install -C -m 644 SimpleIni.h $(DESTDIR)$(PREFIX)/include/
