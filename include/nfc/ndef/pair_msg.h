/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#ifndef NFC_NDEF_PAIR_MSG_H_
#define NFC_NDEF_PAIR_MSG_H_

/**@file
 *
 * @defgroup nfc_ndef_pair_msg NFC Connection Hanover pairing messages
 * @{
 * @ingroup nfc_ndef_messages
 *
 * @brief Generation of The Connection Handover pairing NDEF messages.
 *
 */

#include <stddef.h>
#include <zephyr/types.h>
#include <nfc/ndef/ch.h>
#include <nfc/ndef/le_oob_rec.h>

#ifdef _cplusplus
extern "C" {
#endif

/**
 * @brief Encode an NFC NDEF LE OOB message.
 *
 * This function encodes an NFC NDEF message into a buffer.
 *
 * @param[in] obb Pointer to the LE OOB Record payload descriptor.
 * @param[out] buf Pointer to the buffer for the message.
 * @param[in, out] len Size of the available memory for the message as input.
 *                     Size of the generated message as output.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int nfc_ndef_pair_msg_le_oob_encode(struct nfc_ndef_le_oob_rec_payload_desc *oob,
				    u8_t *buf, size_t *len);

/**
 * @brief Encode an NFC NDEF Handover Select message.
 *
 * This function encodes an NFC NDEF message into a buffer. It
 * create a nested NDEF message with the Alternative Carrier Records.
 * Next the Records with the Carrier data are encoded into the main
 * Connection Hanover Select message. Number of the Alternative
 * Carrier Records must be equal to the number of the Carrier Records.
 *
 * @param[in] obb Pointer to the Alternative Carrier Records.
 * @param[in] carrier Pointer to the Carrier Records which identifies
 *                    the carrier technology.
 * @param[in] cnt Number of the Alternative Records/Carrier Records.
 * @param[out] buf Pointer to the buffer for the message.
 * @param[in, out] len Size of the available memory for the message as input.
 *                     Size of the generated message as output.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int nfc_ndef_pair_msg_hs_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len);

/**
 * @brief Encode an NFC NDEF Handover Request message.
 *
 * This function encodes an NFC NDEF message into a buffer. It
 * create a nested NDEF message with the Alternative Carrier Records.
 * Next the Records with the Carrier data are encoded into the main
 * Connection Hanover Request message. Number of the Alternative
 * Carrier Records must be equal to the number of the Carrier Records.
 *
 * This NDEF message contains also the Collision Resolution Records
 * which uses the Entropy driver to generate 2 - byte length random
 * number.
 *
 * @param[in] obb Pointer to the Alternative Carrier Records.
 * @param[in] carrier Pointer to the Carrier Records which identifies
 *                    the carrier technology.
 * @param[in] cnt Number of the Alternative Records/Carrier Records.
 * @param[out] buf Pointer to the buffer for the message.
 * @param[in, out] len Size of the available memory for the message as input.
 *                     Size of the generated message as output.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int nfc_ndef_pair_msg_hr_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len);

/**
 * @brief Encode an NFC NDEF Handover Mediation message.
 *
 * This function encodes an NFC NDEF message into a buffer. It
 * create a nested NDEF message with the Alternative Carrier Records.
 * Next the Records with the Carrier data are encoded into the main
 * Connection Hanover Mediation message. Number of the Alternative
 * Carrier Records must be equal to the number of the Carrier Records.
 *
 * @param[in] obb Pointer to the Alternative Carrier Records.
 * @param[in] carrier Pointer to the Carrier Records which identifies
 *                    the carrier technology.
 * @param[in] cnt Number of the Alternative Records/Carrier Records.
 * @param[out] buf Pointer to the buffer for the message.
 * @param[in, out] len Size of the available memory for the message as input.
 *                     Size of the generated message as output.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int nfc_ndef_pair_msg_hm_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len);

/**
 * @brief Encode an NFC NDEF Handover Initiate message.
 *
 * This function encodes an NFC NDEF message into a buffer. It
 * create a nested NDEF message with the Alternative Carrier Records.
 * Next the Records with the Carrier data are encoded into the main
 * Connection Hanover Initiate message. Number of the Alternative
 * Carrier Records must be equal to the number of the Carrier Records.
 *
 * @param[in] obb Pointer to the Alternative Carrier Records.
 * @param[in] carrier Pointer to the Carrier Records which identifies
 *                    the carrier technology.
 * @param[in] cnt Number of the Alternative Records/Carrier Records.
 * @param[out] buf Pointer to the buffer for the message.
 * @param[in, out] len Size of the available memory for the message as input.
 *                     Size of the generated message as output.
 *
 * @retval 0 If the operation was successful.
 *           Otherwise, a (negative) error code is returned.
 */
int nfc_ndef_pair_msg_hi_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len);

#ifdef _cplusplus
}
#endif

/**
 * @}
 */

#endif /* NFC_NDEF_PAIR_MSG_H_ */
