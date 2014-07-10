 #!/bin/sh
# Use this script if things go wrong and you can't kill the processes
kill -9 `ps -ef | grep spin_emu | grep -v grep | awk '{print $2}'`
killall -HUP visualiser
