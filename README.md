# depends
Cross-platform dependency compiler for Linux, macOS, iOS (`x86_64` and `ios64`) and Android (`arm64-v8a` ABI)

### depends as subtree
```sh
# add
$ git remote add depends https://github.com/kozyilmaz/depends.git
$ git subtree add --prefix=depends/ --squash depends master
# check
$ git fetch https://github.com/kozyilmaz/depends.git master
$ ./depends/tools/contrib/devtools/git-subtree-check.sh depends
# sync
$ git remote add depends-remote https://github.com/kozyilmaz/depends.git
$ git subtree pull --prefix=depends/ --squash depends-remote master
```

## Linux and macOS
```sh
$ source environment
$ make all
# for debugging
$ PRINT_DEBUG=y make all
```
Output directory will be `$PROJECT_DIR/rootfs/x86_64`

## iOS
```sh
$ source environment ios-arm64
$ make all
# for debugging
$ PRINT_DEBUG=y make all
```
Output directory will be `$PROJECT_DIR/rootfs/ios64`

## iOS Simulator
```sh
$ source environment ios-sim
$ make all
# for debugging
$ PRINT_DEBUG=y make all
```
Output directory will be `$PROJECT_DIR/rootfs/iossim`

## Android aarch64 (arm64-v8a)
Please refer to [Android NDK README](https://developer.android.com/ndk/guides/other_build_systems) for `$NDK` and `$HOST_TAG` variables
```sh
$ export ANDROID_NDK=$PATH_TO_NDK
$ export ANDROID_HOST_TAG=$HOST_TAG
$ source environment android-aarch64
$ make all
# for debugging
$ PRINT_DEBUG=y make all
```
Output directory will be `$PROJECT_DIR/rootfs/android-aarch64`

