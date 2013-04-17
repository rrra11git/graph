#include <QPainter>
#include <QPen>
#include "overlay.h"
 
Overlay::Overlay(QWidget *parent) : QWidget(parent),p_gr_view(0)
{
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}
 
void Overlay::paintEvent(QPaintEvent *pe)
{


//	QWidget::paintEvent ( pe );
	QPainter painter;//(viewport());
	painter.begin ( this );

	painter.setRenderHint ( QPainter::Antialiasing );
//	painter.fillRect ( QRectF ( 0, 0, text_space_x, height() )     , QBrush ( Qt::yellow ) );
//	painter.fillRect ( QRectF ( 0,height()-text_space_y,width(),text_space_y ), QBrush ( Qt::yellow ) );


	painter.setPen ( QPen ( QColor ( 0,0,0 ),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin ) );
	painter.drawPath ( p_gr_view->rectPath );
	painter.fillPath ( p_gr_view->textPath, Qt::black );


	painter.setPen ( QPen ( QColor ( 0x80,0x80,0x80,100 ),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin ) );

	painter.drawPath ( p_gr_view->gridPath );

	painter.end();




}


void Overlay::SetPtrGr_View(Gr_View * tmp)
{
	p_gr_view=tmp;
}