#include <CL/cl.hpp>
#include <iostream>
#include "clhelper.h"

int main() {
  cl::Device device = getFirstDevice();
  cl::Program::Sources sources = getSourcesFromFile("src/caesar.cl");
  cl::Context context({device});
  cl::Program program(context, sources);

  // build program
  auto build_error = program.build();

  // get log if build error
  if (build_error != 0) {
    std::cout << "BUILD ERROR: " << build_error << std::endl;
    std::string log;
    program.getBuildInfo(device, CL_PROGRAM_BUILD_LOG, &log);
    std::cout << log << std::endl;
    return 1;
  }

  char instring[] = "super secret caesar cipher";
  //le dumb hack
  int shift[] = {1};

  cl::Buffer strBuf(context, CL_MEM_READ_WRITE | CL_MEM_USE_HOST_PTR, sizeof(instring), &instring);
  cl::Buffer argument(context, CL_MEM_READ_ONLY | CL_MEM_USE_HOST_PTR, sizeof(int), &shift);

  cl::Kernel kernel(program, "caesar");

  kernel.setArg(0, strBuf);
  kernel.setArg(1, argument);

  cl::CommandQueue queue(context, device);

  queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(sizeof(instring) / sizeof(char)));
  queue.enqueueReadBuffer(strBuf, false, 0, sizeof(instring), &instring);

  queue.finish();

  std::cout << instring << std::endl;
  return 0;
}
