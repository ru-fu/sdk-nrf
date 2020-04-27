/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <drivers/entropy.h>
#include <sys/byteorder.h>

#include <nfc/ndef/pair_msg.h>
#include <nfc/ndef/msg.h>

#define NFC_PAIRING_CH_MAJOR_VER CONFIG_NFC_NDEF_CH_MAJOR_VERSION
#define NFC_PAIRING_CH_MINOR_VER CONFIG_NFC_NDEF_CH_MINOR_VERSION

static int alternate_rec_encode(struct nfc_ndef_record_desc *hc,
				struct nfc_ndef_record_desc *ac,
				size_t cnt)
{
	int err;

	for (size_t i = 0; i < cnt; i++) {
		err = nfc_ndef_ch_rec_local_record_add(hc,
						       &ac[i]);
		if (err) {
			return err;
		}
	}

	return 0;
}

static int ch_rec_create(struct nfc_ndef_msg_desc *msg,
			 struct nfc_ndef_record_desc *ch,
			 struct nfc_ndef_record_desc *carrier,
			 size_t cnt)
{
	int err;

	err = nfc_ndef_msg_record_add(msg, ch);
	if (err) {
		return err;
	}

	for (size_t i = 0; i < cnt; i++) {
		err = nfc_ndef_msg_record_add(msg, &carrier[i]);
		if (err) {
			return err;
		}
	}

	return 0;
}

int nfc_ndef_pair_msg_le_oob_encode(struct nfc_ndef_le_oob_rec_payload_desc *oob,
				    u8_t *buf, size_t *len)
{
	int err;

	NFC_NDEF_MSG_DEF(oob_msg, 1);
	NFC_NDEF_LE_OOB_RECORD_DESC_DEF(oob_rec, 0, oob);

	err = nfc_ndef_msg_record_add(&NFC_NDEF_MSG(oob_msg),
				      &NFC_NDEF_LE_OOB_RECORD_DESC(oob_rec));
	if (err) {
		return err;
	}

	return nfc_ndef_msg_encode(&NFC_NDEF_MSG(oob_msg), buf, len);
}

int nfc_ndef_pair_msg_hs_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len)
{
	int err;

	NFC_NDEF_MSG_DEF(hs_msg, cnt + 1);
	NFC_NDEF_CH_HS_RECORD_DESC_DEF(hs_rec, NFC_PAIRING_CH_MAJOR_VER,
				       NFC_PAIRING_CH_MINOR_VER, cnt);

	err = alternate_rec_encode(&NFC_NDEF_CH_RECORD_DESC(hs_rec), ac, cnt);
	if (err) {
		return err;
	}

	err = ch_rec_create(&NFC_NDEF_MSG(hs_msg),
			    &NFC_NDEF_CH_RECORD_DESC(hs_rec),
			    carrier, cnt);
	if (err) {
		return err;
	}

	return nfc_ndef_msg_encode(&NFC_NDEF_MSG(hs_msg), buf, len);
}

int nfc_ndef_pair_msg_hr_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len)
{
	int err;
	struct device *dev;
	u8_t random_number[sizeof(u16_t)];

	NFC_NDEF_MSG_DEF(hr_msg, cnt + 1);

	dev = device_get_binding(CONFIG_ENTROPY_NAME);
	if (!dev) {
		return -EFAULT;
	}

	/* Get Collision Resolution random number form RNG. */
	err = entropy_get_entropy(dev, random_number, sizeof(random_number));
	if (err) {
		return err;
	}

	NFC_NDEF_CH_CR_RECORD_DESC_DEF(cr_rec, sys_get_le16(random_number));
	NFC_NDEF_CH_HR_RECORD_DESC_DEF(hr_rec, NFC_PAIRING_CH_MAJOR_VER,
				       NFC_PAIRING_CH_MINOR_VER, cnt + 1);

	err = nfc_ndef_ch_rec_local_record_add(&NFC_NDEF_CH_RECORD_DESC(hr_rec),
					       &NFC_NDEF_CH_AC_RECORD_DESC(cr_rec));

	err = alternate_rec_encode(&NFC_NDEF_CH_RECORD_DESC(hr_rec), ac, cnt);
	if (err) {
		return err;
	}

	err = ch_rec_create(&NFC_NDEF_MSG(hr_msg),
			    &NFC_NDEF_CH_RECORD_DESC(hr_rec),
			    carrier, cnt);
	if (err) {
		return err;
	}

	return nfc_ndef_msg_encode(&NFC_NDEF_MSG(hr_msg), buf, len);
}

int nfc_ndef_pair_msg_hm_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len)
{
	int err;

	NFC_NDEF_MSG_DEF(hm_msg, cnt + 1);
	NFC_NDEF_CH_HS_RECORD_DESC_DEF(hm_rec, NFC_PAIRING_CH_MAJOR_VER,
				       NFC_PAIRING_CH_MINOR_VER, cnt);


	err = alternate_rec_encode(&NFC_NDEF_CH_RECORD_DESC(hm_rec), ac, cnt);
	if (err) {
		return err;
	}

	err = ch_rec_create(&NFC_NDEF_MSG(hm_msg),
			    &NFC_NDEF_CH_RECORD_DESC(hm_rec),
			    carrier, cnt);
	if (err) {
		return err;
	}

	return nfc_ndef_msg_encode(&NFC_NDEF_MSG(hm_msg), buf, len);
}

int nfc_ndef_pair_msg_hi_encode(struct nfc_ndef_record_desc *ac,
				struct nfc_ndef_record_desc *carrier,
				size_t cnt, u8_t *buf, size_t *len)
{
	int err;

	NFC_NDEF_MSG_DEF(hi_msg, cnt + 1);
	NFC_NDEF_CH_HS_RECORD_DESC_DEF(hi_rec, NFC_PAIRING_CH_MAJOR_VER,
				       NFC_PAIRING_CH_MINOR_VER, cnt);

	err = alternate_rec_encode(&NFC_NDEF_CH_RECORD_DESC(hi_rec), ac, cnt);
	if (err) {
		return err;
	}

	err = ch_rec_create(&NFC_NDEF_MSG(hi_msg),
			    &NFC_NDEF_CH_RECORD_DESC(hi_rec),
			    carrier, cnt);
	if (err) {
		return err;
	}

	return nfc_ndef_msg_encode(&NFC_NDEF_MSG(hi_msg), buf, len);
}
