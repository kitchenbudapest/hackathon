
> ***WARNING:*** Both the documentation and the framework itself is under heavy
> development and in a very early stage. That means, this repo is full of
> untested and unchecked drafts and notes and anything in it can change without
> further notice. Therefore it comes with absolutely no warranty at all: if it
> melts down your computer -- you cannot say we did not warn you :P Nonetheless,
> feel free to browse or even contribute to it, now that you know what you are
> dealing with ;)

![Kibu Hackathon](fw/artwork/box-lid.png?raw=true)

KIBU HACKATHON FRAMEWORK
========================

The purpose of this framework is to provide all the boilerplate you will need
to build what you want in no time during our hackathon. Not to mention, this
boilerplate is abstracted away from you at a super high level with its context-
based, event driven model.

Currenlty supported languages:

- C (and therefore C++ as well)
- Python
- JavaScript

From here on...

WIP: Random Stuffs
==================

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

***COMPILER EVERYTHING WITH `clang-3.5` ON THE RASPBIAN !!!***
***`sudo LD_LIBRARY_PATH=/usr/local/lib kbjs file.js`***


Prepare your Raspberry Pi 2
---------------------------

1. Install Raspbian:

    ```bash
    # Download disk image and unarchive it
    $ cd downloads
    $ wget https://downloads.raspberrypi.org/raspbian/images/
           raspbian-2015-05-07/2015-05-05-raspbian-wheezy.zip
    $ unzip 2015-05-05-raspbian-wheezy.img

    # Insert SD card
    $ lsblk

    # Copy image to card
    $ sudo dd bs=4M if=2015-05-05-raspbian-wheezy.img of=/dev/sdd

    # Flush cache and remove card
    $ sudo sync
    ```

2. Boot up for the first time:

    For the first time, the RPi2 will automatically start the `raspi-config`
    program for you. You should do the following:

    ```
    1 Expand Filesystem
    |
    8 Advanced Options
    |
    +-- A4 SSH
    |   |
    |   `-- Enable => Ok
    |
    +-- A5 Device Tree
    |   |
    |   `-- Yes => Ok
    |
    `-- Finish
        |
        `-- Reboot => Yes
    ```

3. Install packages:

    After the reboot login. Login data:

    ```
    user: pi
    pass: raspberry
    ```

    Install modern packages:

    ```bash
    # Update everything
    $ sudo apt-get update
    $ sudo apt-get upgrade

    # Get modern gcc, clang, python and scons
    $ sudo nano /etc/apt/sources/list
        wheezy => jessie
    $ sudo apt-get update
    $ sudo apt-get install gcc-4.9 clang-3.5 python3.4 scons
        -> Restart services => Yes

    # Switch back to wheezy
    $ sudo nano /etc/apt/sources/list
        jessie => wheezy
    $ sudo apt-get update
    ```

    Install framework core:

    ```bash
    # Edit bashrc
    $ cd

    # Append the following lines to end of the rc file
    $ nano .bashrc
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/

        Ctrl-X => Y => Enter

    # Reload bashrc
    $ source .bashrc

    # Install custom allocation manager library
    $ sudo apt-get install libjemalloc-dev libjemalloc1

    # Create folder for projects
    $ mkdir devel
    $ cd devel

    # Get framework
    $ git clone https://github.com/kitchenbudapest/hackathon.git
    $ cd hackathon

    # Install framework core
    $ cd fw/kb

    # Build library
    $ scons

    # Install headers and library
    $ sudo cp -R include/kb /usr/local/include/
    $ sudo mv libs/libkb.so /usr/local/lib/
    ```

    Install framework wrappers:

    ```bash
    $ cd ../wrappers/javascript
    $ wget http://duktape.org/duktape-1.3.0.tar.xz

    # Extract archive:
    $ tar xf duktape-1.3.0.tar.xz

    # Build library
    $ scons duktape

    # Install headers and the library:
    $ sudo cp duktape-1.3.0/src/duktape.h /usr/local/include
    $ sudo cp duktape-1.3.0/src/duk_config.h /usr/local/include
    $ sudo mv libduktape.so /usr/local/lib/

    # Build application:
    $ scons kbjs

    # Install app:
    $ sudo mv kbjs /usr/local/bin/

    # Run tests:
    $ kbjs check.js
    ```

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Start developing on the Raspberry Pi 2
--------------------------------------

