class ExMath3D{
public:
	static double zoomByDistanc(double d,double max=100.0);

};

double ExMath3D::zoomByDistanc(double d,double max){
	/*
		d->‡  ret = 0
		d=0    ret = 1
		d->-1000 ret = ‡
	*/
	double ret;
	if (1000.0 + d <= 0.0)ret=max;
	else ret=1000.0/(1000.0+d);
	
	if (ret > max)ret = max;
	return ret;
}


