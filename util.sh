#!/bin/bash

if [ "$1" == "go" ] ; then
    ino build && ino upload && ino serial
elif [ "$1" == "clean" ] ; then
    ino clean && ino build
elif [ "$1" == "editor" ] ; then
    bash -c "cd src && gvim"
fi
