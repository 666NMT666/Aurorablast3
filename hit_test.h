#include <math.h>
class CHitTest{
public:
	static bool CircleToPoint(int x1,int y1,int x2,int y2,int radius);
	static bool CircleToCircle(int x1,int y1,int x2,int y2,int radius1,int radius2);
	static bool CircleToLine();// mijissou

	static bool MovingCircleToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int radius);
	static bool MovingCircleToCircle(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int radius1,int radius2);

	static bool MovingPolygonToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,CVector* r,int n);

	static bool sgn(double a){return (a>0);};

};

bool CHitTest::CircleToPoint(int x1,int y1,int x2,int y2,int r){
	int dx=x2-x1;
	int dy=y2-y1;
	return (dx*dx+dy*dy<r*r);
}

bool CHitTest::CircleToCircle(int x1,int y1,int x2,int y2,int radius1,int radius2){
	int dx=x2-x1;
	int dy=y2-y1;
	int r=radius1+radius2;
	return (dx*dx+dy*dy<r*r);
}

bool CHitTest::MovingCircleToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int r){
	if(CircleToPoint(x1,y1,x2,y2,r))return true;
	
	/*物体1-2間の相対速度ベクトルvx,vy (物体1を固定)*/
	int vx=(x2-prevX2)-(x1-prevX1);
	int vy=(y2-prevY2)-(y1-prevY1);
	if(vx==0 && vy==0)return false;

	/*相対速度に直交する半径rのベクトル*/
	double crossVx=-(double)(r*vy)/sqrt((double)(vy*vy+vx*vx));
	double crossVy= (double)(r*vx)/sqrt((double)(vy*vy+vx*vx));
	
	//(x1-crossVx,y1-crossVy)～(x1+crossVx,y1+crossVy)間の線分と(x2,y2)～(x2-vx,y2-vy)間の線分がクロスすればヒット
	/*現在の位置関係を過去に巻き戻す過程で衝突が起きるかを確認*/
	// 点（x2,y2）から左右確認  // 点（x1+crossVx,y1+crossVy）から左右確認
	if(((((x1-crossVx)-x2)*vy-((y1-crossVy)-y2)*vx)*(((x1+crossVx)-x2)*vy-((y1+crossVy)-y2)*vx)<0)
		&& (((x2-(x1+crossVx))*crossVy-(y2-(y1+crossVy))*crossVx)*((x2-vx-(x1+crossVx))*crossVy-(y2-vy-(y1+crossVy))*crossVx)<0)
		){return true;}
	else {return false;}
}

bool CHitTest::MovingCircleToCircle(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,int r1,int r2){
	if(CircleToCircle(x1,y1,x2,y2,r1,r2))return true;
	
	/*物体1-2間の相対速度ベクトルvx,vy*/
	int vx=(x2-prevX2)-(x1-prevX1);
	int vy=(y2-prevY2)-(y1-prevY1);

	if(vx==0 && vy==0)return false;

	/*相対速度に直交する半径rのベクトル*/
	double crossVx=-(double)((r1+r2)*vy)/sqrt((double)(vy*vy+vx*vx));
	double crossVy= (double)((r1+r2)*vx)/sqrt((double)(vy*vy+vx*vx));
	if(crossVx*(x2-x1)+crossVy*(y2-y1)<0){
		crossVx*=-1; crossVy*=-1; // 直交ベクトルの向きが逆
	}

	//(x1,y1)～(x1+crossVx,y1+crossVy)間の線分と(x2,y2)～(x2-vx,y2-vy)間の線分がクロスすればヒット
	if((sgn((x1-x2)*vy-(y1-y2)*vx)!=sgn((x1+crossVx-x2)*vy-(y1+crossVy-y2)*vx))
		&& (sgn((x2-x1)*crossVy-(y2-y1)*crossVx)!=sgn((x2-vx-x1)*crossVy-(y2-vy-y1)*crossVx))
		){return true;}
	else {return false;}
}

bool CHitTest::MovingPolygonToPoint(int x1,int y1,int x2,int y2,int prevX1,int prevY1,int prevX2,int prevY2,CVector* r,int n){
	//*物体1(x1,y1)は多角形、物体2(x2,y2)は点、r：多角形の全頂点の座標配列、n頂点の数*//
	if(ExMath::isInPoligon(x2,y2,r,n)){ return true; } // 固定バージョン
	
	/*物体1-2間の相対速度ベクトルvx,vy、多角形を固定*/
	double vx=(x2-prevX2)-(x1-prevX1);
	double vy=(y2-prevY2)-(y1-prevY1);

	/*物体2をマイナス相対速度方向に巻き戻す過程で多角形の辺とクロスすれば衝突とする*/
	for(int i=0;i<n-1;i++){
		if((((-vx*(r[i%n].y-y2)-(-vy*(r[i%n].x-x2))))*((-vx*(r[(i+1)%n].y-y2))-(-vy*(r[(i+1)%n].x-x2)))<0) && 
			(((((r[(i+1)%n].y-r[i%n].y)*(x2-r[i%n].x))-(r[(i+1)%n].x-r[i%n].x)*(y2-r[i%n].y)))*
			 ((((r[(i+1)%n].y-r[i%n].y)*(x2-vx-r[i%n].x))-(r[(i+1)%n].x-r[i%n].x)*(y2-vy-r[i%n].y)))<0)
		){return true;}
	}
	return false;
}