Install `sshfs` on your system and then mount the whole raspberry pi to a folder
called `rpi`

```bash
$ pacman -S sshfs
$ cd /tmp
$ mkdir rpi
$ sshfs pi@192.168.x.y:/ rpi
$ cd rpi/home/pi
$ mkdir documents
```

To unmount sshfs:
```bash
$ sudo umount -l /tmp/rpi
```

Create a local directory, where you will work on your computer:

```bash
$ cd ~/documents
$ mkdir MyProject
$ cd MyProject
```

Whenever you want to sync the folder use rsync:

```bash
$ rsync --progress --recursive --archive --delete . /tmp/rpi/documents/MyProject
```

or use the `sync_pi.sh`:

```bash
$ chmod +x sync_pi.sh
$ ./sync_pi.sh <source> <destination> [<interval (sec)>]
```

Install dependencies:

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
$ cd bcm2835-1.45
$ ./configure
$ make
$ sudo make check
$ sudo make install
```

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

Developer Notes
===============

Naming Conventions:
-------------------

- `kb_*`: package prefix = **K**itchen **B**udapest
- `kb_x_y_*`: from y module from x module
- `kb_x_y_AlphaBeta`: type
- `kb_x_y_AlphaBeta_m`: method or property
- `kb_x_y_ALPHA_BETA`: constant
- `KB_X_Y_ALPHA_BETA`: macro


API functions and methods:
--------------------------

```
Function:
    <error> function ( <inputs>..., <outputs>... )
Method:
    <error> method ( <instance>, <inputs>..., <outputs>... )
```

- Error is `kb_Error` in this package;
- Inputs can be pointers or values. If pointers they are almost always `const`s,
  indicating they are read-only values;
- Outputs are always pointers.

Inheritance by compositing:
---------------------------

Almost all types in this framework offers a "members" macro, in case of
compositing a *parent-struct-like* object. These *inheritable* objects also
offers a `new`, `ini` *(initialization)*, `fin` *(finalization)* and `del`
methods. The first and the last one are used for constructing and destructing
the *raw* types, while the `ini` and `fin` methods should be used to set up or
destroy the inherited types.

***Example:***

```C

/*----- Type offered by the framework ----------------------------------------*/
#define T_MEMBERS() \
    int id;         \
    int value;

typedef struct
{
    T_MEMBERS()
} T;

Error
T_ini(T *const self)
{
    if (!self)
        return SELF_IS_NULL;

    self->id    = 0;
    self->value = -1;

    return OKAY;
}

Error
T_new(T **const self)
{
    T *t;
    if (!(t = malloc(sizeof(T))))
        return ALLOC_FAIL;

    T_ini(t);

    *self = t;
    return OKAY;
}


/*----- User wrapped type ----------------------------------------------------*/
typedef struct
{
    T_MEMBERS()
    char name[32];
} MyT;

Error
MyT_new(MyT **const self)
{
    if (!self)
        return SELF_IS_NULL;

    *self = NULL;

    MyT *t;
    if (!(t = malloc(sizeof(MyT))))
        return ALLOC_FAIL;

    Error e;
    if ((e = T_ini((T *const)t)))
        return e;

    strncpy(t->name, "<MyT>", (size_t)32);

    *self = MyT;
    return OKAY;
}
```

Warnings:
---------

- Do not call in any circumstances `kb_rpi2_Context_fin` or
  `kb_rpi2_Context_del` methods inside a callback/the event loop, because that
  will crash your application in a mysterious way.

- Do not call `kb_rpi2_Pin_fin` or `kb_rpi2_Pin_del` methods when you are
  implementing a new `kb_rpi2_Sensor` type, because non of the `kb_rpi2_Pin`
  objects were created by you, and they will be *deleted* by the system at the
  correct time.

- Do not put `;` after the inherit-members-macros
