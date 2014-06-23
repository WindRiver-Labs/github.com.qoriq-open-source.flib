/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __DESC_IPSEC_H__
#define __DESC_IPSEC_H__

#include "flib/rta.h"
#include "common.h"

/**
 * DOC: IPsec Shared Descriptor Constructors
 *
 * Shared descriptors for IPsec protocol.
 */

/* General IPSec ESP encap / decap PDB options */

/**
 * PDBOPTS_ESP_ESN - Extended sequence included
 */
#define PDBOPTS_ESP_ESN		0x10

/**
 * PDBOPTS_ESP_IPVSN - Process IPv6 header
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_IPVSN	0x02

/**
 * PDBOPTS_ESP_TUNNEL - Tunnel mode next-header byte
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_TUNNEL	0x01

/* IPSec ESP Encap PDB options */

/**
 * PDBOPTS_ESP_UPDATE_CSUM - Update ip header checksum
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_UPDATE_CSUM 0x80

/**
 * PDBOPTS_ESP_DIFFSERV - Copy TOS/TC from inner iphdr
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_DIFFSERV	0x40

/**
 * PDBOPTS_ESP_IVSRC - IV comes from internal random gen
 */
#define PDBOPTS_ESP_IVSRC	0x20

/**
 * PDBOPTS_ESP_IPHDRSRC - IP header comes from PDB
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_IPHDRSRC	0x08

/**
 * PDBOPTS_ESP_INCIPHDR - Prepend IP header to output frame
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_INCIPHDR	0x04

/**
 * PDBOPTS_ESP_OIHI_MASK - Mask for Outer IP Header Included
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_OIHI_MASK	0x0c

/**
 * PDBOPTS_ESP_OIHI_PDB_INL - Prepend IP header to output frame from PDB (where
 *                            it is inlined).
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_OIHI_PDB_INL 0x0c

/**
 * PDBOPTS_ESP_OIHI_PDB_REF - Prepend IP header to output frame from PDB
 *                            (referenced by pointer).
 *
 * Vlid only for IPsec new mode.
 */
#define PDBOPTS_ESP_OIHI_PDB_REF 0x08

/**
 * PDBOPTS_ESP_OIHI_IF - Prepend IP header to output frame from input frame
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_OIHI_IF	0x04

/**
 * PDBOPTS_ESP_NAT - Enable RFC 3948 UDP-encapsulated-ESP
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_NAT		0x02

/**
 * PDBOPTS_ESP_NUC - Enable NAT UDP Checksum
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_NUC		0x01

/* IPSec ESP Decap PDB options */

/**
 * PDBOPTS_ESP_ARSNONE - No antireplay window
 */
#define PDBOPTS_ESP_ARSNONE	0x00

/**
 * PDBOPTS_ESP_ARS64 - 64-entry antireplay window
 */
#define PDBOPTS_ESP_ARS64	0xc0

/**
 * PDBOPTS_ESP_ARS128 - 128-entry antireplay window
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_ARS128	0x80

/**
 * PDBOPTS_ESP_ARS32 - 32-entry antireplay window
 */
#define PDBOPTS_ESP_ARS32	0x40

/**
 * PDBOPTS_ESP_VERIFY_CSUM - Validate ip header checksum
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_VERIFY_CSUM 0x20

/**
 * PDBOPTS_ESP_TECN - Implement RRFC6040 ECN tunneling from outer header to
 *                    inner header.
 *
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_TECN	0x20

/**
 * PDBOPTS_ESP_OUTFMT - Output only decapsulation
 *
 * Valid only for IPsec legacy mode.
 */
#define PDBOPTS_ESP_OUTFMT	0x08

/**
 * PDBOPTS_ESP_AOFL - Adjust out frame len
 *
 * Valid only for IPsec legacy mode and for SEC >= 5.3.
 */
#define PDBOPTS_ESP_AOFL	0x04

/**
 * PDBOPTS_ESP_ETU - EtherType Update
 *
 * Add corresponding ethertype (0x0800 for IPv4, 0x86dd for IPv6) in the output
 * frame.
 * Valid only for IPsec new mode.
 */
#define PDBOPTS_ESP_ETU		0x01

#define PDBHMO_ESP_DECAP_SHIFT	12
#define PDBHMO_ESP_ENCAP_SHIFT	4

/**
 * PDBHMO_ESP_DECAP_DTTL - IPsec ESP decrement TTL (IPv4) / Hop limit (IPv6)
 *                         HMO option.
 */
#define PDBHMO_ESP_DECAP_DTTL	(0x02 << PDBHMO_ESP_DECAP_SHIFT)

/**
 * PDBHMO_ESP_ENCAP_DTTL - IPsec ESP increment TTL (IPv4) / Hop limit (IPv6)
 *                         HMO option.
 */
#define PDBHMO_ESP_ENCAP_DTTL	(0x02 << PDBHMO_ESP_ENCAP_SHIFT)

/**
 * PDBHMO_ESP_DIFFSERV - (Decap) DiffServ Copy - Copy the IPv4 TOS or IPv6
 *                       Traffic Class byte from the outer IP header to the
 *                       inner IP header.
 */
#define PDBHMO_ESP_DIFFSERV	(0x01 << PDBHMO_ESP_DECAP_SHIFT)

/**
 * PDBHMO_ESP_SNR - (Encap) - Sequence Number Rollover control
 *
 * Configures behaviour in case of SN / ESN rollover:
 * error if SNR = 1, rollover allowed if SNR = 0.
 * Valid only for IPsec new mode.
 */
#define PDBHMO_ESP_SNR		(0x01 << PDBHMO_ESP_ENCAP_SHIFT)

/**
 * PDBHMO_ESP_DFBIT - (Encap) Copy DF bit - if an IPv4 tunnel mode outer IP
 *                    header is coming from the PDB, copy the DF bit from the
 *                    inner IP header to the outer IP header.
 */
#define PDBHMO_ESP_DFBIT	(0x04 << PDBHMO_ESP_ENCAP_SHIFT)

/**
 * PDBHMO_ESP_DFV - (Decap) - DF bit value
 *
 * If ODF = 1, DF bit in output frame is replaced by DFV.
 * Valid only from SEC Era 5 onwards.
 */
#define PDBHMO_ESP_DFV		(0x04 << PDBHMO_ESP_DECAP_SHIFT)

/**
 * PDBHMO_ESP_ODF - (Decap) Override DF bit in IPv4 header of decapsulated
 *                  output frame.
 *
 * If ODF = 1, DF is replaced with the value of DFV bit.
 * Valid only from SEC Era 5 onwards.
 */
#define PDBHMO_ESP_ODF		(0x08 << PDBHMO_ESP_DECAP_SHIFT)

/**
 * struct ipsec_encap_cbc - PDB part for IPsec CBC encapsulation
 * @iv: initialization vector
 */
struct ipsec_encap_cbc {
	uint32_t iv[4];
};


/**
 * struct ipsec_encap_ctr - PDB part for IPsec CTR encapsulation
 * @ctr_nonce: 4-byte nonce
 * @ctr_initial: initial count constant
 * @iv: initialization vector
 */
struct ipsec_encap_ctr {
	uint32_t ctr_nonce;
	uint32_t ctr_initial;
	uint32_t iv[2];
};

/**
 * struct ipsec_encap_ccm - PDB part for IPsec CCM encapsulation
 * @salt: 3-byte salt (lower 24 bits)
 * @b0_flags: CCM B0; managed by SEC
 * @ctr_flags: counter flags; constant equal to 0x3
 * @ctr_initial: initial count constant
 * @iv: initialization vector
 */
struct ipsec_encap_ccm {
	uint32_t salt;
	uint8_t b0_flags;
	uint8_t ctr_flags;
	uint16_t ctr_initial;
	uint32_t iv[2];
};

/**
 * struct ipsec_encap_gcm - PDB part for IPsec GCM encapsulation
 * @salt: 3-byte salt (lower 24 bits)
 * @rsvd1: reserved, do not use
 * @iv: initialization vector
 */
struct ipsec_encap_gcm {
	uint32_t salt;
	uint32_t rsvd1;
	uint32_t iv[2];
};

/**
 * struct ipsec_encap_pdb - PDB for IPsec encapsulation
 * @hmo: header manipulation options
 * @options: option flags; depend on selected algorithm
 * @seq_num_ext_hi: (optional) IPsec Extended Sequence Number (ESN)
 * @seq_num: IPsec sequence number
 * @spi: IPsec SPI (Security Parameters Index)
 * @rsvd2: reserved, do not use
 * @ip_hdr_len: optional IP Header length (in bytes)
 * @ip_hdr: optional IP Header content (only for IPsec legacy mode)
 */
struct ipsec_encap_pdb {
	uint8_t hmo;
	union {
		uint8_t ip_nh;	/* next header for legacy mode */
		uint8_t rsvd;	/* reserved for new mode */
	};
	union {
		uint8_t ip_nh_offset;	/* next header offset for legacy mode */
		uint8_t aoipho;		/* actual outer IP header offset for
					 * new mode */
	};
	uint8_t options;
	uint32_t seq_num_ext_hi;
	uint32_t seq_num;
	union {
		struct ipsec_encap_cbc cbc;
		struct ipsec_encap_ctr ctr;
		struct ipsec_encap_ccm ccm;
		struct ipsec_encap_gcm gcm;
	};
	uint32_t spi;
	uint16_t rsvd2;
	uint16_t ip_hdr_len;
	uint32_t ip_hdr[0];
};

/**
 * struct ipsec_decap_cbc - PDB part for IPsec CBC decapsulation
 * @rsvd: reserved, do not use
 */
struct ipsec_decap_cbc {
	uint32_t rsvd[2];
};

/**
 * struct ipsec_decap_ctr - PDB part for IPsec CTR decapsulation
 * @salt: 4-byte salt
 * @ctr_initial: initial count constant
 */
struct ipsec_decap_ctr {
	uint32_t salt;
	uint32_t ctr_initial;
};

/**
 * struct ipsec_decap_ccm - PDB part for IPsec CCM decapsulation
 * @salt: 3-byte salt (lower 24 bits)
 * @iv_flags: TBD
 * @ctr_flags: counter flags
 * @ctr_initial: initial count constant
 */
struct ipsec_decap_ccm {
	uint32_t salt;
	uint8_t iv_flags;
	uint8_t ctr_flags;
	uint16_t ctr_initial;
};

/**
 * struct ipsec_decap_gcm - PDB part for IPsec GCN decapsulation
 * @salt: 4-byte salt
 * @resvd: reserved, do not used
 */
