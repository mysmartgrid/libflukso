## LIBFLUKSO - A SIMPLE FLUKSO CLIENT LIBRARY

  https://github.com/mysmartgrid/libflukso/

This little utility is intended to act as a swiss army knife for
accessing various data and functions build around the Flukso power
metering device, which is used in the http://www.mysmartgrid.de projekt. 
The initial code was developed by Henning Bitsch and then extended 
by Mathias Dalheimer. It is provided as-is under the terms of the GPLv3
license.

## USAGE
Some utilities are included in the distribution:

1. flukso-getvalues: A tool for downloading the latest measurements
2. flukso-archive: A tool intended to run periodically. It adds values
   to a libklio datastore.

Each command comes with its own builtin help, so e.g.

    $ flukso-archive -h

provides this information:

    Usage: ./build/src/flukso-archive ACTION [additional options]:
    -h [ --help ]          produce help message
    -v [ --version ]       print libklio version and exit
    -s [ --storefile ] arg the data store to use
    -i [ --id ] arg        the id of the sensor
    -t [ --token ] arg     the access token of the sensor
    -u [ --unit ] arg      the unit of the sensor
    --interval arg         which time interval to query
    -b [ --baseurl ] arg   the base url of the sensor
    -d [ --debug ]         enable output of debugging messages

A typical workflow would be:

1. Create a store.

        $ klio-store create teststore.db
        Attempting to create "teststore.db"
        Initialized store: SQLite3 database, stored in file "teststore.db"

2. Query a sensor. The access token can be found within your mysmartgrid
   account.

        $ flukso-getvalues -d -t <TOKEN> -s dd8d03b94a973cf11a309afcbc4d9b3a -i hour 
        Base URL omitted and no local ip specified. Using default URL https://api.mysmartgrid.de/sensor/
        Unit omitted. Using default unit watt
        Format omitted. Using default format text
        Version omitted. Setting default to 1.0
        Connecting to server and fetching data ...finished.
        Data length: 61 bytes
        Second array element is neither string or integer at entry59: [ 1328796060, "-nan" ]
        Second array element is neither string or integer at entry60: [ 1328796120, "-nan" ]
        1328792520	68
        1328792580	68
        1328792640	68
        1328792700	68
        1328792760	68
        1328792820	69
        ....


2. Add a sensor definition to the store. This must be done manually
   because you have to specify unit and timezone of the sensor.

        $ klio-sensor create -s teststore.db -i dd8d03b94a973cf11a309afcbc4d9b3a \
          -u Watt -z MEZ -d "Line L3" 
        opened store: SQLite3 database, stored in file "teststore.db"
        added: dd8d03b94a973cf11a309afcbc4d9b3a(4c4ef5fd-cb89-4ead-8ed6-397d797b6468), 
        unit Watt, tz=MEZ, description: Unknown

3. Now, use flukso-archive to create an archive:

        $ flukso-archive -s teststore.db -i \
          dd8d03b94a973cf11a309afcbc4d9b3a -t <TOKEN>
        Inserting 59 readings.
        
5. Export sensor data:

        $ klio-export json -s teststore.db -i dd8d03b94a973cf11a309afcbc4d9b3a 
        Using stdout
        opened store: SQLite3 database, stored in file "teststore.db"
        [[1328792820,69],[1328792880,69],[1328792940,69],[1328793000,69],
        [1328793060,69],[1328793120,69],[1328793180,69],[1328793240,69],
        [1328793300,69],[1328793360,69],[1328793420,69],[1328793480,69],
        [1328793540,69],[1328793600,70],[1328793660,70],[1328793720,69],
        [1328793780,69],[1328793840,69],[1328793900,69],[1328793960,69],
        [1328794020,69],[1328794080,69],[1328794140,69],[1328794200,69],
        [1328794260,69],[1328794320,69],[1328794380,69],[1328794440,70],
        [1328794500,70],[1328794560,69],[1328794620,69],[1328794680,69],
        [1328794740,69],[1328794800,69],[1328794860,69],[1328794920,69],
        [1328794980,69],[1328795040,69],[1328795100,69],[1328795160,69],
        [1328795220,69],[1328795280,69],[1328795340,69],[1328795400,69],
        [1328795460,73],[1328795520,158],[1328795580,183],[1328795640,177],
        [1328795700,177],[1328795760,175],[1328795820,176],[1328795880,172],
        [1328795940,171],[1328796000,169],[1328796060,171],[1328796120,166],
        [1328796180,168],[1328796240,167],[1328796300,167]]


## FEEDBACK
  If you encounter problems, please contact the developers on the
  mysmartgrid developer mailing list[1]. Alternatively, the issue tracker
  for this library lives on github[2].

## INSTALLATION
So far, the library has been successfully compiled on Ubuntu Linux
11.10, Debian Linux 6.0 and Mac OS 10.7 (Lion). The library depends on 
several libraries:

1. Boost version 1.48.0 or later
2. sqlite3
3. pkg-config
4. json-c
5. curl 
6. popt
7. libklio

The library uses CMake for compile-time configuration. A Makefile is
provided which wraps the build infrastructure. A simple

    $ make

should suffice to compile the library if all dependencies are available.
Afterwards, you can use

    $ make install

to install the library. If you prefer proper packaging, you can also
build installation packages in several formats:

    $ make release

builds the package with release settings (i.e. full optimization, no
debug symbols) and places the created packages in the 'build'
subdirectory.

## BUGS 
The library was developed with great care, but we cannot guarantee that
no bugs are in the library. Please submit any issues using the issue
tracker[2].

## LICENSE
This library is (c) Fraunhofer ITWM and distributed under the terms of
the GPLv3.

## REFERENCES
 * [1] http://listserv.mysmartgrid.de/mailman/listinfo/msg-dev
 * [2] https://github.com/mysmartgrid/libflukso/issues
