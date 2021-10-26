#!/usr/bin/expect -f

spawn sudo ./downloader
expect "*?assword for ubuntu:*"
send -- "temppwd\n"
interact
