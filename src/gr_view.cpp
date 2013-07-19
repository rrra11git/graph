#include <QPointF>
#include <QtGui>

#include "gr_view.h"
#include "mw_ngraph.h"
#include "node.h"

#define margin_right 20
#define margin_top 10



Gr_View::Gr_View ( QWidget * parent_ ) :QGraphicsView ( parent_ ),N_Graph()
{
	qDebug ( "Gr_View::Gr_View" );
	setFrameStyle ( QFrame::Box );

	scale_x_GV=1;
	scale_y_GV=1;

	old_view_x=1;
	new_view_x=1;



setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );

QFrame* parent_fr=(QFrame*)parent_;

parent=(MW_NGraph*)parent_fr->parent();;
///parent=(MW_NGraph*)parent_;

setMouseTracking(true);
setDragMode(QGraphicsView::RubberBandDrag);
/*
     myMenu.addAction("Menu Item 1");
     myMenu.addAction("Menu Item 2");
     myMenu.addAction("Menu Item 3");
     myMenu.addAction("Menu Item 4");
*/
setContextMenuPolicy(Qt::ActionsContextMenu);
//setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);


createActions();
}

Gr_View::~Gr_View()
{

}



void Gr_View::paintEvent ( QPaintEvent *pe )
{


	QGraphicsView::paintEvent ( pe );
/*
	QPainter painter;//(viewport());
	painter.begin ( viewport() );

	painter.setRenderHint ( QPainter::Antialiasing );
	painter.fillRect ( QRectF ( 0, 0, text_space_x, height() )     , QBrush ( Qt::yellow ) );
	painter.fillRect ( QRectF ( 0,height()-text_space_y,width(),text_space_y ), QBrush ( Qt::yellow ) );


	painter.setPen ( QPen ( QColor ( 0,0,0 ),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin ) );
	painter.drawPath ( rectPath );
	painter.fillPath ( textPath, Qt::black );


	painter.setPen ( QPen ( QColor ( 0x80,0x80,0x80,100 ),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin ) );

	painter.drawPath ( gridPath );
	painter.end();
*/
}

/*!
    \fn Gr_View::SetSize(doule,double)
 */
void Gr_View::SetSize ( double tmp_w,double tmp_h )
{

	text_space_x=60.5;//60.5
	text_space_y=60.5;//+18

//	parent->hSpacer->changeSize(text_space_x-0.5,10,QSizePolicy::Fixed,QSizePolicy::Fixed);
//	parent->hSpacer->changeSize(text_space_y-0.5,10,QSizePolicy::Fixed,QSizePolicy::Fixed);



base_scene_size_x=scene()->width();

//setGeometry (text_space_x,0.5,tmp_w-text_space_x,210);//210

//--------
//qApp->processEvents();
setGeometry (text_space_x,0.5+35,tmp_w-text_space_x-45,tmp_h-text_space_y-35);//ERROR!!!!
/*
35=10+margin_right+larrow
*/

int uuuu=2;
//qDebug("-----------(())-------------- %d",uuuu);
qDebug()<<"-----------(())-------------- "<<tmp_h-text_space_y;
qDebug()<<"-----------()-------------- "<<tmp_h;
//--------

	//resize ( tmp_w-text_space_x-0.0,tmp_h-text_space_y-0.0 );


	setAlignment ( Qt::AlignLeft | Qt::AlignBottom );
	qApp->processEvents();
//scene()->setBackgroundBrush(Qt::blue);
//--------
	SetBasePoint ( text_space_x,tmp_h-text_space_y );//text_space

//	Set_W_H ( tmp_w-text_space_x-4.5,tmp_h-text_space_y-4.5 );//-18
	Set_W_H ( tmp_w-text_space_x-margin_right,tmp_h-text_space_y-margin_top );//
	CalcBaseScene();




	first_x=-1;
	first_y=-1;

}




/*!
    \fn Gr_View::scrollContentsBy ( int dx, int dy )
 */
void Gr_View::scrollContentsBy ( int dx, int dy )
{
	QGraphicsView::scrollContentsBy ( dx,  dy );
//	Draw_Gr_();
}


/*!
    \fn Gr_View::tmp_init()
 */
