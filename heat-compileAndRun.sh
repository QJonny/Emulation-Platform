 #!/bin/sh
echo 'Removing old running processes (if they exist)...'
#kill -9 `ps -ef | grep spin_emu | grep -v grep | awk '{print $2}'`
killall -HUP spin_emu
killall -HUP visualiser
echo 'Cleaning old temp directories (if they exist)...'
rm -rf /tmp/spin_emu*
echo 'Compiling the emulator...'
(cd ./emu/; exec make)
echo 'Compiling the heat_demo...'
(cd ./demos/; exec make prog=heat_demo)
echo 'Compiling the visualiser...'
(cd ../tools/visualiser/; exec g++ visualiser.cpp -o visualiser -lGLU -lGL -lglut -lpthread -lconfig)
echo 'Starting the visualiser and emulator...'
(cd ../tools/visualiser/; exec ./visualiser -c heatmap4.ini &)
(cd ./emu/; exec ./spin_emu)
