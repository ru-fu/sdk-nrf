.. _nfc_ch:

Connection Handover
###################

The Connection Handover defines the NDEF records and the corresponding message structure that supports negotiation and activation of an alternative communication carrier.
The negotiated communication carrier can then be used to perform certain activities between the two devices, such as Bluetooth pairing.
The Connection Hanover module provides functions for creating and encoding Handover Connection records.

Module supporting encoding of the following Connection Hanover Records:
    * Handover Request Record
    * Handover Select Record
    * Handover Mediation Record
    * Handover Initiate Record
    * Handover Carrier Record
    * Local Records:
        * Alternative Carrier Record
	* Collision Resolution Record

API documentation
*****************

| Header file: :file:`include/nfc/ndef/ch.h`
| Source file: :file:`subsys/nfc/ndef/ch.c`

.. _nfc_ndef_ch:

.. doxygengroup:: nfc_ndef_ch
   :project: nrf
   :members:
