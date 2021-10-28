#!/usr/bin/expect -f

set hostname [lrange $argv 0 0]

spawn scp -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null downloader/downloader Launch.sh ubuntu@$hostname:.
expect "*?assword:*"
send -- "temppwd\n"
interact

spawn ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null ubuntu@$hostname ./Launch.sh
expect "*?assword:*"
send -- "temppwd\n"
interact

spawn ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -R /var/run/docker.sock:/var/run/docker.sock ubuntu@$hostname ./Launch.sh
expect "*?assword:*"
send -- "temppwd\n"
interact

spawn ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null ubuntu@$hostname rm downloader Launch.sh /var/run/docker.sock
expect "*?assword:*"
send -- "temppwd\n"
interact
