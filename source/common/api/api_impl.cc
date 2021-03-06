#include "common/api/api_impl.h"

#include <chrono>
#include <string>

#include "common/common/thread.h"
#include "common/event/dispatcher_impl.h"

namespace Envoy {
namespace Api {

Impl::Impl(Thread::ThreadFactory& thread_factory, Stats::Store&, Event::TimeSystem& time_system,
           Filesystem::Instance& file_system)
    : thread_factory_(thread_factory), time_system_(time_system), file_system_(file_system) {}

Event::DispatcherPtr Impl::allocateDispatcher() {
  return std::make_unique<Event::DispatcherImpl>(*this, time_system_);
}

Event::DispatcherPtr Impl::allocateDispatcher(Buffer::WatermarkFactoryPtr&& factory) {
  return std::make_unique<Event::DispatcherImpl>(std::move(factory), *this, time_system_);
}

} // namespace Api
} // namespace Envoy
