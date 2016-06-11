#include <Windows.h>

namespace CExRect{
	RECT getRect(int x,int y,int w,int h) {
		RECT rc = { x, y, x + w, y + h };
		return rc;
	}
	void InitRect(RECT *rc, int l, int t, int r, int b) {
		rc->left = l;
		rc->top = t;
		rc->right = r;
		rc->bottom = b;
	}
	bool isInRect(RECT *rc,int x,int y,int w,int h) {
		return (rc->left - w / 2<x && x<rc->right + w / 2 && rc->top - h / 2<y && y<rc->bottom + h / 2);
	}
	bool isInRect(RECT *rc,int x,int y) {
		return (rc->left<x && x<rc->right && rc->top<y && y<rc->bottom);
	}
	bool isTargetInRect(RECT *rc, int x, int y, int dx, int dy) {
		return (rc->left + dx<x && x<rc->right + dx && rc->top + dy<y && y<rc->bottom + dy);
	}
};
