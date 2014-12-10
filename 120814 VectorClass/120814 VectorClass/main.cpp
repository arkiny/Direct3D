#include <iostream>

#include "main.h"
#include "cVector.h"

using namespace std;

int main(){
	cVector v1(2.0f, -3.0f, 5.0f / 2.0f);
	cVector v2(0.3f, -11.0f / 3.0f, 4.0f);
	cVector v3(0.32f, 6.0f, -9.1f);

	if (v1.equal(v1)){
		cout << "v1 is same as v1" << endl;
	}
	else {
		cout << "Not same" << endl;
	}


	if (v1.equal(v2)){
		cout << "v1 is same as v2" << endl;
	}
	else {
		cout << "Not same" << endl;
	}

	cout.precision(2);
	cVector sumofv1v2 = v1.add(v2);
	cVector diffofv1v2 = v1.sub(v2);
	cVector mulofv1and3 = v1.mul(3);
	cVector normalv1 = v1.normalized();
	float mag = v1.length();
	float dotv1v2 = v1.dot(v2);
	cVector crosv1v2 = v1.cross(v2);

	
	cout << "sum of v1 and v2 is "; // 2.3, -6.666667, 6.5
	sumofv1v2.print();
	cout << "difference of v1 and v2 is ";
	diffofv1v2.print();
	cout << "multyplay of v1 and 3 is";
	mulofv1and3.print();
	cout << "noramalized v1 is ";
	normalv1.print();
	cout << "v1's length(magnitude) is " << mag << endl;
	cout << "dot product of v1 and v2 is " << dotv1v2 << endl; // 21.6
	cout << "cross product of v1 and v2 is ";
	crosv1v2.print();

	//cVector normalized();
	//float length();

	//float dot(cVector in);
	//cVector cross(cVector in);

	//sVector getVectorCoord(){
	//	return *m_sVectorData;
	//}

}