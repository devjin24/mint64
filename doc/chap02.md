# 2장 OS 개발환경을 구축하자

## cygwin 설치 패키지
```
+Devel
	binutils - 2.25-1, 바이너리만 설치
	bison - 3.0.4-1, 바이너리만 설치
	flex - 2.5.39-1, 바이너리만 설치
	gcc-core - 4.9.2-3, 소스및 바이너리 설치
	gcc-g++ - 4.9.2-3, 바이너리만 설치
	libtool - 2.4.6-1, 바이너리만 설치
	make - 4.1-1, 바이너리만 설치
	patchutils - 0.3.3-1, 바이너리만 설치
	texinfo - 5.2-3, 바이너리만 설치

+Libs
	libiconv-devel -1.14-3, 바이너리만 설치
	libintl-devel - 0.19.4-1, 바이너리만 설치
	libgmp-devel - 6.0.0a-2, 바이너리만 설치
	libmpfr-devel - 3.1.2-2, 바이너리만 설치
	libmpc-devel - 1.0.3-1, 바이너리만 설치
	libncurses-devel - 5.9-20150516-1, 바이너리만 설치
```
소스 경로 /usr/src/
## binutils 설치
version 2.29.1

```commandline
export TARGET=x86_64-pc-linux
export PREFIX=/usr/cross
./configure --target=$TARGET --prefix=$PREFIX --enable-64-bit-bfd --disable-shared --disable-nls
make configure-host
make LDFLAGS="-static"
make install

// 아래는 테스트를 위한 부분 커맨드를 실행했을 때 x86_64 관련 항목이 보이면 제대로 된 것입니다.
/usr/cross/bin/x86_64-pc-linux-ld --help | grep "supported "
/usr/cross/bin/x86_64-pc-linux-ld: supported targets: elf64-x86-64 elf32-i386 a.out-i386-linux efi-app-ia32 efi-bsdrv-ia32 efi-rtdrv-ia32 efi-app-x86_64 efi-bsdrv-x86_64 efi-rtdrv-x86_64 elf64-little elf64-big elf32-little elf32-big srec symbolsrec tekhex binary ihex/usr/cross/bin/x86_64-pc-linux-ld: supported emulations: elf_x86_64 elf_i386 i386linux
```

## gcc 빌드, 설치
version 5.5.0  

```commandline
export TARGET=x86_64-pc-linux
export PREFIX=/usr/cross
patch -p1 < ../0001
./contrib/download_prerequisites
sudo apt install libzip-dev
./configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c --without-headers --disable-shared --enable-multilib --with-system-zlib --disable-libssp
make configure-host
make all-gcc
make install-gcc

// 테스트용입니다. 아래와 같이 입력했을 때 m64가 보이면 정상적으로 설치된 것입니다.
/usr/cross/bin/x86_64-pc-linux-gcc -dumpspecs | grep -A1 multilib_options
*multilib_options:
m64/m32
```

## nasm 설치
version 2.13.02

[NASM사이트](http://www.nasm.us/)
exe 파일 다운 받아 cygwin/bin에 넣기

##qemu 설치
10.4 버전 설치

## ubuntu 설치
[binutils](http://ftp.gnu.org/gnu/binutils/)
[gcc](https://bigsearcher.com/mirrors/gcc/releases/gcc-4.9.4/)
./contrib/download_prerequisites 로 gcc 빌드에필요한 라이브러리 다운로드