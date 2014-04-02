AM_CPPFLAGS = @VMOD_INCLUDES@

vmoddir = @VMOD_DIR@
vmod_LTLIBRARIES = libvmod_vsthrottle.la

libvmod_vsthrottle_la_LDFLAGS = -module -export-dynamic -avoid-version -shared

libvmod_vsthrottle_la_SOURCES = \
	vcc_if.c \
	vcc_if.h \
	vmod_vsthrottle.c

vcc_if.c vcc_if.h: @VMODTOOL@ $(top_srcdir)/src/vmod_vsthrottle.vcc
	@VMODTOOL@ $(top_srcdir)/src/vmod_vsthrottle.vcc

VMOD_TESTS = tests/*.vtc
.PHONY: $(VMOD_TESTS)

tests/*.vtc:
	@VARNISHTEST@ -Dvarnishd=@VARNISHD@ -Dvmod_topbuild=$(abs_top_builddir) $@

check: $(VMOD_TESTS)

EXTRA_DIST = \
	vmod_vsthrottle.vcc \
	$(VMOD_TESTS)

CLEANFILES = $(builddir)/vcc_if.c $(builddir)/vcc_if.h
