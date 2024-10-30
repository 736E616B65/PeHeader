#ifndef __PE_HEADER_H__
#define __PE_HEADER_H__

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <tchar.h>

/* DEFINE SECTION */
#define PE_SIGNATURE_LEN sizeof(DWORD)
/* END */

/* IMAGE_HEADER SECTION */
IMAGE_DOS_HEADER idh;
IMAGE_NT_HEADERS32 inh32;
IMAGE_NT_HEADERS64 inh64;
IMAGE_FILE_HEADER ifh;
IMAGE_OPTIONAL_HEADER32 ioh32;
IMAGE_OPTIONAL_HEADER64 ioh64;
IMAGE_SECTION_HEADER ish[1040];
/* END */

typedef struct _IMAGE_HEADER_INFO
{
	WORD magic;
	LONG e_lfanew;
	WORD SizeOfOptionalHeader;
	WORD NumberOfSections;
} IHI;

IHI ihi;
_TUCHAR line[60];

BOOL InitIHI(FILE*);

void print_offset();
int error(int, char[]);

/* set IMAGE_*_HEADER */
void set_image_dos_header(FILE*);
void set_image_nt_headers(FILE*);
void set_image_file_header(FILE*);
void set_image_optional_header(FILE*);
void set_image_section_header(FILE*);
/* end */

/* print IDH */
void print_image_dos_header();
/* end */

/* print INH */
void (*print_image_nt_headers)();
void print_image_nt_headers32();
void print_image_nt_headers64();
void print_image_nt_headers128();
/* end */

/* print IFH */
void print_image_file_header();
/* end */

/* print IOH */
void (*print_image_optional_header)();
void print_image_optional_header32();
void print_image_optional_header64();
void print_image_optional_headers128();
/* end */

/* print ISH */
void print_image_section_header();
/* end */

void title();
void print_hex_and_ascii(void*, int, int);

#endif