.. _shell_bt_nus_readme:

Nordic UART Service (NUS) Shell transport
#########################################

The BLE GATT Nordic UART Service shell transport allows to use shell remotely
over Bluetooth using :ref:`nus_service_readme`.

The NUS Service shell is used in the :ref:`shell_bt_nus` sample.

Using NUS shell
***************

Dedicated software is required on the host side (e.g. PC) to be able to use
shell over Blueooth. Host application must implement complementary service
:ref:`nus_c_readme`.

bt_nus_shell.py
===============

File `scripts/shell/bt_nus_shell.py` contains Python 2 cross platform example
host application. Script is using additional Nordic Development Kit (PCA10040)
as a Bluetooth central device. It is connecting to the specified device and
forwards all NUS traffic to the network port. Terminal application, for example
PuTTy can be used to connect to that port (default port is 8889) and use the
Shell. Script takes following parameters:

	- `com` - port of Development Kit used by the script
	- `snr` - Segger board ID
	- `family` - Development kit chip family (e.g. NRF52)
	- `name` - Advertising name of the device with NUS shell

.. warning::
	Script does not support reconnections so it is required to restart
	`scripts/shell/bt_nus_shell.py` and terminal application after each
	reconnection.

Perform following steps to run Shell over Blueooth using `bt_nus_shell.py`
script:

- Connect Nordic Development Kit (e.g. PCA10040)
- Start the `bt_nus_shell.py` script, for example::

	bt_nus_shell.py --snr 680834186 --name BT_NUS_shell --com COM115 --family NRF52

- Open a terminal, for example PuTTY. Set the Connection Type to Raw and the
  Destination Address to 127.0.0.1:8889.
- Press Enter in the terminal. A console prompt is displayed.

BLE Console
***********

:ref:`ble_console_readme` is a stand-alone Linux application which is using
standard Bluetooth device (HCI dongle or built-in Bluetooth device) and BlueZ
stack to communicate over Bluetooth with device running Shell over Nordic UART
Service transport.

API documentation
*****************

.. doxygengroup:: shell_bt_nus
   :project: nrf
   :members:
