#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Usage: $0 <command>"
	exit 1
fi

# Set the path to the Toralizer library
export LD_PRELOAD=/home/atan/KDev/c_toralizer/libtoralizer.so
${@}
unset LD_PRELOAD


