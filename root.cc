#include "root.h"

#include "pw_async2/basic_dispatcher.h"
#include "pw_async2/future.h"
#include "pw_async2/system_time_provider.h"
#include "pw_async2/value_future.h"
#include "pw_log/log.h"

namespace jsnl {

class Hardware {
 public:
  Hardware() : worker_thread_([this]() { this->Run(); }) {}

  ~Hardware() {
    running_ = false;
    if (worker_thread_.joinable()) {
      worker_thread_.join();
    }
  }

  pw::async2::ValueFuture<size_t> GetData() {
    do_work_ = true;
    return value_provider_.Get();
  }

 private:
  void Run() {
    static size_t counter = 0;
    while (running_) {
      if (do_work_) {
        value_provider_.Resolve(++counter);
        do_work_ = false;
      }
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
  }

  std::atomic<bool> do_work_ = false;
  std::atomic<bool> running_ = true;
  std::thread worker_thread_;
  pw::async2::ValueProvider<size_t> value_provider_;
};

class SomeTask : public pw::async2::Task {
 public:
  SomeTask(pw::chrono::SystemClock::duration duration, Hardware& hardware)
      : Task(PW_ASYNC_TASK_NAME("SomeTask")),
        duration_(duration),
        hardware_(hardware) {}

 private:
  pw::async2::Poll<> DoPend(pw::async2::Context& context) override {
    if (data_count_ >= 10) {
      PW_LOG_INFO("All work done.");
      return pw::async2::Ready();
    }

    while (true) {
      // Step 1: Request the data
      if (!value_future_.is_pendable()) {
        PW_LOG_INFO("Getting hardware data.");
        value_future_ = hardware_.GetData();
      }

      pw::async2::Poll<size_t> result = value_future_.Pend(context);
      if (result.IsPending()) {
        PW_LOG_INFO("Waiting for hardware data.");
        return pw::async2::Pending();
      }

      // Step 2: Read data.
      PW_LOG_INFO("Got hardware data: %zu", result.value());
      data_count_++;
    }
  }

  pw::chrono::SystemClock::duration duration_;
  pw::async2::ValueFuture<size_t> value_future_;
  Hardware& hardware_;
  size_t data_count_ = 0;
};

int Root() {
  // The cooperative scheduler of pw_async2.
  pw::async2::BasicDispatcher dispatcher;
  Hardware hardware;
  SomeTask task(std::chrono::seconds(1), hardware);
  dispatcher.Post(task);
  dispatcher.RunToCompletion();
  return 0;
}

}  // namespace jsnl
