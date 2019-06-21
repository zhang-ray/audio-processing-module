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


    {
        std::vector<bool> result;
        for (int index = 0;!ifs.eof(); index++){
            ifs.read((char *)(buffer.data()), buffer.size()*sizeof(short));
            result.push_back(1==WebRtcVad_Process(vad, 16000, buffer.data(), buffer.size()));
        }


        bool started =false;
        int lastStartIndex = 0;
        for (auto index = 1u; index < result.size(); index++){
            if (started){
                if ((!result[index])&&result[index-1]){
                    // end
                    started = false;
                    std::cout << "active section(second):\t[" << (float)lastStartIndex/100 << "\t:\t" << (float)index/100<<"]" << std::endl;
                }
            }
            else {
                if (result[index]&&(!result[index-1])){
                    started = true;
                    lastStartIndex = index;
                }
            }
        }

    }

    WebRtcVad_Free(vad);

    return 0;
}
