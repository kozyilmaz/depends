
target_name ?= libevhtp

include ../Makefile.build

LIBEVHTP_VERSION=1.2.17-beta

libevhtp_clone:
	if [ ! -f "libevhtp-$(LIBEVHTP_VERSION).tar.gz" ]; then curl -L https://github.com/criticalstack/libevhtp/archive/$(LIBEVHTP_VERSION).tar.gz -o libevhtp-$(LIBEVHTP_VERSION).tar.gz; fi
	if [ ! -d "libevhtp-$(LIBEVHTP_VERSION)" ]; then tar xvf libevhtp-$(LIBEVHTP_VERSION).tar.gz; fi

libevhtp_config:
	( cd libevhtp-$(LIBEVHTP_VERSION); \
		cmake -DCMAKE_INSTALL_PREFIX=${BSPROOTFS} \
		-DCMAKE_C_COMPILER=${BSPCC} \
		-DCMAKE_CXX_COMPILER=${BSPCXX} \
		-DCMAKE_C_FLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS}" \
		-DCMAKE_CXX_FLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS}" \
		-DCMAKE_LD_FLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS}" \
		-DLIBEVENT_INCLUDE_DIR="${BSPROOTFS}/include" \
		-DLIBEVENT_LIBRARIES="openssl pthreads extra event core" \
		-DOPENSSL_ROOT_DIR=${BSPROOTFS} . \
	)

libevhtp_build:
	make -C libevhtp-$(LIBEVHTP_VERSION) -j ${BSPJOB}

libevhtp_install:
	make -C libevhtp-$(LIBEVHTP_VERSION) install

libevhtp_uninstall:
	if [ -f "${BSPROOTFS}/lib/libevhtp.a" ]; then rm -rf ${BSPROOTFS}/lib/libevhtp.a; fi
	if [ -d "${BSPROOTFS}/include/evhtp" ]; then rm -rf ${BSPROOTFS}/include/evhtp; fi
	if [ -f "${BSPROOTFS}/include/evhtp.h" ]; then rm -rf ${BSPROOTFS}/include/evhtp.h; fi
	if [ -d "${BSPROOTFS}/lib/cmake/libevhtp" ]; then rm -rf ${BSPROOTFS}/lib/cmake/libevhtp; fi
	if [ -f "${BSPROOTFS}/lib/pkgconfig/evhtp.pc" ]; then rm -rf ${BSPROOTFS}/lib/pkgconfig/evhtp.pc; fi

libevhtp_clean:
	if [ -f "libevhtp-$(LIBEVHTP_VERSION)/Makefile" ]; then make -C libevhtp-$(LIBEVHTP_VERSION) clean; fi

libevhtp_distclean:
	rm -rf libevhtp-$(LIBEVHTP_VERSION)
	rm -rf libevhtp-$(LIBEVHTP_VERSION).tar.gz
