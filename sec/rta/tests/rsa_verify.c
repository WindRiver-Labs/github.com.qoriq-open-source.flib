#include <stdio.h>
#include "flib/rta.h"
#include "test_common.h"

enum rta_sec_era rta_sec_era;

/* Subroutine to populate a Descriptor buffer */
unsigned build_rsa_verify_desc(uint32_t *buff, uint32_t n_len, uint32_t e_len,
			       const uint64_t n, const uint64_t e,
			       const uint64_t f, const uint64_t g)
{
	struct program prg;
	struct program *program = &prg;
	LABEL(pdb_end);

	PROGRAM_SET_36BIT_ADDR();

	PROGRAM_CNTXT_INIT(buff, 0);
	JOB_HDR(SHR_NEVER, 0, 0, 0);
	{
		{	/* RSA Verify */
			WORD(((e_len << 12) + n_len));	/* e length, n length */
			DWORD(f);	/* output */
			DWORD(g);	/* input */
			DWORD(n);	/* modulus */
			DWORD(e);	/* public expnenent */
			WORD(n_len);	/* g length */
			SET_LABEL(pdb_end);
		}
		PROTOCOL(OP_TYPE_UNI_PROTOCOL, OP_PCLID_RSAENCRYPT, 0);
	}
	PATCH_HDR(0, pdb_end);

	return PROGRAM_FINALIZE();
}

unsigned test_rsa_verify(uint32_t *buff)
{
	uint32_t n_len = 128;
	uint32_t e_len = 3;

	uint64_t buf_phys = 0x200320024ull;
	uint64_t e = (uint64_t) buf_phys;	/* 1st vector in buffer */
	uint64_t n = e + e_len;	/* 2nd                  */
	uint64_t g = n + n_len;	/* 3rd                  */
	uint64_t f = g;		/* 4th overwrites 3rd   */

	return build_rsa_verify_desc(buff, n_len, e_len, n, e, f, g);
}

uint32_t prg_buff[1000];

int main(int argc, char **argv)
{
	unsigned size;

	pr_debug("RSA Verify example program\n");
	rta_set_sec_era(RTA_SEC_ERA_2);
	size = test_rsa_verify(prg_buff);
	pr_debug("size = %d\n", size);
	print_prog(prg_buff, size);

	return 0;
}
