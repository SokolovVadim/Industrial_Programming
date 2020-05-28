## Laboratory work V
[![Build Status](https://travis-ci.com/SokolovVadim/lab04.svg?branch=master)](https://travis-ci.com/SokolovVadim/lab05)

Данная лабораторная работа посвещена изучению фреймворков для тестирования на примере **GTest**

```ShellSession
$ open https://github.com/google/googletest
```
![alt_txt](https://github.com/SokolovVadim/lab05/blob/master/artifacts/screenshot.png)
## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab05** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```ShellSession // Set necessary settings
$ export GITHUB_USERNAME=<имя_пользователя> // set github username
$ alias gsed=sed # for *-nix system // install allias
```

```ShellSession // set surrounding
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```ShellSession // prepare folders from previous repo to be used in current lab
$ git clone https://github.com/${GITHUB_USERNAME}/lab04 projects/lab05
$ cd projects/lab05
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab05
```

```ShellSession // create submodule
$ mkdir third-party // new dir
$ git submodule add https://github.com/google/googletest third-party/gtest // add submodule
$ cd third-party/gtest && git checkout release-1.8.1 && cd ../.. // pecialise version
I had to create new branch for that
$ git add third-party/gtest // add 
$ git commit -m"added gtest framework" // commit test framework
```

```ShellSession
$ gsed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\ // add options
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt
$ cat >> CMakeLists.txt <<EOF // add testing

if(BUILD_TESTS)
  enable_testing() // allow testing
  add_subdirectory(third-party/gtest) // subdir to be found by linker
  file(GLOB \${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check \${\${PROJECT_NAME}_TEST_SOURCES}) // add exec files
  target_link_libraries(check \${PROJECT_NAME} gtest_main) // link libs
  add_test(NAME check COMMAND check) // add what to test
endif()
EOF
```

```ShellSession // write test
$ mkdir tests
$ cat > tests/test1.cpp <<EOF
#include <print.hpp>

#include <gtest/gtest.h> // gtest

TEST(Print, InFileStream) // test module with function and description
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text); // if(result == text)
}
EOF
```

```ShellSession build
$ cmake -H. -B_build -DBUILD_TESTS=ON // config
$ cmake --build _build // build
Scanning dependencies of target gtest
[  8%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[ 16%] Linking CXX static library libgtest.a
[ 16%] Built target gtest
Scanning dependencies of target print
[ 25%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 33%] Linking CXX static library libprint.a
[ 33%] Built target print
Scanning dependencies of target gtest_main
[ 41%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 50%] Linking CXX static library libgtest_main.a
[ 50%] Built target gtest_main
Scanning dependencies of target check
[ 58%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 66%] Linking CXX executable check
[ 66%] Built target check
Scanning dependencies of target gmock
[ 75%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 83%] Linking CXX static library libgmock.a
[ 83%] Built target gmock
Scanning dependencies of target gmock_main
[ 91%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library libgmock_main.a
[100%] Built target gmock_main

$ cmake --build _build --target test // run test
Running tests...
Test project /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec
```

```ShellSession // check if everything OK
$ _build/check
Running main() from /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/third-party/gtest/googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test case.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test case ran. (0 ms total)
[  PASSED  ] 1 test
$ cmake --build _build --target test -- ARGS=--verbose
Running tests...
UpdateCTestConfiguration  from :/home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/_build/DartConfiguration.tcl
Test project /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/_build/check
1: Test timeout computed to be: 9.99988e+06
1: Running main() from /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab05/lab04/third-party/gtest/googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test case.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (0 ms)
1: [----------] 1 test from Print (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test case ran. (0 ms total)
1: [  PASSED  ] 1 test.
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec

```

```ShellSession // add flags
$ gsed -i 's/lab04/lab05/g' README.md // change lab in MD config
$ gsed -i 's/\(DCMAKE_INSTALL_PREFIX=_install\)/\1 -DBUILD_TESTS=ON/' .travis.yml // new prefix
$ gsed -i '/cmake --build _build --target install/a\ // add flags
- cmake --build _build --target test -- ARGS=--verbose
' .travis.yml
language: cpp

script:
- cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install -DBUILD_TESTS=ON
- cmake --build _build
- cmake --build _build --target install
- cmake --build _build --target test -- ARGS=--verbose

addons:
  apt:
    sources:
      - george-edison55-precise-backports
    packages:
      - cmake
      - cmake-data

```

```ShellSession
$ travis lint // check if everything OK
Hooray, .travis.yml looks valid :)
```

```ShellSession // commit .yml & tests
$ git add .travis.yml
$ git add tests
$ git add -p
$ git commit -m"added tests"
$ git push origin master
```

```ShellSession // login
$ travis login --auto
$ travis enable
```

```ShellSession // create artifacts
$ mkdir artifacts
$ sleep 20s && gnome-screenshot --file artifacts/screenshot.png // create screenshot
# for macOS: $ screencapture -T 20 artifacts/screenshot.png
# open https://github.com/${GITHUB_USERNAME}/lab05
```

## Report

```ShellSession
$ popd
$ export LAB_NUMBER=05
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

### Задание
1. Создайте `CMakeList.txt` для библиотеки *banking*.
2. Создайте модульные тесты на классы `Transaction` и `Account`.
    * Используйте mock-объекты.
    * Покрытие кода должно составлять 100%.
3. Настройте сборочную процедуру на **TravisCI**.
4. Настройте [Coveralls.io](https://coveralls.io/).

## Links

- [C++ CI: Travis, CMake, GTest, Coveralls & Appveyor](http://david-grs.github.io/cpp-clang-travis-cmake-gtest-coveralls-appveyor/)
- [Boost.Tests](http://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/)
- [Catch](https://github.com/catchorg/Catch2)

```
Copyright (c) 2015-2019 The ISC Authors
```