void Gr_View::tmp_init()
{


/*
	data_point.push_back ( QPointF ( -0,0 ) );
	data_point.push_back ( QPointF ( 10,10 ) );
	data_point.push_back ( QPointF ( 20,20 ) );
	data_point.push_back ( QPointF ( 30,40 ) );
	data_point.push_back ( QPointF ( 40,40 ) );
	data_point.push_back ( QPointF ( 70,40 ) );
	data_point.push_back ( QPointF ( 20,80 ) );
	data_point.push_back ( QPointF ( 20,150 ) );
	data_point.push_back ( QPointF ( 20,240 ) );
	data_point.push_back ( QPointF ( 20,340 ) );
	data_point.push_back ( QPointF ( 20,440 ) );
	data_point.push_back ( QPointF ( 20,540 ) );


	data_point.push_back ( QPointF ( 20,720 ) );
	data_point.push_back ( QPointF ( 20,730 ) );
	data_point.push_back ( QPointF ( 20,740 ) );
	data_point.push_back ( QPointF ( 20,750 ) );



	data_point.push_back ( QPointF ( 1000,40 ) );
	data_point.push_back ( QPointF ( 3140,40 ) );
	data_point.push_back ( QPointF ( 3100,40 ) );
	data_point.push_back ( QPointF ( 3000,40 ) );
*/
//	data_point.push_back(QPointF(70,50));

	/**/
	for(double tmp=0;tmp<220;tmp=tmp+10)
	{
			data_point.push_back(QPointF(tmp,tmp));
	}
	

//AddData(data_point);
//ConvertCoord(data_point);
//	AddData ( ConvertCoord ( data_point ) );
	AddData (  data_point  );
//scale_x
}


/*!
    \fn Gr_View::AddData(std::vector<QPointF> tmp_point)
 */
void Gr_View::AddData ( std::vector<QPointF> tmp_point1 )
{
//	static QPointF tmp_point;

std::vector<QPointF> tmp_point;
tmp_point=ConvertCoord(tmp_point1);

	std::vector<QPointF>::iterator tmp_it;
	for ( tmp_it=tmp_point.begin();tmp_it!=tmp_point.end();tmp_it++ )
	{
//		( *tmp_it ).setX ( ( *tmp_it ).x() );//-3.5
//		( *tmp_it ).setY ( ( *tmp_it ).y() );//-3.5

//		QGraphicsEllipseItem * oops=scene ()->addEllipse(QRectF (*tmp_it,QSizeF (7,7)),QPen(),QBrush(Qt::blue));
//		oops->setFlags(QGraphicsItem::ItemIsMovable);

		QGraphicsRectItem * oops=scene ()->addRect ( QRectF ( *tmp_it,QSizeF ( 7,7 ) ),QPen(),QBrush ( Qt::blue ) );
		oops->setFlags(QGraphicsItem::ItemIsMovable  );//|QGraphicsItem::ItemIsSelectable
//		oops->setFlags(QGraphicsItem::ItemIgnoresTransformations);
///-----

		Node *  fig_my=new  Node();
		fig_my->setPos(QPointF(*tmp_it));
		scene()->addItem(fig_my);

///-----
		qDebug("(*tmp_it).x() %f",(*tmp_it).x());
	}
}


/*!
    \fn Gr_View::ConvertCoord(QPoint)
 */
std::vector<QPointF>  Gr_View::ConvertCoord ( std::vector<QPointF> tmp_point )
{
	std::vector <QPointF> result;

	static	QPointF res_point;
	std::vector<QPointF>::iterator tmp_it;


	for ( tmp_it=tmp_point.begin();tmp_it!=tmp_point.end();tmp_it++ )
	{
		result.push_back ( QPointF ( ( *tmp_it ).x() *scale_x+Base_X_Scene   -first_x*scale_x , Base_Y_Scene- ( *tmp_it ).y() *scale_y+first_y*scale_y ) );
//		result.push_back ( QPointF ( ( *tmp_it ).x() *scale_x+Base_X_Scene   -first_x*scale_x , Base_Y_Scene- ( *tmp_it ).y() *scale_y+first_y*scale_y ) );

	}

	return result;
}


/*!
    \fn Gr_View::CalcBaseScene()
 */
