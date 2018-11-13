
target_name ?= openssl

include ../Makefile.build

OPENSSL_VERSION=1.1.1

ifeq      ($(TARGET_PLATFORM),WINDOWS)
else ifeq ($(TARGET_PLATFORM),MACOS)
OPENSSL_PLT = darwin64-x86_64-cc
else ifeq ($(TARGET_PLATFORM),LINUX)
OPENSSL_PLT = linux-x86_64
else ifeq ($(TARGET_PLATFORM),IOS64)
OPENSSL_PLT = ios64-xcrun
else ifeq ($(TARGET_PLATFORM),IOSSIM)
OPENSSL_PLT = iossimulator-xcrun
endif

openssl_clone:
	if [ ! -f "openssl-$(OPENSSL_VERSION).tar.gz" ]; then curl -OL https://www.openssl.org/source/openssl-$(OPENSSL_VERSION).tar.gz; fi
	if [ ! -d "openssl-$(OPENSSL_VERSION)" ]; then tar xvf openssl-$(OPENSSL_VERSION).tar.gz; fi

openssl_config:
	$(call patchme,openssl-$(OPENSSL_VERSION))
	( cd openssl-$(OPENSSL_VERSION); \
		CFLAGS="" CXXFLAGS="" LDFLAGS="" \
		./Configure $(OPENSSL_PLT) ${BSPEXTRAFLAGS} --prefix=${BSPROOTFS} \
		no-asm no-shared no-zlib no-zlib-dynamic no-comp no-ssl no-dtls no-tls1 no-tls1_1 no-weak-ssl-ciphers no-hw no-dso no-engine \
	)

openssl_build:
	make -C openssl-$(OPENSSL_VERSION) -j ${BSPJOB}

openssl_install:
	make -C openssl-$(OPENSSL_VERSION) install_sw

openssl_uninstall:
	make -C openssl-$(OPENSSL_VERSION) uninstall_sw

openssl_clean:
	if [ -f "openssl-$(OPENSSL_VERSION)/Makefile" ]; then make -C openssl-$(OPENSSL_VERSION) distclean; fi

openssl_distclean:
	rm -rf openssl-$(OPENSSL_VERSION)
	rm -rf openssl-$(OPENSSL_VERSION).tar.gz
