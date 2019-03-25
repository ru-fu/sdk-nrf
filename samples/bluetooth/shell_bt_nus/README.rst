.. _shell_bt_nus:

Bluetooth: Shell over peripheral UART service (NUS) transport
#############################################################

Sample demonstrates how to use Shell over :ref:`shell_bt_nus_readme` transport.

Overview
********

When connected, host is able to use Shell over Bluetooth to execute commands
or see the logs. See ref:`shell_bt_nus_readme` documentation which provide
details about host tools available in |NCS| for communication with the sample.

Requirements
************

* One of the following development boards:

  * nRF52840 Development Kit board (PCA10056)
  * nRF52 Development Kit board (PCA10040)

* Optionally, additional nRF52 Development Kit board (PCA10040) for host tool
  (see :ref:`shell_bt_nus_readme` for details)

Building and running
********************

This sample can be found under :file:`samples/bluetooth/shell_bt_nus` in the
|NCS| folder structure.

See :ref:`gs_programming` for information about how to build and program the
application.

Testing
=======

See :ref:`shell_bt_nus_readme` for available host tools and how to set them up.