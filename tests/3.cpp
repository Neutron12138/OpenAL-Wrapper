#include <iostream>
#include <base/misc/time.hpp>
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

    using Time = base::SteadyTime;
    auto beg = Time::get_current_time();
    for (auto curr = Time::get_current_time();
         (curr - beg).count() <= 2.0;
         curr = Time::get_current_time())
        ;

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
    for (al_wrapper::Source::State state = source.get_state();
         state != al_wrapper::Source::State::Stopped;
         state = source.get_state())
        ;
    std::cout << "stop play" << std::endl;

    return 0;
}
