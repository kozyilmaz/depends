
target_name ?= bitcoin

include ../Makefile.build

BITCOIN_VERSION=0.17.0

bitcoin_clone:
	if [ ! -f "bitcoin-$(BITCOIN_VERSION).tar.gz" ]; then curl -L https://github.com/bitcoin/bitcoin/archive/v$(BITCOIN_VERSION).tar.gz -o bitcoin-$(BITCOIN_VERSION).tar.gz; fi
	if [ ! -d "bitcoin-$(BITCOIN_VERSION)" ]; then tar xvf bitcoin-$(BITCOIN_VERSION).tar.gz; fi

bitcoin_config:
	$(call patchme,bitcoin-$(BITCOIN_VERSION))
	if [ ! -f "bitcoin-$(BITCOIN_VERSION)/configure" ]; then (cd bitcoin-$(BITCOIN_VERSION) && ./autogen.sh); fi
	( cd bitcoin-$(BITCOIN_VERSION); \
		CC=${BSPCC} \
		CXX=${BSPCXX} \
		CFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CXXFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		CPPFLAGS="${BSPCFLAGS} ${BSPEXTRAFLAGS} -I${BSPROOTFS}/include" \
		LDFLAGS="${BSPLDFLAGS} ${BSPEXTRAFLAGS} -L${BSPROOTFS}/lib" \
		PKG_CONFIG_PATH=${BSPROOTFS}/lib/pkgconfig \
		./configure ${BSPHOST} --prefix=${BSPROOTFS} \
		--with-pic --disable-shared --enable-static \
		--disable-tests --disable-bench --disable-man \
		--disable-asm --disable-zmq --without-miniupnpc \
		--disable-wallet --without-gui --with-daemon \
		--with-utils --with-libs \
		--with-boost=${BSPROOTFS} \
		--with-system-univalue \
		SSL_CFLAGS="-I${BSPROOTFS}/include" SSL_LIBS="-L${BSPROOTFS}/lib -lssl" \
		CRYPTO_CFLAGS="-I${BSPROOTFS}/include" CRYPTO_LIBS="-L${BSPROOTFS}/lib -lcrypto" \
		EVENT_CFLAGS="-I${BSPROOTFS}/include" EVENT_LIBS="-L${BSPROOTFS}/lib -levent" \
		EVENT_PTHREADS_CFLAGS="-I${BSPROOTFS}/include" EVENT_PTHREADS_LIBS="-L${BSPROOTFS}/lib -levent_pthreads" \
		UNIVALUE_CFLAGS="-I${BSPROOTFS}/include" UNIVALUE_LIBS="-L${BSPROOTFS}/lib -lunivalue" \
	)

bitcoin_build:
	make -C bitcoin-$(BITCOIN_VERSION) -j ${BSPJOB}

bitcoin_install:
# bins
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/bitcoind" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/bitcoind ${BSPROOTFS}/bin; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/bitcoin-tx" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/bitcoin-tx ${BSPROOTFS}/bin; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/bitcoin-cli" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/bitcoin-cli ${BSPROOTFS}/bin; fi
# libs
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/secp256k1/.libs/libsecp256k1.a" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/secp256k1/.libs/libsecp256k1.a ${BSPROOTFS}/lib; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/crypto/libbitcoin_crypto_base.a" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/crypto/libbitcoin_crypto*.a ${BSPROOTFS}/lib; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_util.a" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_util.a ${BSPROOTFS}/lib; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_common.a" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_common.a ${BSPROOTFS}/lib; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_consensus.a" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_consensus.a ${BSPROOTFS}/lib; fi
	if [ -f "bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_server.a" ]; then cp bitcoin-$(BITCOIN_VERSION)/src/libbitcoin_server.a ${BSPROOTFS}/lib; fi
