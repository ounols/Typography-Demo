#!/bin/bash
echo [build.sh Start!]
git submodule update --init --recursive --remote
mkdir build
cd ../../Assets
zip -r Assets.zip . -x '*Assets.zip*'
mv Assets.zip ../platforms/Web/build/Assets.zip
cd ../platforms/Web/build
../../../../emsdk/upstream/emscripten/emcmake cmake -DCMAKE_BUILD_TYPE=Debug ../
cmake --build .
mkdir result
mv AvatarRenderer.data AvatarRenderer.html AvatarRenderer.js AvatarRenderer.wasm AvatarRenderer.wasm.map result/
