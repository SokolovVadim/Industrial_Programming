## Laboratory work VIII

[![Build Status](https://travis-ci.com/SokolovVadim/lab08.svg?branch=master)](https://travis-ci.com/SokolovVadim/lab08)

Данная лабораторная работа посвещена изучению систем автоматизации развёртывания и управления приложениями на примере **Docker**

```sh
$ open https://docs.docker.com/get-started/
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab08** на сервисе **GitHub**
- [x] 2. Ознакомиться со ссылками учебного материала
- [x] 3. Выполнить инструкцию учебного материала
- [x] 4. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

```sh
set username
$ export GITHUB_USERNAME=<имя_пользователя>
```

```
configure surrounding
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
```

```sh
use previous lab as prototype to new one
$ git clone https://github.com/${GITHUB_USERNAME}/lab07 lab08
$ cd lab08
$ git submodule update --init
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab08
```

```sh
set OS
$ cat > Dockerfile <<EOF
FROM ubuntu:18.04
EOF
```

```sh
set g++
$ cat >> Dockerfile <<EOF

RUN apt update
RUN apt install -yy gcc g++ cmake
EOF
```

```sh
set work dir
$ cat >> Dockerfile <<EOF

COPY . print/
WORKDIR print
EOF
```

```sh
set build
$ cat >> Dockerfile <<EOF

RUN cmake -H. -B_build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=_install
RUN cmake --build _build
RUN cmake --build _build --target install
EOF
```

```sh
set log
$ cat >> Dockerfile <<EOF

ENV LOG_PATH /home/logs/log.txt
EOF
```

```sh
$ cat >> Dockerfile <<EOF

VOLUME /home/logs
EOF
```

```sh
$ cat >> Dockerfile <<EOF

WORKDIR _install/bin
EOF
```

```sh
$ cat >> Dockerfile <<EOF

ENTRYPOINT ./demo
EOF
```
previously install docker
Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.


```sh
run Dockerfile
$ docker build -t logger .
Removing intermediate container b1039005a762
 ---> 5336c0d8a3ba
Step 11/12 : WORKDIR _install/bin
 ---> Running in bd081c463be1
Removing intermediate container bd081c463be1
 ---> 4f9ed27b78ff
Step 12/12 : ENTRYPOINT ./demo
 ---> Running in d5d8d75588a0
Removing intermediate container d5d8d75588a0
 ---> 6c16d4af4878
Successfully built 6c16d4af4878
Successfully tagged logger:latest


```

```sh
show all the images
$ docker images
REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
logger              latest              6c16d4af4878        51 seconds ago      346MB
<none>              <none>              0faa559d79e0        7 minutes ago       326MB
ubuntu              18.04               4e5021d210f6        13 days ago         64.2MB
hello-world         latest              fce289e99eb9        15 months ago       1.84kB

```

```sh
move logs to container
$ mkdir logs
$ docker run -it -v "$(pwd)/logs/:/home/logs/" logger
text1
text2
text3
<C-D>
➜  logs git:(master) ✗ cat log.txt 
text1
text2
text3

```

```sh
show logs
$ docker inspect logger
   },
        "Metadata": {
            "LastTagTime": "2020-04-02T23:01:58.052809058+03:00"
        }
    }
]

```

```sh
$ cat logs/log.txt
➜  lab08 git:(master) ✗ cat logs/log.txt
text1
text2
text3

```

```sh
change travis sticker
$ gsed -i 's/lab07/lab08/g' README.md
```

```sh
update travis
$ vim .travis.yml
/lang<CR>o
services:
- docker<ESC>
jVGdo
script:
- docker build -t logger .<ESC>
:wq
```

```sh
$ git add Dockerfile
$ git add .travis.yml
$ git commit -m"adding Dockerfile"
$ git push origin master
```

```sh
travis config
$ travis login --auto
$ travis enable
```

## Report

```sh
$ popd
$ export LAB_NUMBER=08
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Links

- [Book](https://www.dockerbook.com)
- [Instructions](https://docs.docker.com/engine/reference/builder/)

```
Copyright (c) 2015-2019 The ISC Authors
```