void Gr_View::CalcBaseScene()
{
	Base_X_Scene=0.0;// ( int ) Base_X;///scale_x_GV;//+(int)text_space_x;
qDebug("Base_X_Scene %f scale_x %f",Base_X_Scene,scale_x);
	D_Y_Scene=scene()->height()-viewport()->height()-0;
//	Base_Y_Scene=/**/D_Y_Scene+Base_Y;//tmp_y;
	Base_Y_Scene=scene()->height();//tmp_y;
}


/*!
    \fn Gr_View::resizeEvent ( QResizeEvent * event )

void Gr_View::resizeEvent ( QResizeEvent * event )
{
qDebug("void Gr_View::resizeEvent ( QResizeEvent * event ) ");
QWidget::resizeEvent ( event ) ;
CalcBaseScene();

}

 */




void Gr_View::SetBegin_XY ( double tmp_x, double tmp_y )
{
	double coord_scene_x;
	double coord_scene_y;
	std::vector<QPointF> tmp_vec;
	std::vector<QPointF> tmp_res;

	tmp_vec.push_back ( QPointF ( tmp_x,tmp_y ) );
	tmp_res=ConvertCoord ( tmp_vec );
	coord_scene_x= ( *tmp_res.begin() ).x();
	coord_scene_y= ( *tmp_res.begin() ).y();

	ensureVisible ( coord_scene_x-Base_X_Scene+1,coord_scene_y, viewport()->width() ,10000,0,0 );

	qDebug ( "coord_scene_x=%f",coord_scene_x );
	qDebug ( "coord_scene_y=%f",coord_scene_y );


///
	QPointF tmmp,oops;
	tmmp= mapToScene ( 0,0 );
	Draw_Gr ( tmp_x, ( D_Y_Scene-tmmp.y() ) /scale_y+first_y );//,(D_Y_Scene-tmmp.y()+lenght_axis_v)/scale_y+first_y

	viewport()->update();

	/*
		Draw_Gr((first_x+tmmp.x()/scale_x),first_x+((tmmp.x())+lenght_axis_h)/scale_x,
	( D_Y_Scene-tmmp.y())/scale_y+first_y,(D_Y_Scene-tmmp.y()+lenght_axis_v)/scale_y+first_y);//
	*/
///
}



/*!
    \fn Gr_View::ShowGrid(double ,double,double ,double)
 */
void Gr_View::ShowGrid ( double x_beg,double tmp_diap_x,double y_beg,double tmp_diap_y )
{
	first_x=x_beg;
	first_y=y_beg;
	diap_x=tmp_diap_x;
	diap_y=tmp_diap_y;

	diap_base_x=tmp_diap_x;
	diap_base_y=tmp_diap_y;



	CalcData ( x_beg,y_beg );//x_beg+diap_x,,y_beg+diap_y
	SetBegin_XY ( first_x, first_y );

}


/*!
    \fn Gr_View::Scale(qreal,qreal)
 */
void Gr_View::Scale ( qreal sc_x,qreal sc_y )
{
	qDebug("new scale x =%f scale y %f",sc_x,sc_y);
static qreal old_scale_x=1.;
static qreal old_scale_y=1.;

if(100.<scale_x_GV || scale_x_GV<0.01) {qDebug("ERROR SCALE");return;}

old_view_x=viewport()->width()/scale_x_GV;

	scale ( 1./old_scale_x*sc_x,1./old_scale_y*sc_y );

//	scale ( sc_x,1. );


//	scale_x_GV=scale_x_GV*sc_x;
//	diap_x=diap_x/sc_x;

	old_scale_x=sc_x;
	scale_x_GV=sc_x;
	diap_x=diap_base_x/sc_x;


	old_scale_y=sc_y;
	scale_y_GV=sc_y;
	diap_y=diap_base_y/sc_y;


new_view_x=viewport()->width()/scale_x_GV;
qDebug("scale_x_GV %f",scale_x_GV);
qDebug("scale_y_GV %f",scale_y_GV);
tmp3();
CalcSlyder();
SetSlyder();
return;


}




/*!
    \fn Gr_View::CalcSlyder(int,int,int)
 */
