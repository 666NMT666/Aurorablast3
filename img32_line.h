#define BLT_ADD_PIXEL {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	r=destpixel.R + srcpixel.R; destpixel.R=r>255?255:r;\
	r=destpixel.G + srcpixel.G; destpixel.G=r>255?255:r;\
	r=destpixel.B + srcpixel.B; destpixel.B=r>255?255:r;\
	*destadr=destpixel.ARGB;\
}
#define BLT_SCREEN_PIXEL() {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	r=destpixel.R + srcpixel.R-((destpixel.R*srcpixel.R)>>8); destpixel.R=r>255?255:r;\
	r=destpixel.G + srcpixel.G-((destpixel.G*srcpixel.G)>>8); destpixel.G=r>255?255:r;\
	r=destpixel.B + srcpixel.B-((destpixel.B*srcpixel.B)>>8); destpixel.B=r>255?255:r;\
	*destadr=destpixel.ARGB;\
}
#define BLT_MINUS_PIXEL(){\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	r=destpixel.R>srcpixel.R ? destpixel.R-srcpixel.R:0;\
	r=destpixel.G>srcpixel.G ? destpixel.G-srcpixel.G:0;\
	r=destpixel.B>srcpixel.B ? destpixel.B-srcpixel.B:0;\
	*destadr=destpixel.ARGB;\
}
#define BLT_MUL_PIXEL() {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	destpixel.R=(destpixel.R * srcpixel.R)>>8;\
	destpixel.G=(destpixel.G * srcpixel.G)>>8;\
	destpixel.B=(destpixel.B * srcpixel.B)>>8;\
	*destadr=destpixel.ARGB;\
}
#define BLT_BLACKEN_PIXEL(alpha) {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	destpixel.R=srcpixel.R<(alpha)?0:srcpixel.R-(alpha);\
	destpixel.G=srcpixel.G<(alpha)?0:srcpixel.G-(alpha);\
	destpixel.B=srcpixel.B<(alpha)?0:srcpixel.B-(alpha);\
	*destadr=destpixel.ARGB;\
}
#define BLT_WHITEN_PIXEL(alpha) {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	r=srcpixel.R+(alpha); destpixel.R=r>255?255:r;\
	r=srcpixel.G+(alpha); destpixel.G=r>255?255:r;\
	r=srcpixel.B+(alpha); destpixel.B=r>255?255:r;\
	*destadr=destpixel.ARGB;\
}
#define BLT_ALPHA2_PIXEL() {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	destpixel.R=(destpixel.R + srcpixel.R)>>1;\
	destpixel.G=(destpixel.G + srcpixel.G)>>1;\
	destpixel.B=(destpixel.B + srcpixel.B)>>1;\
	*destadr=destpixel.ARGB;\
}
#define BLT_ALPHA3_PIXEL() {\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	destpixel.R=(destpixel.R + srcpixel.R+srcpixel.R+srcpixel.R)>>2;\
	destpixel.G=(destpixel.G + srcpixel.G+srcpixel.G+srcpixel.G)>>2;\
	destpixel.B=(destpixel.B + srcpixel.R+srcpixel.B+srcpixel.B)>>2;\
	*destadr=destpixel.ARGB;\
}
#define BLT_XMINUS_PIXEL(){\
	srcpixel.ARGB=*srcadr; destpixel.ARGB=*destadr;\
	r=destpixel.G>srcpixel.G ? destpixel.G-srcpixel.G:0;\
	r=destpixel.B>srcpixel.B ? destpixel.B-srcpixel.B:0;\
	*destadr=destpixel.ARGB;\
}
