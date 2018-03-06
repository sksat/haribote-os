#!/bin/bash

error () {
	if [ $# == 0 ]; then
		echo "error"
		exit -1
	elif [ $# == 1 ]; then
		echo "error: "
		printf "\t"
		echo $1
		exit -1
	else
		echo $1
		exit $2
	fi
}

root () {
	if [ "`whoami`" != "root" ]; then
		echo "require root priviledge"
		sudo env >/dev/null 2>&1
	fi
}

install () {
	pac=""
	com=""
	if [ $# == 0 ]; then
		error "please set package"
	elif [ $# == 1 ]; then
		pac=$1
		com=$1
	elif [ $# == 2 ]; then
		pac=$1
		com=$2
	fi
	printf "%-30s" "install $pac ..."
	if [ type $com > /dev/null 2>&1 ]; then
		root
		apt-get install -y $pac
	else
		printf "already installed.\n"
	fi
}

check_emacs () {
	if [ ! `type emacs > /dev/null 2>&1` ]; then
		echo "warning: emacs found!"
	fi
}

echo "install tools for OS dev"

install git
install hexedit

check_emacs

install vim

echo "install tolset..."
if [ ! -e tolset ]; then
	mkdir tolset
else
	if [ ! -d tolset ]; then
		error "please delete 'tolset'"
	fi
fi
if [ -e tolset/z_tools ]; then
	echo "z_tools found."
else
	git clone https://github.com/HariboteOS/z_tools_linux tolset/z_tools
fi
if [ `getconf LONG_BIT` = "64" ]; then
	install libc6-i386
fi
install qemu
install bochs-sdl
install make

echo "all install finished!"
