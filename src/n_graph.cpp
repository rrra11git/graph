
#include "math.h"

#include "n_graph.h"
#include <stdio.h>
#include <stdbool.h>
#include <complex.h>
#include <QtDebug>
#include <iostream.h>

//#define Sk 3
#define St_l 2
#define larrow 15
#define precision 1

N_Graph::N_Graph()
{

Sk=3.;

	cur_num_stroke_x=10;
	cur_num_stroke_y=8;
	scale_x=1;
	scale_y=1;


}


N_Graph::~N_Graph()
{
}


/*
void N_Graph::paintEvent(QPaintEvent * event)
{
	QPainterPath rectPath1;


	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	//painter.fillRect(event->rect(), QBrush(Qt::white));
	painter.setPen(QPen(QColor (0,0,0),1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));
	painter.drawPath(rectPath);
	painter.fillPath(textPath, Qt::black);


//	painter.drawText(30, 30, tr("x"));

}

*/

void N_Graph::AddAxisH(qreal x_tmp, qreal y_tmp, unsigned long int lengh_tmp,unsigned long int Scur_x  )
{
	rectPath.moveTo (QPointF( x_tmp-Sk,y_tmp ));
	rectPath.lineTo( x_tmp+lengh_tmp, y_tmp);
/**/

	std::vector <std::pair <QString, unsigned long int>  >::iterator it_tmp;
	for(it_tmp=Data_H_Axis.begin();it_tmp!=Data_H_Axis.end();it_tmp++)
	{
		AddStrokeX(Base_X+(*it_tmp).second,Base_Y);
		AddTextH_Axis(Base_X+(*it_tmp).second,Base_Y,(*it_tmp).first,-90);
	}

}

void N_Graph::AddAxisV(qreal x_tmp, qreal y_tmp, unsigned long int lengh_tmp,unsigned long int Scur_y  )
{

	
	rectPath.moveTo (QPointF( x_tmp,y_tmp+Sk ));
	rectPath.lineTo( x_tmp, y_tmp-lengh_tmp);


/**/

	std::vector <std::pair <QString, unsigned long int>  >::iterator it_tmp;
	for(it_tmp=Data_V_Axis.begin();it_tmp!=Data_V_Axis.end();it_tmp++)
	{
		AddStrokeY(Base_X,Base_Y-(*it_tmp).second);
		AddTextV_Axis(Base_X,Base_Y-(*it_tmp).second,(*it_tmp).first,0);
	}

}


void N_Graph::AddStrokeX(qreal x_tmp,qreal y_tmp)
{
	rectPath.moveTo (QPointF( x_tmp,y_tmp-St_l ));
	rectPath.lineTo( x_tmp, y_tmp+St_l);
}

void N_Graph::AddStrokeY(qreal x_tmp,qreal y_tmp)
{

	rectPath.moveTo (QPointF( x_tmp-St_l,y_tmp ));
	rectPath.lineTo( x_tmp+St_l, y_tmp);
}


void N_Graph::AddArrow(qreal x_tmp,qreal y_tmp,double rotat)
{
//return;
	QMatrix rotationMatrix;
	rotationMatrix.translate(x_tmp,y_tmp);	
	rotationMatrix.rotate(rotat);

	QPainterPath rectPath1;
	
	rectPath1.moveTo (QPointF( 0,0 ));
	rectPath1.lineTo(0,-2);
	rectPath1.lineTo( larrow,0);
	rectPath1.lineTo( 0,2);
	rectPath1.lineTo( 0,0);

	rectPath.addPath(rotationMatrix.map(rectPath1));

}


void N_Graph::AddTextH_Axis(qreal x_tmp, qreal y_tmp,QString str_tmp, double rotat)
{//return;
	QMatrix rotationMatrix;

	QPainterPath tmpPath;
	QFont font;
	font.setPixelSize(10);
	QRect fontBoundingRect = QFontMetrics(font).boundingRect(str_tmp);
	unsigned long int width_font=fontBoundingRect.width ();
	width_font=QFontMetrics(font).width(str_tmp);

	unsigned long int height_font=QFontMetrics(font).height();

	rotationMatrix.translate(x_tmp+4,y_tmp+width_font+10);	//height_font/4
	rotationMatrix.rotate(rotat);

	tmpPath.addText(QPointF(0,0), font, str_tmp);
	textPath.addPath(rotationMatrix.map(tmpPath));
	
}



