/*
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */
#include <stddef.h>
#include <errno.h>
#include <sys/byteorder.h>
#include <nfc/ndef/ch.h>

#define HS_REC_VERSION_SIZE 1

/* Size of the field with CPS data. */
#define AC_REC_CPS_BYTE_SIZE 1

/* Size of the Data Reference Length field. */
#define AC_REC_DATA_REF_LEN_SIZE 1

/* Size of the Data Reference Length field. */
#define AC_REC_AUX_DATA_REF_COUNT_SIZE 1

/* Size of the field with CTF data.*/
#define HC_REC_CTF_BYTE_SIZE 1

/* Size of the field with Carrier Type Length. */
#define HC_REC_CARRIER_TYPE_LEN_SIZE 1

/* Handover Select Record type. */
const u8_t nfc_ndef_ch_hs_rec_type_field[] = {'H', 's'};

/* Handover Request Record type. */
const u8_t nfc_ndef_ch_hr_rec_type_field[] = {'H', 'r'};

/* Handover Mediation Record type. */
const u8_t nfc_ndef_ch_hm_rec_type_field[] = {'H', 'm'};

/* Handover Initiate Record type. */
const u8_t nfc_ndef_ch_hi_rec_type_field[] = {'H', 'i'};

/* Handover Carrier Record. */
const u8_t nfc_ndef_ch_hc_rec_type_field[] = {'H', 'c'};

/* Handover Alternative Carrier record type. */
const u8_t nfc_ndef_ch_ac_rec_type_field[] = {'a', 'c'};

/* Handover Collision Resolution record type. */
const u8_t nfc_ndef_ch_cr_rec_type_field[] = {'c', 'r'};

static u32_t nfc_ac_rec_payload_size_get(const struct nfc_ndef_ch_ac_rec_payload_desc *ac_rec_payload_desc)
{
	/* Initialize with size of byte with CPS. */
	u32_t payload_size = AC_REC_CPS_BYTE_SIZE;

	/* Add Carrier Data Reference size. */
	payload_size +=  ac_rec_payload_desc->carrier_data_ref.length +
			 AC_REC_DATA_REF_LEN_SIZE;

	/* Add Auxiliary Data Reference Count size. */
	payload_size += AC_REC_AUX_DATA_REF_COUNT_SIZE;

	for (size_t i = 0; i < ac_rec_payload_desc->aux_data_ref_count; i++) {
		/* Add Auxiliary Data Reference size. */
		payload_size += ac_rec_payload_desc->aux_data_ref[i].length +
				AC_REC_DATA_REF_LEN_SIZE;
	}

	return payload_size;
}

static u32_t nfc_hc_payload_size_get(const struct nfc_ndef_ch_hc_rec_payload_desc *hc_rec)
{
	u32_t payload_size = HC_REC_CTF_BYTE_SIZE;

	payload_size += hc_rec->carrier.type_length +
			HC_REC_CARRIER_TYPE_LEN_SIZE;

	payload_size += hc_rec->carrier.data_length;

	return payload_size;
}

int nfc_ndef_ch_rec_payload_constructor(struct nfc_ndef_ch_rec_payload_desc *ch_rec_payload_desc,
					u8_t *buff, u32_t *len)
{
	int err;

	if (buff) {
		/* There must be at least 1 free byte in buffer for version byte. */
		if (*len < HS_REC_VERSION_SIZE) {
			return -ENOMEM;
		}

		/* Major/minor version byte. */
		*buff = ((ch_rec_payload_desc->major_version << 4) & 0xF0) |
			(ch_rec_payload_desc->minor_version & 0x0F);

		buff += HS_REC_VERSION_SIZE;

		/* Decrement remaining buffer size. */
		*len -= HS_REC_VERSION_SIZE;
	}

	/* Encode local records encapsulated in a message. */
	err = nfc_ndef_msg_encode(ch_rec_payload_desc->local_records,
				  buff, len);
	if (err) {
		return err;
	}

	/* Add version byte to the total record size. */
	*len += HS_REC_VERSION_SIZE;

	return 0;
}

void nfc_ndef_ch_rec_local_record_clear(struct nfc_ndef_record_desc *ch_rec)
{
	struct nfc_ndef_ch_rec_payload_desc *ch_payload =
		(struct nfc_ndef_ch_rec_payload_desc *)ch_rec->payload_descriptor;

	nfc_ndef_msg_clear(ch_payload->local_records);
}

int nfc_ndef_ch_rec_local_record_add(struct nfc_ndef_record_desc *ch_rec,
				     struct nfc_ndef_record_desc *local_rec)
{
	struct nfc_ndef_ch_rec_payload_desc *ch_payload =
		(struct nfc_ndef_ch_rec_payload_desc *)ch_rec->payload_descriptor;

	return nfc_ndef_msg_record_add(ch_payload->local_records, local_rec);
}