void Gr_View::CalcSlyder()
{
	parent->scr_h->setMinimum ( 0);
	parent->scr_h->setMaximum (scene()->width()-(viewport()->width())/scale_x_GV);// +10*scale_x*(1/scale_x_GV));
	parent->scr_h->setPageStep((viewport())->width());///scale_x_GV
//
	parent->scr_v->setMinimum ( 0);
	parent->scr_v->setMaximum (scene()->height()-(height())/scale_y_GV);// +10*scale_x*(1/scale_x_GV));
	parent->scr_v->setPageStep((viewport())->height());///scale_y_GV
//

	QPointF tmmp;
	tmmp= mapToScene ( -0,0 );
//if(tmmp.x()>=9653) 	parent->scr_h->setValue (9653);
//	else 

//parent->scr_v->setValue (scene()->height()-(viewport()->height())/scale_y_GV-tmmp.y());

//parent->scr_h->setValue (tmmp.x());
//parent->scr_v->setValue (tmmp.y());
}


/*!
    \fn Gr_View::Draw_Gr()
 */
void Gr_View::Draw_Gr_()
{
//qDebug("void Gr_View::Draw_Gr_()");
	QPointF tmmp,oops;
//	tmmp= mapToScene ( -0,height()+0.5 );
	tmmp= mapToScene ( -0,0 );


	Draw_Gr ( ( first_x+(tmmp.x())/scale_x ),  (scene()->height()-height()/scale_y_GV-tmmp.y() ) /scale_y+first_y );//
//	Draw_Gr ( ( first_x+(tmmp.x())/scale_x ), (600.-tmmp.y()) /scale_y+first_y );//

qDebug("aaaaa %.14f", (scene()->height()-height()-tmmp.y() ) /scale_y+first_y);
//	qDebug("D_Y_Scene%f",D_Y_Scene);
	qDebug("Draw_Gr_() _tmmp.y() %f",tmmp.y());
//	qDebug("height()%f",height());
//	qDebug("scale_y%f",scale_y);

	viewport()->update();

	parent->frame_gr->update();

}


/*!
    \fn Gr_View::tmp1()
 */



/*!
    \fn Gr_View::tmp3()
 */
void Gr_View::tmp3()
{return;
	qDebug("void Gr_View::tmp3()");
	static double sum_appendix;
	double new_appendix;

	new_appendix=(new_view_x-old_view_x)/2.;
	sum_appendix+=new_appendix;
qDebug("sum_appendix= %f",sum_appendix);
qDebug("scene()->width () %f",scene()->width());
	if(sum_appendix<=0) 
	{
		qDebug("NO CUT");
		return;
	}

	QRectF tmp_rect;
	tmp_rect=	sceneRect ();

	scene()->setSceneRect ( tmp_rect.x(),tmp_rect.y(),600.+sum_appendix,tmp_rect.height() );///base_scene_size_x


}

/*!
    \fn Gr_View::SetX ( int)
 */
void Gr_View::SetX ( int tmp)
{
	qDebug("void Gr_View::SetX ( int tmp) %d",tmp);
	SetXY(tmp,parent->scr_v->maximum ()-parent->scr_v->value());

}	



/*!
    \fn Gr_View::SetY(int)
 */
void Gr_View::SetY(int tmp)
{

qDebug("void Gr_View::SetY(int tmp) %d",tmp);
//parent->scr_v->setValue (scene()->height()-(viewport()->height())/scale_y_GV-tmmp.y());
//qDebug(" YYYYYY %d",100-tmp);
//		SetXY(parent->scr_h->value(),scene()->height()-(viewport()->height())/scale_y_GV-tmp);
		SetXY(parent->scr_h->value(),parent->scr_v->maximum ()-tmp);

}


/*!
    \fn Gr_View::SetXY(int, int)
 */
