#include <iostream>
#include "webrtc_vad.hpp"
#include <fstream>
#include <vector>

int main(int argc, char *argv[]){
    /// input PCM:
    ///     SampleRate:16k
    ///     duration 10ms
    if (argc !=2){
        std::cerr << "./test_00 s16le_16k_mono.pcm" << std::endl;
        return -1;
    }

    auto vad = WebRtcVad_Create();
    if (WebRtcVad_Init(vad)){
        std::cerr << "WebRtcVad_Init failed" << std::endl;
        return -1;
    }

    if (WebRtcVad_set_mode(vad, 3)){
        std::cerr << "WebRtcVad_set_mode failed" << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);
    std::vector<short> buffer(16000/100);
    if (!ifs.is_open()){
        std::cerr << "could not open file" << std::endl;
        return -1;
    }

    for (int index = 0;!ifs.eof(); index++){
        ifs.read((char *)(buffer.data()), buffer.size()*sizeof(short));
        auto result = WebRtcVad_Process(vad, 16000, buffer.data(), buffer.size());
        std::cout << "offset(second):\t" << index*0.01
                  << "\t" <<((result==1)?"active":"inactive")
                  << std::endl;
    }

    return 0;
}
