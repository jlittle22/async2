#include "root.h"

#include <iostream>

#include "pw_async2/basic_dispatcher.h"
#include "pw_async2/future.h"
#include "pw_async2/system_time_provider.h"
#include "pw_log/log.h"

namespace jsnl {

int Root() {
  // Populates static boot_time variable.
  GetBootTime();

  std::cerr << "Hello from Root" << std::endl;
  return 0;
}

}  // namespace jsnl
