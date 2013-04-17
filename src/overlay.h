#ifndef OVERLAY_H 
#define OVERLAY_H

#include <QWidget>
#include "gr_view.h"
 
class Overlay : public QWidget
{
	public:
		Overlay(QWidget *parent=0);
		void	SetPtrGr_View(Gr_View *);
		Gr_View * p_gr_view;

	
	protected:
		void paintEvent(QPaintEvent *event);

};

#endif