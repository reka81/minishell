#!/bin/bash

if [ -p /dev/stdin ]; then
    echo "Input was fed to cat"
else
    echo "Input was not fed to cat"
fi