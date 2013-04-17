	#include <QtGui>
#include "mw_ngraph.h"


MW_NGraph::MW_NGraph(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::MF_NGraph()
{
	setupUi(this);


QGraphicsScene * scene =new QGraphicsScene(QRectF(-000, 0, 600, 600));


/*
uuu=new Gr_View(this);
uuu->setScene(scene);
uuu->move(10,10);
uuu->SetSize(365,280);
uuu->ShowGrid(-10,100,-0,50);
uuu->show();
uuu->tmp_init();
connect(scr_h,SIGNAL(valueChanged ( int )),this,SLOT(TstSlot(int)));
connect(this,SIGNAL(sig_scr_h( int )),uuu,SLOT(SetX ( int)));
*/


//----

graphicsView->setScene(scene);
QSize tmp_size;
tmp_size=frame_gr->size();

graphicsView->SetSize(tmp_size.width(),tmp_size.height());//


graphicsView->ShowGrid(-10,100,-10,100);
graphicsView->tmp_init();
connect(scr_h,SIGNAL(valueChanged ( int )),graphicsView,SLOT(SetX(int)));
connect(scr_v,SIGNAL(valueChanged ( int )),graphicsView,SLOT(SetY(int)));

//connect(this,SIGNAL(sig_scr_h( int )),graphicsView,SLOT(SetX ( int)));

//--

//--

Overlay *   overlay = new Overlay(this);

overlay->setGeometry(frame_gr->geometry());
overlay->SetPtrGr_View(graphicsView);
overlay->show();

graphicsView->CalcSlyder();
//emit sig_scr_h(0);//
//emit sig_scr_v(0);//
scr_h->setValue(0);
scr_v->setValue(scr_v->maximum());

}

MW_NGraph::~MW_NGraph()
{
//delete overlay;
}



/*!
    \fn Gr_View::pb_Test_Clicked()
 */
void MW_NGraph::pb_Test_Clicked()
{
	qDebug("void Gr_View::pb_Test_Clicked()");

graphicsView->Scale(2.,1.);
}


void MW_NGraph::TstSlot(int tmp)
{

	qDebug("void MW_NGraph::TstSlot(int) %d",tmp);
	emit sig_scr_h(tmp);//

}


/*!
    \fn MW_NGraph::pb_Test2_Clicked()
 */
void MW_NGraph::pb_Test2_Clicked()
{
qDebug("void MW_NGraph::pb_Test2_Clicked()");
qDebug("3 graphicsView->viewport()->width()%d",graphicsView->viewport()->width());
graphicsView->CalcSlyder();

}


/*!
    \fn MW_NGraph::pb_Test3_Clicked()
 */
void MW_NGraph::pb_Test3_Clicked()
{
graphicsView->tmp3();
}


/*!
    \fn MW_NGraph::sb_ScaleX_Changed(double)
 */
void MW_NGraph::sb_ScaleX_Changed(double tmp )
{

graphicsView->Scale(tmp,sb_ScaleY->value());
}


/*!
    \fn MW_NGraph::sb_ScaleY_Changed(double)
 */
void MW_NGraph::sb_ScaleY_Changed(double tmp)
{

	graphicsView->Scale(sb_ScaleX->value(),tmp);	
}
