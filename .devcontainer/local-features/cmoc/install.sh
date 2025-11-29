#!/bin/sh
set -e

# Installation instructions
# LWTools: http://www.lwtools.ca/
# CMOC: http://sarrazip.com/dev/cmoc.html

echo "Activating feature 'cmoc'"
SOURCE_DIR=/usr/src
LWTOOLS=lwtools-4.24
CMOC=cmoc-0.1.97
mkdir -p $SOURCE_DIR

# Install LWTools
cd $SOURCE_DIR
wget http://www.lwtools.ca/releases/lwtools/$LWTOOLS.tar.gz
tar -xvf $LWTOOLS.tar.gz
rm $LWTOOLS.tar.gz
cd $LWTOOLS
make
make install

# Install dependencies for CMOC
apt update
apt install -y bison flex

# Install CMOC itself
cd $SOURCE_DIR
wget http://gvlsywt.cluster051.hosting.ovh.net/dev/$CMOC.tar.gz
tar -xvf $CMOC.tar.gz
rm $CMOC.tar.gz
cd $CMOC
./configure
make
make install

# Clean up
apt remove --purge -y bison flex
cd $SOURCE_DIR
rm -rf $LWTOOLS $CMOC