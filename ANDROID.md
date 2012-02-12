# Native bionic (Android) port of Busybox

## Prepare a standalone Android Toolchain

- download Android NDK from [https://developer.android.com/ndk/downloads/index.html](https://developer.android.com/ndk/downloads/index.html)
- unpack android-ndk-rXX-linux-x86\_64.zip into a suitable directory (tested with r17b)
- cd in thejust unpacked directory launch \
  `./build/tools/make_standalone_toolchain.py --arch arm --api 21 --install-dir ~/arm-linux-androideabi` \
  adding your preferred architecture to the command line like `--arch arm` and if you want and your minimum api
  level
- open `~/arm-linux-androideabi/sysroot/usr/include/android/api-level.h` \
  and change:

  `#define __ANDROID_API__ __ANDROID_API_FUTURE__` \
  with \
  `#define __ANDROID_API__ 21`

  (the same number used on commandline or the default if not specified)

## Configuring busybox

- execute (or add to your bashrc): `export PATH=$PATH:$HOME/arm-linux-androideabi/bin`,
  adjust the path if needed
- verify that the compiler is in the path with `arm-linux-androideabi-gcc -v`
- in busybox source tree launch `make sherpya_android_defconfig`
- if you want to configure further, launch `make menuconfig`,
  if needed change `Cross Compiler prefix` in `Busybox Settings`
- launch make (add -jX if you want to use multiple jobs


/opt/arm-linux-androideabi/sysroot/usr/include/android/api-level.h

## Bugs & Limitations

- The current Android NDK has a fake resolver stub, so if you build a static busybox, the resulting
  executable will not be able to resolve hosts, e.g. `ping www.google.it` will fail,
  so just leave it dynamic
- Android versions before 4.1 (API 16) do not support PIE, you need to disable it
- Android versions after 5.0 (API 21) require PIE, you need to enabled it (default in my config)
- Running executables built with ancient API on newer Android versions may crash 