/*!
    \fn N_Graph::SetDiapH()
 */
void N_Graph::SetDiapH(double min_tmp,double tmp_max)//, unsigned long int lenght_tmp
{
	QString tmp_string;
	double d_val,cur_value;
	d_val=CalcOptimumStep_H_Value(min_tmp,tmp_max);

	double num_st_v=(tmp_max-min_tmp)/d_val;//кол-во шагов
	double st_px=lenght_axis_h/num_st_v;//lenght 1st in px	
	double k1;
	
	//величина до первого штриха
	if(min_tmp<0)
	{
		k1=fabs(fmod(min_tmp,d_val));//-
		if(!k1) k1=d_val;
	}
	else k1=fabs(d_val)-fabs(fmod(min_tmp,d_val));//+

//	if(k1<0.00000001){k1=d_val;qDebug("????????");};//если кратно шагу значения (k1=0) выставляем=шагу значения

//	qDebug("k1_ %20.17f",k1);
	double oops=k1/d_val*st_px;///смещение (px) до первого штриха



	tmp_string.setNum(min_tmp,'f',precision);//
	par_val=std::make_pair(tmp_string,0);//надпись и смещение штриха относительно 0
	Data_H_Axis.push_back(par_val);


	double cur_l;
	cur_l=oops;//-25;

	cur_value=       floor (   (min_tmp+d_val)/d_val)*d_val;//значение для первого штриха

	for(double tmp=cur_value;tmp<tmp_max;tmp+=d_val)
	{
	
		tmp_string.setNum(tmp);//,'e'
//		qDebug("setNum----H-%s",(tmp_string.toAscii ()).constData ());
									///РАЗОБРАТЬСЯ!!!!!!!floor(cur_l+1.0)
		par_val=std::make_pair(tmp_string,floor(cur_l+0.999));//надпись и смещение штриха относительно 0
//		par_val=std::make_pair(tmp_string,ceil(cur_l));//надпись и смещение штриха относительно 0
//		qDebug("delta H %f",cur_l- floor(cur_l+0.999)  );
		Data_H_Axis.push_back(par_val);
//		qDebug("H ----cur_l %f",cur_l);
		cur_l+=st_px;
	}

	tmp_string.setNum(tmp_max,'f',precision);
	par_val=std::make_pair(tmp_string,lenght_axis_h);//надпись и смещение штриха относительно 0
	Data_H_Axis.push_back(par_val);

//что бы не накладывался текст
/**/
	if(Data_H_Axis.size()>=4) //на всякий случай
	{
		if(  (*(Data_H_Axis.begin()+1)).second<10) (*( Data_H_Axis.begin() +1 )).first="";//для первого штриха

		if( (  ( (*(Data_H_Axis.end()-1)).second) - (*(Data_H_Axis.end()-2)).second)<10 )
			(*( Data_H_Axis.end() -2 )).first="";//для предпоследнего
	}

}


/*!
    \fn N_Graph::CalcOptimumStep_H_Value(double,double)
 */
double N_Graph::CalcOptimumStep_H_Value(long double  val_min,long double  val_max)
{
	long double base_step_val;//
	double res; 
	double st;

	base_step_val=(val_max-val_min)/cur_num_stroke_x;
	st= floor(log10 (base_step_val));
	res=base_step_val+0.51*pow(10,st);//floor(ost+0.05)*
	res=((int)(res/pow(10,(st))))*pow(10,st);
	return res;

}




/*!
    \fn N_Graph::SetBasePoint(qreal,qreal)
 */
void N_Graph::SetBasePoint(qreal tmp_x,qreal tmp_y)
{
	Base_X=tmp_x;
	Base_Y=tmp_y;
}


