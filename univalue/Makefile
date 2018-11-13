
target_name ?= univalue

include ../Makefile.build

UNIVALUE_VERSION=1.0.4

univalue_clone:
	if [ ! -f "univalue-$(UNIVALUE_VERSION).tar.gz" ]; then curl -L https://github.com/jgarzik/univalue/archive/v$(UNIVALUE_VERSION).tar.gz -o univalue-$(UNIVALUE_VERSION).tar.gz; fi;
	if [ ! -d "univalue-$(UNIVALUE_VERSION)" ]; then tar xvf univalue-$(UNIVALUE_VERSION).tar.gz; fi

univalue_config:
	if [ ! -f "univalue-$(UNIVALUE_VERSION)/configure" ]; then (cd univalue-$(UNIVALUE_VERSION) && ./autogen.sh); fi
	( cd univalue-$(UNIVALUE_VERSION); \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		./configure ${BSPHOST} --prefix=${BSPROOTFS} \
		--with-pic --enable-static --disable-shared; \
	)

univalue_build:
	make -C univalue-$(UNIVALUE_VERSION) -j ${BSPJOB}

univalue_install:
	make -C univalue-$(UNIVALUE_VERSION) install

univalue_uninstall:
	make -C univalue-$(UNIVALUE_VERSION) uninstall

univalue_clean:
	if [ -f "univalue-$(UNIVALUE_VERSION)/Makefile" ]; then make -C univalue-$(UNIVALUE_VERSION) clean; fi

univalue_distclean:
	rm -rf univalue-$(UNIVALUE_VERSION)
	rm -rf univalue-$(UNIVALUE_VERSION).tar.gz
