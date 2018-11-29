# depends
Cross-platform dependency compiler for Linux, macOS and iOS (`x86_64` and `ios64`)

### depends as subtree
```
# add
$ git remote add depends https://github.com/kozyilmaz/depends.git
$ git subtree add --prefix=depends/ depends master

# sync
$ git remote add depends-remote https://github.com/kozyilmaz/depends.git
$ git subtree pull --prefix=depends/ depends-remote master
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
$ source environment.ios64
$ make all
# for debugging
$ PRINT_DEBUG=y make all
```
Output directory will be `$PROJECT_DIR/rootfs/ios64`

## iOS Simulator
```sh
$ source environment.iossim
$ make all
# for debugging
$ PRINT_DEBUG=y make all
```
Output directory will be `$PROJECT_DIR/rootfs/iossim`