void Gr_View::SetXY(int tmp_x, int tmp_y)
{
	qDebug("  void Gr_View::SetXY(int tmp_x, int tmp_y) %d %d",tmp_x,tmp_y);
/*
	ensureVisible ( tmp_x,(scene()->height()-height()-tmp_y -0.0000),
				 viewport()->width()/scale_x_GV,
				(height()/scale_y_GV),0,0 );///
*/


	ensureVisible ( tmp_x,(scene()->height()-height()/scale_y_GV)-tmp_y +0.80000,
				 (viewport()->width()-1)/scale_x_GV,
				((height()-1)/scale_y_GV),0.,0. );///


/*
	ensureVisible ( tmp_x,(390.-(double)tmp_y )+0.8,
				 viewport()->width()/scale_x_GV,
				209/scale_y_GV,0,0 );///

*/

qDebug("bbb    %.14f", (scene()->height()-height()/scale_y_GV)-tmp_y -0.0000);
qDebug("ccc %f",(height()-1)/scale_y_GV);
//qDebug("ddd %f",height());
//qDebug("eee %f",viewport()->height());
	Draw_Gr_();

//	Draw_Gr ( ( first_x+(tmp_x)/scale_x ),  (scene()->height()-height()/scale_y_GV-tmp_y ) /scale_y+first_y );//
//	parent->frame_gr->update();

	
}


/*!
    \fn Gr_View::SetSlyder()
 */
void Gr_View::SetSlyder()
{qDebug("void Gr_View::SetSlyder()");
	QPointF tmmp,oops;
	tmmp= mapToScene ( 0,0 );//Base_Y
	parent->scr_v->setValue (tmmp.y());
	parent->scr_h->setValue (tmmp.x());
qDebug(" parent->scr_v->setValue (tmmp.y())%f",tmmp.y());
qDebug(" parent->scr_h->setValue (tmmp.x())%f",tmmp.x());
Draw_Gr_();
}


/*!
    \fn Gr_View::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
 */
void Gr_View::mouseMoveEvent (  QMouseEvent * mouseEvent ) //QGraphicsSceneMouseEvent
{
	static int tmp;
	//qDebug("mouseMoveEvent %d",tmp++);

	if( items(mouseEvent->pos()).size() )
	{
	//	qDebug(" yes");
	} //else qDebug("no");
	QGraphicsView::mouseMoveEvent(mouseEvent);
}




void Gr_View::mousePressEvent(QMouseEvent *event)
{
	if(event->button() ==  Qt::RightButton )
	{
		unsigned char is_element;
		
		if( items(event->pos()).size() )
		{
			qDebug("yes el");
			QPoint gl_point;
			is_element=1;
//			gl_point=mapToGlobal(event->pos());
//			myMenu.exec(gl_point);//globalPos

		}else is_element=0;
		
		CorrectAction(is_element);
//		tmp_point=event->pos();

//		posFirst.setX( event->pos().x() );
//		posFirst.setY( event->pos().y() );
//		pressed = true;
//		selectionLine->setVisible(true);
		qDebug("press R");


	}	else	qDebug("press L");

    QGraphicsView::mousePressEvent(event);
}


void Gr_View::mouseReleaseEvent(QMouseEvent *event)
{
	qDebug("mouseReleaseEvent");
//	is_element=0;
	QGraphicsView::mouseReleaseEvent(event);
}


void Gr_View::createActions()
{
	action_1 = new QAction(tr("Menu_1"), this);
	action_1->setIcon(QIcon(":/pict/copy.png"));
//	action_1->setShortcut(tr("Ctrl+1"));
	insertAction(0,action_1);
	connect(action_1, SIGNAL(triggered()), this, SLOT(Menu_1()));

	action_2 = new QAction(tr("Menu_2"), this);
	action_2->setIcon(QIcon(":/pict/cut.png"));
//	action_2->setShortcut(tr("Ctrl+2"));
	insertAction(0,action_2);
	connect(action_2, SIGNAL(triggered()), this, SLOT(Menu_2()));

	action_3 = new QAction(tr("Menu_3"), this);
	action_3->setIcon(QIcon(":/pict/paste.png"));
//	action_3->setShortcut(tr("Ctrl+3"));
	insertAction(0,action_3);
	connect(action_3, SIGNAL(triggered()), this, SLOT(Menu_3()));

	qDebug("actions().size() %d",actions().size());

}

void Gr_View::Menu_1()
{
qDebug("void Gr_View::Menu_1()");

}

void Gr_View::Menu_2()
{
qDebug("void Gr_View::Menu_2()");
}

void Gr_View::Menu_3()
{
qDebug("void Gr_View::Menu_3()");
}


void Gr_View::CorrectAction( unsigned char tmp)
{
	action_1->setEnabled(tmp);
	action_2->setEnabled(tmp);
	action_3->setEnabled(tmp);
}


