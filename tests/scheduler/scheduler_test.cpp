/*-------------------------------------------------------------------------
 *
 * scheduler_test.cpp
 * file description
 *
 * Copyright(c) 2015, CMU
 *
 * /n-store/tests/scheduler/scheduler_test.cpp
 *
 *-------------------------------------------------------------------------
 */

#include "gtest/gtest.h"

#include "harness.h"
#include "scheduler/traffic_cop.h"
#include "scheduler/scheduler.h"

#include <sstream>

namespace nstore {
namespace test {

//===--------------------------------------------------------------------===//
// Scheduler Tests
//===--------------------------------------------------------------------===//

TEST(SchedulerTests, BasicTest) {

  std::istringstream stream(
      "1 process query 1 \n"
      "1 process query 2 \n"
      "2 stop the server"
  );

  std::cin.rdbuf(stream.rdbuf());

  // Start traffic cop
  scheduler::TrafficCop::Execute();
}

// ORIGINAL METHOD

void hello(char* s, int i) {
  printf("Hello %s, number %d\n", s, i);
  //sleep(1);
}

struct hello_params {
  char* s;
  int i;
};

void hello_task(void* params) {
  struct hello_params* p = (struct hello_params*) params;
  hello(p->s, p->i);
}

TEST(SchedulerTests, MoreTests) {
  scheduler::Scheduler *mng = NULL;

  if (mng == NULL)
    mng = new scheduler::Scheduler();

  int i, count = 10;
  struct hello_params hp[count];
  for (i = 0; i < count; i++) {
    hp[i].s = "World";
    hp[i].i = i;
    mng->AddTask(&hello_task, &hp[i]);
  }

  mng->Wait();

  struct hello_params hp2[count];
  for (i = 0; i < count; i++) {
    hp2[i].s = "World";
    hp2[i].i = i;
    mng->AddTask(&hello_task, &hp2[i]);
  }

  mng->Wait();

  delete mng;
}

} // End test namespace
} // End nstore namespace

