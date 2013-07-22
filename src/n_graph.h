#ifndef N_GRAPH_H
#define N_GRAPH_H

#include<QtGui>
#include <QPainterPath>



class N_Graph
{
//	Q_OBJECT

	public:
		N_Graph();
		~N_Graph();


//		unsigned long int SmX;

    void SetBasePoint(qreal,qreal);
    void Set_W_H(unsigned long int, unsigned long int);
    void SetDiap_Y(double);
    void SetDiap_X(double);

    void Draw_Gr(double, double);//,double,double

 //   void AddData(std::vector<QPointF>);
//    void CalcData(double ,double);// ���������� ��������� ��������  


//	std::vector<unsigned long int>:: iterator optim_delta_it;
		QPainterPath rectPath;
		QPainterPath textPath;
		QPainterPath gridPath;




	double  scale_x;
	double  scale_y;





	private:

double Sk;

	qreal Base_X;
	qreal Base_Y;

	double diap_x;//������������ �������� �� �
	double diap_y;	
    void AddGrid();


	unsigned long int lenght_axis_h;
	unsigned long int lenght_axis_v;



		unsigned long int Wa;
		unsigned long int Ha;
//		void paintEvent(QPaintEvent *);
		void AddAxisH(qreal x_tmp, qreal y_tmp, unsigned long int lengh_tmp,unsigned long int Scur_x  );
		void AddAxisV(qreal x_tmp, qreal y_tmp, unsigned long int lengh_tmp,unsigned long int Scur_x  );

		void AddTextH_Axis(qreal x_tmp, qreal y_tmp,QString str_tmp, double rotat);
		void AddTextV_Axis(qreal x_tmp, qreal y_tmp,QString str_tmp, double rotat);

		void SetDiapH(double,double);//, unsigned long int
		void SetDiapV(double,double);//, unsigned long int

		double CalcOptimumStep_H_Value(long double ,long double );
		double CalcOptimumStep_V_Value(double ,double );

		unsigned long int cur_num_stroke_x; // минимальное кол-во штрихов по X
		unsigned long int cur_num_stroke_y; // минимальное кол-во штрихов по X

		void AddStrokeX(qreal x_tmp,qreal Y_tmp);
		void AddStrokeY(qreal x_tmp,qreal Y_tmp);
		void AddArrow(qreal x_tmp,qreal y_tmp,double rotat);		

	std::vector <std::pair <QString, unsigned long int>  >Data_H_Axis;
	std::vector <std::pair <QString, unsigned long int>  >Data_V_Axis;

	std::pair <QString, unsigned long int>   par_val;
	




	public slots:


};
 

#endif