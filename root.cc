#include "root.h"

#include "pw_async2/basic_dispatcher.h"
#include "pw_async2/future.h"
#include "pw_async2/system_time_provider.h"
#include "pw_log/log.h"

namespace jsnl {

class SomeTask : public pw::async2::Task {
 public:
  SomeTask(pw::chrono::SystemClock::duration duration)
      : Task(PW_ASYNC_TASK_NAME("SomeTask")), duration_(duration) {}

 private:
  pw::async2::Poll<> DoPend(pw::async2::Context& context) override {
    // Acquire a future when the task first runs.
    if (!time_future_.is_pendable()) {
      time_future_ = pw::async2::GetSystemTimeProvider().WaitFor(duration_);
    }

    // Wait for the timer to complete.
    if (time_future_.Pend(context).IsPending()) {
      PW_LOG_INFO("Waiting…");
      // Notify the dispatcher that the task is stalled.
      return pw::async2::Pending();
    }

    PW_LOG_INFO("Done!");
    // Notify the dispatcher that the task is complete.
    return pw::async2::Ready();
  }

  pw::chrono::SystemClock::duration duration_;
  pw::async2::TimeFuture<pw::chrono::SystemClock> time_future_;
};

int Root() {
  // The cooperative scheduler of pw_async2.
  pw::async2::BasicDispatcher dispatcher;
  SomeTask task(std::chrono::seconds(1));
  dispatcher.Post(task);
  dispatcher.RunToCompletion();
  return 0;
}

}  // namespace jsnl
