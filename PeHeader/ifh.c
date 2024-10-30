#include "PeHeader.h"

void set_image_file_header(FILE* f)
{
	fseek(f, ihi.e_lfanew + PE_SIGNATURE_LEN, SEEK_SET);
	fread(&ifh, sizeof(IMAGE_FILE_HEADER), 1, f);
}

void print_image_file_header()
{
	print_hex_and_ascii(&ifh, sizeof(IMAGE_FILE_HEADER), ihi.e_lfanew + PE_SIGNATURE_LEN);
}