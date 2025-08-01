#include <iostream>
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include <base/core/time.hpp>
#include "../al_wrapper/al_wrapper.hpp"

struct MADecoder
{
    ma_decoder_config config = ma_decoder_config_init(ma_format_s16, 1, 44100);
    ma_decoder decoder;

    MADecoder()
    {
        ma_result result = ma_decoder_init_file("assets/室内系的TrackMaker (DJ版)-hanser.mp3", &config, &decoder);
        if (result != MA_SUCCESS)
            throw BASE_MAKE_RUNTIME_ERROR("Failed to load audio file, reason: ", result);
    }
    ~MADecoder() { ma_decoder_uninit(&decoder); }
    operator ma_decoder *() { return &decoder; }
};

int main()
{
    auto device = al_wrapper::create_device();
    auto context = device.create_context();
    context.make_context_current();

    al_wrapper::set_doppler_factor(1.0f);
    al_wrapper::set_doppler_velocity(343.3f);

    auto &listener = al_wrapper::Listener::get_instance();
    listener.set_gain(2.0f);

    MADecoder decoder;
    ma_uint64 frame_count;
    ma_result result = ma_decoder_get_length_in_pcm_frames(decoder, &frame_count);
    if (result != MA_SUCCESS)
        throw BASE_MAKE_RUNTIME_ERROR("Failed to get frame count, reason: ", result);

    std::vector<base::Int16> data(frame_count);
    ma_decoder_read_pcm_frames(decoder, data.data(), frame_count, nullptr);

    auto buffer = al_wrapper::create_buffer_from_mono_data(data);
    auto source = al_wrapper::create_source_from_buffer(buffer);
    source.play();

    constexpr glm::vec3 VELOCITY = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 position = glm::vec3(0.0f, 0.0f, -100.0f);
    source.set_gain(2.0f);
    source.set_velocity(VELOCITY);
    source.set_position(position);

    using Time = base::SteadyTime;
    double elapsed = 0.0;
    auto beg = Time::get_current_time();
    float sec;
    for (auto state = source.get_state();
         state != al_wrapper::Source::State::Stopped;
         state = source.get_state())
    {
        auto curr = Time::get_current_time();
        double delta = (curr - beg).count();
        beg = curr;

        position += VELOCITY * float(delta);
        source.set_position(position);

        elapsed += delta;
        if (elapsed < 1.0)
            continue;

        sec = source.get_parameter<ALfloat>(al_wrapper::Source::ParameterName::SecOffset);
        std::cout << "current offset in seconds: " << sec << std::endl;
        elapsed -= 1.0;
    }

    std::cout << "total length in seconds: " << sec << std::endl;
    system("pause");

    return 0;
}
