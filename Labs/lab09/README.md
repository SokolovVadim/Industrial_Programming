## Laboratory work IX
[![Build Status](https://travis-ci.com/SokolovVadim/lab09.svg?branch=master)](https://travis-ci.com/SokolovVadim/lab09)

Данная лабораторная работа посвещена изучению процесса создания пакета на примере **Github Release**

```sh
$ open https://help.github.com/articles/creating-releases/
```

## Tasks

- [x] 1. Создать публичный репозиторий с названием **lab09** на сервисе **GitHub**
- [x] 2. Ознакомиться со ссылками учебного материала
- [x] 3. Получить токен для доступа к репозиториям сервиса **GitHub**
- [x] 4. Выполнить инструкцию учебного материала
- [x] 5. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial



// set username and token, set packet manager & gpg


```sh
$ export GITHUB_TOKEN=92ad92394fe42572c3f91c6e9dea1fe36e9c125e
$ export GITHUB_USERNAME=SokolovVadim
$ export PACKAGE_MANAGER=apt-get
$ export GPG_PACKAGE_NAME=gpg

gpg (GnuPG) 2.2.4
libgcrypt 1.8.1


install xclip to perform ooperations like on OSX
and set alias


```sh
# for *-nix system
$ $PACKAGE_MANAGER install xclip
$ alias gsed=sed
$ alias pbcopy='xclip -selection clipboard'
$ alias pbpaste='xclip -selection clipboard -o'
```
configure surrounding

download go packages
// previously downloaded go
The following additional packages will be installed:
  golang-1.14-go golang-1.14-src golang-src

```sh
$ cd ${GITHUB_USERNAME}/workspace
$ pushd .
$ source scripts/activate
$ go get github.com/aktau/github-release
```

Use previous lab as entry
```sh
$ git clone https://github.com/${GITHUB_USERNAME}/lab08 projects/lab09
$ cd projects/lab09
$ git remote remove origin
$ git remote add origin https://github.com/${GITHUB_USERNAME}/lab09
```


substitute lab08 by lab09 at readme (image from travis including)
```sh
$ gsed -i 's/lab08/lab09/g' README.md
```

install and config

```sh
$ $PACKAGE_MANAGER install ${GPG_PACKAGE_NAME} // install gpg
$ gpg --list-secret-keys --keyid-format LONG // show already existing keys
$ gpg --full-generate-key // generate new key

gpg (GnuPG) 2.2.4; Copyright (C) 2017 Free Software Foundation, Inc.
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.

Please select what kind of key you want:
   (1) RSA and RSA (default)
   (2) DSA and Elgamal
   (3) DSA (sign only)
   (4) RSA (sign only)
Your selection? 1
RSA keys may be between 1024 and 4096 bits long.
What keysize do you want? (3072) 4096
Requested keysize is 4096 bits
Please specify how long the key should be valid.
         0 = key does not expire
      <n>  = key expires in n days
      <n>w = key expires in n weeks
      <n>m = key expires in n months
      <n>y = key expires in n years
Key is valid for? (0) 0
Key does not expire at all
Is this correct? (y/N) y

GnuPG needs to construct a user ID to identify your key.

Real name: Vadim Sokolov
Email address: varem99@mail.ru
Comment: github release
You selected this USER-ID:
    "Vadim Sokolov (github release) <varem99@mail.ru>"

Change (N)ame, (C)omment, (E)mail or (O)kay/(Q)uit? O
We need to generate a lot of random bytes. It is a good idea to perform
some other action (type on the keyboard, move the mouse, utilize the
disks) during the prime generation; this gives the random number
generator a better chance to gain enough entropy.
We need to generate a lot of random bytes. It is a good idea to perform
some other action (type on the keyboard, move the mouse, utilize the
disks) during the prime generation; this gives the random number
generator a better chance to gain enough entropy.
gpg: key EAB1E228CA92FEEC marked as ultimately trusted
gpg: directory '/home/vadim/.gnupg/openpgp-revocs.d' created
gpg: revocation certificate stored as '/home/vadim/.gnupg/openpgp-revocs.d/CC2778B379C074D4AD48E35FEAB1E228CA92FEEC.rev'
public and secret key created and signed.

pub   rsa4096 2020-04-09 [SC]
      CC2778B379C074D4AD48E35FEAB1E228CA92FEEC
uid                      Vadim Sokolov (github release) <varem99@mail.ru>
sub   rsa4096 2020-04-09 [E]


$ gpg --list-secret-keys --keyid-format LONG // show new key

gpg: checking the trustdb
gpg: marginals needed: 3  completes needed: 1  trust model: pgp
gpg: depth: 0  valid:   1  signed:   0  trust: 0-, 0q, 0n, 0m, 0f, 1u
/home/vadim/.gnupg/pubring.kbx
------------------------------
sec   rsa4096/EAB1E228CA92FEEC 2020-04-09 [SC]
      CC2778B379C074D4AD48E35FEAB1E228CA92FEEC
uid                 [ultimate] Vadim Sokolov (github release) <varem99@mail.ru>
ssb   rsa4096/5DCF8B05DFD58B3C 2020-04-09 [E]


$ gpg -K ${GITHUB_USERNAME}

// separate Key to open & secret id
$ GPG_KEY_ID=$(gpg --list-secret-keys --keyid-format LONG | grep ssb | tail -1 | awk '{print $2}' | awk -F'/' '{print $2}')
$ GPG_SEC_KEY_ID=$(gpg --list-secret-keys --keyid-format LONG | grep sec | tail -1 | awk '{print $2}' | awk -F'/' '{print $2}')

echo $GPG_KEY_ID 
5DCF8B05DFD58B3C

echo $GPG_SEC_KEY_ID 
EAB1E228CA92FEEC

$ gpg --armor --export ${GPG_KEY_ID} | pbcopy // read info to system buffer

-----BEGIN PGP PUBLIC KEY BLOCK-----

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
gr0Am/OiS6tIDobE
=I8B+
-----END PGP PUBLIC KEY BLOCK-----


$ pbpaste
echo $GPG_SEC_KEY_ID 
EAB1E228CA92FEEC

$ open https://github.com/settings/keys
$ git config user.signingkey ${GPG_SEC_KEY_ID} // add keys
$ git config gpg.program gpg
```


create tag and sign it
```sh
$ test -r ~/.bash_profile && echo 'export GPG_TTY=$(tty)' >> ~/.bash_profile
$ echo 'export GPG_TTY=$(tty)' >> ~/.profile
```

Build and check
```sh
$ cmake -H. -B_build -DCPACK_GENERATOR="TGZ"

-- Configuring done
-- Generating done
-- Build files have been written to: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab09/lab09/_build

$ cmake --build _build --target package

Scanning dependencies of target print
[ 25%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 50%] Linking CXX static library libprint.a
[ 50%] Built target print
Scanning dependencies of target demo
[ 75%] Building CXX object CMakeFiles/demo.dir/demo/main.cpp.o
[100%] Linking CXX executable demo
[100%] Built target demo
Run CPack packaging tool...
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: print
CPack: - Install project: print
CPack: Create package
CPack: - package: /home/vadim/3rdCourse/6thTerm/IndustrialProgr/lab09/lab09/_build/print-0.1.0.0-Linux.tar.gz generated.


```

```sh
$ travis login --auto
$ travis enable
```


enter with digital signature
```sh
$ git tag -s v0.1.0.0
added version with tag signing
$ git tag -v v0.1.0.0 // validation

object 0025d9dd4b0e52d5554c244d18eb726184c29478
type commit
tag v0.1.0.0
tagger Vadim <varem99@mail.ru> 1586463404 +0300

v0.1.0.0 release
gpg: Signature made Чт 09 апр 2020 23:17:29 MSK
gpg:                using RSA key CC2778B379C074D4AD48E35FEAB1E228CA92FEEC
gpg: Good signature from "Vadim Sokolov (github release) <varem99@mail.ru>" [ultimate]


$ git show v0.1.0.0
Tagger: Vadim <varem99@mail.ru>
Date:   Thu Apr 9 23:16:44 2020 +0300

v0.1.0.0 release
-----BEGIN PGP SIGNATURE-----
...

$ git push origin master --tags // push with new tag

To https://github.com/SokolovVadim/lab09.git
 * [new tag]         v0.1.0.0 -> v0.1.0.0
```



Make release
```sh
$ github-release --version
github-release v0.7.2

$ github-release info -u ${GITHUB_USERNAME} -r lab09 // list of tags

tags:
- v0.1.0.0 (commit: https://api.github.com/repos/SokolovVadim/lab09/commits/0025d9dd4b0e52d5554c244d18eb726184c29478)
releases:

$ github-release release \
    --user ${GITHUB_USERNAME} \
    --repo lab09 \
    --tag v0.1.0.0 \
    --name "libprint" \
    --description "my first release"

releases:
- v0.1.0.0, name: 'libprint', description: 'my first release', id: 25376976, tagged: 09/04/2020 at 20:16, published: 09/04/2020 at 20:55, draft: ✗, prerelease: ✗

```

move tar.gz as an arthefact to release
and set OS version

```sh
$ export PACKAGE_OS=`uname -s` PACKAGE_ARCH=`uname -m` 
$ export PACKAGE_FILENAME=print-${PACKAGE_OS}-${PACKAGE_ARCH}.tar.gz
$ github-release upload \
    --user ${GITHUB_USERNAME} \
    --repo lab09 \
    --tag v0.1.0.0 \
    --name "${PACKAGE_FILENAME}" \
    --file _build/*.tar.gz
```

```sh
$ github-release info -u ${GITHUB_USERNAME} -r lab09

✗
  - artifact: print-Linux-x86_64.tar.gz, downloads: 0, state: uploaded, type: application/octet-stream, size: 6.4 kB, id: 19614269


$ wget https://github.com/${GITHUB_USERNAME}/lab09/releases/download/v0.1.0.0/${PACKAGE_FILENAME}
download path

$ tar -ztf ${PACKAGE_FILENAME}

print-0.1.0.0-Linux/bin/
print-0.1.0.0-Linux/bin/demo
print-0.1.0.0-Linux/include/
print-0.1.0.0-Linux/include/print.hpp
print-0.1.0.0-Linux/lib/
print-0.1.0.0-Linux/lib/libprint.a
print-0.1.0.0-Linux/cmake/
print-0.1.0.0-Linux/cmake/print-config-noconfig.cmake
print-0.1.0.0-Linux/cmake/print-config.cmake

```

## Report

```sh
$ popd
$ export LAB_NUMBER=09
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER} tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gistup -m "lab${LAB_NUMBER}"
```

## Links

- [Create Release](https://help.github.com/articles/creating-releases/)
- [Get GitHub Token](https://help.github.com/articles/creating-a-personal-access-token-for-the-command-line/)
- [Signing Commits](https://help.github.com/articles/signing-commits-with-gpg/)
- [Go Setup](http://www.golangbootcamp.com/book/get_setup)
- [github-release](https://github.com/aktau/github-release)

```
Copyright (c) 2015-2020 The ISC Authors
```
