
ifeq ($(BSPROOT),)
    $(error You must first run 'source environment')
endif

TOOLSGOALS := clean distclean
ifeq ($(filter $(TOOLSGOALS),$(MAKECMDGOALS)),)
# check if 'tools' is already built, if not, add to subdir
ifeq ($(shell if [ -e $(BSPTOOLS)/version.txt ]; then cat $(BSPTOOLS)/version.txt | cut -d '-' -f 1; fi),)
subdir-y += tools
endif
else
# add tools for 'clean' and 'distclean' anyway
subdir-y += tools
endif

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

subdir-${DEPENDS_ENABLE_UNIVALUE} += \
	univalue

subdir-${DEPENDS_ENABLE_BITCOIN} += \
	boost \
	bitcoin

bitcoin_depends-y = \
	openssl \
	libevent \
	univalue \
	boost


include Makefile.lib

tools-check:
	@echo "  CHECK      tools"
	@git fetch https://github.com/kozyilmaz/tools.git master
	@$(TOPDIR)/tools/contrib/devtools/git-subtree-check.sh tools

tools-update:
	@echo "  UPDATE     tools"
ifeq ($(shell git remote -v |grep '\<tools-remote\>'),)
	@git remote add tools-remote https://github.com/kozyilmaz/tools.git
else
	@git remote set-url tools-remote https://github.com/kozyilmaz/tools.git
endif
	@git subtree pull --prefix=tools/ --squash tools-remote master

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
