
ifeq ($(BSPROOT),)
    $(error You must first run 'source environment')
endif

subdir-y += \
	tools

subdir-${DEPENDS_ENABLE_OPENSSL} += \
	openssl

subdir-${DEPENDS_ENABLE_CURL} += \
	curl

curl_depends-y = \
	openssl

subdir-${DEPENDS_ENABLE_LIBEVENT} += \
	libevent

libevent_depends-y = \
	openssl

subdir-${DEPENDS_ENABLE_LIBEVHTP} += \
	libevhtp

libevhtp_depends-y = \
	openssl \
	libevent

subdir-${DEPENDS_ENABLE_LIBOQS} += \
	liboqs

liboqs_depends-y = \
	openssl

subdir-${DEPENDS_ENABLE_UNIVALUE} += \
	univalue

subdir-${DEPENDS_ENABLE_BITCOIN} += \
	boost \
	bitcoin

bitcoin_depends-y = \
	openssl \
	libevent \
	univalue \
	boost \
	liboqs

subdir-${DEPENDS_ENABLE_ABELIAN} += \
	abelian

abelian_depends-y = \
	liboqs \
	bitcoin


include Makefile.lib

clone:
	@true

config:
	@true

build:
	@true

install:
	@true

uninstall:
	@true

clean:
	@true

distclean: clean
	@true
