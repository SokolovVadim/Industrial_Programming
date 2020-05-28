## Laboratory work VI
[![Build Status](https://travis-ci.com/SokolovVadim/lab06.svg?branch=master)](https://travis-ci.com/SokolovVadim/lab06)
Данная лабораторная работа посвещена изучению средств пакетирования на примере **CPack**

```ShellSession
$ open https://cmake.org/Wiki/CMake:CPackPackageGenerators
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab06** на сервисе **GitHub**
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```ShellSession // set Github Username and allias
$ export GITHUB_USERNAME=<имя_пользователя>
$ export GITHUB_EMAIL=<адрес_почтового_ящика>
$ alias edit=<nano|vi|vim|subl>
$ alias gsed=sed # for *-nix system
```

```ShellSession // set surrounding
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```ShellSession // use folders of previous lab for new lab
$ git clone https://github.com/${GITHUB_USERNAME}/lab05 projects/lab06
$ cd projects/lab06
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab06
```

```ShellSession // Set print Versions in CMakeList.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_STRING "v\${PRINT_VERSION}")
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION\
  \${PRINT_VERSION_MAJOR}.\${PRINT_VERSION_MINOR}.\${PRINT_VERSION_PATCH}.\${PRINT_VERSION_TWEAK})
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_TWEAK 0) // set verion tweak
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_PATCH 0) set verion patch
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_MINOR 1) set verion minor
' CMakeLists.txt
$ gsed -i '/project(print)/a\
set(PRINT_VERSION_MAJOR 0) set verion major
' CMakeLists.txt
$ git diff // show the diff in working tree
```
diff --git a/CMakeLists.txt b/CMakeLists.txt
index aa7a323..71b64e3 100644
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ -7,6 +7,13 @@ option(BUILD_EXAMPLES "Build examples" OFF)
 option(BUILD_TESTS "Build tests" OFF)
 
 project(print)
+set(PRINT_VERSION_MAJOR 0)
+set(PRINT_VERSION_MINOR 1)
+set(PRINT_VERSION_PATCH 0)
+set(PRINT_VERSION_TWEAK 0)
+set(PRINT_VERSION
+  ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
+set(PRINT_VERSION_STRING "v${PRINT_VERSION}")
 
 add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

```ShellSession // Generate log & description
$ touch DESCRIPTION && edit DESCRIPTION // create file DESCRIPTION and fill it
$ touch ChangeLog.md // create file Changelog
$ export DATE="`LANG=en_US date +'%a %b %d %Y'`" // write to var DATE current date
$ cat > ChangeLog.md <<EOF
* ${DATE} ${GITHUB_USERNAME} <${GITHUB_EMAIL}> 0.1.0.0 // write Username & email and current date
- Initial RPM release
EOF
```

```ShellSession // Set Cpack config
$ cat > CPackConfig.cmake <<EOF
include(InstallRequiredSystemLibraries) /// installing libraries
EOF
```

```ShellSession // configure version
$ cat >> CPackConfig.cmake <<EOF
set(CPACK_PACKAGE_CONTACT ${GITHUB_EMAIL})  // config email
set(CPACK_PACKAGE_VERSION_MAJOR \${PRINT_VERSION_MAJOR}) // set versions
set(CPACK_PACKAGE_VERSION_MINOR \${PRINT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH \${PRINT_VERSION_PATCH})
set(CPACK_PACKAGE_VERSION_TWEAK \${PRINT_VERSION_TWEAK})
set(CPACK_PACKAGE_VERSION \${PRINT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_FILE \${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION) // set source tree
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing") // set summary
EOF
```

```ShellSession // license & readme
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RESOURCE_FILE_LICENSE \${CMAKE_CURRENT_SOURCE_DIR}/LICENSE) // set LICENSE
set(CPACK_RESOURCE_FILE_README \${CMAKE_CURRENT_SOURCE_DIR}/README.md) // set README
EOF
```

```ShellSession // set Cpack info
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_RPM_PACKAGE_NAME "print-devel") // set name
set(CPACK_RPM_PACKAGE_LICENSE "MIT") // set license
set(CPACK_RPM_PACKAGE_GROUP "print") // set print as group
set(CPACK_RPM_CHANGELOG_FILE \${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md) // set source dir
set(CPACK_RPM_PACKAGE_RELEASE 1) // set release version
EOF
```

```ShellSession set DEBIAN_PACKAGE
$ cat >> CPackConfig.cmake <<EOF

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev") // libprint
set(CPACK_DEBIAN_PACKAGE_PREDEPENDS "cmake >= 3.0") // Cmake requirements
set(CPACK_DEBIAN_PACKAGE_RELEASE 1) // set release version
EOF
```

```ShellSession // include Cpack
$ cat >> CPackConfig.cmake <<EOF

include(CPack) // include Cpack
EOF
```

```ShellSession // include config to cmake
$ cat >> CMakeLists.txt <<EOF

include(CPackConfig.cmake) // include cpackconfig
EOF
```

```ShellSession // change lab ref in readme
$ gsed -i 's/lab05/lab06/g' README.md
```

```ShellSession // add and commit with version
$ git add .
$ git commit -m"added cpack config"
$ git tag v0.1.0.0 // tag version
$ git push origin master --tags // tags
```

```ShellSession // travis login
$ travis login --auto travis login
$ travis enable
```

```ShellSession // build and pack
$ cmake -H. -B_build // config
The C compiler identification is GNU 7.5.0
-- The CXX compiler identification is GNU 7.5.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab06/lab06/_build

$ cmake --build _build // build
Scanning dependencies of target print
[ 50%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[100%] Linking CXX static library libprint.a
[100%] Built target print
$ cd _build
$ cpack -G "TGZ" // pack
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print
CPack: Create package
CPack: - package: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab06/lab06/_build/print-0.1.0.0-Linux.tar.gz generated.
$ cd ..
```

```ShellSession // generate pack
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ" // gen pack
-- Configuring done
-- Generating done
-- Build files have been written to: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab06/lab06/_build

$ cmake --build _build --target package // build
[100%] Built target print
Run CPack packaging tool...
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print
CPack: Create package
CPack: - package: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab06/lab06/_build/print-0.1.0.0-Linux.tar.gz generated.
```

```ShellSession
$ mkdir artifacts // create artifacts
$ mv _build/*.tar.gz artifacts // put tar to artifacts
$ tree artifacts // show tar
```
artifacts
└── print-0.1.0.0-Linux.tar.gz

0 directories, 1 file


## Report

```ShellSession
$ popd
$ export LAB_NUMBER=06
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

После того, как вы настроили взаимодействие с системой непрерывной интеграции,</br>
обеспечив автоматическую сборку и тестирование ваших изменений, стоит задуматься</br>
о создание пакетов для измениний, которые помечаются тэгами (см. вкладку [releases](https://github.com/tp-labs/lab06/releases)).</br>
Пакет должен содержать приложение _solver_ из [предыдущего задания](https://github.com/tp-labs/lab03#задание-1)
Таким образом, каждый новый релиз будет состоять из следующих компонентов:
- архивы с файлами исходного кода (`.tar.gz`, `.zip`)
- пакеты с бинарным файлом _solver_ (`.deb`, `.rpm`, `.msi`, `.dmg`)

В качестве подсказки:
```bash
$ cat .travis.yml
os: osx
script:
...
- cpack -G DragNDrop # dmg

$ cat .travis.yml
os: linux
script:
...
- cpack -G DEB # deb

$ cat .travis.yml
os: linux
addons:
  apt:
    packages:
    - rpm
script:
...
- cpack -G RPM # rpm

$ cat appveyor.yml
platform:
- x86
- x64
build_script:
...
- cpack -G WIX # msi
```

Для этого нужно добавить ветвление в конфигурационные файлы для **CI** со следующей логикой:</br>
если **commit** помечен тэгом, то необходимо собрать пакеты (`DEB, RPM, WIX, DragNDrop, ...`) </br>
и разместить их на сервисе **GitHub**. (см. пример для [Travi CI](https://docs.travis-ci.com/user/deployment/releases))</br>

## Links

- [DMG](https://cmake.org/cmake/help/latest/module/CPackDMG.html)
- [DEB](https://cmake.org/cmake/help/latest/module/CPackDeb.html)
- [RPM](https://cmake.org/cmake/help/latest/module/CPackRPM.html)
- [NSIS](https://cmake.org/cmake/help/latest/module/CPackNSIS.html)

```
Copyright (c) 2015-2019 The ISC Authors
```
