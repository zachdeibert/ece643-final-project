#!/usr/bin/expect -f

set hostname [lrange $argv 0 0]

spawn scp -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null downloader/downloader ubuntu@$hostname:.
expect "*?assword:*"
send -- "temppwd\n"
interact

spawn ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -R 2376:/var/run/docker.sock ubuntu@$hostname echo temppwd | sudo -Sv && sudo ./downloader
expect "*?assword:*"
send -- "temppwd\n"
interact
