Raspberry Pi's default login data:

```
user: pi
pass: raspberry
```

Make sure SSH is enabled:

```
$ raspi-config
=> Advanced settings
=> enable SSH
```

Install `sshfs` on your system and then mount the whole raspberry pi to a folder
called `rpi`

```
$ pacman -S sshfs
$ cd /tmp
$ mkdir rpi
$ sshfs pi@192.168.x.y:/ rpi
$ cd rpi/home/pi
$ mkdir documents
```

To unmount sshfs:
```
$ sudo umount -l /tmp/rpi
```

Create a local directory, where you will work on your computer:

```
$ cd ~/documents
$ mkdir MyProject
$ cd MyProject
```

Whenever you want to sync the folder use rsync:

```
$ rsync --progress --recursive --archive --delete . /tmp/rpi/documents/MyProject
```

or use the `sync_pi.sh`:
```
$ chmod +x sync_pi.sh
$ ./sync_pi.sh
```

Install dependencies:

Low-level GPIO access:

```
$ git clone git://git.drogon.net/wiringPi
$ cd wiringPi
$ ./build
```

Build system
```
$ sudo apt-get install scons
```
After the wiringPi has been successfully installed, you can list the pins:

```
$ gpio readall
```


ETC:

```
apt get install git tree clang
```
- - -

Install dependency `bcm2835`:

```
$ cd /tmp
$ wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.45.tar.gz
$ tar zxvf bcm2835-1.45.tar.gz
$ cd bcm2835
$ ./configure
$ make
$ sudo make check
$ sudo make install
```

Enable Device Tree:

```
$ sudo raspi-config
  |
  +--> 8 Advanced Options
  |    |
  |    '--> A5 Device Tree
  |         |
  |         +--> Yes
  |         |
  |         '--> Ok
  |
  '--> Finish
$ sudo reboot
```


