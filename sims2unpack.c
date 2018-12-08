#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "sims2unpack.h"

int unpack_dbpf(FILE *dbpf)
{
	struct dbpf_t str;
	fread(&str.magic, 4, 1, dbpf);
	// first 4 bytes == "DBPF"
	if (str.magic != 0x46504244)
		return 0;
	fread(&str.majorv, 4, 1, dbpf);
	fread(&str.minorv, 4, 1, dbpf);
	fread(&str.majoru, 4, 1, dbpf);
	fread(&str.minoru, 4, 1, dbpf);
	fread(&str.flags, 4, 1, dbpf);
	fread(&str.created, 4, 1, dbpf);
	fread(&str.modified, 4, 1, dbpf);
	fread(&str.idx_major, 4, 1, dbpf);
	fread(&str.idx_no, 4, 1, dbpf);
	fread(&str.idx_off, 4, 1, dbpf);
	fread(&str.idx_sz, 4, 1, dbpf);
	fread(&str.hole_no, 4, 1, dbpf);
	fread(&str.hole_off, 4, 1, dbpf);
	fread(&str.hole_sz, 4, 1, dbpf);
	fread(&str.idx_minor, 4, 1, dbpf);

	char outname[16];
	int idxpos = str.idx_off;
	str.idx = malloc(str.idx_no * sizeof(struct idx_t));
	for (int i = 0; i < str.idx_no; i++) {
		sprintf(outname, "out.%d", i);
		fseek(dbpf, idxpos, 0);

		FILE *out = fopen(outname, "wb");
		fread(&str.idx[i].typeid, 4, 1, dbpf);
		fread(&str.idx[i].grpid, 4, 1, dbpf);
		fread(&str.idx[i].instid_hi, 4, 1, dbpf);
		fread(&str.idx[i].instid_lo, 4, 1, dbpf);
		fread(&str.idx[i].file_off, 4, 1, dbpf);
		fread(&str.idx[i].file_sz, 4, 1, dbpf);
		printf("dumping %s...\n", outname);
		printf("file size: %u\n", str.idx[i].file_sz);

		idxpos = ftell(dbpf);
		uint8_t tmp;
		fseek(dbpf, str.idx[i].file_off, 0);
		for (int j = 0; j < str.idx[i].file_sz; j++) {
			fread(&tmp, 1, 1, dbpf);
			fwrite(&tmp, 1, 1, out);
		}
		fclose(out);
	}

	free(str.idx);
	return 1;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("usage: ./sims2unpack [file.packed]\n");
		printf("\tfiles are dumped in the current directory as out.[number], be aware!\n");
		return 1;
	}

	FILE *dbpf = fopen(argv[1], "rb");
	if (!dbpf) {
		printf("fatal: file could not be opened\n");
		return 1;
	}

	if (!unpack_dbpf(dbpf)) {
		printf("fatal: file is not a valid dbpf archive\n");
		return 1;
	}

	fclose(dbpf);
	return 0;
}
