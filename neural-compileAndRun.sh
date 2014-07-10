 #!/bin/sh
echo 'Removing old running processes (if they exist)...'
#kill -9 `ps -ef | grep spin_emu | grep -v grep | awk '{print $2}'`
killall -HUP spin_emu
killall -HUP visualiser
echo 'Cleaning old temp directories (if they exist)...'
rm -rf /tmp/spin_emu*
echo 'Compiling the emulator...'
(cd ./emu/; exec make)
echo 'Compiling the neural model application framework...'
(cd ../src/app_frame/build; exec make -f emu.make.package clean)
(cd ../src/app_frame/build; exec make -f emu.make.package)
(cd ../src/app_dump/build;  exec make -f emu.make.package clean)
(cd ../src/app_dump/build;  exec make -f emu.make.package)
(cd ../src/app_spike_source/build;  exec make -f emu.make.package clean)
(cd ../src/app_spike_source/build;  exec make -f emu.make.package)
echo 'Starting the emulator...'
(cd ./emu/; exec ./spin_emu)
