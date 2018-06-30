REM Start qemu on windows.
@ECHO OFF

REM SDL_VIDEODRIVER=directx is faster than windib. But keyboard cannot work well.
SET SDL_VIDEODRIVER=windib

REM SDL_AUDIODRIVER=waveout or dsound can be used. Only if QEMU_AUDIO_DRV=sdl.
SET SDL_AUDIODRIVER=dsound

REM QEMU_AUDIO_DRV=dsound or fmod or sdl or none can be used. See qemu -audio-help.
SET QEMU_AUDIO_DRV=dsound

REM QEMU_AUDIO_LOG_TO_MONITOR=1 displays log messages in QEMU monitor.
SET QEMU_AUDIO_LOG_TO_MONITOR=0

REM PCI-based PC(default): -M pc 
REM ISA-based PC         : -M isapc
REM -M isapc is added for NE2000 ISA card.

set PROJECT_HOME="C:\Users\devjin24\GitHub\devjin24\mint64"
set QEMU_HOME="C:\Program Files (x86)\qemu-0.10.4"
chdir /d %QEMU_HOME%
qemu-system-x86_64.exe -L . -m 64 -fda %PROJECT_HOME%\Disk.img -boot a -localtime -M pc -serial tcp::4444,server,nowait -smp 2
:pause > null