int nfc_ndef_ch_hc_rec_payload_constructor(struct nfc_ndef_ch_hc_rec_payload_desc *hc_rec,
					   u8_t *buff, u32_t *len)
{
	u32_t payload_size = nfc_hc_payload_size_get(hc_rec);

	if (!buff) {
		*len = payload_size;
		return 0;
	}

	/* Not enough space in the buffer, return an error. */
	if (payload_size > *len) {
		return -ENOMEM;
	}

	/* Invalid CTF value. */
	if ((hc_rec->ctf < TNF_WELL_KNOWN) ||
	    (hc_rec->ctf > TNF_EXTERNAL_TYPE)) {
		    return -EFAULT;
	}

	*buff = hc_rec->ctf;
	buff += HC_REC_CTF_BYTE_SIZE;

	/* Copy Carrier data */
	*buff = hc_rec->carrier.type_length;
	buff += HC_REC_CARRIER_TYPE_LEN_SIZE;

	memcpy(buff, hc_rec->carrier.type, hc_rec->carrier.type_length);
	buff += hc_rec->carrier.type_length;

	/* Copy Optionall Carrier data. */
	memcpy(buff, hc_rec->carrier.data, hc_rec->carrier.data_length);
	buff += hc_rec->carrier.data_length;

	*len = payload_size;

	return 0;
}

int nfc_ndef_ch_ac_rec_payload_constructor(struct nfc_ndef_ch_ac_rec_payload_desc *nfc_rec_ac_payload_desc,
					   u8_t *buff, u32_t *len)
{
	u32_t payload_size = nfc_ac_rec_payload_size_get(nfc_rec_ac_payload_desc);

	if (!buff) {
		*len = payload_size;
		return 0;
	}

	/* Not enough space in the buffer, return an error. */
	if (payload_size > *len) {
		return -ENOMEM;
	}

	/* Invalid CPS value. */
	if (nfc_rec_ac_payload_desc->cps & ~NFC_NDEF_CH_AC_CPS_MASK) {
		return -EFAULT;
	}

	/* Copy CPS. */
	*buff = nfc_rec_ac_payload_desc->cps;
	buff += AC_REC_CPS_BYTE_SIZE;

	/* Copy Carrier Data Reference. */
	*buff = nfc_rec_ac_payload_desc->carrier_data_ref.length;
	buff += AC_REC_DATA_REF_LEN_SIZE;

	memcpy(buff,
	       nfc_rec_ac_payload_desc->carrier_data_ref.data,
	       nfc_rec_ac_payload_desc->carrier_data_ref.length);
	buff += nfc_rec_ac_payload_desc->carrier_data_ref.length;

	/* Copy Auxiliary Data Reference. */
	*buff = nfc_rec_ac_payload_desc->aux_data_ref_count;
	buff += AC_REC_AUX_DATA_REF_COUNT_SIZE;

	for (size_t i = 0; i < nfc_rec_ac_payload_desc->aux_data_ref_count; i++) {
		*buff = nfc_rec_ac_payload_desc->aux_data_ref[i].length;
		buff += AC_REC_DATA_REF_LEN_SIZE;

		memcpy(buff,
		       nfc_rec_ac_payload_desc->aux_data_ref[i].data,
		       nfc_rec_ac_payload_desc->aux_data_ref[i].length);
		buff += nfc_rec_ac_payload_desc->aux_data_ref[i].length;
	}

	/* Assign payload size to the return buffer. */
	*len = payload_size;

	return 0;
}

void nfc_ndef_ch_ac_rec_auxiliary_data_ref_clear(struct nfc_ndef_record_desc *ac_rec)
{
	struct nfc_ndef_ch_ac_rec_payload_desc *ac_rec_payload =
		(struct nfc_ndef_ch_ac_rec_payload_desc *)ac_rec->payload_descriptor;

	ac_rec_payload->aux_data_ref_count = 0;
}

int nfc_ndef_ch_ac_rec_auxiliary_data_ref_add(struct nfc_ndef_record_desc *ac_rec,
					      u8_t *aux_data, u8_t aux_length)
{
	struct nfc_ndef_ch_ac_rec_payload_desc *ac_rec_payload =
		(struct nfc_ndef_ch_ac_rec_payload_desc *)ac_rec->payload_descriptor;

	if (ac_rec_payload->aux_data_ref_count >= ac_rec_payload->max_aux_data_ref) {
		return -ENOMEM;
	}

	ac_rec_payload->aux_data_ref[ac_rec_payload->aux_data_ref_count].data = aux_data;
	ac_rec_payload->aux_data_ref[ac_rec_payload->aux_data_ref_count].length = aux_length;
	ac_rec_payload->aux_data_ref_count++;

	return 0;
}

int nfc_ndef_ch_cr_rec_payload_constructor(struct nfc_ndef_ch_cr_rec_payload_desc *nfc_rec_cr_payload_desc,
					   u8_t *buff, u32_t *len)
{
	u32_t payload_size = 0;

	if (buff) {
		if (sizeof(nfc_rec_cr_payload_desc->random) > *len) {
			return -ENOMEM;
		}

		sys_put_be16(nfc_rec_cr_payload_desc->random, buff);
		payload_size += sizeof(nfc_rec_cr_payload_desc->random);
	}

	*len = payload_size;

	return 0;
}
