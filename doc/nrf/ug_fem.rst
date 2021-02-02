.. _ug_fem:

Working with RF front-end modules
#################################

.. contents::
   :local:
   :depth: 2

An RF front-end module (FEM) is a range extender that can be used to increase the range distance and the strength of a link's connection.
In addition to increasing range, an RF FEM also increases the robustness of the link connection.
A more robust link leads to less packet loss, meaning less retransmissions.
The probability of successfully receiving the first packet also increases, resulting in a more stable link latency.

FEMs provide a power amplifier (PA) that increases the TX power and a low-noise amplifier (LNA) that increases the RX sensitivity.
Some FEMs, like the nRF21540, provide a power down (PDN) control that can be used to power down the FEM internal circuits, to reduce energy consumption.

For testing purposes, a FEM is usually integrated in either a development kit or a shield that you connect to a development kit.

Software support
****************

The |NCS| provides FEM support based on the :ref:`nrfxlib:mpsl_fem` in the :ref:`nrfxlib:mpsl` (MPSL) library.

Using MPSL
==========

The MPSL library provides an implementation for the 3-pin GPIO interface of the nRF21540 and a simplified version for FEMs with a 2-pin interface.

To use this implementation, your application must use a protocol driver that enables the FEM feature provided by the MPSL library.
The MPSL library provides multiprotocol support, but you can also use it in applications that require only one protocol.

.. note::
   Currently, the following protocols use FEM support provided by MPSL:

   * :ref:`ug_thread`
   * :ref:`ug_zigbee`

   These protocols support the :ref:`nrf21540 DK <nrf21540dk_nrf52840>` and the nRF21540 EK for nRF52 Series devices.
   There is no multiprotocol support yet.
   There is no support for nRF5340 yet.



application must use and enable MPSL

Direct support
==============

If your application cannot use MPSL or if the FEM driver in MPSL does not support all features that you need, you can implement your own driver for nRF21540.

See the :ref:`radio_test` and :ref:`direct_test_mode` samples for an example implementation.

Hardware description
********************

From ug_radio_fem.rst:
|NCS| provides a friendly wrapper that configures FEM based on devicetree (DTS) and Kconfig information.
To enable FEM support, you must enable FEM and MPSL, and add an ``nrf_radio_fem`` node in the devicetree file.
The node can also be provided by the target board devicetree file or by an overlay file.
See :ref:`zephyr:dt-guide` for more information about the DTS data structure, and :ref:`zephyr:dt_vs_kconfig` for information about differences between DTS and Kconfig.

add node in DTS (defines where to get which input), assign GPIOTE and PPI channels

Hardware support
****************

DK vs. shield

nRF21540 DK
===========

The nRF21540 DK is a nRF52840 DK + FEM
Easy way for a first test

can be used like nRF52840 DK (according to Michal, all nRF42840 samples should work out of the box when programmed for nRF21540 DK)

board definition contains the DTS node, so can just be used

Shields
=======

Shields are attached to a DK
Shield can be used for testing stand-alone without software or with software (not supported yet), or in cmobination with a DK.

Setup
-----

Check pin assignment and update/create dts overlay file

connect the shield to the DK

program (make sure to keep existing overlay files, maybe use -DSHIELD in the future?)

nRF21540 EK
-----------

Has a 3-pin PA/LNA interface

The following steps ... (from ug_radio_fem)

Shields with 2-pin PA/LNA interface
-----------------------------------

For example, SKY66112-11

The following steps ... (from ug_radio_fem)
