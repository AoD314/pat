
#include <stdlib.h>
#include <string>
#include <iostream>

#include <QtGui/qapplication.h>

#include "mainwindow.hpp"
#include "settings.hpp"

#include "pat/number.hpp"
#include "pat/point.hpp"

using pat::MainWindow;
using pat::Number;
using pat::Point;

using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
    Number n1 = 1;
    Number n2;
    n2 = (1 * 4 + n1) / 2.0;
    cout << "n1 : " << n1 << endl;
    cout << "n2 : " << n2 << endl;

	cout << n1 << " < " << n2 << " is " << ((n1 < n2)?"true":"false") << endl;

    Point p1, p2, p3;

    p1.add(n1).add(n2);
    p2.add(4.0).add(3);

    p3 = 11 - (p1 + p2);

    cout << "p1 : " << p1 << endl;
	for (int i = 0; i < p1.dim(); i++)
	{
		cout << "delta(" << i << ") = " << p1.delta(i) << endl;
	}

    cout << "p2 : " << p2 << endl;

    cout << "p3 : " << p3 << endl;
	cout << "p3.dim() : " << p3.dim() << endl;
	p3[0] = 777.0;
	p3[1] = -101;
	cout << "p3 : " << p3 << endl;

    p3 -= 1.5;
    cout << "p3 : " << p3 << endl;
    cout << "new p : " << (p3 * 2) - 7 << endl;

/*
	QApplication app(argc, argv);

	Settings * settings = new Settings(argc, argv);

	MainWindow main_windows(settings);
	main_windows.show();

	return app.exec();
    */

    return 0;
}
