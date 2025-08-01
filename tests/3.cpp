#include <iostream>
#include <thread>
#include "../al_wrapper/al_wrapper.hpp"

int main()
{
    constexpr ALfloat TIME = 2.0f;
    constexpr ALuint FREQUENCY = 44100;
    constexpr ALsizei SAMPLES = TIME * FREQUENCY;

    auto capture = al_wrapper::create_capture_device(FREQUENCY, al_wrapper::Format::Mono16, SAMPLES);

    system("pause");
    std::cout << "start capture" << std::endl;
    capture.start();

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "stop capture" << std::endl;
    capture.stop();
    std::vector<base::Int16> samples(SAMPLES);
    capture.read_samples(samples);

    auto device = al_wrapper::create_device();
    auto context = device.create_context();
    context.make_context_current();

    auto buffer = al_wrapper::create_buffer_from_mono_data(samples, FREQUENCY);
    auto source = al_wrapper::create_source_from_buffer(buffer);

    system("pause");
    std::cout << "start play" << std::endl;
    source.play();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "stop play" << std::endl;

    return 0;
}
