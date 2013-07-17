#ifndef Gr_VIEW_H
#define Gr_VIEW_H


#include <QGraphicsView>
#include "n_graph.h"

class MW_NGraph;

class Gr_View : public QGraphicsView, public N_Graph
{
	Q_OBJECT


	public:
		Gr_View(QWidget * parent = 0);
		void CalcSlyder();
		void ShowGrid(double ,double,double ,double);
		void AddData(std::vector<QPointF> tmp_point);//отрисовка фигур 
		~Gr_View();
		void Scale(qreal,qreal);

		void SetSize(double,double);//set size Gr_View (pcs)
		void tmp_init();//add data items (correct this later)
		void tmp3();// 

	private:


		std::vector<QPointF> ConvertCoord(std::vector<QPointF>);//перевод в систему координатсцены для отрисовки
		void CalcBaseScene();//вызывается при изменении высоты сцены

		void SetBegin_XY(double, double);


//    void resizeEvent ( QResizeEvent * event ) ;
	
		double scale_x_GV;
		double scale_y_GV;
		void scrollContentsBy ( int dx, int dy );

		void Draw_Gr_();


    void SetXY(int, int);
    void SetSlyder();

	
		std::vector<QPointF> data_point;

		MW_NGraph * parent;
	double diap_base_x;
	double diap_base_y;

	 QMenu myMenu;


//






		void paintEvent(QPaintEvent *);

		double text_space_x;//ширина поля по X для текста(оси Y)
		double text_space_y;
		double Base_X_Scene;//
		double Base_Y_Scene;//Y сцены соответствующий y=0 нарисованной системе координат
		double D_Y_Scene;
		double base_scene_size_x;

	double old_view_x;
	double new_view_x;



	void createActions();
	void CorrectAction(unsigned char);
	QAction * action_1;
	QAction * action_2;
	QAction * action_3;


	public slots:


	void mouseMoveEvent (  QMouseEvent * mouseEvent );//QGraphicsSceneMouseEvent
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	
	void SetX ( int);
	void SetY(int);
	
	void Menu_1();
	void Menu_2();
	void Menu_3();
};

#endif 