struct ipsec_decap_gcm {
	uint32_t salt;
	uint32_t resvd;
};

/**
 * struct ipsec_decap_pdb - PDB for IPsec decapsulation
 * @ip_hdr_len: HMO (upper nibble) + IP header length (lower 3 nibbles)
 * @options: option flags; depend on selected algorithm
 * @seq_num_ext_hi: (optional) IPsec Extended Sequence Number (ESN)
 * @seq_num: IPsec sequence number
 * @anti_replay: Anti-replay window bits array
 */
struct ipsec_decap_pdb {
	uint16_t ip_hdr_len;
	union {
		uint8_t ip_nh_offset;	/* next header offset for legacy mode */
		uint8_t aoipho;		/* actual outer IP header offset for
					 * new mode */
	};
	uint8_t options;
	union {
		struct ipsec_decap_cbc cbc;
		struct ipsec_decap_ctr ctr;
		struct ipsec_decap_ccm ccm;
		struct ipsec_decap_gcm gcm;
	};
	uint32_t seq_num_ext_hi;
	uint32_t seq_num;
	uint32_t anti_replay[4];
};

/**
 * enum ipsec_icv_size - Type selectors for icv size in IPsec protocol
 * @IPSEC_ICV_MD5_SIZE: full-length MD5 ICV
 * @IPSEC_ICV_MD5_TRUNC_SIZE: truncated MD5 ICV
 */
enum ipsec_icv_size {
	IPSEC_ICV_MD5_SIZE = 16,
	IPSEC_ICV_MD5_TRUNC_SIZE = 12
};

/*
 * IPSec ESP Datapath Protocol Override Register (DPOVRD)
 */

#define IPSEC_DECO_DPOVRD_USE		0x80

struct ipsec_deco_dpovrd {
	uint8_t ovrd_ecn;
	uint8_t ip_hdr_len;
	uint8_t nh_offset;
	union {
		uint8_t next_header;	/* next header if encap */
		uint8_t rsvd;		/* reserved if decap */
	};
};

struct ipsec_new_encap_deco_dpovrd {
#define IPSEC_NEW_ENCAP_DECO_DPOVRD_USE	0x8000
	uint16_t ovrd_ip_hdr_len;	/* OVRD + outer IP header material
					 * length */
#define IPSEC_NEW_ENCAP_OIMIF		0x80
	uint8_t oimif_aoipho;		/* OIMIF + actual outer IP header
					 * offset */
	uint8_t rsvd;
};

struct ipsec_new_decap_deco_dpovrd {
	uint8_t ovrd;
	uint8_t aoipho_hi;		/* upper nibble of actual outer IP
					 * header */
	uint16_t aoipho_lo_ip_hdr_len;	/* lower nibble of actual outer IP
					 * header + outer IP header material */
};

/**
 * cnstr_shdsc_ipsec_encap - IPSec ESP encapsulation protocol-level shared
 *                           descriptor. Requires an MDHA split key.
 * @descbuf: pointer to buffer used for descriptor construction
 * @bufsize: pointer to descriptor size to be written back upon completion
 * @ps: if 36/40bit addressing is desired, this parameter must be non-zero
 * @pdb: pointer to the PDB to be used with this descriptor
 *       This structure will be copied inline to the descriptor under
 *       construction. No error checking will be made. Refer to the
 *       block guide for a details of the encapsulation PDB.
 * @cipherdata: pointer to block cipher transform definitions
 *              Valid algorithm values - one of OP_PCL_IPSEC_*
 * @authdata: pointer to authentication transform definitions. Note that since a
 *            split key is to be used, the size of the split key itself is
 *            specified. Valid algorithm values - one of OP_PCL_IPSEC_*
 */
static inline void cnstr_shdsc_ipsec_encap(uint32_t *descbuf,
					   unsigned *bufsize,
					   unsigned short ps,
					   struct ipsec_encap_pdb *pdb,
					   struct alginfo *cipherdata,
					   struct alginfo *authdata)
{
	struct program prg;
	struct program *program = &prg;

	LABEL(keyjmp);
	REFERENCE(pkeyjmp);
	LABEL(hdr);
	REFERENCE(phdr);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	phdr = SHR_HDR(SHR_SERIAL, hdr, 0);
	COPY_DATA((uint8_t *)pdb,
		  sizeof(struct ipsec_encap_pdb) + pdb->ip_hdr_len);
	SET_LABEL(hdr);
	pkeyjmp = JUMP(IMM(keyjmp), LOCAL_JUMP, ALL_TRUE, BOTH|SHRD);
	KEY(MDHA_SPLIT_KEY, authdata->key_enc_flags, PTR(authdata->key),
	    authdata->keylen, IMMED);
	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, IMMED);
	SET_LABEL(keyjmp);
	PROTOCOL(OP_TYPE_ENCAP_PROTOCOL,
		 OP_PCLID_IPSEC,
		 (uint16_t)(cipherdata->algtype | authdata->algtype));
	PATCH_JUMP(pkeyjmp, keyjmp);
	PATCH_HDR(phdr, hdr);
	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_ipsec_decap - IPSec ESP decapsulation protocol-level sharedesc
 *                           Requires an MDHA split key.
 * @descbuf: pointer to buffer used for descriptor construction
 * @bufsize: pointer to descriptor size to be written back upon completion
 * @ps: if 36/40bit addressing is desired, this parameter must be non-zero
 * @pdb: pointer to the PDB to be used with this descriptor
 *       This structure will be copied inline to the descriptor under
 *       construction. No error checking will be made. Refer to the
 *       block guide for details about the decapsulation PDB.
 * @cipherdata: pointer to block cipher transform definitions.
 *              Valid algorithm values - one of OP_PCL_IPSEC_*
 * @authdata: pointer to authentication transform definitions. Note that since a
 *            split key is to be used, the size of the split key itself is
 *            specified. Valid algorithm values - one of OP_PCL_IPSEC_*
 */
static inline void cnstr_shdsc_ipsec_decap(uint32_t *descbuf,
					   unsigned *bufsize,
					   unsigned short ps,
					   struct ipsec_decap_pdb *pdb,
					   struct alginfo *cipherdata,
					   struct alginfo *authdata)
{
	struct program prg;
	struct program *program = &prg;

	LABEL(keyjmp);
	REFERENCE(pkeyjmp);
	LABEL(hdr);
	REFERENCE(phdr);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	phdr = SHR_HDR(SHR_SERIAL, hdr, 0);
	COPY_DATA((uint8_t *)pdb, sizeof(struct ipsec_decap_pdb));
	SET_LABEL(hdr);
	pkeyjmp = JUMP(IMM(keyjmp), LOCAL_JUMP, ALL_TRUE, BOTH|SHRD);
	KEY(MDHA_SPLIT_KEY, authdata->key_enc_flags, PTR(authdata->key),
	    authdata->keylen, IMMED);
	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, IMMED);
	SET_LABEL(keyjmp);
	PROTOCOL(OP_TYPE_DECAP_PROTOCOL,
		 OP_PCLID_IPSEC,
		 (uint16_t)(cipherdata->algtype | authdata->algtype));
	PATCH_JUMP(pkeyjmp, keyjmp);
	PATCH_HDR(phdr, hdr);
	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_ipsec_encap_des_aes_xcbc - IPSec DES-CBC/3DES-CBC and
 *     AES-XCBC-MAC-96 ESP encapsulation shared descriptor.
 * @descbuf: pointer to buffer used for descriptor construction
 * @bufsize: pointer to descriptor size to be written back upon completion
 * @pdb: pointer to the PDB to be used with this descriptor
 *       This structure will be copied inline to the descriptor under
 *       construction. No error checking will be made. Refer to the
 *       block guide for a details of the encapsulation PDB.
 * @cipherdata: pointer to block cipher transform definitions
 *              Valid algorithm values - OP_PCL_IPSEC_DES, OP_PCL_IPSEC_3DES.
 * @authdata: pointer to authentication transform definitions
 *            Valid algorithm value: OP_PCL_IPSEC_AES_XCBC_MAC_96.
 *
 * Supported only for platforms with 32-bit address pointers and SEC ERA 4 or
 * higher. The tunnel/transport mode of the IPsec ESP is supported only if the
 * Outer/Transport IP Header is present in the encapsulation output packet.
 * The descriptor performs DES-CBC/3DES-CBC & HMAC-MD5-96 and then rereads
 * the input packet to do the AES-XCBC-MAC-96 calculation and to overwrite
 * the MD5 ICV.
 * The descriptor uses all the benefits of the built-in protocol by computing
 * the IPsec ESP with a hardware supported algorithms combination
 * (DES-CBC/3DES-CBC & HMAC-MD5-96). The HMAC-MD5 authentication algorithm
 * was chosen in order to speed up the computational time for this intermediate
 * step.
 * Warning: The user must allocate at least 32 bytes for the authentication key
 * (in order to use it also with HMAC-MD5-96),even when using a shorter key
 * for the AES-XCBC-MAC-96.
 */
static inline void cnstr_shdsc_ipsec_encap_des_aes_xcbc(uint32_t *descbuf,
		unsigned *bufsize, struct ipsec_encap_pdb *pdb,
		struct alginfo *cipherdata, struct alginfo *authdata)
{
	struct program prg;
	struct program *program = &prg;

	LABEL(hdr);
	LABEL(shd_ptr);
	LABEL(keyjump);
	LABEL(outptr);
	LABEL(swapped_seqin_fields);
	LABEL(swapped_seqin_ptr);
	REFERENCE(phdr);
	REFERENCE(pkeyjump);
	REFERENCE(move_outlen);
	REFERENCE(move_seqout_ptr);
	REFERENCE(swapped_seqin_ptr_jump);
	REFERENCE(write_swapped_seqin_ptr);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	phdr = SHR_HDR(SHR_SERIAL, hdr, 0);
	COPY_DATA((uint8_t *)pdb,
		  sizeof(struct ipsec_encap_pdb) + pdb->ip_hdr_len);
	SET_LABEL(hdr);
	pkeyjump = JUMP(IMM(keyjump), LOCAL_JUMP, ALL_TRUE, SHRD | SELF);
	/*
	 * Hard-coded KEY arguments. The descriptor uses all the benefits of
	 * the built-in protocol by computing the IPsec ESP with a hardware
	 * supported algorithms combination (DES-CBC/3DES-CBC & HMAC-MD5-96).
	 * The HMAC-MD5 authentication algorithm was chosen with
	 * the keys options from below in order to speed up the computational
	 * time for this intermediate step.
	 * Warning: The user must allocate at least 32 bytes for
	 * the authentication key (in order to use it also with HMAC-MD5-96),
	 * even when using a shorter key for the AES-XCBC-MAC-96.
	 */
	KEY(MDHA_SPLIT_KEY, 0, PTR(authdata->key), 32, 0);
	SET_LABEL(keyjump);
	LOAD(IMM(LDST_SRCDST_WORD_CLRW | CLRW_CLR_C1MODE | CLRW_CLR_C1DATAS |
		 CLRW_CLR_C1CTX | CLRW_CLR_C1KEY | CLRW_RESET_CLS1_CHA),
	     CLRW, 0, 4, 0);
	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, 0);
	PROTOCOL(OP_TYPE_ENCAP_PROTOCOL, OP_PCLID_IPSEC,
		 (uint16_t)(cipherdata->algtype | OP_PCL_IPSEC_HMAC_MD5_96));
	/* Swap SEQINPTR to SEQOUTPTR. */
	move_seqout_ptr = MOVE(DESCBUF, 0, MATH1, 0, IMM(16), WAITCOMP);
	MATHB(MATH1, AND, IMM(~(CMD_SEQ_IN_PTR ^ CMD_SEQ_OUT_PTR)), MATH1,
	      8, IFB);
/*
 * TODO: RTA currently doesn't support creating a LOAD command
 * with another command as IMM.
 * To be changed when proper support is added in RTA.
 */
	LOAD(IMM(0xa00000e5), MATH3, 4, 4, 0);
	MATHB(MATH3, SHLD, MATH3, MATH3,  8, 0);
	write_swapped_seqin_ptr = MOVE(MATH1, 0, DESCBUF, 0, IMM(20), WAITCOMP);
	swapped_seqin_ptr_jump = JUMP(IMM(swapped_seqin_ptr), LOCAL_JUMP,
				      ALL_TRUE, 0);
	LOAD(IMM(LDST_SRCDST_WORD_CLRW | CLRW_CLR_C1MODE | CLRW_CLR_C1DATAS |
		 CLRW_CLR_C1CTX | CLRW_CLR_C1KEY | CLRW_RESET_CLS1_CHA),
	     CLRW, 0, 4, 0);
	SEQOUTPTR(0, 65535, RTO);
	move_outlen = MOVE(DESCBUF, 0, MATH0, 4, IMM(8), WAITCOMP);
	MATHB(MATH0, SUB,
	      IMM((uint64_t)(pdb->ip_hdr_len + IPSEC_ICV_MD5_TRUNC_SIZE)),
	      VSEQINSZ, 4, 0);
	MATHB(MATH0, SUB, IMM(IPSEC_ICV_MD5_TRUNC_SIZE), VSEQOUTSZ, 4, 0);
	KEY(KEY1, authdata->key_enc_flags, PTR(authdata->key), authdata->keylen,
	    0);
	ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_XCBC_MAC,
		      OP_ALG_AS_INITFINAL, ICV_CHECK_DISABLE, OP_ALG_ENCRYPT);
	SEQFIFOLOAD(SKIP, pdb->ip_hdr_len, 0);
	SEQFIFOLOAD(MSG1, 0, VLF | FLUSH1 | LAST1);
	SEQFIFOSTORE(SKIP, 0, 0, VLF);
	SEQSTORE(CONTEXT1, 0, IPSEC_ICV_MD5_TRUNC_SIZE, 0);
/*
 * TODO: RTA currently doesn't support adding labels in or after Job Descriptor.
 * To be changed when proper support is added in RTA.
 */
	/* Label the Shared Descriptor Pointer */
	SET_LABEL(shd_ptr);
	shd_ptr += 1;
	/* Label the Output Pointer */
	SET_LABEL(outptr);
	outptr += 3;
	/* Label the first word after JD */
	SET_LABEL(swapped_seqin_fields);
	swapped_seqin_fields += 8;
	/* Label the second word after JD */
	SET_LABEL(swapped_seqin_ptr);
	swapped_seqin_ptr += 9;

	PATCH_HDR(phdr, hdr);
	PATCH_JUMP(pkeyjump, keyjump);
	PATCH_JUMP(swapped_seqin_ptr_jump, swapped_seqin_ptr);
	PATCH_MOVE(move_outlen, outptr);
	PATCH_MOVE(move_seqout_ptr, shd_ptr);
	PATCH_MOVE(write_swapped_seqin_ptr, swapped_seqin_fields);
	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_ipsec_decap_des_aes_xcbc - IPSec DES-CBC/3DES-CBC and
 *     AES-XCBC-MAC-96 ESP decapsulation shared descriptor.
 * @descbuf: pointer to buffer used for descriptor construction
 * @bufsize: pointer to descriptor size to be written back upon completion
 * @pdb: pointer to the PDB to be used with this descriptor
 *       This structure will be copied inline to the descriptor under
 *       construction. No error checking will be made. Refer to the
 *       block guide for a details of the encapsulation PDB.
 * @cipherdata: pointer to block cipher transform definitions
 *              Valid algorithm values - OP_PCL_IPSEC_DES, OP_PCL_IPSEC_3DES.
 * @authdata: pointer to authentication transform definitions
 *            Valid algorithm value: OP_PCL_IPSEC_AES_XCBC_MAC_96.
 *
 * Supported only for platforms with 32-bit address pointers and SEC ERA 4 or
 * higher. The tunnel/transport mode of the IPsec ESP is supported only if the
 * Outer/Transport IP Header is present in the decapsulation input packet.
 * The descriptor computes the AES-XCBC-MAC-96 to check if the received ICV
 * is correct, rereads the input packet to compute the MD5 ICV, overwrites
 * the XCBC ICV, and then sends the modified input packet to the
 * DES-CBC/3DES-CBC & HMAC-MD5-96 IPsec.
 * The descriptor uses all the benefits of the built-in protocol by computing
 * the IPsec ESP with a hardware supported algorithms combination
 * (DES-CBC/3DES-CBC & HMAC-MD5-96). The HMAC-MD5 authentication algorithm
 * was chosen in order to speed up the computational time for this intermediate
 * step.
 * Warning: The user must allocate at least 32 bytes for the authentication key
 * (in order to use it also with HMAC-MD5-96),even when using a shorter key
 * for the AES-XCBC-MAC-96.
 */
