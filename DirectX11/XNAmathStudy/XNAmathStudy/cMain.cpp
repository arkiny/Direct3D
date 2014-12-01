#include <Windows.h>
#include <iostream>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

//#if defined(__cplusplus) && !defined(XM_NO_OPERATOR_OVERLOADS)
//XMVECTOR operator+ (FXMVECTOR V);
//XMVECTOR operator- (FXMVECTOR V);
//XMVECTOR& operator+= (XMVECTOR& V1, FXMVECTOR V2);
//XMVECTOR& operator-= (XMVECTOR& V1, FXMVECTOR V2);
//XMVECTOR& operator*= (XMVECTOR& V1, FXMVECTOR V2);
//XMVECTOR& operator/= (XMVECTOR& V1, FXMVECTOR V2);
//XMVECTOR& operator*= (XMVECTOR& V, FLOAT S);
//XMVECTOR& operator/= (XMVECTOR& V, FLOAT S);
//XMVECTOR operator+ (FXMVECTOR V1, FXMVECTOR V2);
//XMVECTOR operator- (FXMVECTOR V1, FXMVECTOR V2);
//XMVECTOR operator* (FXMVECTOR V1, FXMVECTOR V2);
//XMVECTOR operator/ (FXMVECTOR V1, FXMVECTOR V2);
//XMVECTOR operator* (FXMVECTOR V, FLOAT S);
//XMVECTOR operator* (FLOAT S, FXMVECTOR V);
//XMVECTOR operator/ (FXMVECTOR V, FLOAT S);
//#endif // __cplusplus && !XM_NO_OPERATOR_OVERLOADS

using namespace DirectX;
using namespace DirectX::PackedVector;
using namespace std;

#include "cMain.h"

ostream& operator<<(ostream& os, FXMVECTOR v){
	XMFLOAT3 dest;
	XMStoreFloat3(&dest, v);
	os << "<" << dest.x << "," << dest.y << "," << dest.z << ")";
	return os;
}

cMain::cMain()
{
}


cMain::~cMain()
{
}


int main(){
	
	///save vector
	// Check support for SSE2 (Pentium4, AMD K8, and above).
	//if (!XMVerifyCPUSupport())
	//{
	//	cout << "xna math not supported" << endl;
	//	return 0;
	//}
	//XMVECTOR p = XMVectorZero();
	//XMVECTOR q = XMVectorSplatOne();
	//XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	//XMVECTOR v = XMVectorReplicate(-2.0f);
	//XMVECTOR w = XMVectorSplatZ(u);
	//cout << "p = " << p << endl;
	//cout << "q = " << q << endl;
	//cout << "u = " << u << endl;
	//cout << "v = " << v << endl;
	//cout << "w = " << w << endl;

	///vector operation
	cout.setf(ios_base::boolalpha);
	// Check support for SSE2 (Pentium4, AMD K8, and above).
	if (!XMVerifyCPUSupport())
	{
		cout << "xna math not supported" << endl;
		return 0;
	}
	XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR w = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);
	// Vector addition: XMVECTOR operator +
	XMVECTOR a = u + v;
	// Vector subtraction: XMVECTOR operator -
	XMVECTOR b = u - v;
	// Scalar multiplication: XMVECTOR operator *
	XMVECTOR c = 10.0f*u;
	// ||u||
	XMVECTOR L = XMVector3Length(u);
	// d = u / ||u||
	XMVECTOR d = XMVector3Normalize(u);
	// s = u dot v
	XMVECTOR s = XMVector3Dot(u, v);
	// e = u x v
	XMVECTOR e = XMVector3Cross(u, v);
	// Find proj_n(w) and perp_n(w)
	XMVECTOR projW;
	XMVECTOR perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, n);
	// Does projW + perpW == w?
	bool equal = XMVector3Equal(projW + perpW, w) != 0;
	bool notEqual = XMVector3NotEqual(projW + perpW, w) != 0;
	// The angle between projW and perpW should be 90 degrees.
	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);
	float angleRadians = XMVectorGetX(angleVec);
	float angleDegrees = XMConvertToDegrees(angleRadians);
	cout << "u = " << u << endl;
	cout << "v = " << v << endl;
	cout << "w = " << w << endl;
	cout << "n = " << n << endl;
	cout << "a = u + v = " << a << endl;
	cout << "b = u - v = " << b << endl;
	cout << "c = 10 * u = " << c << endl;
	cout << "d = u / ||u|| = " << d << endl;
	cout << "e = u x v = " << e << endl;
	cout << "L = ||u|| = " << L << endl;
	cout << "s = u.v = " << s << endl;
	cout << "projW = " << projW << endl;
	cout << "perpW = " << perpW << endl;
	cout << "projW + perpW == w = " << equal << endl;
	cout << "projW + perpW != w = " << notEqual << endl;
	cout << "angle = " << angleDegrees << endl;

	/// floating pointerror
	//cout.precision(8);
	//// Check support for SSE2 (Pentium4, AMD K8, and above).
	//if (!XMVerifyCPUSupport())
	//{
	//	cout << "xna math not supported" << endl;
	//	return 0;
	//}
	//XMVECTOR u = XMVectorSet(1.0f, 1.0f, 1.0f, 0.0f);
	//XMVECTOR n = XMVector3Normalize(u);
	//float LU = XMVectorGetX(XMVector3Length(n));
	//// Mathematically, the length should be 1. Is it numerically?
	//cout << LU << endl;
	//if (LU == 1.0f)
	//	cout << "Length 1" << endl;
	//else
	//	cout << "Length not 1" << endl;
	//// Raising 1 to any power should still be 1. Is it?
	//float powLU = powf(LU, 1.0e6f);
	//cout << "LU^(10^6) = " << powLU << endl;

	return 0;
}