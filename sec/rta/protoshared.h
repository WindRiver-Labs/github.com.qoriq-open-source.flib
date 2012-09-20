/*
 * CAAM Descriptor Construction Library
 * Protocol-level Shared Descriptor Constructors
 */
/* Copyright 2012 Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 documentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to endorse or promote products
 *	 derived from this software without specific prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __RTA_PROTOSHARED_H__
#define __RTA_PROTOSHARED_H__

#include "rta.h"

/*
 * SNOW/f8 (UEA2) as a shared descriptor
 *
 * @descbuf - pointer to descriptor-under-construction buffer
 * @bufsize - points to size to be updated at completion
 * @cipherkey - cipher key
 * @keylen  - size of key in bits
 * @dir     - cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count   - UEA2 count value (32 bits)
 * @bearer  - UEA2 bearer ID (5 bits)
 * @direction - UEA2 direction (1 bit)
 */
static inline void cnstr_shdsc_snow_f8(uint32_t *descbuf, uint16_t *bufsize,
			 uint8_t *cipherkey, uint32_t keylen,
			 uint8_t dir, uint32_t count,
			 uint8_t bearer, uint8_t direction)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;
	uint64_t ct = count;
	uint64_t br = bearer;
	uint64_t dr = direction;
	uint64_t context = (ct << 32) | (br << 27) | (dr << 26);

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, 0);
	{
		KEY(KEY1, 0, IMM((uintptr_t)cipherkey), keylen, 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, SIZE(4), 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SNOW_F8, OP_ALG_AAI_F8,
			      OP_ALG_AS_INITFINAL, 0, dir);
		LOAD(IMM(context), CONTEXT1, 0, SIZE(8), 0);
		SEQFIFOLOAD(MSG1, SIZE(32), WITH(VLF | LAST1 | LAST2));
		SEQFIFOSTORE(MSG, 0, SIZE(32), WITH(VLF));
	}
	*bufsize = PROGRAM_FINALIZE();
}

/*
 * SNOW/f9 (UIA2) as a shared descriptor
 *
 * @descbuf - pointer to descriptor-under-construction buffer
 * @bufsize - points to size to be updated at completion
 * @bufsize - points to size to be updated at completion
 * @cipherkey - cipher key
 * @keylen  - size of key in bits
 * @dir     - cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count   - UEA2 count value (32 bits)
 * @fresh   - UEA2 fresh value ID (32 bits)
 * @direction - UEA2 direction (1 bit)
 */
static inline void cnstr_shdsc_snow_f9(uint32_t *descbuf, uint16_t *bufsize,
			 uint8_t *cipherkey, uint32_t keylen,
			 uint8_t dir, uint32_t count,
			 uint32_t fresh, uint8_t direction,
			 uint32_t datalen)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;
	uint64_t ct = count;
	uint64_t fr = fresh;
	uint64_t dr = direction;
	uint64_t context[2];

	context[0] = (ct << 32) | (dr << 26);
	context[1] = fr << 32;

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, 0);
	{
		KEY(KEY2, 0, IMM((uintptr_t)cipherkey), keylen, 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SNOW_F9, OP_ALG_AAI_F9,
			      OP_ALG_AS_INITFINAL, 0, dir);
		LOAD(PTR((uintptr_t)context), CONTEXT2, 0, SIZE(16), IMMED);
		SEQFIFOLOAD(BIT_DATA, datalen, WITH(CLASS2 | LAST1 | LAST2));
		/* Save lower half of MAC out into a 32-bit sequence */
		SEQSTORE(CONTEXT2, 0, SIZE(4), 0);
	}
	*bufsize = PROGRAM_FINALIZE();
}

/*
 * CBC blockcipher
 * @descbuf - descriptor buffer
 * @bufsize - limit/returned descriptor buffer size
 * @cipherkey - key data to inline
 * @keylen  - key length
 * @iv      - iv data
 * @ivsize  - iv length
 * @dir     - DIR_ENCRYPT/DIR_DECRYPT
 * @cipher  - OP_ALG_ALGSEL_AES/DES/3DES
 */
