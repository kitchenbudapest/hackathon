Build and install `libkb` from source:
======================================

1. Add library path for the linker to look up:

    ```bash
    # Edit bashrc
    $ nano ~/.bashrc
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib/
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/

        Ctrl-X => Y => Enter

    # Reload bashrc
    $ source ~/.bashrc
    ```

2. Build and install:

    ```bash
    # Build library
    $ scons

    # Install library and headers
    $ sudo mv libs/libkb.so /usr/local/lib/
    $ sudo cp -R include/kb /usr/local/include/
    ```
