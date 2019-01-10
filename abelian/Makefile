
target_name ?= abelian

include ../Makefile.build

abelian_clone:
	@true

abelian_config:
	@true

abelian_build:
	( cd abelian-test; \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		make \
	)

abelian_install:
	cp abelian-test/address ${BSPROOTFS}/bin/abe-address

abelian_uninstall:
	rm -rf ${BSPROOTFS}/bin/abe-address

abelian_clean:
	make -C abelian-test clean

abelian_distclean:
	make -C abelian-test clean
