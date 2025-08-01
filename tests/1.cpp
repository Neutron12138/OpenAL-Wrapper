#include <iostream>
#include <thread>
#include <cmath>
#include "../al_wrapper/al_wrapper.hpp"

int main()
{
    al_wrapper::PlaybackDevice device = al_wrapper::create_device();
    al_wrapper::PlaybackContext context = al_wrapper::create_context_from_device(device);
    context.make_context_current();

    const int SAMPLE_RATE = 44100;
    const int DURATION = 1; // 1秒
    const int NUM_SAMPLES = SAMPLE_RATE * DURATION;
    std::vector<short> samples(NUM_SAMPLES);
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        samples[i] = 32760 * sin(8.0 * 3.14159265 * 440.0 * i / SAMPLE_RATE);
    }

    al_wrapper::Buffer buffer = al_wrapper::create_buffer_from_mono_data(samples, SAMPLE_RATE);
    al_wrapper::Source source = al_wrapper::create_source_from_buffer(buffer);

    source.play();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}