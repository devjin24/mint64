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
[QEMU 다운로드사이트](https://download.qemu.org)
[QEMU build 참고 사이트](https://wiki.qemu.org/Hosts/Linux)
```
sudo apt install libsdl1.2-dev libglib2.0-dev libfdt-dev
LIBS+=-lrt ./configure --prefix=/usr/cross --target-list=x86_64-softmmu --disable-vnc
make
make install
```
13장부터 이미지 안읽히는 버그 수정
```
    mov byte [ SECTORNUMBER ], al       ; 증가시킨 섹터 번호를 SECTORNUMBER에 다시 설정
    cmp al, 37                          ; 증가시킨 섹터 번호를 37와 비교
    jl READDATA                         ; 섹터 번호가 37 미만이라면 READDATA로 이동
```
표준화되진 못했지만 2.88MB 규격의 FD가 있는데(Extra-Density Floppy Disk, EDFD라고 합니다.)
요즘 QEMU가 그쪽에 맞춰진듯 합니다.
버그까진 아니고.. 2.88MB로 에뮬레이션하는 신형 QEMU에 맞추지 못했다고 보면 되겠네요.
PC에서 부팅시에도, 모드는 FDD 에뮬레이션 모드지만 CHS는 USB 용량을 따라갔을 확률이 높습니다...

## ubuntu 설치
[binutils](http://ftp.gnu.org/gnu/binutils/)
[gcc](https://bigsearcher.com/mirrors/gcc/releases/gcc-4.9.4/)
./contrib/download_prerequisites 로 gcc 빌드에필요한 라이브러리 다운로드