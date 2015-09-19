
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


- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

WIP: Random Stuffs
------------------

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

- - -

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
