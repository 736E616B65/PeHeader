#include "PeHeader.h"

unsigned char bcode[1040] = { 0, };
void set_image_optional_header(FILE* f)
{
	fseek(f, ihi.e_lfanew + PE_SIGNATURE_LEN + sizeof(IMAGE_FILE_HEADER), SEEK_SET);
	if (ihi.SizeOfOptionalHeader != 0xF0 && ihi.SizeOfOptionalHeader != 0xF8)
	{
		fread(bcode, ihi.SizeOfOptionalHeader, 1, f);
		print_image_optional_header = print_image_optional_headers128;
	}
	else if (ihi.magic == 0x10B)
	{
		fread(&ioh32, sizeof(IMAGE_OPTIONAL_HEADER32), 1, f);
		print_image_optional_header = print_image_optional_header32;
	}
	else if (ihi.magic == 0x20B)
	{
		fread(&ioh64, sizeof(IMAGE_OPTIONAL_HEADER64), 1, f);
		print_image_optional_header = print_image_optional_header64;
	}
}

void print_image_optional_headers128()
{
	print_hex_and_ascii(bcode, ihi.SizeOfOptionalHeader, ihi.e_lfanew + PE_SIGNATURE_LEN + sizeof(IMAGE_FILE_HEADER));
}

void print_image_optional_header32()
{
	print_hex_and_ascii(&ioh32, sizeof(IMAGE_OPTIONAL_HEADER32), ihi.e_lfanew + PE_SIGNATURE_LEN + sizeof(IMAGE_FILE_HEADER));
}

void print_image_optional_header64()
{
	print_hex_and_ascii(&ioh64, sizeof(IMAGE_OPTIONAL_HEADER64), ihi.e_lfanew + PE_SIGNATURE_LEN + sizeof(IMAGE_FILE_HEADER));
}