/*!
    \fn N_Graph::Set_W_H(unsigned long int, unsigned long int)
 */
void N_Graph::Set_W_H(unsigned long int tmp_w, unsigned long int tmp_h)
{
	Wa=tmp_w;
	Ha=tmp_h;

	lenght_axis_h=Wa-larrow-10;//-Sk-25
	lenght_axis_v=Ha-larrow-10;//-Sk-25

}


/*!
    \fn N_Graph::Draw_Gr(double, double)
 */
void N_Graph::Draw_Gr(double min_tmp_x, double min_tmp_y)//double max_tmp_x,, double max_tmp_y
{
//qDebug("Draw_Gr min_tmp_x %f  min_tmp_y %f",min_tmp_x,min_tmp_y);


double cur_x_min;//������� ����������� �������� �� �
double cur_y_min;

cur_x_min=min_tmp_x;
cur_y_min=min_tmp_y;

		 rectPath=QPainterPath();
		 textPath=QPainterPath();
		 gridPath=QPainterPath();
Data_H_Axis.clear();
Data_V_Axis.clear();

	SetDiapH(min_tmp_x,min_tmp_x+diap_x);//, Wa-Sk-25
	SetDiapV(min_tmp_y,min_tmp_y+diap_y);//, Ha-Sk-25




AddGrid();

	
	AddAxisH(Base_X,Base_Y, Wa-0,50);//-Sk
	AddAxisV(Base_X,Base_Y, Ha-0,10);//-Sk
	
	AddArrow(Base_X+Wa-larrow,Base_Y,0);//-Sk
	AddArrow(Base_X,Base_Y-Ha+larrow,-90);//-Sk

}

void N_Graph::AddTextV_Axis(qreal x_tmp, qreal y_tmp,QString str_tmp, double rotat)
{

	QMatrix rotationMatrix;

	QPainterPath tmpPath;
	QFont font;
	font.setPixelSize(10);
	QRect fontBoundingRect = QFontMetrics(font).boundingRect(str_tmp);
	unsigned long int width_font=fontBoundingRect.width ();
	width_font=QFontMetrics(font).width(str_tmp);

	unsigned long int height_font=QFontMetrics(font).height();

//	rotationMatrix.translate(x_tmp+4,y_tmp+width_font+10);	//height_font/4
	rotationMatrix.translate(x_tmp-width_font-10,y_tmp+4);	//height_font/4

	rotationMatrix.rotate(rotat);

	tmpPath.addText(QPointF(0,0), font, str_tmp);
	textPath.addPath(rotationMatrix.map(tmpPath));

/*
*/	
}



double N_Graph::CalcOptimumStep_V_Value(double  val_min,double  val_max)
{

return CalcOptimumStep_H_Value(val_min,val_max);

	unsigned char num_dec=0;///кол-во разрядов
	double res; 
	double tmp;
	double base_step_val;
	base_step_val=(val_max-val_min)/cur_num_stroke_y;
	
	if (base_step_val<1) return res=1;
	
	

	
	do
	{
		tmp=base_step_val/10;
		num_dec++;
		base_step_val=tmp;
	}
	while (tmp>1);
	
	return (((int)((base_step_val+0.05)*10))/10. *pow(10,num_dec));
}

