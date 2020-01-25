#!/bin/bash
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" > /dev/null 2>&1 && pwd )"
VS_BUID_DIR="$ROOT_DIR/vs_build"
SX7_TOOLCHAIN_DIR="$ROOT_DIR/toolchains/sx7_toolchain"
BIN_DIR="$ROOT_DIR/bin"


if [ ! -d "$SX7_TOOLCHAIN_DIR" ]; then
  # Download SX7 toolchain
  python $ROOT_DIR/toolchains/scripts/sigma_toolchain.py --toolchain sx7_toolchain-v1.tar.gz
fi

if [ ! -d "$VS_BUID_DIR" ]; then
  # Clone V-Silicon build repository
  git clone git@github.com:BuddyTV/vs_build.git
fi

# setup toolchain paths
export PATH="$PATH:$SX7_TOOLCHAIN_DIR/armv7a/bin"
export CCPREFIX="$SX7_TOOLCHAIN_DIR/armv7a/bin/armv7a-cros-linux-gnueabi-"