static inline void cnstr_shdsc_cbc_blkcipher(uint32_t *descbuf, uint16_t *bufsize,
			       uint8_t *cipherkey, uint32_t keylen,
			       uint8_t *iv, uint32_t ivlen,
			       uint8_t dir, uint32_t cipher)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, HDR_SAVECTX);
	{
		/* Insert Key */
		KEY(KEY1, 0, IMM((uintptr_t)cipherkey), keylen, 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, SIZE(4), 0);
		ALG_OPERATION(cipher, OP_ALG_AAI_CBC, OP_ALG_AS_INIT, 0, dir);
		/* IV load, convert size */
		LOAD(PTR((uintptr_t)iv), CONTEXT1, 0, ivlen, IMMED);
		/* Insert sequence load/store with VLF */
		SEQFIFOLOAD(MSG1, SIZE(32), WITH(VLF | LAST1 | LAST2));
		SEQFIFOSTORE(MSG, 0, SIZE(32), WITH(VLF));
	}
	*bufsize = PROGRAM_FINALIZE();
}

/*
 * HMAC shared
 * @descbuf - descriptor buffer
 * @bufsize - limit/returned descriptor buffer size
 * @md_key  - key data to inline (length based on message digest algorithm)
 * @md_algo - message digest algorithm: OP_ALG_ALGSEL_MD5/SHA1-512
 * @icv     - HMAC comparison for ICV, NULL if no check desired
 */
static inline void cnstr_shdsc_hmac(uint32_t *descbuf, uint16_t *bufsize,
		      uint8_t *md_key, uint32_t md_algo, uint8_t *icv)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;
	uint8_t storelen;
	uint8_t opicv;

	/* Compute fixed-size store based on alg selection */
	switch (md_algo) {
	case OP_ALG_ALGSEL_MD5:
		storelen = 16;
		break;
	case OP_ALG_ALGSEL_SHA1:
		storelen = 20;
		break;
	case OP_ALG_ALGSEL_SHA224:
		storelen = 28;
		break;
	case OP_ALG_ALGSEL_SHA256:
		storelen = 32;
		break;
	case OP_ALG_ALGSEL_SHA384:
		storelen = 48;
		break;
	case OP_ALG_ALGSEL_SHA512:
		storelen = 64;
		break;
	default:
		return;
	}

	opicv = icv ? ICV_CHECK_ENABLE : ICV_CHECK_DISABLE;

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, HDR_SAVECTX);
	{
		KEY(KEY2, 0, IMM((uintptr_t)md_key), storelen, 0);
		/* compute sequences */
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, SIZE(4), 0);
		/* Do operation */
		ALG_OPERATION(md_algo, OP_ALG_AAI_HMAC, OP_ALG_AS_INITFINAL,
			      opicv, DIR_ENC);
		/* Do load (variable length) */
		SEQFIFOLOAD(MSG2, SIZE(32), WITH(VLF | LAST1 | LAST2));
		SEQSTORE(CONTEXT2, 0, storelen, 0);
	}
	*bufsize = PROGRAM_FINALIZE();
}

/*
 * KASUMI F8 (Confidentialy) as a shared descriptor
 * (ETSI "Document 1: f8 and f9 specification")
 *
 * @descbuf - pointer to descriptor-under-construction buffer
 * @bufsize - points to size to be updated at completion
 * @cipherkey - cipher key
 * @keylen  - size of key in bits
 * @dir     - cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count   - count value (32 bits)
 * @bearer  - bearer ID (5 bits)
 * @direction - direction (1 bit)
 */
static inline void cnstr_shdsc_kasumi_f8(uint32_t *descbuf, uint16_t *bufsize,
			   uint8_t *cipherkey, uint32_t keylen,
			   uint8_t dir, uint32_t count,
			   uint8_t bearer, uint8_t direction)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;
	uint64_t ct = count;
	uint64_t br = bearer;
	uint64_t dr = direction;
	uint64_t context = (ct << 32) | (br << 27) | (dr << 26);

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, 0);
	{
		KEY(KEY1, 0, IMM((uintptr_t)cipherkey), keylen, 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQOUTSZ, SIZE(4), 0);
		ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_F8,
			      OP_ALG_AS_INITFINAL, 0, dir);
		LOAD(IMM(context), CONTEXT1, 0, SIZE(8), 0);
		SEQFIFOLOAD(MSG1, SIZE(32), WITH(VLF | LAST1 | LAST2));
		SEQFIFOSTORE(MSG, 0, SIZE(32), WITH(VLF));
	}
	*bufsize = PROGRAM_FINALIZE();
}

/*
 * KASUMI F9 (Integrity) as a shared descriptor
 * (ETSI "Document 1: f8 and f9 specification")
 *
 * @descbuf - pointer to descriptor-under-construction buffer
 * @bufsize - points to size to be updated at completion
 * @cipherkey - cipher key
 * @keylen  - size of key in bits
 * @dir     - cipher direction (DIR_ENCRYPT/DIR_DECRYPT)
 * @count   - count value (32 bits)
 * @fresh   - fresh value ID (32 bits)
 * @direction - direction (1 bit)
 * @datalen - size of data in bits
 */
static inline void cnstr_shdsc_kasumi_f9(uint32_t *descbuf, uint16_t *bufsize,
			   uint8_t *cipherkey, uint32_t keylen,
			   uint8_t dir, uint32_t count,
			   uint32_t fresh, uint8_t direction,
			   uint32_t datalen)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;
	uint16_t ctx_offset = 16;
	uint64_t ct = count;
	uint64_t fr = fresh;
	uint64_t dr = direction;
	uint64_t context[3];

	context[0] = (ct << 32) | (dr << 26);
	context[1] = (fr << 32);

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, 0);
	{
		KEY(KEY1, 0, IMM((uintptr_t)cipherkey), keylen, 0);
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_F9,
			      OP_ALG_AS_INITFINAL, 0, dir);
		LOAD(PTR((uintptr_t)context), CONTEXT1, 0, SIZE(24), IMMED);
		SEQFIFOLOAD(BIT_DATA, datalen, WITH(CLASS1 | LAST1 | LAST2));
		/* Save output MAC of DWORD 2 into a 32-bit sequence */
		SEQSTORE(CONTEXT1, ctx_offset, SIZE(4), 0);
	}
	*bufsize = PROGRAM_FINALIZE();
}

/*
 * CRC32 Accelerator (IEEE 802 CRC32 protocol mode)
 *
 * @descbuf - descriptor buffer
 * @bufsize - limit of descriptor buffer size
 *
 *  DIS - turned on
 *  DOS - turned on
 *  DOC - turned off
 */
static inline void cnstr_shdsc_crc(uint32_t *descbuf, uint16_t *bufsize)
{
	struct program prg;
	struct program *program = &prg;
	uint sec_subversion = 3;

	PROGRAM_CNTXT_INIT(descbuf, 0, sec_subversion);
	SHR_HDR(SHR_ALWAYS, 1, 0);
	{
		MATHB(SEQINSZ, SUB, MATH2, VSEQINSZ, SIZE(4), 0);
		ALG_OPERATION(OP_ALG_ALGSEL_CRC,
			      OP_ALG_AAI_802 | OP_ALG_AAI_DOC,
			      OP_ALG_AS_FINALIZE, 0, DIR_ENC);
		SEQFIFOLOAD(MSG2, SIZE(32), WITH(VLF | LAST2));
		SEQSTORE(CONTEXT2, 0, SIZE(4), 0);
	}
	*bufsize = PROGRAM_FINALIZE();
}

#endif /* __RTA_PROTOSHARED_H__ */