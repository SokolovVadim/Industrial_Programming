## Laboratory work XI

![ngrock](https://github.com/SokolovVadim/lab11/blob/master/ngrok.png)

Данная лабораторная работа посвещена изучению процесса создания сеансов совместной разработки с использованием инструмента **ngrok**

```sh
$ open https://ngrok.com/
```

## Tasks

- [x] 1. Ознакомиться со ссылками учебного материала
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

vagrant ssh -> su - developer

// prepare for dependencies installation
```sh
$ cd ~
$ mkdir install
$ mkdir tmp
$ export HOME_PREFIX=`pwd`/install
$ echo $HOME_PREFIX
/home/vagrant/install

$ export USERNAME=`whoami`
```
// install everything from here
```sh
$ cd tmp
```


// download libevent and configure
```sh
$ wget https://github.com/libevent/libevent/releases/download/release-2.1.8-stable/libevent-2.1.8-stable.tar.gz

--2020-04-16 19:36:56--  https://github.com/libevent/libevent/releases/download/release-2.1.8-stable/libevent-2.1.8-stable.tar.gz
Resolving github.com (github.com)... 140.82.118.3
Connecting to github.com (github.com)|140.82.118.3|:443... connected.
HTTP request sent, awaiting response... 302 Found
Location: https://github-production-release-asset-2e65be.s3.amazonaws.com/1856976/f9ea6922-e66b-11e6-9f5c-722c00daa657?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20200416%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20200416T193500Z&X-Amz-Expires=300&X-Amz-Signature=ace48a975b81d61979a29a4120a4f6927b43408fdeae1d67e53c435b6f4b16de&X-Amz-SignedHeaders=host&actor_id=0&repo_id=1856976&response-content-disposition=attachment%3B%20filename%3Dlibevent-2.1.8-stable.tar.gz&response-content-type=application%2Foctet-stream [following]
--2020-04-16 19:36:56--  https://github-production-release-asset-2e65be.s3.amazonaws.com/1856976/f9ea6922-e66b-11e6-9f5c-722c00daa657?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20200416%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20200416T193500Z&X-Amz-Expires=300&X-Amz-Signature=ace48a975b81d61979a29a4120a4f6927b43408fdeae1d67e53c435b6f4b16de&X-Amz-SignedHeaders=host&actor_id=0&repo_id=1856976&response-content-disposition=attachment%3B%20filename%3Dlibevent-2.1.8-stable.tar.gz&response-content-type=application%2Foctet-stream
Resolving github-production-release-asset-2e65be.s3.amazonaws.com (github-production-release-asset-2e65be.s3.amazonaws.com)... 52.216.30.92
Connecting to github-production-release-asset-2e65be.s3.amazonaws.com (github-production-release-asset-2e65be.s3.amazonaws.com)|52.216.30.92|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 1026485 (1002K) [application/octet-stream]
Saving to: ‘libevent-2.1.8-stable.tar.gz’

libevent-2.1.8-stable 100%[========================>]   1002K   183KB/s    in 5.5s    

2020-04-16 19:37:03 (183 KB/s) - ‘libevent-2.1.8-stable.tar.gz’ saved [1026485/1026485]

$ tar -xvzf libevent-2.1.8-stable.tar.gz

libevent-2.1.8-stable/ChangeLog
libevent-2.1.8-stable/evthread.c
libevent-2.1.8-stable/win32select.c
libevent-2.1.8-stable/config.guess
libevent-2.1.8-stable/arc4random.c
libevent-2.1.8-stable/evthread-internal.h
libevent-2.1.8-stable/bufferevent_openssl.c
libevent-2.1.8-stable/kqueue.c
libevent-2.1.8-stable/event_iocp.c
libevent-2.1.8-stable/Doxyfile
libevent-2.1.8-stable/defer-internal.h
libevent-2.1.8-stable/epoll.c
libevent-2.1.8-stable/strlcpy-internal.h
libevent-2.1.8-stable/event.c
libevent-2.1.8-stable/Makefile.in
libevent-2.1.8-stable/evport.c
libevent-2.1.8-stable/strlcpy.c
libevent-2.1.8-stable/evdns.c
libevent-2.1.8-stable/evrpc.c
libevent-2.1.8-stable/event-internal.h
libevent-2.1.8-stable/openssl-compat.h
libevent-2.1.8-stable/compat/
libevent-2.1.8-stable/compat/sys/
libevent-2.1.8-stable/compat/sys/queue.h
libevent-2.1.8-stable/libevent_pthreads.pc.in


$ cd libevent-2.1.8-stable

ChangeLog               devpoll.c              ipv6-internal.h
ChangeLog-1.4           epoll.c                kqueue-internal.h
ChangeLog-2.0           epoll_sub.c            kqueue.c
Doxyfile                epolltable-internal.h  libevent.pc.in
LICENSE                 evbuffer-internal.h    libevent_core.pc.in
Makefile.am             evconfig-private.h     libevent_extra.pc.in
Makefile.in             evconfig-private.h.in  libevent_openssl.pc.in
Makefile.nmake          evdns.c                libevent_pthreads.pc.in
WIN32-Code              event-internal.h       listener.c
aclocal.m4              event.c                log-internal.h
arc4random.c            event_iocp.c           log.c
autogen.sh              event_rpcgen.py        ltmain.sh
buffer.c                event_tagging.c        m4
buffer_iocp.c           evmap-internal.h       make-event-config.sed
bufferevent-internal.h  evmap.c                minheap-internal.h
bufferevent.c           evport.c               missing
bufferevent_async.c     evrpc-internal.h       mm-internal.h
bufferevent_filter.c    evrpc.c                openssl-compat.h
bufferevent_openssl.c   evsignal-internal.h    poll.c
bufferevent_pair.c      evthread-internal.h    ratelim-internal.h
bufferevent_ratelim.c   evthread.c             sample
bufferevent_sock.c      evthread_pthread.c     select.c
changelist-internal.h   evthread_win32.c       signal.c
compat                  evutil.c               strlcpy-internal.h
compile                 evutil_rand.c          strlcpy.c
config.guess            evutil_time.c          test
config.h.in             ht-internal.h          test-driver
config.sub              http-internal.h        time-internal.h
configure               http.c                 util-internal.h
configure.ac            include                whatsnew-2.0.txt
defer-internal.h        install-sh             whatsnew-2.1.txt
depcomp                 iocp-internal.h        win32select.c


$ ./configure --prefix=${HOME_PREFIX}

checking for a BSD-compatible install... /usr/bin/install -c
checking whether build environment is sane... yes
checking for a thread-safe mkdir -p... /usr/bin/mkdir -p
checking for gawk... gawk
checking whether make sets $(MAKE)... yes
checking whether make supports nested variables... yes
checking whether make supports nested variables... (cached) yes
checking for style of include used by make... GNU
checking for gcc... no
checking for cc... no
checking for cl.exe... no
configure: error: in `/home/vagrant/tmp/libevent-2.1.8-stable':
configure: error: no acceptable C compiler found in $PATH
See `config.log' for more details

//   gcc hasn't been insatalled yet -> install gcc
Setting up libasan5:amd64 (9.2.1-9ubuntu2) ...
Setting up libquadmath0:amd64 (9.2.1-9ubuntu2) ...
Setting up libatomic1:amd64 (9.2.1-9ubuntu2) ...
Setting up libubsan1:amd64 (9.2.1-9ubuntu2) ...
Setting up libcc1-0:amd64 (9.2.1-9ubuntu2) ...
Setting up liblsan0:amd64 (9.2.1-9ubuntu2) ...
Setting up libitm1:amd64 (9.2.1-9ubuntu2) ...
Setting up libtsan0:amd64 (9.2.1-9ubuntu2) ...
Setting up libgcc-9-dev:amd64 (9.2.1-9ubuntu2) ...
Setting up gcc-9 (9.2.1-9ubuntu2) ...
Setting up gcc (4:9.2.1-3.1ubuntu1) ...
Processing triggers for man-db (2.8.7-3) ...
Processing triggers for libc-bin (2.30-0ubuntu2.1) ...

//// trying to configure again
./configure --prefix=${HOME_PREFIX}

checking whether pthreads work with -pthread... yes
checking for joinable pthread attribute... PTHREAD_CREATE_JOINABLE
checking if more special flags are required for pthreads... no
checking size of pthread_t... 8
checking for library containing ERR_remove_thread_state... -lcrypto
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating libevent.pc
config.status: creating libevent_openssl.pc
config.status: creating libevent_pthreads.pc
config.status: creating libevent_core.pc
config.status: creating libevent_extra.pc
config.status: creating Makefile
config.status: creating config.h
config.status: creating evconfig-private.h
config.status: evconfig-private.h is unchanged
config.status: executing depfiles commands
config.status: executing libtool commands


$ make && make install
Libraries have been installed in:
   /home/vagrant/install/lib

If you ever happen to want to link against installed libraries
in a given directory, LIBDIR, you must either use libtool, and
specify the full pathname of the library, or use the '-LLIBDIR'
flag during linking and do at least one of the following:
   - add LIBDIR to the 'LD_LIBRARY_PATH' environment variable
     during execution
   - add LIBDIR to the 'LD_RUN_PATH' environment variable
     during linking
   - use the '-Wl,-rpath -Wl,LIBDIR' linker flag
   - have your system administrator add LIBDIR to '/etc/ld.so.conf'

See any operating system documentation about shared libraries for
more information, such as the ld(1) and ld.so(8) manual pages.
----------------------------------------------------------------------
 /usr/bin/mkdir -p '/home/vagrant/install/include'
 /usr/bin/install -c -m 644 include/evdns.h include/event.h include/evhttp.h include/evrpc.h include/evutil.h '/home/vagrant/install/include'
 /usr/bin/mkdir -p '/home/vagrant/install/include/event2'
 /usr/bin/install -c -m 644 include/event2/buffer.h include/event2/buffer_compat.h include/event2/bufferevent.h include/event2/bufferevent_compat.h include/event2/bufferevent_ssl.h include/event2/bufferevent_struct.h include/event2/dns.h include/event2/dns_compat.h include/event2/dns_struct.h include/event2/event.h include/event2/event_compat.h include/event2/event_struct.h include/event2/http.h include/event2/http_compat.h include/event2/http_struct.h include/event2/keyvalq_struct.h include/event2/listener.h include/event2/rpc.h include/event2/rpc_compat.h include/event2/rpc_struct.h include/event2/tag.h include/event2/tag_compat.h include/event2/thread.h include/event2/util.h include/event2/visibility.h '/home/vagrant/install/include/event2'
 /usr/bin/mkdir -p '/home/vagrant/install/include/event2'
 /usr/bin/install -c -m 644 include/event2/event-config.h '/home/vagrant/install/include/event2'
 /usr/bin/mkdir -p '/home/vagrant/install/lib/pkgconfig'
 /usr/bin/install -c -m 644 libevent.pc libevent_core.pc libevent_extra.pc libevent_pthreads.pc libevent_openssl.pc '/home/vagrant/install/lib/pkgconfig'
make[2]: Leaving directory '/home/vagrant/tmp/libevent-2.1.8-stable'
make[1]: Leaving directory '/home/vagrant/tmp/libevent-2.1.8-stable'


$ cd ..
```

// download ncurses and configure
```sh
$ wget http://invisible-island.net/datafiles/release/ncurses.tar.gz

--2020-04-16 19:44:39--  http://invisible-island.net/datafiles/release/ncurses.tar.gz
Resolving invisible-island.net (invisible-island.net)... 192.124.249.12
Connecting to invisible-island.net (invisible-island.net)|192.124.249.12|:80... connected.
HTTP request sent, awaiting response... 301 Moved Permanently
Location: https://invisible-island.net/datafiles/release/ncurses.tar.gz [following]
--2020-04-16 19:44:40--  https://invisible-island.net/datafiles/release/ncurses.tar.gz
Connecting to invisible-island.net (invisible-island.net)|192.124.249.12|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 3425862 (3.3M) [application/x-gzip]
Saving to: ‘ncurses.tar.gz’

ncurses.tar.gz                              100%[===========================================================================================>]   3.27M   266KB/s    in 9.4s    

2020-04-16 19:44:49 (355 KB/s) - ‘ncurses.tar.gz’ saved [3425862/3425862]


$ tar -xvzf ncurses.tar.gz

ncurses-6.2/Ada95/samples/ncurses2-test_sgr_attributes.ads
ncurses-6.2/Ada95/samples/sample-header_handler.adb
ncurses-6.2/Ada95/samples/sample-form_demo-handler.adb
ncurses-6.2/Ada95/samples/rain.ads
ncurses-6.2/Ada95/samples/sample-curses_demo-mouse.ads
ncurses-6.2/Ada95/samples/ncurses2-slk_test.ads
ncurses-6.2/Ada95/samples/status.adb
ncurses-6.2/Ada95/samples/sample-form_demo.adb
ncurses-6.2/Ada95/samples/ncurses2-flushinp_test.adb
ncurses-6.2/Ada95/samples/sample-curses_demo-attributes.ads
ncurses-6.2/Ada95/samples/README
ncurses-6.2/Ada95/samples/sample-form_demo-handler.ads
ncurses-6.2/Ada95/samples/ncurses2-demo_forms.adb
ncurses-6.2/Ada95/samples/ncurses2-getch_test.adb
ncurses-6.2/Ada95/samples/sample-my_field_type.ads
ncurses-6.2/Ada95/samples/sample-menu_demo-handler.adb
ncurses-6.2/Ada95/samples/sample-menu_demo.adb
ncurses-6.2/Ada95/samples/ncurses2-m.adb
ncurses-6.2/Ada95/samples/sample-my_field_type.adb
ncurses-6.2/Ada95/samples/ncurses2-trace_set.adb
ncurses-6.2/Ada95/samples/tour.adb


$ cd ncurses-5.9

ANNOUNCE  COPYING   Makefile.in   README        TO-DO       announce.html.in  config.sub    convert_configure.pl  form        man   mk-0th.awk  mk-hdr.awk  panel
AUTHORS   INSTALL   Makefile.os2  README.MinGW  VERSION     c++               configure     dist.mk               include     menu  mk-1st.awk  ncurses     progs
Ada95     MANIFEST  NEWS          README.emx    aclocal.m4  config.guess      configure.in  doc                   install-sh  misc  mk-2nd.awk  package     test


$ ./configure --prefix=${HOME_PREFIX}

Appending rules for normal model (ncurses: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for debug model (ncurses: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for normal model (progs: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for debug model (progs: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for normal model (panel: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for debug model (panel: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for normal model (menu: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for debug model (menu: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for normal model (form: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for debug model (form: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for normal model (test: ticlib+termlib+ext_tinfo+base+ext_funcs)
Appending rules for debug model (test: ticlib+termlib+ext_tinfo+base+ext_funcs)
creating headers.sh

** Configuration summary for NCURSES 6.2 20200212:

       extended funcs: yes
       xterm terminfo: xterm-new

        bin directory: /home/vagrant/install/bin
        lib directory: /home/vagrant/install/lib
    include directory: /home/vagrant/install/include/ncurses
        man directory: /home/vagrant/install/share/man
   terminfo directory: /home/vagrant/install/share/terminfo


$ make && make install


"terminfo.tmp", line 1115, col 36, terminal 'fbterm': limiting value of `pairs' from 0x10000 to 0x7fff
"terminfo.tmp", line 4800, col 36, terminal 'xterm+256color': limiting value of `pairs' from 0x10000 to 0x7fff
"terminfo.tmp", line 4819, col 36, terminal 'xterm+256setaf': limiting value of `pairs' from 0x10000 to 0x7fff
"terminfo.tmp", line 4863, col 25, terminal 'xterm+direct2': limiting value of `colors' from 0x1000000 to 0x7fff
"terminfo.tmp", line 4863, col 40, terminal 'xterm+direct2': limiting value of `pairs' from 0x10000 to 0x7fff
"terminfo.tmp", line 4878, col 25, terminal 'xterm+direct': limiting value of `colors' from 0x1000000 to 0x7fff
"terminfo.tmp", line 4878, col 40, terminal 'xterm+direct': limiting value of `pairs' from 0x10000 to 0x7fff
"terminfo.tmp", line 4900, col 25, terminal 'xterm+indirect': limiting value of `colors' from 0x1000000 to 0x7fff
"terminfo.tmp", line 4900, col 40, terminal 'xterm+indirect': limiting value of `pairs' from 0x10000 to 0x7fff
"terminfo.tmp", line 7641, col 36, terminal 'dvtm-256color': limiting value of `pairs' from 0x10000 to 0x7fff
1750 entries written to /home/vagrant/install/share/terminfo
** built new /home/vagrant/install/share/terminfo
** sym-linked /home/vagrant/install/lib/terminfo for compatibility
installing std
installing stdcrt
installing vt100
installing vt300
finished install.data
/usr/bin/install -c ncurses-config /home/vagrant/install/bin/ncurses6-config
make[1]: Leaving directory '/home/vagrant/tmp/ncurses-6.2/misc'


$ cd ..
```


// download TMUX and configure with adding flags to compiler

```sh
$ wget https://github.com/tmux/tmux/releases/download/2.5/tmux-2.5.tar.gz

Resolving github.com (github.com)... 140.82.118.3
Connecting to github.com (github.com)|140.82.118.3|:443... connected.
HTTP request sent, awaiting response... 302 Found
Location: https://github-production-release-asset-2e65be.s3.amazonaws.com/36836475/2c975d56-4447-11e7-9b0d-546f71b509fc?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20200416%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20200416T194832Z&X-Amz-Expires=300&X-Amz-Signature=bea5f1a3d5254ea4e785582af2f79be5be7c2f12a9a3cac4bac98fc402f646e2&X-Amz-SignedHeaders=host&actor_id=0&repo_id=36836475&response-content-disposition=attachment%3B%20filename%3Dtmux-2.5.tar.gz&response-content-type=application%2Foctet-stream [following]
--2020-04-16 19:48:32--  https://github-production-release-asset-2e65be.s3.amazonaws.com/36836475/2c975d56-4447-11e7-9b0d-546f71b509fc?X-Amz-Algorithm=AWS4-HMAC-SHA256&X-Amz-Credential=AKIAIWNJYAX4CSVEH53A%2F20200416%2Fus-east-1%2Fs3%2Faws4_request&X-Amz-Date=20200416T194832Z&X-Amz-Expires=300&X-Amz-Signature=bea5f1a3d5254ea4e785582af2f79be5be7c2f12a9a3cac4bac98fc402f646e2&X-Amz-SignedHeaders=host&actor_id=0&repo_id=36836475&response-content-disposition=attachment%3B%20filename%3Dtmux-2.5.tar.gz&response-content-type=application%2Foctet-stream
Resolving github-production-release-asset-2e65be.s3.amazonaws.com (github-production-release-asset-2e65be.s3.amazonaws.com)... 52.216.110.43
Connecting to github-production-release-asset-2e65be.s3.amazonaws.com (github-production-release-asset-2e65be.s3.amazonaws.com)|52.216.110.43|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 475717 (465K) [application/octet-stream]
Saving to: ‘tmux-2.5.tar.gz’

tmux-2.5.tar.gz                             100%[===========================================================================================>] 464.57K   651KB/s    in 0.7s    

2020-04-16 19:48:33 (651 KB/s) - ‘tmux-2.5.tar.gz’ saved [475717/475717]



$ tar -xvzf tmux-2.5.tar.gz

tmux-2.5/example_tmux.conf
tmux-2.5/osdep-aix.c
tmux-2.5/osdep-cygwin.c
tmux-2.5/osdep-darwin.c
tmux-2.5/osdep-dragonfly.c
tmux-2.5/osdep-freebsd.c
tmux-2.5/osdep-hpux.c
tmux-2.5/osdep-linux.c
tmux-2.5/osdep-netbsd.c
tmux-2.5/osdep-openbsd.c
tmux-2.5/osdep-sunos.c
tmux-2.5/osdep-unknown.c
tmux-2.5/mdoc2man.awk
tmux-2.5/tmux.1


$ cd tmux-2.5

CHANGES               cmd-choose-tree.c      cmd-list-sessions.c   cmd-save-buffer.c       cmd-wait-for.c     key-bindings.c     osdep-openbsd.c  tty-acs.c
COPYING               cmd-command-prompt.c   cmd-list-windows.c    cmd-select-layout.c     cmd.c              key-string.c       osdep-sunos.c    tty-keys.c
FAQ                   cmd-confirm-before.c   cmd-list.c            cmd-select-pane.c       colour.c           layout-custom.c    osdep-unknown.c  tty-term.c
Makefile.am           cmd-copy-mode.c        cmd-load-buffer.c     cmd-select-window.c     compat             layout-set.c       paste.c          tty.c
Makefile.in           cmd-detach-client.c    cmd-lock-server.c     cmd-send-keys.c         compat.h           layout.c           proc.c           utf8.c
README                cmd-display-message.c  cmd-move-window.c     cmd-set-buffer.c        configure          log.c              resize.c         window-choose.c
TODO                  cmd-display-panes.c    cmd-new-session.c     cmd-set-environment.c   configure.ac       mdoc2man.awk       screen-redraw.c  window-clock.c
aclocal.m4            cmd-find-window.c      cmd-new-window.c      cmd-set-hook.c          control-notify.c   names.c            screen-write.c   window-copy.c
alerts.c              cmd-find.c             cmd-paste-buffer.c    cmd-set-option.c        control.c          notify.c           screen.c         window.c
arguments.c           cmd-if-shell.c         cmd-pipe-pane.c       cmd-show-environment.c  environ.c          options-table.c    server-client.c  xmalloc.c
attributes.c          cmd-join-pane.c        cmd-queue.c           cmd-show-messages.c     etc                options.c          server-fn.c      xmalloc.h
cfg.c                 cmd-kill-pane.c        cmd-refresh-client.c  cmd-show-options.c      example_tmux.conf  osdep-aix.c        server.c         xterm-keys.c
client.c              cmd-kill-server.c      cmd-rename-session.c  cmd-source-file.c       format.c           osdep-cygwin.c     session.c
cmd-attach-session.c  cmd-kill-session.c     cmd-rename-window.c   cmd-split-window.c      grid-view.c        osdep-darwin.c     signal.c
cmd-bind-key.c        cmd-kill-window.c      cmd-resize-pane.c     cmd-string.c            grid.c             osdep-dragonfly.c  status.c
cmd-break-pane.c      cmd-list-buffers.c     cmd-respawn-pane.c    cmd-swap-pane.c         hooks.c            osdep-freebsd.c    style.c
cmd-capture-pane.c    cmd-list-clients.c     cmd-respawn-window.c  cmd-swap-window.c       input-keys.c       osdep-hpux.c       tmux.1
cmd-choose-buffer.c   cmd-list-keys.c        cmd-rotate-window.c   cmd-switch-client.c     input.c            osdep-linux.c      tmux.c
cmd-choose-client.c   cmd-list-panes.c       cmd-run-shell.c       cmd-unbind-key.c        job.c              osdep-netbsd.c     tmux.h


$ ./configure --prefix=${HOME_PREFIX} CFLAGS="-I${HOME_PREFIX}/include -I${HOME_PREFIX}/include/ncurses" LDFLAGS="-L${HOME_PREFIX}/lib"

checking if getopt is suitable... no
checking for library containing fdforkpty... no
checking for library containing forkpty... -lutil
checking whether TAILQ_CONCAT is declared... yes
checking whether TAILQ_PREV is declared... yes
checking whether TAILQ_REPLACE is declared... no
checking for __progname... yes
checking for program_invocation_short_name... yes
checking whether PR_SET_NAME is declared... yes
checking whether F_CLOSEM is declared... no
checking for /proc/$$... yes
checking platform... linux
checking that generated files are newer than configure... done
configure: creating ./config.status
config.status: creating Makefile
config.status: executing depfiles commands


$ make && make install

 /usr/bin/mkdir -p '/home/vagrant/install/bin'
  /usr/bin/install -c tmux '/home/vagrant/install/bin'
make  install-exec-hook
make[2]: Entering directory '/home/vagrant/tmp/tmux-2.5'
if test xmdoc = xmdoc; then \
	sed -e "s|@SYSCONFDIR@|/etc|g" ./tmux.1 \
		>./tmux.1.mdoc; \
else \
	sed -e "s|@SYSCONFDIR@|/etc|g" ./tmux.1| \
		gawk -f./mdoc2man.awk >./tmux.1.man; \
fi
/usr/bin/mkdir -p /home/vagrant/install/share/man/man1
/usr/bin/install -c -m 644 ./tmux.1.mdoc \
	/home/vagrant/install/share/man/man1/tmux.1
make[2]: Leaving directory '/home/vagrant/tmp/tmux-2.5'
make[1]: Nothing to be done for 'install-data-am'.
make[1]: Leaving directory '/home/vagrant/tmp/tmux-2.5'


$ cd ..
```

// download NGROK
```sh
$ wget https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-amd64.zip

--2020-04-16 19:50:49--  https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-amd64.zip
Resolving bin.equinox.io (bin.equinox.io)... 52.3.53.111, 34.201.247.239, 34.202.138.174, ...
Connecting to bin.equinox.io (bin.equinox.io)|52.3.53.111|:443... connected.
HTTP request sent, awaiting response... 200 OK
Length: 13773305 (13M) [application/octet-stream]
Saving to: ‘ngrok-stable-linux-amd64.zip’

ngrok-stable-linux-amd64.zip                100%[===========================================================================================>]  13.13M  73.6KB/s    in 3m 41s  

2020-04-16 19:54:34 (60.8 KB/s) - ‘ngrok-stable-linux-amd64.zip’ saved [13773305/13773305]


$ unzip ngrok-stable-linux-amd64.zip

// install unzip previously
sudo apt-get install -y unzip
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Suggested packages:
  zip
The following NEW packages will be installed:
  unzip
0 upgraded, 1 newly installed, 0 to remove and 0 not upgraded.
Need to get 169 kB of archives.
After this operation, 593 kB of additional disk space will be used.
Get:1 http://archive.ubuntu.com/ubuntu eoan/main amd64 unzip amd64 6.0-25ubuntu1 [169 kB]
Fetched 169 kB in 1s (185 kB/s)
Selecting previously unselected package unzip.
(Reading database ... 43597 files and directories currently installed.)
Preparing to unpack .../unzip_6.0-25ubuntu1_amd64.deb ...
Unpacking unzip (6.0-25ubuntu1) ...
Setting up unzip (6.0-25ubuntu1) ...
Use of uninitialized value $ARGV[0] in string ne at /usr/sbin/update-mime line 43.
Processing triggers for mime-support (3.63ubuntu1) ...
Processing triggers for man-db (2.8.7-3) ...


  inflating: ngrok        

$ mv ngrok ${HOME_PREFIX}/bin
```

// export paths to use NGROK
```sh
$ export LD_LIBRARY_PATH=${HOME_PREFIX}/lib
$ export PATH="${HOME_PREFIX}/bin:${PATH}"
$ tmux

vagrant@vagrant:~/tmp$ ls
libevent-2.1.8-stable  ncurses-6.2  tmux-2.5
vagrant@vagrant:~/tmp$ 



```

```sh
$ cd ~
$ rm -rf tmp install
```


// easy way to install ngrok
```sh
$ brew install tmux ngrok # or use linuxbrew 🎉
```

```sh
$ tmux new -s session_with_group
```

```sh
# Alisa:
$ open https://ngrok.com/signup
$ export NGROK_TOKEN=<токен>
$ ngrok authtoken ${NGROK_TOKEN}
Authtoken saved to configuration file: /home/vagrant/.ngrok2/ngrok.yml

$ ngrok tcp 22
Session Status                online                                                                                                                                            
Account                       Vadim Sokolov (Plan: Free)                                                                                                                        
Version                       2.3.35                                                                                                                                            
Region                        United States (us)                                                                                                                                
Web Interface                 http://127.0.0.1:4040                                                                                                                             
Forwarding                    tcp://0.tcp.ngrok.io:18708 -> localhost:22                                                                                                        
                                                                                                                                                                                
Connections                   ttl     opn     rt1     rt5     p50     p90                                                                                                       
                              0       0       0.00    0.00    0.00    0.00   


<порт_ngrok_сервера>

127.0.0.1:4040  
```

```sh
# Bob:
$ ssh ${USERNAME}@0.tcp.ngrok.io -p<порт_ngrok_сервера>
<пароль_от_учетной_записи>
$ tmux a -t session_with_group
$ <C-B>"
```

## Report

```sh
$ cd ~/workspace/
$ export LAB_NUMBER=11
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER}.git tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Links

- [Tmux](https://raw.githubusercontent.com/tmux/tmux/master/README)
- [Libevent](http://libevent.org)
- [Ncurses](http://invisible-island.net/ncurses/)

```
Copyright (c) 2015-2020 The ISC Authors
```
