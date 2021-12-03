#!/usr/bin/expect -f

set hostname [lrange $argv 0 0]

spawn ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null ubuntu@$hostname
expect "*?assword:*"
send -- "temppwd\n"
expect "*$ "
send -- "sudo systemctl stop accounts-daemon\n"
expect "*?assword*"
send -- "temppwd\n"
expect "*$ "
send -- "sudo systemctl stop acpid\n"
expect "*$ "
send -- "sudo systemctl stop apache2\n"
expect "*$ "
send -- "sudo systemctl stop apparmor\n"
expect "*$ "
send -- "sudo systemctl stop apport\n"
expect "*$ "
send -- "sudo systemctl stop avahi-daemon\n"
expect "*$ "
send -- "sudo systemctl stop console-setup\n"
expect "*$ "
send -- "sudo systemctl stop cpufrequtils\n"
expect "*$ "
send -- "sudo systemctl stop cron\n"
expect "*$ "
send -- "sudo systemctl stop cups-browsed\n"
expect "*$ "
send -- "sudo systemctl stop cups\n"
expect "*$ "
send -- "sudo systemctl stop dbus\n"
expect "*$ "
send -- "sudo systemctl stop hostapd\n"
expect "*$ "
send -- "sudo systemctl stop keyboard-setup\n"
expect "*$ "
send -- "sudo systemctl stop kmod-static-nodes\n"
expect "*$ "
send -- "sudo systemctl stop lightdm\n"
expect "*$ "
send -- "sudo systemctl stop lm-sensors\n"
expect "*$ "
send -- "sudo systemctl stop loadcpufreq\n"
expect "*$ "
send -- "sudo systemctl stop ModemManager\n"
expect "*$ "
sleep 2
send -- "sudo pkill -u avahi\n"
expect "*$ "
send -- "sudo pkill -u lightdm\n"
expect "*$ "
send -- "sudo pkill -u ntp\n"
expect "*$ "
send -- "sudo pkill -u rtkit\n"
expect "*$ "
send -- "sudo systemctl stop NetworkManager\n"
sleep 1
close
