.. _lib_fota_download:

FOTA download
#############

The firmware over-the-air (FOTA) download library provides functions for downloading a firmware file as an upgrade candidate to the DFU target that is used in the :ref:`lib_dfu_target` library.

The arguments for performing a FOTA download is ``host`` (e.g. "my_domain.com") and ``file`` (e.g. "path/to/resource/file.bin").

The library uses the :ref:`lib_download_client` to download the image.
After downloading the first fragment, the :ref:`lib_dfu_target` library is used to identify the type of the image being downloaded.
Examples of image types are modem upgrades, and upgrades handled by MCUboot.

Once the download has been started, all received data fragments are passed to the :ref:`lib_dfu_target` library.
The :ref:`lib_dfu_target` library takes care of where the upgrade candidate is stored, depending on the image type that is being downloaded.

When the download client sends the event indicating that the download has completed, the received firmware is tagged as an upgrade candidate, and the download client is instructed to disconnect from the server.
The library then sends a :cpp:enumerator:`FOTA_DOWNLOAD_EVT_FINISHED<fota_download::FOTA_DOWNLOAD_EVT_FINISHED>` callback event.
When the consumer of the library receives this event, it should issue a reboot command to apply the upgrade.

By default, the FOTA download library uses HTTP for downloading the firmware file.
To use HTTPS instead, apply the changes described in :ref:`the HTTPS section of the download client documentation <download_client_https>` to the library.

The FOTA download library is used in the :ref:`http_application_update_sample` sample.


.. note::
  If an upgradeable bootloader is included in the project, the FOTA download library must perform some special handling of the ``file`` argument.
  Firstly, a :ref:`secure service<lib_secure_service>` is invoked to deduce the active MCUboot partition (S0 or S1)
  Next, the ``file`` argument is given to the ``dfu_target_mcuboot_set_path`` function, alongside a flag indicating which MCUboot partition is active.
  Now the entry corresponding to the non active slot will be handed to the :ref:`lib_download_client` library.
  To perform an upgrade of MCUboot, the ``file`` argument must contain two entries, separated by a space.
  The first entry  must point to the MCUboot variant linked against the S0 partition.
  The second entry  must point to the MCUboot variant linked against the S1 partition.
  See :ref:`upgradeable_bootloader` for more information.
  If there is a space character in the ``file`` argument, the ``dfu_target_mcuboot_set_path`` function is called to select the correct entry.



API documentation
*****************

| Header file: :file:`include/net/fota_download.h`
| Source files: :file:`subsys/net/lib/fota_download/src/`

.. doxygengroup:: fota_download
   :project: nrf
   :members:
