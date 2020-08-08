To add a new test file in the folder `test`:
- in the test file write `#include <boost/test/unit_test.hpp>`
- include the test file in the project (with CLion add it in the `add_executable()` command in the CMakeLists.txt file)
- (include in the project also the files containing the classes to be tested)
- compile and run the main.cpp (already present in the master)
- (in CLion it is also possible to run separately a test suite or a test case, or running all of them by selecting the configuration `All in main.cpp`)