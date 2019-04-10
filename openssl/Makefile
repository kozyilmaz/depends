
target_name ?= openssl

include ../Makefile.build

OPENSSL_VERSION=1.1.1b

ifeq      (${BSPPLATFORM},ios-arm64)
OPENSSL_PLT = ios64-xcrun
else ifeq (${BSPPLATFORM},ios-sim)
OPENSSL_PLT = iossimulator-xcrun
else ifeq (${BSPPLATFORM},android-aarch64)
OPENSSL_PLT = android-arm64 -D__ANDROID_API__=21
else ifeq (${BSPPLATFORM},x64_64)
# native
ifeq      ($(HOST_PLATFORM),WINDOWS)
else ifeq ($(HOST_PLATFORM),MACOS)
OPENSSL_PLT = darwin64-x86_64-cc
else ifeq ($(HOST_PLATFORM),LINUX)
OPENSSL_PLT = linux-x86_64
endif
endif

openssl_clone:
	if [ ! -f "openssl-$(OPENSSL_VERSION).tar.gz" ]; then curl -OL https://www.openssl.org/source/openssl-$(OPENSSL_VERSION).tar.gz; fi
	if [ ! -d "openssl-$(OPENSSL_VERSION)" ]; then tar xvf openssl-$(OPENSSL_VERSION).tar.gz; fi

openssl_config:
	$(call patchme,openssl-$(OPENSSL_VERSION))
	( cd openssl-$(OPENSSL_VERSION); \
		CFLAGS="" CXXFLAGS="" LDFLAGS="" \
		./Configure $(OPENSSL_PLT) ${BSPEXTRAFLAGS} --prefix=${BSPROOTFS} \
		no-asm no-shared  \
		no-comp no-hw no-dso no-engine \
		no-ssl no-dtls \
		no-tls1 no-tls1_1 \
		no-weak-ssl-ciphers \
		no-zlib no-zlib-dynamic \
	)

openssl_build:
	make -C openssl-$(OPENSSL_VERSION) -j ${BSPJOB}

openssl_install:
	make -C openssl-$(OPENSSL_VERSION) install_sw

openssl_uninstall:
	make -C openssl-$(OPENSSL_VERSION) uninstall_sw

openssl_clean:
	rm -rf openssl-$(OPENSSL_VERSION)

openssl_distclean:
	rm -rf openssl-$(OPENSSL_VERSION)
	rm -rf openssl-$(OPENSSL_VERSION).tar.gz
