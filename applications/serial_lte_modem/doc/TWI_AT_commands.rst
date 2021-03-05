.. _SLM_AT_TWI:

TWI AT commands
***************

.. contents::
   :local:
   :depth: 2

The following commands list contains TWI related AT commands.

Open TWI instance #XTWIOP
=========================

The ``#XTWIOP`` command opens TWI instance.

Set command
-----------

The set command allows you to open TWI instance.

Syntax
~~~~~~

::

   #XTWIOP=<index>

The ``<index>`` parameter accepts the following integer values:

* ``0`` - i2c0
* ``1`` - i2c1
* ``2`` - i2c2
* ``3`` - i2c3

Example
~~~~~~~

::

   AT#XTWIOP=2
   OK

Read command
------------

The read command is not supported.

Test command
------------

The test command is not supported.

Write to TWI slave device #XTWIW
=================================

The ``#XTWIW`` command writes data to a TWI slave device.

Set command
-----------

The set command allows you to write data to a TWI slave device.

Syntax
~~~~~~

::

   #XTWIW=<index>,<dev_addr>,<data>

The ``<index>`` parameter accepts the following integer values:

* ``0`` - i2c0
* ``1`` - i2c1
* ``2`` - i2c2
* ``3`` - i2c3

The ``<dev_addr>`` parameter is a hexadecimal string.
  It represents the slave device address to write. The maximum size is 2-digit (e.g. "DE" for 0xDE)
The ``<data>`` parameter is a hexadecimal string.
  It represents the data to be written to slave device. The maximum size is 254-digit. (e.g. "DEADBEEF" for 0xDEADBEEF)

Example
~~~~~~~

::

   AT#XTWIW=2,"76","D0"
   OK

Read command
------------

The read command is not supported.

Test command
------------

The test command is not supported.

Read from TWI slave device #XTWIR
=================================

The ``#XTWIR`` command reads data from a TWI slave device.

Set command
-----------

The set command allows you to read data from a TWI slave device.

Syntax
~~~~~~

::

   #XTWIR=<index>,<dev_addr>,<num_read>

The ``<index>`` parameter accepts the following integer values:

* ``0`` - i2c0
* ``1`` - i2c1
* ``2`` - i2c2
* ``3`` - i2c3

The ``<dev_addr>`` parameter is a hexadecimal string.
  It represents the slave device address to read. The maximum size is 2-digit (e.g. "DE" for 0xDE)
The ``<num_read>`` parameter is an unsigned 8-bit integer.
  It represents the number of data to be read from slave device. The available range is from 0 to 255.

Response syntax
~~~~~~~~~~~~~~~

::

   #XTWIR: <size>
   <data>

The ``<size>`` value is an unsigned integer.
  It represents the actual number of the bytes read from slave device.
The ``<data>`` parameter is a hexadecimal string.
  It represents the data read from slave device.

Example
~~~~~~~

::

   AT#XTWIR=2,"76",1

   #XTWIWR: 2
   61
   OK

Read command
------------

The read command is not supported.

Test command
------------

The test command is not supported.

Write data to then read data from an TWI device #XTWIWR
=======================================================

The ``#XTWIWR`` command writes to then read data from a TWI slave device.

Set command
-----------

The set command allows you to write data to then read data from a TWI slave device.

Syntax
~~~~~~

::

   #XTWIW=<index>,<dev_addr>,<data>,<num_read>

The ``<index>`` parameter accepts the following integer values:

* ``0`` - i2c0
* ``1`` - i2c1
* ``2`` - i2c2
* ``3`` - i2c3

The ``<dev_addr>`` parameter is a hexadecimal string.
  It represents the slave device address to write. The maximum size is 2-digit (e.g. "DE" for 0xDE)
The ``<data>`` parameter is a hexadecimal string.
  It represents the data to be written to slave device. The maximum size is 254-digit. (e.g. "DEADBEEF" for 0xDEADBEEF)
The ``<num_read>`` parameter is an unsigned 8-bit integer.
  It represents the number of data to be read from slave device. The available range is from 0 to 255.

Response syntax
~~~~~~~~~~~~~~~

::

   #XTWIWR: <size>
   <data>

The ``<size>`` value is an unsigned integer.
  It represents the actual number of the bytes read from slave device.
The ``<data>`` parameter is a hexadecimal string.
  It represents the data read from slave device.

Example
~~~~~~~

::

   AT#XTWIWR=2,"76","D0",1

   #XTWIWR: 2
   61
   OK

Read command
------------

The read command is not supported.

Test command
------------

The test command is not supported.
