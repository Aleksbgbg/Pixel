#ifndef SRC_RUN_H_
#define SRC_RUN_H_

enum class ExitCode {
  kOk = 0,
  kGenericError = 1,
};

ExitCode Run();

#endif  // SRC_RUN_H_
