#!/bin/bash

file_size=( "5K" "10k" "100k" "1M" "10M" "100M" "500M" )

for i in "${file_size[@]}"
do
{ dd if=/dev/zero of=/media/linux/device/file.img bs=$1 count=1 | grep bytes | grep awk '{print $8}' && /usr/bin/time cat /media/linux/device/file.img | grep real | awk '{print $3}' && /usr/bin/time rm /media/linux/device/file.img | grep real | awk '{print $3}' } 2> $1-filesystem-${file_size[@]}.txt 
done