#pragma once

#include <base/cpp_version.hpp>

// base

#include "base/al.hpp"
#include "base/alc.hpp"
#include "base/enums.hpp"
#include "base/al_resource.hpp"
#include "base/alc_resource.hpp"

// context

#include "context/playback_context.hpp"

// device

#include "device/device.hpp"
#include "device/playback_device.hpp"
#include "device/capture_device.hpp"

// buffer

#include "buffer/buffer.hpp"

// source

#include "source/source.hpp"

// listener

#include "listener/orientation.hpp"
#include "listener/listener.hpp"

// implementation

#ifdef AL_WRAPPER_INCLUDE_IMPL
#include "al_wrapper.cpp"
#endif
