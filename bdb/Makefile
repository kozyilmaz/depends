
target_name ?= bdb

include ../Makefile.build

BDB_VERSION=6.2.23

bdb_clone:
	if [ ! -f "db-$(BDB_VERSION).tar.gz" ]; then curl -OL http://download.oracle.com/berkeley-db/db-$(BDB_VERSION).tar.gz; fi;
	if [ ! -d "db-$(BDB_VERSION)" ]; then tar xvf db-$(BDB_VERSION).tar.gz; fi

bdb_config:
# use zcash/depends/packages/bdb.mk reference for sed changes
	( cd db-$(BDB_VERSION); \
		sed -i.old 's/WinIoCtl.h/winioctl.h/g' src/dbinc/win_db.h && \
		sed -i.old 's/__atomic_compare_exchange\\(/__atomic_compare_exchange_db(/' src/dbinc/atomic.h && \
		sed -i.old 's/atomic_init/atomic_init_db/' src/dbinc/atomic.h src/mp/mp_region.c src/mp/mp_mvcc.c src/mp/mp_fget.c src/mutex/mut_method.c src/mutex/mut_tas.c \
	)
	( cd db-$(BDB_VERSION)/build_unix; \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		../dist/configure ${BSPHOST} --prefix=${BSPROOTFS} \
		--with-pic --disable-shared --enable-static \
		--enable-cxx --disable-replication \
	)

bdb_build:
	make -C db-$(BDB_VERSION)/build_unix -j ${BSPJOB} libdb_cxx-6.2.a libdb-6.2.a

bdb_install:
	make -C db-$(BDB_VERSION)/build_unix install_lib install_include

bdb_uninstall:
	make -C db-$(BDB_VERSION)/build_unix uninstall_lib uninstall_include

bdb_clean:
	if [ -f "db-$(BDB_VERSION)/build_unix/Makefile" ]; then make -C db-$(BDB_VERSION)/build_unix distclean; fi

bdb_distclean:
	rm -rf db-$(BDB_VERSION)
