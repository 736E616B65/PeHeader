#include "PeHeader.h"

void title()
{
	int i1 = 0;
	int i2 = 0;
	LPCTSTR menu[] = 
	{ 
		_T("IMAGE_NT_HEADERS32"), _T("IMAGE_OPTIONAL_HEADER32"),
		_T("IMAGE_NT_HEADERS64"), _T("IMAGE_OPTIONAL_HEADER64")
	};

	if (ihi.magic == 0x10B)
	{
		i1 = 0;
		i2 = 1;
	}
	else if (ihi.magic == 0x20B)
	{
		i1 = 2;
		i2 = 3;
	}

	/*print pe header */
	_tprintf(_T("IMAGE_DOS_HEADER\n"));
	_tprintf(_T("\t%s\n"), menu[i1]);
	_tprintf(_T("\tIMAGE_FILE_HEADER\n"));
	_tprintf(_T("\t%s\n"), menu[i2]);
	/* end */

	/* print sections */
	for (i1 = 0; i1 < ihi.NumberOfSections; i1++)
	{
		_tprintf(_T("\tIMAGE_SECTION_HEADER "));
		for (i2 = 0; i2 < 8; i2++)
			_tprintf(_T("%c"), ish[i1].Name[i2]);
		_tprintf(_T("\n"));
	}
	/* end */
}

void print_offset()
{
	TBYTE offset[0x10]	= { 0, };
	UINT i					= 0;

	/* set offset */
	for (i = 0; i <= 0xF; i++)
	{
		offset[i] = i;
	}
	/* end */

	/* print offset */
	_tprintf(_T("%-8s %02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X\n"),
		_T("offset"), offset[0], offset[1], offset[2], offset[3], offset[4], offset[5], offset[6], offset[7], offset[8],
		offset[9], offset[10], offset[11], offset[12], offset[13], offset[14], offset[15]);
	/* end */


	for (i = 0; i < 57; i++)
		line[i] = _T('-');
	line[i + 1] = _T('\0');

	_tprintf(_T("%s\n"), line);
}

BOOL InitIHI(FILE* f)
{
	size_t ch = 0;
	int size = 0;

	ch = fseek(f, 0, SEEK_SET);
	if (ch != 0)
		error(GetLastError(), _T("fseek() error"));

	/* set ihi.e_lfanew */
	size = sizeof(IMAGE_DOS_HEADER);
	ch = fread(&idh, 1, size, f);
	if (ch < size)
		error(GetLastError(), _T("set ihi.e_lfanew error"));
	ihi.e_lfanew = idh.e_lfanew;
	/* end */

	/* set ihi.magic */
	size = idh.e_lfanew + PE_SIGNATURE_LEN + sizeof(IMAGE_FILE_HEADER);
	ch = fseek(f, size, SEEK_SET);
	if (ch != 0)
		error(GetLastError(), _T("set ihi.magic error"));

	size = sizeof(WORD);
	ch = fread(&ihi.magic, 1, size, f);
	if (ch < size)
		error(GetLastError(), _T("set ihi.magic error"));
	/* end */

	/* set ihi.NumberOfSections */
	size = idh.e_lfanew + PE_SIGNATURE_LEN + sizeof(WORD);
	ch = fseek(f, size, SEEK_SET);
	if (ch != 0)
		error(GetLastError(), _T("set ihi.NumberOfSections error"));

	size = sizeof(WORD);
	ch = fread(&ihi.NumberOfSections, 1, size, f);
	if (ch < size)
		error(GetLastError(), _T("set ihi.NumberOfSections error"));
	/* end */

	/* set ihi.SizeOfOptionalHeader */
	size = idh.e_lfanew + PE_SIGNATURE_LEN + (sizeof(DWORD) * 4);
	ch = fseek(f, size, SEEK_SET);
	if (ch != 0)
		error(GetLastError(), _T("set ihi.SizeOfOptionalHeader error"));

	size = sizeof(WORD);
	ch = fread(&ihi.SizeOfOptionalHeader, 1, size, f);
	if (ch < size)
		error(GetLastError(), _T("set ihi.SizeOfOptionalHeader error"));
	/* end */
}

void print_hex_and_ascii(void* IHVer, int size, int e_lfanew)
{
	UINT a = 0;
	UINT b = 0;
	UINT i = 0;
	unsigned char code[0x1040] = { 0, };
	unsigned char ascii[0x1040] = { 0, };

	/* memcpy image_header to code */
	memcpy(code, IHVer, size);
	
	/* set ascii */
	for (i = 0; i < size; i++)
	{
		if ((0x20 <= code[i]) && (code[i] <= 0x7E))
		{
			ascii[i] = code[i];
		}
		else
		{
			ascii[i] = '.';
		}
	}

	/* print hex and ascii */
	for (i = 0; i < size - (size % 0x10); i += 0x10)
	{
		printf("%08X %02X %02X %02X %02X %02X %02X %02X %02X  %02X %02X %02X %02X %02X %02X %02X %02X", e_lfanew + i,
			code[0 + i], code[1 + i], code[2 + i], code[3 + i], code[4 + i], code[5 + i], code[6 + i], code[7 + i],
			code[8 + i], code[9 + i], code[10 + i], code[11 + i], code[12 + i], code[13 + i], code[14 + i], code[15 + i]);

		printf(" %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",
			ascii[0 + i], ascii[1 + i], ascii[2 + i], ascii[3 + i], ascii[4 + i], ascii[5 + i], ascii[6 + i], ascii[7 + i],
			ascii[8 + i], ascii[9 + i], ascii[10 + i], ascii[11 + i], ascii[12 + i], ascii[13 + i], ascii[14 + i], ascii[15 + i]);
	}
	if (size % 0x10 != 0)
	{
		printf("%08X ", e_lfanew + i);
		for (a = 0; a < size % 0x10; a++)
		{
			printf("%02X ", code[a + i]);
			if (a == 0x8)
				printf(" ");
		}

		for (b = 0; b < 57 - (a * 3 + 8); b++)
		{
			printf(" ");
		}

		for (b = 0; b < size % 0x10; b++)
		{
			printf("%c", ascii[b + i]);
		}
		printf("\n");
	}

	_tprintf(_T("%s\n"), line);
}

int error(int code, char str[])
{
	_tprintf(_T("%s\n"), str);
	exit(code);
}