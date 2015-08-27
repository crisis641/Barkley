#pragma once

#include <string>

#include <FreeImage.h>
#include <FreeImage/Utilities.h>

#include <barkley_types.h>
#include <utils/log.h>

namespace barkley {

	static BYTE* load_image(const char* filename, uint* width, uint* height, uint* bits)
	{

		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

		FIBITMAP *dib = nullptr;
		
		
		fif = FreeImage_GetFileType(filename, 0);
		
		if (fif == FIF_UNKNOWN)
			fif = FreeImage_GetFIFFromFilename(filename);

		if (fif == FIF_UNKNOWN)
			return nullptr;

		
		if (FreeImage_FIFSupportsReading(fif))
			dib = FreeImage_Load(fif, filename);
		if (!dib)
			return nullptr;
		//BARKLEY_ASSERT(dib, "Could not load image '", filename, "'!");

		BYTE* pixels = FreeImage_GetBits(dib);
		*width = FreeImage_GetWidth(dib);
		*height = FreeImage_GetHeight(dib);
		*bits = FreeImage_GetBPP(dib);

#ifdef BARKLEY_EMSCRIPTIEN
		SwapRedBlue32(dib);
#endif

		int size = *width * *height * (*bits / 8);
		BYTE* result = new BYTE[size];
		memcpy(result, pixels, size);
		FreeImage_Unload(dib);

		return result;

	}
}