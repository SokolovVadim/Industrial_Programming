## Laboratory work IV
[![Build Status](https://travis-ci.com/SokolovVadim/lab04.svg?branch=master)](https://travis-ci.com/SokolovVadim/lab04)

Данная лабораторная работа посвещена изучению систем непрерывной интеграции на примере сервиса **Travis CI**

```ShellSession
$ open https://travis-ci.org
```

## Tasks

- [x] 1. Авторизоваться на сервисе **Travis CI** с использованием **GitHub** аккаунта
- [x] 2. Создать публичный репозиторий с названием **lab04** на сервисе **GitHub**
- [x] 3. Ознакомиться со ссылками учебного материала
- [x] 4. Включить интеграцию сервиса **Travis CI** с созданным репозиторием
- [x] 5. Получить токен для **Travis CLI** с правами **repo** и **user**
- [x] 6. Получить фрагмент вставки значка сервиса **Travis CI** в формате **Markdown**
- [x] 7. Выполнить инструкцию учебного материала
- [x] 8. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

token:
1281932122f03fb1aeb6f5f9e522c03159a0f3a7

```ShellSession // conifure USERNAME & TOken
$ export GITHUB_USERNAME=<имя_пользователя>
$ export GITHUB_TOKEN=<полученный_токен>
```

```ShellSession // configure surrounding
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```ShellSession // travis installation
$ \curl -sSL https://get.rvm.io | bash -s -- --ignore-dotfiles // install rvm
$ echo "source $HOME/.rvm/scripts/rvm" >> scripts/activate // set rvm in surrounding
$ . scripts/activate // run script
$ rvm autolibs disable // automatically install dependencies
$ rvm install ruby-2.4.2 // install ruby
$ rvm use 2.4.2 --default // use this version as default
$ gem install travis // install travis via ruby
```

```ShellSession // use previous cmakelist
$ git clone https://github.com/${GITHUB_USERNAME}/lab03 projects/lab04 // clone prev repo as lab04
$ cd projects/lab04
$ git remote remove origin // remove prev origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab04 // add new origin
```

```ShellSession // set language
$ cat > .travis.yml <<EOF
language: cpp // c++
EOF
```

```ShellSession // build settings
$ cat >> .travis.yml <<EOF

script:
- cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install // build prefixes
- cmake --build _build 
- cmake --build _build --target install // target install
EOF
```

```ShellSession // add dependencies on cmake
$ cat >> .travis.yml <<EOF

addons:
  apt:
    sources:
      - george-edison55-precise-backports
    packages:
      - cmake
      - cmake-data
EOF
```

```ShellSession // login via token
$ travis login --github-token ${GITHUB_TOKEN}
Shell completion not installed. Would you like to install it now? |y| y
Successfully logged in as SokolovVadim!

```

```ShellSession // check for warnings
$ travis lint // Display warnings for a .travis.yml.

```

```ShellSession
$ ex -sc '1i|<фрагмент_вставки_значка>' -cx README.md // export image from travis 
```

```ShellSession
$ git add .travis.yml
$ git add README.md
$ git commit -m"added CI"
$ git push origin master
```

```ShellSession
$ travis lint
$ travis accounts
$ travis sync
$ travis repos
$ travis enable
$ travis whatsup
$ travis branches
$ travis history
$ travis show
```

## Report

```ShellSession
$ popd
$ export LAB_NUMBER=04
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Homework

Вы продолжаете проходить стажировку в "Formatter Inc." (см [подробности](https://github.com/tp-labs/lab03#Homework)).

В прошлый раз ваше задание заключалось в настройке автоматизированной системы **CMake**.

Сейчас вам требуется настроить систему непрерывной интеграции для библиотек и приложений, с которыми вы работали в [прошлый раз](https://github.com/tp-labs/lab03#Homework). Настройте сборочные процедуры на различных платформах:
* используйте [TravisCI](https://travis-ci.com/) для сборки на операционной системе **Linux** с использованием компиляторов **gcc** и **clang**;
* используйте [AppVeyor](https://www.appveyor.com/) для сборки на операционной системе **Windows**.

## Links

- [Travis Client](https://github.com/travis-ci/travis.rb)
- [AppVeyour](https://www.appveyor.com/)
- [GitLab CI](https://about.gitlab.com/gitlab-ci/)

```
Copyright (c) 2015-2019 The ISC Authors
```