void N_Graph::SetDiapV(double min_tmp,double tmp_max)//, unsigned long int lenght_tmp
{



///-------------
	QString tmp_string;
	double d_val,cur_value;
	d_val=CalcOptimumStep_V_Value(min_tmp,tmp_max);

	double num_st_v=(tmp_max-min_tmp)/d_val;//кол-во шагов
	double st_px=lenght_axis_v/num_st_v;//lenght 1st in px	
	double k1;
	
	//величина до первого штриха
	if(min_tmp<0)
	{
		k1=fabs(fmod(min_tmp,d_val));//-
		if(!k1) k1=d_val;
	}
	else k1=fabs(d_val)-fabs(fmod(min_tmp,d_val));//+

	double oops=k1/d_val*st_px;///смещение (px) до первого штриха

///--------

	tmp_string.setNum(min_tmp,'f',precision);
	par_val=std::make_pair(tmp_string,0);//надпись и смещение штриха относительно 0
	Data_V_Axis.push_back(par_val);
	double cur_l;
	cur_l=oops;//


	cur_value=       floor (   (min_tmp+d_val)/d_val)*d_val;//значение для первого штриха
/**/

	for(double tmp=cur_value;tmp<tmp_max;tmp+=d_val)
	{
	
		tmp_string.setNum(tmp);//,'e',12
//		qDebug("setNum-----V %s",(tmp_string.toAscii ()).constData ());

								///РАЗОБРАТЬСЯ !!!! ,floor(cur_l-0.5))
		par_val=std::make_pair(tmp_string,ceil(cur_l-2.5));//надпись и смещение штриха относительно 0
//		qDebug("delta V %f",cur_l- ceil(cur_l-2.5)  );
		Data_V_Axis.push_back(par_val);
//		qDebug("V ----cur_l %f",cur_l);
		cur_l+=st_px;
	}

	tmp_string.setNum(tmp_max,'f',precision);
	par_val=std::make_pair(tmp_string,lenght_axis_v);//надпись и смещение штриха относительно 0
	Data_V_Axis.push_back(par_val);


//что бы не накладывался текст

	if(Data_H_Axis.size()>=4) //на всякий случай
	{
		if(  (*(Data_V_Axis.begin()+1)).second<10) (*( Data_V_Axis.begin() +1 )).first="";//для первого штриха

		if( (  ( (*(Data_V_Axis.end()-1)).second) - (*(Data_V_Axis.end()-2)).second)<10 )
			(*( Data_V_Axis.end() -2 )).first="";//для предпоследнего
	}



}

/*!
    \fn N_Graph::AddGrid()
 */
	
void N_Graph::AddGrid()
{

	unsigned char out_grig=3;
	std::vector <std::pair <QString, unsigned long int>  >::iterator it_tmp_x,  it_tmp_y;

	for(it_tmp_y=Data_V_Axis.begin()+1;it_tmp_y!=Data_V_Axis.end();it_tmp_y++)
	{
		gridPath.moveTo (QPointF( Base_X,Base_Y- (*it_tmp_y).second));
		gridPath.lineTo( QPointF(Base_X+(*(Data_H_Axis.end()-1)).second+out_grig,  Base_Y- (*it_tmp_y).second));
	}
/**/
	for(it_tmp_x=Data_H_Axis.begin()+1;it_tmp_x!=Data_H_Axis.end();it_tmp_x++)
	{
		gridPath.moveTo (QPointF( Base_X+ (*it_tmp_x).second,Base_Y));
		gridPath.lineTo( QPointF(Base_X+(*it_tmp_x).second,    Base_Y-(*(Data_V_Axis.end()-1)).second-out_grig));
	}

}


/*!
    \fn N_Graph::AddData(std::vector<QPointF>)

void N_Graph::AddData(std::vector<QPointF> tmp_point)
{
	std::vector<QPointF>::iterator tmp_it;
	for (tmp_it=tmp_point.begin();tmp_it!=tmp_point.end();tmp_it++)
	{
		
	}

}
 */

/*!
    \fn N_Graph::CalcData(double tmp_w,double tmp_h)

void N_Graph::CalcData(double first_h_diap,double first_v_diap)//
{

	Draw_Gr( first_h_diap,  first_v_diap);//second_h_diap,, second_v_diap

}
 */

/*!
    \fn N_Graph::SetDiap_X(double)
 */
void N_Graph::SetDiap_X(double tmp)
{
	diap_x=tmp;
	scale_x=lenght_axis_h/diap_x;//(second_h_diap-first_h_diap)

}


/*!
    \fn N_Graph::SetDiap_Y(double)
 */
void N_Graph::SetDiap_Y(double tmp)
{
	diap_y=tmp;
	scale_y=lenght_axis_v/diap_y;//(second_v_diap-first_v_diap)
}