# headers
# secp256k1
	mkdir -p ${BSPROOTFS}/include/bitcoin/secp256k1; cp bitcoin-$(BITCOIN_VERSION)/src/secp256k1/include/*.h ${BSPROOTFS}/include/bitcoin/secp256k1
# crypto
	mkdir -p ${BSPROOTFS}/include/bitcoin/crypto; cp bitcoin-$(BITCOIN_VERSION)/src/crypto/*.h ${BSPROOTFS}/include/bitcoin/crypto
	mkdir -p ${BSPROOTFS}/include/bitcoin/crypto/ctaes; cp bitcoin-$(BITCOIN_VERSION)/src/crypto/ctaes/*.h ${BSPROOTFS}/include/bitcoin/crypto/ctaes
# config
	mkdir -p ${BSPROOTFS}/include/bitcoin/config; cp bitcoin-$(BITCOIN_VERSION)/src/config/*.h ${BSPROOTFS}/include/bitcoin/config
# compat
	mkdir -p ${BSPROOTFS}/include/bitcoin/compat; cp bitcoin-$(BITCOIN_VERSION)/src/compat/*.h ${BSPROOTFS}/include/bitcoin/compat
# support
	mkdir -p ${BSPROOTFS}/include/bitcoin/support; cp bitcoin-$(BITCOIN_VERSION)/src/support/*.h ${BSPROOTFS}/include/bitcoin/support
	mkdir -p ${BSPROOTFS}/include/bitcoin/support/allocators; cp bitcoin-$(BITCOIN_VERSION)/src/support/allocators/*.h ${BSPROOTFS}/include/bitcoin/support/allocators
# script
	mkdir -p ${BSPROOTFS}/include/bitcoin/script; cp bitcoin-$(BITCOIN_VERSION)/src/script/*.h ${BSPROOTFS}/include/bitcoin/script
# primitives
	mkdir -p ${BSPROOTFS}/include/bitcoin/primitives; cp bitcoin-$(BITCOIN_VERSION)/src/primitives/*.h ${BSPROOTFS}/include/bitcoin/primitives
# consensus
	mkdir -p ${BSPROOTFS}/include/bitcoin/consensus; cp bitcoin-$(BITCOIN_VERSION)/src/consensus/*.h ${BSPROOTFS}/include/bitcoin/consensus
# others
	cp bitcoin-$(BITCOIN_VERSION)/src/prevector.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/span.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/serialize.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/uint256.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/arith_uint256.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/random.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/version.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/hash.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/key.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/pubkey.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/compat.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/fs.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/sync.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/threadsafety.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/tinyformat.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/logging.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/utilmemory.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/utiltime.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/util.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/init.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/netaddress.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/protocol.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/streams.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/key_io.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/keystore.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/outputtype.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/amount.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/chainparamsbase.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/chainparams.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/base58.h ${BSPROOTFS}/include/bitcoin
	cp bitcoin-$(BITCOIN_VERSION)/src/core_io.h ${BSPROOTFS}/include/bitcoin

bitcoin_uninstall:
	if [ -f "${BSPROOTFS}/bin/bitcoind" ]; then rm -rf ${BSPROOTFS}/bin/bitcoind; fi
	if [ -f "${BSPROOTFS}/bin/bitcoin-tx" ]; then rm -rf ${BSPROOTFS}/bin/bitcoin-tx; fi
	if [ -f "${BSPROOTFS}/bin/bitcoin-cli" ]; then rm -rf ${BSPROOTFS}/bin/bitcoin-cli; fi
	if [ -f "${BSPROOTFS}/lib/libsecp256k1.a" ]; then rm -rf ${BSPROOTFS}/lib/libsecp256k1.a; fi
	if [ -f "${BSPROOTFS}/lib/libbitcoin_crypto_base.a" ]; then rm -rf ${BSPROOTFS}/lib/libbitcoin_crypto*.a; fi
	if [ -f "${BSPROOTFS}/lib/libbitcoin_util.a" ]; then rm -rf ${BSPROOTFS}/lib/libbitcoin_util.a; fi
	if [ -f "${BSPROOTFS}/lib/libbitcoin_common.a" ]; then rm -rf ${BSPROOTFS}/lib/libbitcoin_common.a; fi
	if [ -f "${BSPROOTFS}/lib/libbitcoin_consensus.a" ]; then rm -rf ${BSPROOTFS}/lib/libbitcoin_consensus.a; fi
	if [ -f "${BSPROOTFS}/lib/libbitcoin_server.a" ]; then rm -rf ${BSPROOTFS}/lib/libbitcoin_server.a; fi
	if [ -d "${BSPROOTFS}/include/bitcoin" ]; then rm -rf ${BSPROOTFS}/include/bitcoin; fi

bitcoin_clean:
	if [ -f "bitcoin-$(BITCOIN_VERSION)/Makefile" ]; then make -C bitcoin-$(BITCOIN_VERSION) clean; fi

bitcoin_distclean:
	rm -rf bitcoin-$(BITCOIN_VERSION)
	rm -rf bitcoin-$(BITCOIN_VERSION).tar.gz
