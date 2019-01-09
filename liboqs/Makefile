
target_name ?= liboqs

include ../Makefile.build

LIBOQS_VERSION=nist-branch-snapshot-2018-11

liboqs_clone:
	if [ ! -f "$(LIBOQS_VERSION).tar.gz" ]; then curl -OL https://github.com/open-quantum-safe/liboqs/archive/$(LIBOQS_VERSION).tar.gz; fi;
	if [ ! -d "liboqs-$(LIBOQS_VERSION)" ]; then tar xvf $(LIBOQS_VERSION).tar.gz; fi

liboqs_config:
	$(call patchme,liboqs-$(LIBOQS_VERSION))

liboqs_build:
	( cd liboqs-$(LIBOQS_VERSION); \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		OPENSSL_INCLUDE_DIR=${BSPROOTFS}/include \
		OPENSSL_LIB_DIR=${BSPROOTFS}/lib \
		make \
	)

liboqs_install:
	make -C liboqs-$(LIBOQS_VERSION) install

liboqs_uninstall:
	make -C liboqs-$(LIBOQS_VERSION) uninstall

liboqs_clean:
	if [ -f "liboqs-$(LIBOQS_VERSION)/Makefile" ]; then make -C liboqs-$(LIBOQS_VERSION) distclean; fi

liboqs_distclean:
	rm -rf liboqs-$(LIBOQS_VERSION)
	rm -rf liboqs-$(LIBOQS_VERSION).tar.gz
