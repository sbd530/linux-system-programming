#!/bin/bash

# -e : file exists?
# -f : is regular file?
# -d : is diretory?
# -b : is block device file?
# -c : is charater device file?
# -L : is symbolic link file?
# -r : has read permission?
# -w : has write permission?
# -x : has execute permission?

if [ -e /etc/passwd ]; then
    echo "file exists"
else
    echo "file doesn't exists"
fi

if [ -f /etc/passwd ]; then
    echo "is regular file"
else
    echo "isn't regular file"
fi

if [ -d /etc/ ]; then
    echo "diretory exists"
else
    echo "diretory doesn't exists"
fi

if [ -b /dev/sda ]; then
    echo "is block device file"
else
    echo "isn't block device file"
fi

if [ -c /dev/autofs ]; then
    echo "is charater device file"
else
    echo "isn't charater device file"
fi

if [ -L /usr/lib/cpp ]; then
    echo "is symbolic link file"
else
    echo "isn't symbolic link file"
fi

TARGET_FILE="./string.sh"
if [ -r "$TARGET_FILE" ]; then
    echo "$TARGET_FILE is readable"
else
    echo "$TARGET_FILE is not readable"
fi
if [ -w "$TARGET_FILE" ]; then
    echo "$TARGET_FILE is writable"
else
    echo "$TARGET_FILE is not writable"
fi
if [ -x "$TARGET_FILE" ]; then
    echo "$TARGET_FILE is executable"
else
    echo "$TARGET_FILE is not executable"
fi