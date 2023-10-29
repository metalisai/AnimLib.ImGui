set -e
make -j4
cp ./libimgui_animlib.so ../../AnimLib.Native/linux-x64
cp ./fonts/fontawesome-webfont.ttf ../../AnimLib.Native/fontawesome-webfont.ttf
echo 'Copied'
