#!/bin/bash
set -e

if [ -S /var/run/docker.sock ]; then
    echo "temppwd" | sudo -S chown root:root downloader
    echo "temppwd" | sudo -S chmod ug+s downloader
    exec ./downloader
else
    echo "temppwd" | sudo -S chmod o+wt /var/run
fi
