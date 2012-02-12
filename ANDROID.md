# Prepare a standalone Android Toolchain
- download Android NDK from https://developer.android.com/ndk/downloads/index.html
- unpack android-ndk-rXX-linux-x86_64.zip into a suitable directory
- in the just unpacked directory launch `./build/tools/make-standalone-toolchain.sh`,

  adding your preferred architecture to the command line like `--arch=arm` and if you want

  platform using something like `--platform=platform-21`, use --help to see the default (needed later)
- after a while the script will outputs something like `Package installed to /tmp/ndk-sherpya`
- in that folder you will find `arm-linux-androideabi.tar.bz2` (depending on the given arch)
- unpack this archive somewhere like in your home directory: `tar xjvf arm-linux-androideabi.tar.bz2 -C ~`
- open ~/arm-linux-androideabi/sysroot/usr/include/android/api-level.h and change:

  `#define __ANDROID_API__ __ANDROID_API_FUTURE__`

  with

  `#define __ANDROID_API__ 21`

  (the same number used on commandline or the default if not specified)

# Configuring busybox
- execute (or add to your bashrc): `export PATH=$PATH:$HOME/arm-linux-androideabi/bin`,
  adjust the path if needed
- verify that the compiler is in the path with `arm-linux-androideabi-gcc -v`
- in busybox source tree launch `make sherpya_android_defconfig`
- if you want to configure further, launch `make menuconfig`,
  if needed change `Cross Compiler prefix` in `Busybox Settings`
- launch make (add -jX if you want to use multiple jobs

# Bugs
- The current Android NDK has a fake resolver stub, so if you build a static busybox, the resulting
  executable will not be able to resolve hosts, e.g. `ping www.google.it` will fail,
  so just leave it dynamic
