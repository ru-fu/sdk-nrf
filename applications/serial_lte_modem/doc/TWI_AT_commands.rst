.. _SLM_AT_TWI:

TWI AT commands
***************

.. contents::
   :local:
   :depth: 2

The following commands list contains AT commands related to the two-wire interface (TWI).

Open TWI instance #XTWIOP
=========================

The ``#XTWIOP`` command opens a TWI instance.

Set command
-----------

The set command allows you to open a TWI instance.

Syntax
~~~~~~

::

   #XTWIOP=<index>

The ``<index>`` parameter accepts the following integer values:

* ``0`` - Use TWI0 (``i2c0``).
* ``1`` - Use TWI1 (``i2c1``).
* ``2`` - Use TWI2 (``i2c2``).
* ``3`` - Use TWI3 (``i2c3``).

See :ref:`zephyr:nordic_nrf_twi`.


Response syntax
~~~~~~~~~~~~~~~

There is no response.

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

* The ``<index>`` parameter accepts the following integer values:

  * ``0`` - Use TWI0 (``i2c0``).
  * ``1`` - Use TWI1 (``i2c1``).
  * ``2`` - Use TWI2 (``i2c2``).
  * ``3`` - Use TWI3 (``i2c3``).

  See :ref:`zephyr:nordic_nrf_twi`.

* The ``<dev_addr>`` parameter is a hexadecimal string.
  It represents the slave device address to write to.
  The maximum length is 2 characters (for example, "DE" for 0xDE).
* The ``<data>`` parameter is a hexadecimal string.
  It represents the data to be written to slave device.
  The maximum length is 254 characters (for example, "DEADBEEF" for 0xDEADBEEF).

Response syntax
~~~~~~~~~~~~~~~

There is no response.

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

* The ``<index>`` parameter accepts the following integer values:

  * ``0`` - Use TWI0 (``i2c0``).
  * ``1`` - Use TWI1 (``i2c1``).
  * ``2`` - Use TWI2 (``i2c2``).
  * ``3`` - Use TWI3 (``i2c3``).

  See :ref:`zephyr:nordic_nrf_twi`.

* The ``<dev_addr>`` parameter is a hexadecimal string.
  It represents the slave device address to read from.
  The maximum length is 2 characters (for example, "DE" for 0xDE).
* The ``<num_read>`` parameter is an unsigned 8-bit integer.
  It represents the amount of data to read from the slave device.
  The available range is from 0 to 255 bytes.

Response syntax
~~~~~~~~~~~~~~~

::

   #XTWIR: <size>
   <data>

* The ``<size>`` value is an unsigned integer.
  It represents the actual number of bytes read from the slave device.
* The ``<data>`` parameter is a hexadecimal string.
  It represents the data read from the slave device.

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

Write data and read from TWI device #XTWIWR
===========================================

The ``#XTWIWR`` command writes data to a TWI slave device and then reads data from the device.

Set command
-----------

The set command allows you to first write data to a TWI slave device and then read that data back.

Syntax
~~~~~~

::

   #XTWIW=<index>,<dev_addr>,<data>,<num_read>

* The ``<index>`` parameter accepts the following integer values:

  * ``0`` - Use TWI0 (``i2c0``).
  * ``1`` - Use TWI1 (``i2c1``).
  * ``2`` - Use TWI2 (``i2c2``).
  * ``3`` - Use TWI3 (``i2c3``).

  See :ref:`zephyr:nordic_nrf_twi`.

* The ``<dev_addr>`` parameter is a hexadecimal string.
  It represents the slave device address to write to.
  The maximum length is 2 characters (for example, "DE" for 0xDE).
* The ``<data>`` parameter is a hexadecimal string.
  It represents the data to be written to slave device.
  The maximum length is 254 characters (for example, "DEADBEEF" for 0xDEADBEEF).
* The ``<num_read>`` parameter is an unsigned 8-bit integer.
  It represents the amount of data to read from the slave device.
  The available range is from 0 to 255 bytes.

Response syntax
~~~~~~~~~~~~~~~

::

   #XTWIWR: <size>
   <data>

* The ``<size>`` value is an unsigned integer.
  It represents the actual number of bytes read from the slave device.
* The ``<data>`` parameter is a hexadecimal string.
  It represents the data read from the slave device.

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
