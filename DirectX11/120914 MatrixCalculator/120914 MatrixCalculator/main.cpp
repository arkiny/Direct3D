#include <iostream>
#include <fstream>
#include "cMatrix.h"

using namespace std;

int main(){
	//cout << "<<< A >>>" <<endl;
	//cMatrix A(2);

	//A.setElement(0, 0, 1);
	//A.setElement(0, 1, 2);
	//A.setElement(1, 0, 3);
	//A.setElement(1, 1, 4);

	//A.print();
	//cout << "<<< det A >>>" << endl;
	//cout << A.det() << endl;
	//cout << "<<< transpose A >>>" << endl;
	//A.transpose();
	//A.print();
	//A.transpose();
	//cout << "<<< adj A >>>" << endl;
	//A.adj().print();
	//cout << "<<< inverse A >>>" << endl;
	//A.inverse().print();
	//cout << endl;


	//cout << "<<< B >>>" << endl;
	//cMatrix B(2);
	//B.setElement(0, 0, 5);
	//B.setElement(0, 1, 6);
	//B.setElement(1, 0, 7);
	//B.setElement(1, 1, 8);
	//B.print();
	//cout << endl;

	//if (A == A) cout << "A = A" << endl;
	//if (A == B){
	//	cout << "A == B" << endl;
	//}
	//else {
	//	cout << "A != B" << endl;
	//}
	//cout << endl;

	//cout << "A + B" << endl;
	//// 6 8
	//// 10 12
	//(A + B).print();
	//
	//cout << "B + A" << endl;
	////4 4
	////4 4
	//(B - A).print();
	//
	//cout << "A * 3" << endl;
	////3 6
	////9 12
	//(A * 3).print();

	//cout << "A * B" << endl;
	//(A * B).print();

	////A.adj().print();

	//cMatrix C(3);
	//float j = 1.0f;
	//for (int i = 0; i < 3; i++){
	//	C.setElement(i, 0, j);
	//	j+= 1.0f;
	//	C.setElement(i, 1, j);
	//	j += 1.0f;
	//	C.setElement(i, 2, j);
	//	j += 1.0f;
	//}
	//cout << "<<< C>>>" << endl;
	//C.print();
	//cout << "<<< det C >>>" << endl;
	//cout << C.det() << endl;
	//cout << "<<< adj C >>>" << endl;
	//C.adj().print();
	//cout << "<<< inverse C >>>" << endl;
	//C.inverse().print();
	//cout << endl;
	//cout << endl;

	//cMatrix D(3);
	//D.setElement(0, 0, 1);
	//D.setElement(0, 1, 3);
	//D.setElement(0, 2, 2);
	//D.setElement(1, 0, 1);
	//D.setElement(1, 1, 2);
	//D.setElement(1, 2, 3);
	//D.setElement(2, 0, 6);
	//D.setElement(2, 1, 5);
	//D.setElement(2, 2, 4);

	//cMatrix E(4);
	//E.setElement(0, 0, 1);
	//E.setElement(0, 1, 2);
	//E.setElement(0, 2, 3);
	//E.setElement(0, 3, 3);
	//E.setElement(1, 0, 1);
	//E.setElement(1, 1, 2);
	//E.setElement(1, 2, 3);
	//E.setElement(1, 3, 4);
	//E.setElement(2, 0, 1);
	//E.setElement(2, 1, 4);
	//E.setElement(2, 2, 5);
	//E.setElement(2, 3, 4);
	//E.setElement(3, 0, 6);
	//E.setElement(3, 1, 7);
	//E.setElement(3, 2, 3);
	//E.setElement(3, 3, 4);
	//

	//cout << "<<< E >>>" << endl;
	//E.print();
	//cout << "<<< det E >>>" << endl;
	//cout << E.det() << endl;
	//cout << "<<< adj E >>>" << endl;
	//E.adj().print();
	//cout << "<<< inverse E >>>" << endl;
	//E.inverse().print();
	//cout << endl;

	////cout << A.minor(0, 0) << endl;
	////cout << C.minor(0, 0) << endl;

	//
	//
	//cout << D.det() << endl;

	//

	//cMatrix F(5);
	//F.setElement(0, 0, 1);
	//F.setElement(0, 1, 2);
	//F.setElement(0, 2, 3);
	//F.setElement(0, 3, 3);
	//F.setElement(0, 4, 2);
	//F.setElement(1, 0, 1);
	//F.setElement(1, 1, 2);
	//F.setElement(1, 2, 3);
	//F.setElement(1, 3, 4);
	//F.setElement(1, 4, 2);
	//F.setElement(2, 0, 1);
	//F.setElement(2, 1, 4);
	//F.setElement(2, 2, 5);
	//F.setElement(2, 3, 4);
	//F.setElement(2, 4, 2);
	//F.setElement(3, 0, 6);
	//F.setElement(3, 1, 7);
	//F.setElement(3, 2, 3);
	//F.setElement(3, 3, 4);
	//F.setElement(3, 4, 2);
	//F.setElement(4, 0, 6);
	//F.setElement(4, 1, 7);
	//F.setElement(4, 2, 2);
	//F.setElement(4, 3, 1);
	//F.setElement(4, 4, 2);
	//cout << "<<< F >>>" << endl;
	//F.print();
	//cout << "<<< det F >>>" << endl;
	//cout << F.det() << endl;
	//cout << "<<< adj F >>>" << endl;
	//F.adj().print();
	//cout << "<<< inverse F >>>" << endl;
	//F.inverse().print();
	//cout << "Re-Confirm" << endl;
	//(F * F.inverse()).print();
	//
	//if (F * F.inverse() == F.Identity(F)){
	//	cout << "get some" << endl;
	//}
	//cout << endl;

}
