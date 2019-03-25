.. _ble_console_readme:

BLE Console
###########

BLE Console is a desktop application which can be used to communicate with a nRF
device over Bluetooth Low Energy using Nordic UART Service.

Requirements
************

BLE compliannt receiver or dongle
Linux Host with BlueZ driver
shell_bt_nus module for communication on target device


Usage
*****

It is recommended to use BLE Console on a natively installed Linux (i.e. not on
virtual machine, as problems with BLE connection may occur when using VM).

BLE Console does not support Windows.

BlueZ configuration
*******************

BLE Console requires bluetooth daemon to be run in experimental mode.

If you want bluetooth daemon to start in experimental mode by default::

	nano /etc/systemd/system/bluetooth.service

add '-E' after 'ExecStart=/usr/lib/bluetooth/bluetoothd', line should look like
this::

	ExecStart=/usr/lib/bluetooth/bluetoothd -E

than log out or reboot::

	sudo service bluetooth restart

In case of using virtual machine it is most likely that bluetooth service will
require restart after every machine start, run command::

	sudo service bluetooth restart

After succsseful configuration pair with the device using Bluetooth tools
provided by your Linux vendor. In case of Ubuntu siply go to
settings -> Bluetooth. After successful pairing you are ready to start using
BLE Console.

Dependencies
************

`sudo apt install python-gtk2`

`sudo apt install python-vte`

`sudo apt install python-dbus`
