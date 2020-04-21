#!/usr/bin/env bash

UNAME=$(uname|cut -f 1 -d -)

if [ "${UNAME}" == "MINGW64_NT" ] || [ "${UNAME}" == "MSYS_NT" ] || [ "${UNAME}" == "MINGW32_NT" ]; then
    export JAVA_HOME="/c/lang/openjdk"
    export GOROOT="/c/lang/Go"
    export GOPATH=${HOME}/env/go
    export PATH="${PATH}:${GOROOT}/bin:${JAVA_HOME}/bin"
fi


# gnustep japanese font
#defaults write NSGlobalDomain NSFont Takaoゴシック
#defaults write NSGlobalDomain NSUserFont Takaoゴシック
#defaults write NSGlobalDomain NSBoldFont Takaoゴシック

