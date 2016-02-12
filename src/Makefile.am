AM_CPPFLAGS = @VMOD_INCLUDES@ -Wall -Werror

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_vsthrottle.la

libvmod_vsthrottle_la_LDFLAGS = -module -export-dynamic -avoid-version \
	-shared $(LIBS)

libvmod_vsthrottle_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_vsthrottle.c

vcc_if.c vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_vsthrottle.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_vsthrottle.vcc

VMOD_TESTS = $(top_srcdir)/src/tests/*.vtc
.PHONY: $(VMOD_TESTS)

$(top_srcdir)/src/tests/*.vtc:
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_vsthrottle.vcc \
	vtree.h \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
