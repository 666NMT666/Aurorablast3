#pragma once
#include "img32.h"

class CImagePNG : public CImage32{
	
public:
	CImagePNG(char* file) {
		if (file == NULL)return;
		else {
			m_buffer = NULL;
			load(file);
		}
	}
	virtual ~CImagePNG() { Free(); }
	virtual void load(char* fname);
	//virtual void save(char* fname);

};