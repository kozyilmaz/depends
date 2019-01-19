
target_name ?= liboqs

include ../Makefile.build

LIBOQS_VERSION=35c0fd5b19baa8fa8b50ca744ffdd8612377899d

liboqs_clone:
	if [ ! -d "liboqs-$(LIBOQS_VERSION)" ]; then git clone https://github.com/open-quantum-safe/liboqs.git liboqs-$(LIBOQS_VERSION); cd liboqs-$(LIBOQS_VERSION); git checkout $(LIBOQS_VERSION); cd ..; fi;

liboqs_config:
#	$(call patchme,liboqs-$(LIBOQS_VERSION))
	if [ ! -f "liboqs-$(LIBOQS_VERSION)/configure" ]; then (cd liboqs-$(LIBOQS_VERSION) && LIBTOOLIZE=glibtoolize autoreconf -i -v -f); fi
	( cd liboqs-$(LIBOQS_VERSION); \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		./configure ${BSPHOST} --prefix=${BSPROOTFS} \
		--with-pic --disable-shared --enable-static \
		--disable-doxygen-doc --disable-doxygen-dot \
		--enable-openssl --with-openssl-dir=${BSPROOTFS} \
	)

liboqs_build:
	make -C liboqs-$(LIBOQS_VERSION) -j ${BSPJOB}
	make -C liboqs-$(LIBOQS_VERSION) test

liboqs_install:
	make -C liboqs-$(LIBOQS_VERSION) install
	cp liboqs-$(LIBOQS_VERSION)/tests/kat_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/test_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/test_sig ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/test_aes ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/test_sha3 ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/speed_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/speed_sig ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/example_kem ${BSPROOTFS}/bin
	cp liboqs-$(LIBOQS_VERSION)/tests/example_sig ${BSPROOTFS}/bin

liboqs_uninstall:
	make -C liboqs-$(LIBOQS_VERSION) uninstall
	rm -rf ${BSPROOTFS}/include/oqs
	rm -rf ${BSPROOTFS}/bin/kat_kem
	rm -rf ${BSPROOTFS}/bin/test_kem
	rm -rf ${BSPROOTFS}/bin/test_sig
	rm -rf ${BSPROOTFS}/bin/test_aes
	rm -rf ${BSPROOTFS}/bin/test_sha3
	rm -rf ${BSPROOTFS}/bin/speed_kem
	rm -rf ${BSPROOTFS}/bin/speed_sig
	rm -rf ${BSPROOTFS}/bin/example_kem
	rm -rf ${BSPROOTFS}/bin/example_sig

liboqs_clean:
	if [ -f "liboqs-$(LIBOQS_VERSION)/Makefile" ]; then make -C liboqs-$(LIBOQS_VERSION) clean; fi

liboqs_distclean:
	rm -rf liboqs-$(LIBOQS_VERSION)
