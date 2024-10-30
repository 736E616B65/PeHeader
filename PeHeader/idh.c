#include "PeHeader.h"

WORD addr = 0;
void set_image_dos_header(FILE* f)
{
	fseek(f, 0, SEEK_SET);
	size_t ch = fread(&idh, sizeof(IMAGE_DOS_HEADER), 1, f);
	if (ch == 0)
		error(GetLastError(), _T("set_image_dos_header.fread error"));
}

void print_idh()
{
	print_hex_and_ascii(&idh, sizeof(IMAGE_DOS_HEADER), addr);
}
