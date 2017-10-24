#!/bin/bash

LOCALFOLDER=`pwd`

if [ -d $LOCALFOLDER/app/html ]; then
    rm -fR $LOCALFOLDER/app/html/
fi

mkdir $LOCALFOLDER/app/html

CC=emcc
CFLAGS="-I$LOCALFOLDER/imgui/include/"

IMGUI_FILES="$LOCALFOLDER/imgui/src/imgui.cpp $LOCALFOLDER/imgui/src/imgui_draw.cpp $LOCALFOLDER/imgui/src/imgui_impl_sdl.cpp"

DEMOFILE="$LOCALFOLDER/app/src/imgui_demo.cpp"

ENTRYPOINT="$LOCALFOLDER/app/src/main.cpp"

EMSFLAGS="-s USE_SDL=2 -s GL_FFP_ONLY=1 -o"

OUTPUT=$LOCALFOLDER/app/html/imgui.html

echo "$CC $CFLAGS $IMGUI_FILES $DEMOFILE $ENTRYPOINT $EMSFLAGS $OUTPUT -O3"

`$CC $CFLAGS $IMGUI_FILES $DEMOFILE $ENTRYPOINT $EMSFLAGS $OUTPUT -O3`