static inline void cnstr_shdsc_ipsec_decap_des_aes_xcbc(uint32_t *descbuf,
		unsigned *bufsize, struct ipsec_decap_pdb *pdb,
		struct alginfo *cipherdata, struct alginfo *authdata)
{
	struct program prg;
	struct program *program = &prg;

	LABEL(hdr);
	LABEL(jump_cmd);
	LABEL(keyjump);
	LABEL(outlen);
	LABEL(seqin_ptr);
	LABEL(seqout_ptr);
	LABEL(swapped_seqout_fields);
	LABEL(swapped_seqout_ptr);
	REFERENCE(seqout_ptr_jump);
	REFERENCE(phdr);
	REFERENCE(pkeyjump);
	REFERENCE(move_jump);
	REFERENCE(move_jump_back);
	REFERENCE(move_seqin_ptr);
	REFERENCE(swapped_seqout_ptr_jump);
	REFERENCE(write_swapped_seqout_ptr);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	phdr = SHR_HDR(SHR_SERIAL, hdr, 0);
	COPY_DATA((uint8_t *)pdb, sizeof(struct ipsec_decap_pdb));
	SET_LABEL(hdr);
	pkeyjump = JUMP(IMM(keyjump), LOCAL_JUMP, ALL_TRUE, SHRD | SELF);
	/*
	 * Hard-coded KEY arguments. The descriptor uses all the benefits of
	 * the built-in protocol by computing the IPsec ESP with a hardware
	 * supported algorithms combination (DES-CBC/3DES-CBC & HMAC-MD5-96).
	 * The HMAC-MD5 authentication algorithm was chosen with
	 * the keys options from bellow in order to speed up the computational
	 * time for this intermediate step.
	 * Warning: The user must allocate at least 32 bytes for
	 * the authentication key (in order to use it also with HMAC-MD5-96),
	 * even when using a shorter key for the AES-XCBC-MAC-96.
	 */
	KEY(MDHA_SPLIT_KEY, 0, PTR(authdata->key), 32, 0);
	SET_LABEL(keyjump);
	LOAD(IMM(LDST_SRCDST_WORD_CLRW | CLRW_CLR_C1MODE | CLRW_CLR_C1DATAS |
		 CLRW_CLR_C1CTX | CLRW_CLR_C1KEY | CLRW_RESET_CLS1_CHA),
	     CLRW, 0, 4, 0);
	KEY(KEY1, authdata->key_enc_flags, PTR(authdata->key), authdata->keylen,
	    0);
	MATHB(SEQINSZ, SUB,
	      IMM((uint64_t)(pdb->ip_hdr_len + IPSEC_ICV_MD5_TRUNC_SIZE)),
	      MATH0, 4, 0);
	MATHB(MATH0, SUB, ZERO, VSEQINSZ, 4, 0);
	ALG_OPERATION(OP_ALG_ALGSEL_MD5, OP_ALG_AAI_HMAC_PRECOMP,
		      OP_ALG_AS_INITFINAL, ICV_CHECK_DISABLE, OP_ALG_ENCRYPT);
	ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_XCBC_MAC,
		      OP_ALG_AS_INITFINAL, ICV_CHECK_ENABLE, OP_ALG_DECRYPT);
	SEQFIFOLOAD(SKIP, pdb->ip_hdr_len, 0);
	SEQFIFOLOAD(MSG1, 0, VLF | FLUSH1);
	SEQFIFOLOAD(ICV1, IPSEC_ICV_MD5_TRUNC_SIZE, FLUSH1 | LAST1);
	/* Swap SEQOUTPTR to SEQINPTR. */
	move_seqin_ptr = MOVE(DESCBUF, 0, MATH1, 0, IMM(16), WAITCOMP);
	MATHB(MATH1, OR, IMM(CMD_SEQ_IN_PTR ^ CMD_SEQ_OUT_PTR), MATH1, 8,
	      IFB);
