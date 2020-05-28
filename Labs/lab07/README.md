## Laboratory work VII

Данная лабораторная работа посвещена изучению систем управления пакетами на примере **Hunter**

```sh
$ open https://github.com/ruslo/hunter
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab07** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
export github username and set gsed
$ export GITHUB_USERNAME=<имя_пользователя>
$ alias gsed=sed
```

```sh
configure surrounding
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```sh
use previous repo to be new one
$ git clone https://github.com/${GITHUB_USERNAME}/lab06 projects/lab07
$ cd projects/lab07
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab07
```

```sh 
download hunter and add url
$ mkdir -p cmake // make directory cmake
$ wget https://raw.githubusercontent.com/cpp-pm/gate/master/cmake/HunterGate.cmake -O cmake/HunterGate.cmake // getting hunter
Resolving raw.githubusercontent.com (raw.githubusercontent.com)... 151.101.112.133
Connecting to raw.githubusercontent.com (raw.githubusercontent.com)|151.101.112.133|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 17070 (17K) [text/plain]
Saving to: ‘cmake/HunterGate.cmake’

cmake/HunterGate.cm 100%[===================>]  16,67K  56,3KB/s    in 0,3s    

2020-04-02 21:57:50 (56,3 KB/s) - ‘cmake/HunterGate.cmake’ saved [17070/17070]

// put url and SHA1 key to CMakeLists
$ gsed -i '/cmake_minimum_required(VERSION 3.4)/a\

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
    SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
)
' CMakeLists.txt
```

```sh
rm gtest and set print version
$ git rm -rf third-party/gtest 
// set finding packages
$ gsed -i '/set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")/a\

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)
' CMakeLists.txt
$ gsed -i 's/add_subdirectory(third-party/gtest)//' CMakeLists.txt // rm subdir
$ gsed -i 's/gtest_main/GTest::main/' CMakeLists.txt // add namespace
```

```sh
Build
$ cmake -H. -B_builds -DBUILD_TESTS=ON // init hunter workspace
-- [hunter] Calculating Toolchain-SHA1
-- [hunter] Calculating Config-SHA1
-- [hunter] HUNTER_ROOT: /home/vadim/.hunter
-- [hunter] [ Hunter-ID: 5659b15 | Toolchain-ID: 9b2c9d4 | Config-ID: 8a1641b ]
-- [hunter] GTEST_ROOT: /home/vadim/.hunter/_Base/5659b15/9b2c9d4/8a1641b/Install (ver.: 1.10.0)
-- Configuring done

$ cmake --build _builds
Build

Scanning dependencies of target print
[ 25%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 50%] Linking CXX static library libprint.a
[ 50%] Built target print
Scanning dependencies of target check
[ 75%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[100%] Linking CXX executable check
[100%] Built target check

$ cmake --build _builds --target test // run tests
Running tests...
Test project /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab07/lab07/_builds
    Start 1: check
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec

$ ls -la $HOME/.hunter // show hunter dir
total 12
drwxr-xr-x  3 vadim vadim 4096 апр  2 22:11 .
drwxr-xr-x 60 vadim vadim 4096 апр  2 22:18 ..
drwxr-xr-x  6 vadim vadim 4096 апр  2 22:12 _Base

```

```sh
use hunter to run tests
$ git clone https://github.com/cpp-pm/hunter $HOME/projects/hunter
download hunter
$ export HUNTER_ROOT=$HOME/projects/hunter // export hunter
$ rm -rf _builds // rm build
$ cmake -H. -B_builds -DBUILD_TESTS=ON // download packages
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Looking for pthread_create
-- Looking for pthread_create - not found
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE  
-- Configuring done
-- Generating done
-- Build files have been written to: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab07/lab07/_builds

$ cmake --build _builds // build
Scanning dependencies of target print
[ 25%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 50%] Linking CXX static library libprint.a
[ 50%] Built target print
Scanning dependencies of target check
[ 75%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[100%] Linking CXX executable check
[100%] Built target check

$ cmake --build _builds --target test // run tests
Running tests...
Test project /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab07/lab07/_builds
    Start 1: check
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec

```

```sh
use hunter new version
$ cat $HUNTER_ROOT/cmake/configs/default.cmake | grep GTest // show hunter version
hunter_default_version(GTest VERSION 1.7.0-hunter-6)
hunter_default_version(GTest VERSION 1.10.0)

$ cat $HUNTER_ROOT/cmake/projects/GTest/hunter.cmake // show smth interesting
hunter_pick_scheme(DEFAULT url_sha1_cmake)
hunter_cacheable(GTest)
hunter_download(PACKAGE_NAME GTest PACKAGE_INTERNAL_DEPS_ID 1)

$ mkdir cmake/Hunter
add config to gtest
$ cat > cmake/Hunter/config.cmake <<EOF
hunter_config(GTest VERSION 1.7.0-hunter-9)
EOF
# add LOCAL in HunterGate function
```

```sh
create demo
$ mkdir demo
// write file.cpp
$ cat > demo/main.cpp <<EOF
#include <print.hpp>

#include <cstdlib>

int main(int argc, char* argv[])
{
  const char* log_path = std::getenv("LOG_PATH");
  if (log_path == nullptr)
  {
    std::cerr << "undefined environment variable: LOG_PATH" << std::endl;
    return 1;
  }
  std::string text;
  while (std::cin >> text)
  {
    std::ofstream out{log_path, std::ios_base::app};
    print(text, out);
    out << std::endl;
  }
}
EOF

// add target demo
$ gsed -i '/endif()/a\

add_executable(demo ${CMAKE_CURRENT_SOURCE_DIR}/demo/main.cpp)
target_link_libraries(demo print)
install(TARGETS demo RUNTIME DESTINATION bin)
' CMakeLists.txt
```

```sh
install compilers
$ mkdir tools
$ git submodule add https://github.com/ruslo/polly tools/polly // download tools
$ tools/polly/bin/polly.py --test
Log saved: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab07/lab07/_logs/polly/default/log.txt
-
Generate: 0:00:04.642112s
Build: 0:00:01.856440s
Test: 0:00:00.071641s
-
Total: 0:00:06.570742s
-
SUCCESS

$ tools/polly/bin/polly.py --install
Log saved: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab07/lab07/_logs/polly/default/log.txt
-
Generate: 0:00:04.646923s
Build: 0:00:01.836454s
-
Total: 0:00:06.483794s
-
SUCCESS

$ tools/polly/bin/polly.py --toolchain clang-cxx14 // for mac
```

## Report

```sh
$ popd
$ export LAB_NUMBER=07
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

### Задание
1. Создайте cвой hunter-пакет.

## Links

- [Create Hunter package](https://docs.hunter.sh/en/latest/creating-new/create.html)
- [Custom Hunter config](https://github.com/ruslo/hunter/wiki/example.custom.config.id)
- [Polly](https://github.com/ruslo/polly)

```
Copyright (c) 2015-2020 The ISC Authors
```
