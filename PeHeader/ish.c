#include "PeHeader.h"

void set_image_section_header(FILE* f)
{
	int i = 0;
	if (ihi.magic == 0x10B)
	{
		fseek(f, ihi.e_lfanew + sizeof(IMAGE_NT_HEADERS32), SEEK_SET);
	}
	else if (ihi.magic == 0x20B)
	{
		fseek(f, ihi.e_lfanew + sizeof(IMAGE_NT_HEADERS64), SEEK_SET);
	}

	for (i = 0; i < ihi.NumberOfSections; i++)
	{
		fread(&ish[i], sizeof(IMAGE_SECTION_HEADER), 1, f);
	}
}

void print_image_section_header()
{
	unsigned int j = 0;
	if (ihi.magic == 0x10B)
	{
		j = ihi.e_lfanew + sizeof(IMAGE_NT_HEADERS32);
	}
	else if (ihi.magic == 0x20B)
	{
		j = ihi.e_lfanew + sizeof(IMAGE_NT_HEADERS64);
	}

	for (int i = 0; i < ihi.NumberOfSections; i++)
	{
		print_hex_and_ascii(&ish[i], sizeof(IMAGE_SECTION_HEADER), j + (sizeof(IMAGE_SECTION_HEADER) * (i + 1)));
	}
}