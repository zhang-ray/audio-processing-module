#ifdef __ANDROID__

#include <iostream>
#include <memory>
#include <jni.h>
#include <cassert>

#include "webrtc_vad.hpp"


namespace {
VadInst* vad=nullptr;
}

extern "C" {

JNIEXPORT jint JNICALL Java_com_z_r_vadInit(JNIEnv *env, jclass) {
    vad = WebRtcVad_Create();
    if (WebRtcVad_Init(vad)){
        std::cerr << "WebRtcVad_Init failed" << std::endl;
        return -1;
    }

    if (WebRtcVad_set_mode(vad, 3)){
        std::cerr << "WebRtcVad_set_mode failed" << std::endl;
        return -1;
    }

    return 0;
}


JNIEXPORT jint JNICALL Java_com_z_r_vadProcess16kHzMono(JNIEnv *env, jclass , jshortArray data) {
    auto pArray = env->GetShortArrayElements(data, nullptr);
    auto size = env->GetArrayLength(data);
    return WebRtcVad_Process(vad, 16000, pArray, size);
}


JNIEXPORT void JNICALL Java_com_z_r_vadDeInit(JNIEnv *env, jclass) {
    WebRtcVad_Free(vad);
}


}



#endif // __ANDROID__