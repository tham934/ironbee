ACLOCAL_AMFLAGS = -I acinclude
SUBDIRS = @TOPLEVEL_SUBDIRS@

include $(top_srcdir)/build/common.mk
EXTRA_DIST = include \
             ironbee_config_auto.h \
             README.adoc \
             CHANGES.adoc \
             CODESTYLE.adoc \
             DEVELOPMENT.adoc \
			 LICENSE \
			 NOTICE \
			 VERSION \
			 get-version.sh \
			 codecheck \
			 autogen.sh \
			 experimental

RPM_RELEASE ?= 1

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ironbee.pc
# Sort to eliminate duplicates if top_srcdir == top_builddir
pkginclude_HEADERS = $(sort $(wildcard $(top_srcdir)/include/ironbee/*.h) $(top_builddir)/include/ironbee/release.h)
doxygen doxygen-pdf:
	@(cd docs && $(MAKE) $@)

ref-manual:
	@(cd docs && $(MAKE) ref-manual)

guide:
	@(cd docs && $(MAKE) guide)

lua-api-docs:
	@(cd lua && $(MAKE) lua-api-docs)

luajit:
	@(cd libs && $(MAKE) )

nginx:
	@(cd servers/nginx && $(MAKE) nginx )

nginx-install:	nginx
	@(cd servers/nginx && $(MAKE) nginx-install)

tengine-install:
	@(cd servers/nginx && $(MAKE) tengine-install)

.PHONY: doxygen doxygen-pdf manual luajit nginx

rpm_topdir=$(abs_top_builddir)/packaging/rpm
rpm-package: dist
	if test x$(HAVE_RPM) = xyes ; then \
		cd $(rpm_topdir) ; \
		mkdir -p BUILD RPMS SOURCES ; \
		cd SOURCES ; \
		ln -s ../../../$(distdir).tar.gz ; \
		cd .. ; \
		rpmbuild $(RPM_OPTS) --define "_topdir $(rpm_topdir)" --define "_release $(RPM_RELEASE)" -ba ironbee.spec && \
		echo "Package successfully built in `pwd`/RPMS." ; \
	else \
		echo "Error: RPM executable and/or source directory not found." ; \
	fi

module_include_HEADERS = \
	$(top_srcdir)/include/ironbee/module/*.h
if CPP
module_include_HEADERS += \
	$(top_srcdir)/include/ironbee/module/*.hpp
ironbeepp_include_HEADERS = \
    $(top_srcdir)/include/ironbeepp/*.hpp
predicate_include_HEADERS = \
	$(top_srcdir)/include/ironbee/predicate/*.hpp
endif
