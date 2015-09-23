Build `duktape` and `kbjs` from source:
=======================================

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

2. Build and install shared library of `duktape`:

    ```bash
    # Download release:
    $ wget http://duktape.org/duktape-1.3.0.tar.xz

    # Extract archive:
    $ tar xf duktape-1.3.0.tar.xz

    # Build library
    $ scons duktape

    # Install headers and the library:
    $ sudo cp duktape-1.3.0/src/duktape.h /usr/local/include
    $ sudo cp duktape-1.3.0/src/duk_config.h /usr/local/include
    $ sudo mv libduktape.so /usr/local/lib/
    ```

3. Build and install javascript interpreter `kbjs`:

    ```bash
    # Build application:
    $ scons kbjs

    # Install app:
    $ sudo mv kbjs /usr/local/bin/

    # Run tests:
    $ kbjs check.js
    ```
