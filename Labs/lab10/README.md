## Laboratory work X


Данная лабораторная работа посвещена изучению процесса создания и конфигурирования виртуальной среды разработки с использованием **Vagrant**

```sh
$ open https://www.vagrantup.com/intro/index.html
```

## Tasks

- [x] 1. Ознакомиться со ссылками учебного материала
- [x] 2. Выполнить инструкцию учебного материала
- [x] 3. Составить отчет и отправить ссылку личным сообщением в **Slack**

## Tutorial

// export username & packet manager
```sh
$ export GITHUB_USERNAME=<имя_пользователя>
$ export PACKAGE_MANAGER=<пакетный_менеджер>
```


// install vagrant
```sh
$ cd ${GITHUB_USERNAME}/workspace
$ ${PACKAGE_MANAGER} install vagrant
```

Place vagrantfile into directory
```sh
$ vagrant version
Installed Version: 2.0.2

$ vagrant init hashicorp/bionic64
A `Vagrantfile` has been placed in this directory. You are now
ready to `vagrant up` your first virtual environment! Please read
the comments in the Vagrantfile as well as documentation on
`vagrantup.com` for more information on using Vagrant.

$ less Vagrantfile
$ vagrant init -f -m hashicorp/bionic64
A `Vagrantfile` has been placed in this directory. You are now
ready to `vagrant up` your first virtual environment! Please read
the comments in the Vagrantfile as well as documentation on
`vagrantup.com` for more information on using Vagrant.

```

```sh
$ mkdir shared
```

// use docker to be installed and change root rights
```sh
$ cat > Vagrantfile <<EOF
\$script = <<-SCRIPT
sudo apt install docker.io -y
sudo docker pull fastide/ubuntu:19.04
sudo docker create -ti --name fastide fastide/ubuntu:19.04 bash
sudo docker cp fastide:/home/developer /home/
sudo useradd developer
echo "developer:developer" | sudo chpasswd
sudo chown -R developer /home/developer
SCRIPT
EOF
```


// configure plugins (disk space etc)

```sh
$ cat >> Vagrantfile <<EOF

Vagrant.configure("2") do |config|

  config.vagrant.plugins = ["vagrant-vbguest", "vagrant-disksize"]
EOF
```


// configure disk size, use VB as a provider and configure it, ssh
```sh
$ cat >> Vagrantfile <<EOF

  config.vm.box = "bento/ubuntu-19.04"
  config.vm.network "public_network"
  config.disksize.size = "20GB"
  config.vm.synced_folder('shared', '/vagrant', type: 'rsync')

  config.vm.provider "virtualbox" do |vb|
    vb.gui = true
    vb.memory = "2048"
  end

  config.vm.provision "shell", inline: \$script, privileged: true

  config.ssh.extra_args = "-tt"

end
EOF
```
// up , ssh -> commands, su - developer
// tcp -> info
// url, port, username

