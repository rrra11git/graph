#include <QApplication>
#include <QtGui>

#include "mw_ngraph.h"

// ----------------------------------------------------------------------
int main(int argc, char** argv) 
{
	QApplication app(argc, argv);
	MW_NGraph form;
	form.show();
//	form->setAttribute(Qt::WA_DeleteOnClose, true);
	return app.exec();

}