/*
 * TODO: RTA currently doesn't support creating a LOAD command
 * with another command as IMM.
 * To be changed when proper support is added in RTA.
 */
	LOAD(IMM(0xA00000e1), MATH3, 4, 4, 0);
	MATHB(MATH3, SHLD, MATH3, MATH3,  8, 0);
	write_swapped_seqout_ptr = MOVE(MATH1, 0, DESCBUF, 0, IMM(20),
					WAITCOMP);
	swapped_seqout_ptr_jump = JUMP(IMM(swapped_seqout_ptr), LOCAL_JUMP,
				       ALL_TRUE, 0);
/*
 * TODO: To be changed when proper support is added in RTA (can't load
 * a command that is also written by RTA).
 * Change when proper RTA support is added.
 */
	SET_LABEL(jump_cmd);
	WORD(0xA00000f3);
	SEQINPTR(0, 65535, RTO);
	MATHB(MATH0, SUB, ZERO, VSEQINSZ, 4, 0);
	MATHB(MATH0, ADD, IMM(pdb->ip_hdr_len), VSEQOUTSZ, 4, 0);
	move_jump = MOVE(DESCBUF, 0, OFIFO, 0, IMM(8), WAITCOMP);
	move_jump_back = MOVE(OFIFO, 0, DESCBUF, 0, IMM(8), 0);
	SEQFIFOLOAD(SKIP, pdb->ip_hdr_len, 0);
	SEQFIFOLOAD(MSG2, 0, VLF | LAST2);
	SEQFIFOSTORE(SKIP, 0, 0, VLF);
	SEQSTORE(CONTEXT2, 0, IPSEC_ICV_MD5_TRUNC_SIZE, 0);
	seqout_ptr_jump = JUMP(IMM(seqout_ptr), LOCAL_JUMP, ALL_TRUE, CALM);

	LOAD(IMM(LDST_SRCDST_WORD_CLRW | CLRW_CLR_C1MODE | CLRW_CLR_C1DATAS |
		 CLRW_CLR_C1CTX | CLRW_CLR_C1KEY | CLRW_CLR_C2MODE |
		 CLRW_CLR_C2DATAS | CLRW_CLR_C2CTX | CLRW_RESET_CLS1_CHA),
	     CLRW, 0, 4, 0);
	SEQINPTR(0, 65535, RTO);
	MATHB(MATH0, ADD,
	      IMM((uint64_t)(pdb->ip_hdr_len + IPSEC_ICV_MD5_TRUNC_SIZE)),
	      SEQINSZ, 4, 0);
	KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
	    cipherdata->keylen, 0);
	PROTOCOL(OP_TYPE_DECAP_PROTOCOL, OP_PCLID_IPSEC,
		 (uint16_t)(cipherdata->algtype | OP_PCL_IPSEC_HMAC_MD5_96));
/*
 * TODO: RTA currently doesn't support adding labels in or after Job Descriptor.
 * To be changed when proper support is added in RTA.
 */
	/* Label the SEQ OUT PTR */
	SET_LABEL(seqout_ptr);
	seqout_ptr += 2;
	/* Label the Output Length */
	SET_LABEL(outlen);
	outlen += 4;
	/* Label the SEQ IN PTR */
	SET_LABEL(seqin_ptr);
	seqin_ptr += 5;
	/* Label the first word after JD */
	SET_LABEL(swapped_seqout_fields);
	swapped_seqout_fields += 8;
	/* Label the second word after JD */
	SET_LABEL(swapped_seqout_ptr);
	swapped_seqout_ptr += 9;

	PATCH_HDR(phdr, hdr);
	PATCH_JUMP(pkeyjump, keyjump);
	PATCH_JUMP(seqout_ptr_jump, seqout_ptr);
	PATCH_JUMP(swapped_seqout_ptr_jump, swapped_seqout_ptr);
	PATCH_MOVE(move_jump, jump_cmd);
	PATCH_MOVE(move_jump_back, seqin_ptr);
	PATCH_MOVE(move_seqin_ptr, outlen);
	PATCH_MOVE(write_swapped_seqout_ptr, swapped_seqout_fields);
	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_ipsec_new_encap -  IPSec new mode ESP encapsulation
 *     protocol-level shared descriptor. If an authentication key is required by
 *     the protocol, it must be a MDHA split key.
 * @descbuf: pointer to buffer used for descriptor construction
 * @bufsize: pointer to descriptor size to be written back upon completion
 * @ps: if 36/40bit addressing is desired, this parameter must be non-zero
 * @pdb: pointer to the PDB to be used with this descriptor
 *       This structure will be copied inline to the descriptor under
 *       construction. No error checking will be made. Refer to the
 *       block guide for details about the encapsulation PDB.
 * @opt_ip_hdr:  pointer to Optional IP Header
 *     -if OIHI = PDBOPTS_ESP_OIHI_PDB_INL, opt_ip_hdr points to the buffer to
 *     be inlined in the PDB. Number of bytes (buffer size) copied is provided
 *     in pdb->ip_hdr_len.
 *     -if OIHI = PDBOPTS_ESP_OIHI_PDB_REF, opt_ip_hdr points to the address of
 *     the Optional IP Header. The address will be inlined in the PDB verbatim.
 *     -for other values of OIHI options field, opt_ip_hdr is not used.
 * @cipherdata: pointer to block cipher transform definitions
 *              Valid algorithm values - one of OP_PCL_IPSEC_*
 * @authdata: pointer to authentication transform definitions. Note that since a
 *            split key is to be used, the size of the split key itself is
 *            specified. Valid algorithm values - one of OP_PCL_IPSEC_*
 */