```sh
$ vagrant validate

Vagrantfile validated successfully.


$ vagrant status

Current machine states:

default                   not created (virtualbox)

The environment has not yet been created. Run `vagrant up` to
create the environment. If a machine is not created, only the
default provider will be shown. So if a provider is not listed,
then the machine is not created for that environment.


$ vagrant up # --provider virtualbox
$ vagrant port // check tcp port
The forwarded ports for the machine are listed below. Please note that
these values may differ from values configured in the Vagrantfile if the
provider supports automatic port collision detection and resolution.

    22 (guest) => 2222 (host)

$ vagrant status
Current machine states:

default                   running (virtualbox)

The VM is running. To stop this VM, you can run `vagrant halt` to
shut it down forcefully, or you can run `vagrant suspend` to simply
suspend the virtual machine. In either case, to restart it again,
simply run `vagrant up`
$ vagrant ssh
Welcome to Ubuntu 19.10 (GNU/Linux 5.3.0-45-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

  System information as of Thu 16 Apr 2020 06:05:33 PM UTC

  System load:  0.09              Processes:           104
  Usage of /:   2.6% of 61.80GB   Users logged in:     0
  Memory usage: 7%                IP address for eth0: 10.0.2.15
  Swap usage:   0%                IP address for eth1: 192.168.1.92


0 updates can be installed immediately.
0 of these updates are security updates.


The list of available updates is more than a week old.
To check for new updates run: sudo apt update


This system is built by the Bento project by Chef Software

exit
logout
Connection to 127.0.0.1 closed.

// get list of snapshots
$ vagrant snapshot list
default: No snapshots have been taken yet!
    default: You can take a snapshot using `vagrant snapshot save`. Note that
    default: not all providers support this yet. Once a snapshot is taken, you
    default: can list them using this command, and use commands such as
    default: `vagrant snapshot restore` to go back to a certain snapshot.

// save snapshot
$ vagrant snapshot push
==> default: Snapshotting the machine as 'push_1587060412_2445'...
==> default: Snapshot saved! You can restore the snapshot at any time by
==> default: using `vagrant snapshot restore`. You can delete it using
==> default: `vagrant snapshot delete`.

$ vagrant snapshot list
==> default: 
push_1587060412_2445

$ vagrant halt // shutdown VM
==> default: Attempting graceful shutdown of VM...

$ vagrant snapshot pop // boot VM again
==> default: Checking if box 'bento/ubuntu-19.10' version '202003.31.0' is up to date...
==> default: Resuming suspended VM...
==> default: Booting VM...
==> default: Waiting for machine to boot. This may take a few minutes...
    default: SSH address: 127.0.0.1:2222
    default: SSH username: vagrant
    default: SSH auth method: private key
==> default: Machine booted and ready!
==> default: Machine already provisioned. Run `vagrant provision` or use the `--provision`
==> default: flag to force provisioning. Provisioners marked to run always will still run.

```


configure user info via esxi
```ruby
  config.vm.provider :vmware_esxi do |esxi|

    esxi.esxi_hostname = '<exsi_hostname>'
    esxi.esxi_username = 'root'
    esxi.esxi_password = 'prompt:'

    esxi.esxi_hostport = 22

    esxi.guest_name = '${GITHUB_USERNAME}'

    esxi.guest_username = 'vagrant'
    esxi.guest_memsize = '2048'
    esxi.guest_numvcpus = '2'
    esxi.guest_disk_type = 'thin'
  end
```

install vmware as plugin
```sh
$ vagrant plugin install vagrant-vmware-esxi
Installing the 'vagrant-vmware-esxi' plugin. This can take a few minutes...
Fetching: iniparse-1.5.0.gem (100%)
Fetching: mini_portile2-2.4.0.gem (100%)
Fetching: nokogiri-1.10.9.gem (100%)
Building native extensions.  This could take a while...
Fetching: vagrant-vmware-esxi-2.4.5.gem (100%)
Installed the plugin 'vagrant-vmware-esxi (2.4.5)'!

$ vagrant plugin list
vagrant-vmware-esxi (2.4.5, global)

$ vagrant up --provider=vmware_esxi
```

## Report

```sh
$ cd ~/workspace/
$ export LAB_NUMBER=10
$ git clone https://github.com/tp-labs/lab${LAB_NUMBER}.git tasks/lab${LAB_NUMBER}
$ mkdir reports/lab${LAB_NUMBER}
$ cp tasks/lab${LAB_NUMBER}/README.md reports/lab${LAB_NUMBER}/REPORT.md
$ cd reports/lab${LAB_NUMBER}
$ edit REPORT.md
$ gist REPORT.md
```

## Links

- [VirualBox](https://www.virtualbox.org/)
- [Vagrant providers](https://github.com/hashicorp/vagrant/wiki/Available-Vagrant-Plugins#providers)
- [Vagrant vbguest plugin](https://github.com/dotless-de/vagrant-vbguest)
- [Vagrant disksize plugin](https://github.com/sprotheroe/vagrant-disksize)
- [Vagrant vmware esxi plugin](https://github.com/josenk/vagrant-vmware-esxi)

```
Copyright (c) 2015-2020 The ISC Authors
```
