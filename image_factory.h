#ifndef _IMAGE_FACTORY_H
#define _IMAGE_FACTORY_H
#include "img32.h"
#include "imgdib.h"
#include "png.h"
#include "pngstruct.h"
#include "pnginfo.h"
class CImageFactory{
public:
	static CImage32* newBitmap(const char* const fname){
		CImage32* dest=new CImage32();
		dest->load(fname);
		return dest;
	}
	static void InitBitmap(CImage32* dest,const char* const fname){
		dest->load(fname);
	}
	static void InitBitmapZ(CImage32* dest,const char* const fname){
		CImageDIB *tmp=new CImageDIB();
		tmp->InitBitmapZ(fname);
		dest->Resize(tmp->Width(),tmp->Height());
		dest->SetBuffer(tmp->Buffer());
		delete tmp;
	}
};

#endif