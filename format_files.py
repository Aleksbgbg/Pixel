"""
Formats C++ source and header files in codebase
- Adds trailing newline
- Fixes incorrect header guards
"""

import os


CODE_PATHS = ["src"]
EXTENSIONS = [".cpp", ".cc", ".h"]

root = os.path.dirname(os.path.realpath(__file__))

for path in CODE_PATHS:
  for subdir, dirs, files in os.walk(path):
    for file in files:
      if any(file.endswith(extension) for extension in EXTENSIONS):
        continue

      modified = False

      relative_path = os.path.join(subdir, file)

      with open(relative_path, "r+") as file_handle:
        lines = file_handle.read().split("\n")

        # Enforce trailing newline
        if len(lines[-1]) > 0:
          lines.append("")
          modified = True

        # Coerce header guards
        if file.endswith(".h"):
          header_guard = relative_path.upper().replace("\\", "_").replace("/", "_")[:-2] + "_H_"

          end_guard_line_index = 0

          for (index, line) in enumerate(lines):
            if line.startswith("#endif"):
              end_guard_line_index = index

          guard_line = f"#ifndef {header_guard}"
          define_line = f"#define {header_guard}"
          end_guard_line = f"#endif  // {header_guard}"

          if lines[0] != guard_line or lines[1] != define_line or lines[end_guard_line_index] != end_guard_line:
            lines[0] = guard_line
            lines[1] = define_line
            lines[end_guard_line_index] = end_guard_line

            modified = True

        if modified:
          file_handle.seek(0)
          file_handle.write("\n".join(lines))
          file_handle.truncate()
