#include <windows.h>
#include "img_png.h"
#include "png.h"
#include "pngstruct.h"
#include "pnginfo.h"

void CImagePNG::load(char* fname) {
	FILE *fin;
	errno_t err;
	if ((err = fopen_s(&fin, fname, "rb")) != 0) { return; }
	const size_t numSizeSignature = 8;
	const int numByteSignature = sizeof(BYTE)*numSizeSignature;
	BYTE signature[numByteSignature];
	size_t numSizeReadSignature = fread(signature, sizeof(BYTE), numSizeSignature, fin);
	if (numSizeReadSignature != numSizeSignature) {
		fclose(fin);
		return;
	}
	if (png_sig_cmp(signature, 0, numByteSignature)) {
		fclose(fin);
		return;
	}
	png_struct* pPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!pPngStruct) {
		fclose(fin);
		return;
	}
	png_info* pPngInfo = png_create_info_struct(pPngStruct);
	if (!pPngInfo) {
		png_destroy_read_struct(&pPngStruct, NULL, NULL);
		fclose(fin);
		return;
	}

	if (setjmp(png_jmpbuf(pPngStruct))) {
		png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
		fclose(fin);
		return;
	}

	png_init_io(pPngStruct, fin);
	png_set_sig_bytes(pPngStruct, numByteSignature);
	png_read_png(pPngStruct, pPngInfo,
		PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING |
		PNG_TRANSFORM_PACKSWAP | PNG_TRANSFORM_EXPAND |
		PNG_TRANSFORM_BGR, NULL);

	png_uint_32 width = pPngInfo->width;
	png_uint_32 height = pPngInfo->height;
	int bit_depth = pPngInfo->bit_depth;
	int color_type = pPngInfo->color_type;

	Resize(width, height);
	png_byte** pRowTable = pPngInfo->row_pointers;
	for (UINT y = 0; y<height; y++) {
		png_byte* pRow = pRowTable[y];
		for (UINT x = 0; x<width; x++) {
			TARGB color;
			if (color_type == PNG_COLOR_TYPE_GRAY) {
				color.B = color.G = color.R = *pRow++;
				color.A = 255;
			}
			else if (color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
				color.B = color.G = color.R = *pRow++;
				color.A = *pRow++;
			}
			else if (color_type == PNG_COLOR_TYPE_RGB) {
				color.B = *pRow++;
				color.G = *pRow++;
				color.R = *pRow++;
				color.A = 0;
			}
			else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA) {
				color.B = *pRow++;
				color.G = *pRow++;
				color.R = *pRow++;
				color.A = *pRow++;
			}
			PixelSet(x, y, color.ARGB);
		}
	}
	png_destroy_read_struct(&pPngStruct, &pPngInfo, NULL);
	fclose(fin);
}
