#ifndef MW_NGRAPH_H
#define MW_NGRAPH_H

#include <QWidget>

#include "gr_view.h"
#include "ui_mf_ngraph.h"
#include "overlay.h"



class MW_NGraph : public QWidget,  public Ui::MF_NGraph
{
  Q_OBJECT

public:
  MW_NGraph(QWidget* parent = 0, Qt::WFlags fl = 0 );
  ~MW_NGraph();

//Gr_View * uuu;
Overlay *   overlay;
  /*$PUBLIC_FUNCTIONS$*/



public slots:
  /*$PUBLIC_SLOTS$*/
void	pb_Test_Clicked();
    void TstSlot(int);
    void pb_Test2_Clicked();
    void pb_Test3_Clicked();
    void sb_ScaleX_Changed(double);
    void sb_ScaleY_Changed(double);
protected:
  /*$PROTECTED_FUNCTIONS$*/

protected slots:
  /*$PROTECTED_SLOTS$*/

signals:
void sig_scr_h(int);


};

#endif



