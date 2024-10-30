#include "PeHeader.h"


int _tmain(int argc, TCHAR* argv[])
{
	if (argc < 2)
		error(-1, _T("usage print image_dos_header<file_name>"));

	FILE* f = _tfopen(argv[1], _T("rb"));
	if (f == NULL)
		error(GetLastError(), _T("fopen error"));

	InitIHI(f);

	set_image_dos_header(f);
	set_image_nt_headers(f);
	set_image_file_header(f);
	set_image_optional_header(f);
	set_image_section_header(f);
	fclose(f);

	title();

	print_offset();
	print_idh();
	print_image_nt_headers();
	print_image_file_header();
	print_image_optional_header();
	print_image_section_header();
}
