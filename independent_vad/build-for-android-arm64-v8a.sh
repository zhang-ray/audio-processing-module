#!/bin/bash


rm -rf ../independent_vad-build-android-arm64-v8a
exit 1 | \
mkdir ../independent_vad-build-android-arm64-v8a && cd ../independent_vad-build-android-arm64-v8a

exit 1 | \
~/Android/Sdk/cmake/3.10.2.4988404/bin/cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk-bundle/build/cmake/android.toolchain.cmake -DANDROID_ABI=arm64-v8a -DANDROID_ARM_NEON=TRUE -DCMAKE_BUILD_TYPE=Release ../independent_vad

# build 
exit 1 | \
make -j8
