all: Utility BootLoader Kernel32 Kernel64 Disk.img

BootLoader:
	@echo
	@echo  ====================== Build Boot Loader ======================
	@echo
	
	make -C 00.BootLoader
	
	@echo
	@echo  ================ Success Build Boot Loader ===================
	@echo

Kernel32:
	@echo
	@echo ====================== Build 32bit kernel ======================
	@echo
	
	make -C 01.Kernel32
	
	@echo
	@echo ================ Success Build 32bit kernel ======================
	@echo

Kernel64:
	@echo
	@echo ====================== Build 64bit kernel ======================
	@echo

	make -C 02.Kernel64

	@echo
	@echo ================ Success Build 64bit kernel ======================
	@echo

Disk.img: 00.BootLoader/BootLoader.bin 01.Kernel32/Kernel32.bin 02.kernel64/Kernel64.bin
	@echo
	@echo  ====================== make Disk image ======================
	@echo

	./ImageMaker $^

	@echo
	@echo  ================ Success make Disk image ======================
	@echo

Utility:
	@echo
	@echo  ====================== Utility Build start ======================
	@echo

	make -C 04.Utility

	@echo
	@echo  ================ Utility Build Start ======================
	@echo

clean:
	make -C 00.BootLoader clean
	make -C 01.Kernel32 clean
	make -C 02.Kernel64 clean
	make -C 04.Utility clean
	rm -f Disk.img