static inline void cnstr_shdsc_ipsec_new_encap(uint32_t *descbuf,
					       unsigned *bufsize,
					       unsigned short ps,
					       struct ipsec_encap_pdb *pdb,
					       uint8_t *opt_ip_hdr,
					       struct alginfo *cipherdata,
					       struct alginfo *authdata)
{
	struct program prg;
	struct program *program = &prg;

	LABEL(keyjmp);
	REFERENCE(pkeyjmp);
	LABEL(hdr);
	REFERENCE(phdr);

	if (rta_sec_era < RTA_SEC_ERA_8) {
		pr_err("IPsec new mode encap: available only for Era %d or above\n",
		       USER_SEC_ERA(RTA_SEC_ERA_8));
		*bufsize = 0;
		return;
	}

	PROGRAM_CNTXT_INIT(descbuf, 0);
	PROGRAM_SET_BSWAP();
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	phdr = SHR_HDR(SHR_SERIAL, hdr, 0);

	COPY_DATA((uint8_t *)pdb, sizeof(struct ipsec_encap_pdb));

	switch (pdb->options & PDBOPTS_ESP_OIHI_MASK) {
	case PDBOPTS_ESP_OIHI_PDB_INL:
		COPY_DATA(opt_ip_hdr, pdb->ip_hdr_len);
		break;
	case PDBOPTS_ESP_OIHI_PDB_REF:
		if (ps)
			COPY_DATA(opt_ip_hdr, BYTES_8);
		else
			COPY_DATA(opt_ip_hdr, BYTES_4);
		break;
	default:
		break;
	}
	SET_LABEL(hdr);

	pkeyjmp = JUMP(IMM(keyjmp), LOCAL_JUMP, ALL_TRUE, SHRD);
	if (authdata->keylen)
		KEY(MDHA_SPLIT_KEY, authdata->key_enc_flags, PTR(authdata->key),
		    authdata->keylen, 0);
	if (cipherdata->keylen)
		KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
		    cipherdata->keylen, 0);
	SET_LABEL(keyjmp);
	PROTOCOL(OP_TYPE_ENCAP_PROTOCOL,
		 OP_PCLID_IPSEC_NEW,
		 (uint16_t)(cipherdata->algtype | authdata->algtype));
	PATCH_JUMP(pkeyjmp, keyjmp);
	PATCH_HDR(phdr, hdr);
	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_ipsec_new_decap - IPSec new mode ESP decapsulation protocol-level
 *     shared descriptor. If an authentication key is required by the protocol,
 *     it must be a MDHA split key.
 * @descbuf: pointer to buffer used for descriptor construction
 * @bufsize: pointer to descriptor size to be written back upon completion
 * @ps: if 36/40bit addressing is desired, this parameter must be non-zero
 * @pdb: pointer to the PDB to be used with this descriptor
 *       This structure will be copied inline to the descriptor under
 *       construction. No error checking will be made. Refer to the
 *       block guide for details about the decapsulation PDB.
 * @cipherdata: pointer to block cipher transform definitions
 *              Valid algorithm values 0 one of OP_PCL_IPSEC_*
 * @authdata: pointer to authentication transform definitions. Note that since a
 *            split key is to be used, the size of the split key itself is
 *            specified. Valid algorithm values - one of OP_PCL_IPSEC_*
 */
static inline void cnstr_shdsc_ipsec_new_decap(uint32_t *descbuf,
					       unsigned *bufsize,
					       unsigned short ps,
					       struct ipsec_decap_pdb *pdb,
					       struct alginfo *cipherdata,
					       struct alginfo *authdata)
{
	struct program prg;
	struct program *program = &prg;

	LABEL(keyjmp);
	REFERENCE(pkeyjmp);
	LABEL(hdr);
	REFERENCE(phdr);

	if (rta_sec_era < RTA_SEC_ERA_8) {
		pr_err("IPsec new mode decap: available only for Era %d or above\n",
		       USER_SEC_ERA(RTA_SEC_ERA_8));
		*bufsize = 0;
		return;
	}

	PROGRAM_CNTXT_INIT(descbuf, 0);
	PROGRAM_SET_BSWAP();
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	phdr = SHR_HDR(SHR_SERIAL, hdr, 0);
	COPY_DATA((uint8_t *)pdb, sizeof(struct ipsec_decap_pdb));
	SET_LABEL(hdr);
	pkeyjmp = JUMP(IMM(keyjmp), LOCAL_JUMP, ALL_TRUE, SHRD);
	if (authdata->keylen)
		KEY(MDHA_SPLIT_KEY, authdata->key_enc_flags, PTR(authdata->key),
		    authdata->keylen, 0);
	if (cipherdata->keylen)
		KEY(KEY1, cipherdata->key_enc_flags, PTR(cipherdata->key),
		    cipherdata->keylen, 0);
	SET_LABEL(keyjmp);
	PROTOCOL(OP_TYPE_DECAP_PROTOCOL,
		 OP_PCLID_IPSEC_NEW,
		 (uint16_t)(cipherdata->algtype | authdata->algtype));
	PATCH_JUMP(pkeyjmp, keyjmp);
	PATCH_HDR(phdr, hdr);
	*bufsize = PROGRAM_FINALIZE();
}

#endif /* __DESC_IPSEC_H__ */
