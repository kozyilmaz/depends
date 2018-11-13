
target_name ?= boost

include ../Makefile.build

BOOST_MAJOR=1
BOOST_MINOR=66
BOOST_MICRO=0

BOOST_VERSION=$(BOOST_MAJOR)_$(BOOST_MINOR)_$(BOOST_MICRO)

ifeq      ($(TARGET_PLATFORM),MACOS)
BOOST_TOOLSET = darwin
else ifeq ($(TARGET_PLATFORM),IOS64)
BOOST_TOOLSET = darwin
else ifeq ($(TARGET_PLATFORM),IOSSIM)
BOOST_TOOLSET = darwin
else
BOOST_TOOLSET = gcc
endif

boost_clone:
	if [ ! -f "boost_$(BOOST_VERSION).tar.bz2" ]; then curl -OL https://dl.bintray.com/boostorg/release/$(BOOST_MAJOR).$(BOOST_MINOR).$(BOOST_MICRO)/source/boost_$(BOOST_VERSION).tar.bz2; fi
	if [ ! -d "boost_$(BOOST_VERSION)" ]; then tar xvf boost_$(BOOST_VERSION).tar.bz2; fi

boost_config:
	if [ ! -f boost_$(BOOST_VERSION)/tools/build/src/user-config.jam ]; then \
		echo "using $(BOOST_TOOLSET) : custom : ${BSPCXX} ${BSPCFLAGS} ; " >> boost_$(BOOST_VERSION)/tools/build/src/user-config.jam; \
	fi
	( cd boost_$(BOOST_VERSION); ./bootstrap.sh --prefix=${BSPROOTFS} --without-icu --with-libraries=chrono,filesystem,program_options,system,thread,test )

boost_build:
	( cd boost_$(BOOST_VERSION); \
		./b2 headers; \
		./b2 cxxflags="-std=c++11 -fPIC ${BSPCFLAGS} ${BSPEXTRAFLAGS}" linkflags="-std=c++11 -fPIC ${BSPLDFLAGS} ${BSPEXTRAFLAGS}" -j ${BSPJOB} variant=release --layout=tagged --build-type=complete threading=multi link=static -sNO_BZIP2=1 -sNO_ZLIB=1 runtime-link=shared \
	)

boost_install:
	( cd boost_$(BOOST_VERSION); \
		./b2 cxxflags="-std=c++11 -fPIC ${BSPCFLAGS} ${BSPEXTRAFLAGS}" linkflags="-std=c++11 -fPIC ${BSPLDFLAGS} ${BSPEXTRAFLAGS}" -j ${BSPJOB} variant=release --layout=tagged --build-type=complete threading=multi link=static -sNO_BZIP2=1 -sNO_ZLIB=1 runtime-link=shared install \
	)

boost_uninstall:
	rm -rf ${BSPROOTFS}/include/boost;
	rm -rf ${BSPROOTFS}/lib/libboost_*

boost_clean:
	if [ -f "boost_$(BOOST_VERSION)/Makefile" ]; then make -C boost_$(BOOST_VERSION) distclean; fi

boost_distclean:
	rm -rf boost_$(BOOST_VERSION)
	rm -rf boost_$(BOOST_VERSION).tar.bz2
