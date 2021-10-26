#!/usr/bin/expect -f

set hostname [lrange $argv 0 0]

spawn scp downloader/downloader Launch.sh ubuntu@$hostname:.
expect "*?assword:*"
send -- "temppwd\n"
interact

spawn ssh -R /var/run/docker.sock:/var/run/docker.sock ubuntu@$hostname ./Launch.sh
expect "*?assword:*"
send -- "temppwd\n"
interact

spawn ssh ubuntu@$hostname rm downloader Launch.sh /var/run/docker.sock
expect "*?assword:*"
send -- "temppwd\n"
interact
