.. _nfc_pair:

NFC Pair messages
#################

The NFC Pair message contains the Connection Handover Record, which is used to establish connection and pair with other Bluetooth Device.

Module supporting encoding of the following messages:
   * Generic OOB message
   * Handover Select message
   * Handover Request message
   * Handover Mediation message
   * Handover Initiate message

API documentation
*****************

.. _nfc_pair_msg:

| Header file: :file:`include/nfc/ndef/pair_msg.h`
| Source file: :file:`subsys/nfc/ndef/pair_msg.c`

.. doxygengroup:: nfc_ndef_pair_msg
   :project: nrf
   :members:
