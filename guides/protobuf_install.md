1. Download cpp version https://github.com/protocolbuffers/protobuf/releases/tag/v4.0.0-rc2
2. extract and go to the folder in terminal (WSL)
3. ```
    sudo apt-get install autoconf (se non ancora installato)
    ./autogen.sh
    ./configure
    make
    make check
    sudo make install
    sudo ldconfig
    ```
