# CPP_ITCH_PARSER

CPP Itch Parser is a NASDAQ ITCH 5.0 Parser written in C++.

## Building

### Prerequisites

* libuv 1.0 or later
* Boost libraries

**macOS**:

```
brew install boost cmake libuv pkg-config
```

### Building and Installing

To build Helix:

```
cmake .
make
```

To build a debug version of Helix that enables AddressSanitizer:

```
mkdir -p build/debug
cd build/debug
cmake -DCMAKE_BUILD_TYPE=debug ../..
```

To install CPP_ITCH_PARSER:

```
make install
```

Please note that itch_parser generates a ``pkg-config`` file so you can use ``pkg-config`` to integrate Helix with your project build system. If you installed Helix in the default location `/usr/local/`, you need to set the `PKG_CONFIG_PATH` environment variable as follows:

```
export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig/
```

## Usage

To convert a NASDAQ TotalView-ITCH 5.0 file to CSV:

```
./itch_parser -i 07302015.NASDAQ_ITCH50 -s AAPL -c nasdaq-binaryfile-itch50 -f csv -o AAPL.csv
```

Please note that itch_parser only works with uncompressed files.

## Features

### Core

* [x] C++ API
* [x] C binding
* [x] Order book view
* [x] Data normalization
* [x] Data filtering
* [x] Retransmission requests
* [ ] Order book aggregation
* [ ] Synthetic NBBO

### Protocols

* NASDAQ
  * [x] NASDAQ TotalView-ITCH 5.0
  * [x] Nordic Equity TotalView-ITCH 2.02.2
  * [x] MoldUDP
  * [x] MoldUDP64
  * [x] BinaryFILE
  * [x] SoupFILE
* Parity
  * [x] PMD
