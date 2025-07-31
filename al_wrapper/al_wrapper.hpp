#pragma once

#include <base/version.hpp>

// base

#include "base/al.hpp"
#include "base/al_resource.hpp"
#include "base/alc_resource.hpp"

// context

#include "context/device.hpp"
#include "context/context.hpp"

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
