# rivlib-utils

Collection of utilities for working with [Riegl](http://www.riegl.com/) data files.
Includes:

* **ri-inclination**: extract inclination data from .rxp files


## Example

Running:

```bash
ri-inclination file:140123_202748.rxp
```

will produce output like:

```csv
Time,Roll,Pitch
91.8223,-0.286,-0.275
92.8221,-0.285,-0.265
93.9119,-0.288,-0.274
94.9033,-0.286,-0.261
95.8631,-0.287,-0.262
96.8597,-0.283,-0.276
97.8537,-0.289,-0.268
98.8159,-0.286,-0.272
99.9358,-0.290,-0.266
100.8962,-0.286,-0.277
```

This output is on stdout, and can be piped to a file for later use.


## Time reference

The time value produced by **ri-inclination** is the scanner's internal timestamp.
It is possible to retrieve GPS time from rxp files, but this is not implemented as of yet and is an area for future improvement.


## Installation

**rivlib-utils** is known to work on Ubuntu 12.04 with rivlib 3.5rc1, though it should work with many unix builds and rivlib versions.
There are no builds or official releases of **rivlib-utils**, so you must build from source.

First, aquire rivlib from the [RIEGL software download site](http://www.riegl.com/members-area/software-downloads/libraries/) and make sure it is present on your system.
Then, follow the standard Github+cmake+make build sequence, pointing CMake to your version of rivlib:

```bash
git clone https://github.com/gadomski/rivlib-utils.git
cd rivlib-utils
mkdir build
cd build
cmake .. -G "Unix Makefiles" -DRiVLib_DIR=/path/to/your/rivlib-rc1_35-x86_64-linux-gcc43
make
```

The utilities will build in the `bin/` directory.
If you'd like to use the utilities without specifying an absolute path, run:

```bash
(sudo) make install
```

You may need the sudo if your `/usr/local` is not writable by your user.

This software could reasonably be expected to work on a Windows system, since the only dependency is rivlib which comes in a Windows build.
You're on your own for figuring out how to make that work, however.


## License

This code is available under the MIT license.
See LICENSE.txt for more information.


## Contributing

Please use [Github's issues](https://github.com/gadomski/rivlib-utils/issues) and [pull requests](https://github.com/gadomski/rivlib-utils/pulls) to flag bugs and offer patches, respectively.
