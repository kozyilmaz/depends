
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
		PREFIX=${BSPROOTFS} \
		make \
	)

liboqs_install:
	make -C liboqs-$(LIBOQS_VERSION) install-noshared PREFIX=${BSPROOTFS}
	cp liboqs-$(LIBOQS_VERSION)/kat_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/kat_sig ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/test_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/test_sig ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/speed_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/speed_sig ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/example_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/example_sig ${BSPROOTFS}/bin

liboqs_uninstall:
	rm -rf ${BSPROOTFS}/include/oqs
	rm -rf ${BSPROOTFS}/lib/liboqs.a
	rm -rf ${BSPROOTFS}/lib/liboqs.so
	rm -rf ${BSPROOTFS}/bin/kat_kem
	rm -rf ${BSPROOTFS}/bin/kat_sig
	rm -rf ${BSPROOTFS}/bin/test_kem
	rm -rf ${BSPROOTFS}/bin/test_sig
	rm -rf ${BSPROOTFS}/bin/speed_kem
	rm -rf ${BSPROOTFS}/bin/speed_sig
	rm -rf ${BSPROOTFS}/bin/example_kem
	rm -rf ${BSPROOTFS}/bin/example_sig

liboqs_clean:
	if [ -f "liboqs-$(LIBOQS_VERSION)/Makefile" ]; then make -C liboqs-$(LIBOQS_VERSION) clean PREFIX=${BSPROOTFS}; fi

liboqs_distclean:
	rm -rf liboqs-$(LIBOQS_VERSION)
	rm -rf $(LIBOQS_VERSION).tar.gz
