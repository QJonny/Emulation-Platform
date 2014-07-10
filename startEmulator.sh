 #!/bin/sh
echo 'Removing old running processes (if they exist)...'
#kill -9 `ps -ef | grep spin_emu | grep -v grep | awk '{print $2}'`
killall -HUP spin_emu
killall -HUP visualiser
echo 'Cleaning old temp directories (if they exist)...'
rm -rf /tmp/spin_emu*
echo 'Compiling the emulator...'
(cd ./emu/; exec make)
echo 'Starting the emulator...'
(cd ./emu/; exec ./spin_emu)
