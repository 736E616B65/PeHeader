#include "PeHeader.h"

int size = 0;
_TUCHAR code[1040] = { 0, };
void set_image_nt_headers(FILE* f)
{
	/* signature + IMAGE_HEADER + SizeOfOptionalHeader = IMAGE_NT_HEADERS */
	size = (PE_SIGNATURE_LEN + sizeof(IMAGE_FILE_HEADER) + ihi.SizeOfOptionalHeader);

	fseek(f, ihi.e_lfanew, SEEK_SET);
	if (ihi.SizeOfOptionalHeader != 0xF0 && ihi.SizeOfOptionalHeader != 0xF8)
	{
		fread(code, size, 1, f);
		print_image_nt_headers = print_image_nt_headers128;
	}
	else if (ihi.magic == 0x10B)
	{
		fread(&inh32, size, 1, f);
		print_image_nt_headers = print_image_nt_headers32;
	}
	else if (ihi.magic == 0x20B)
	{
		fread(&inh64, size, 1, f);
		print_image_nt_headers = print_image_nt_headers64;
	}
}

void print_image_nt_headers128()
{
	print_hex_and_ascii(code, size, ihi.e_lfanew);
}

void print_image_nt_headers32()
{
	print_hex_and_ascii(&inh32, sizeof(IMAGE_NT_HEADERS32), ihi.e_lfanew);
}

void print_image_nt_headers64()
{
	print_hex_and_ascii(&inh64, sizeof(IMAGE_NT_HEADERS64), ihi.e_lfanew);
}