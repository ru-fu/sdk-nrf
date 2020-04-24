.. _nfc_pairing:

Bluetooth: NFC Pairing Reference
################################

The NFC Pairing Reference sample shows how to use BLE Connection Handover pairing using an NFC tag.
The application shows shows the usage of :ref:`_nfc_pair`.
The example can be used to test the touch-to-pair feature with Nordic devices with NFC Reader or a other NFC Poller devices, for example a mobile phone.

This application uses minimal Bluetooth functionalities. It has only Device Information service.

It allows to perform pairing in one of the following mode:
   * LE Secure OOB

Overview
********

When the application starts, it initializes and starts the NFCT peripheral, which is used for pairing.
The application does not start advertising immediately, but only when the NFC tag is read by an NFC polling device, for example a smartphone or a tablet with NFC support.
The message that the tag sends to the NFC device contains data required to initiate pairing.
To start the NFC data transfer, the NFC device must touch the NFC antenna that is connected to the Development board.

After reading the tag, the device can pair with the device which is advertising.
Connection state of the device is signalled by LEDs.
When the connection is lost due to timeout, the library automatically triggers direct advertising.

Requirements
************

* One of the following development boards:

  * |nRF5340DK|
  * |nRF52840DK|
  * |nRF52DK|

* NFC Poller device, Smartphone or tablet

User interface
**************

LED 1:
   Indicates Bluetooth Connection established
LED_2:
   Indicates if an NFC field is present.

Building and running
********************

.. |sample path| replace:: :file:`samples/bluetooth/nfc_pairing`

.. include:: /includes/build_and_run.txt

Testing
=======

After programming the sample to your board, test it by performing the following steps:

1. Touch the NFC antenna with the smartphone or tablet and observe that LED 2 is lit.
#. Confirm pairing with 'Nordic_NFC_pairing' in a pop-up windows on the smartphone or tablet and observe that LED1 is lit.
#. Move the smartphone/tablet away from the NFC antenna and observe that LED 2
   turns off.

Dependencies
************

This sample uses the following |NCS| libraries:

* :ref:`_nfc_ndef_le_oob`
* :ref:`_nfc_ndef_pair_msg`
* :ref:`_nfc_ch`
* :ref:`_dk_buttons_and_leds_readme`

In addition, it uses the Type 4 Tag library from nrfxlib:

* :ref:`nrfxlib:nfc_api_type4`

The sample uses the following Zephyr libraries:

* ``include/zephyr.h``
* ``include/device.h``
* :ref:`GPIO Interface <zephyr:api_peripherals>`
