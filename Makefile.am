## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS = dist-bzip2

SUBDIRS = src \
	include

ogreopcodedocdir = ${prefix}/doc/ogreopcode

# Why does this fail?
#EXTRA_DIST = $(ogreopcode_HEADERS)\
# $(Opcode_HEADERS) \
#	ogreopcode.pc.in

EXTRA_DIST =\
	ogreopcode.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = ogreopcode.pc

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done

