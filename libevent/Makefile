
target_name ?= libevent

include ../Makefile.build

LIBEVENT_VERSION=2.1.8-stable

libevent_clone:
	if [ ! -f "libevent-$(LIBEVENT_VERSION).tar.gz" ]; then curl -OL https://github.com/libevent/libevent/releases/download/release-$(LIBEVENT_VERSION)/libevent-$(LIBEVENT_VERSION).tar.gz; fi;
	if [ ! -d "libevent-$(LIBEVENT_VERSION)" ]; then tar xvf libevent-$(LIBEVENT_VERSION).tar.gz; fi

libevent_config:
	( cd libevent-$(LIBEVENT_VERSION); \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		./configure ${BSPHOST} --prefix=${BSPROOTFS} \
		--with-pic --enable-static --disable-shared \
		--enable-openssl --disable-libevent-regress \
		--disable-samples --disable-debug-mode; \
	)

libevent_build:
	make -C libevent-$(LIBEVENT_VERSION) -j ${BSPJOB}

libevent_install:
	make -C libevent-$(LIBEVENT_VERSION) install

libevent_uninstall:
	make -C libevent-$(LIBEVENT_VERSION) uninstall

libevent_clean:
	if [ -f "libevent-$(LIBEVENT_VERSION)/Makefile" ]; then make -C libevent-$(LIBEVENT_VERSION) distclean; fi

libevent_distclean:
	rm -rf libevent-$(LIBEVENT_VERSION)
	rm -rf libevent-$(LIBEVENT_VERSION).tar.gz
