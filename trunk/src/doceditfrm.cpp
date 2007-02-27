#include <QSqlQuery>
#include <QMenu>
#include <QCloseEvent>
#include <QMessageBox>
//
#include "doceditfrm.h"
#include "vars.h"
#include "addrselectfrm.h"
//
extern QString username, fullname, docfolder, templatefolder;
//
QString opendocID = "";
QString opendocSource = "";
QString b_text = "";
QString docprefix, tnr, companyaddress, docfile;
QStringList vatlist, vatamount, docnames, filename, doccount, docdef;
//
doceditfrm::doceditfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void doceditfrm::init()
{
    QDate date = QDate::currentDate();
    boxdate->setDate(date);
    
    lbluser->setText(username);
    
    docnames.clear();
    docnames << tr("Offer") << tr("Order confirmation") << tr("Delivery note") << tr("Bill");
    
	readdoctab();
    initvat();
    loadmaincfg();
    
    tabmain->setColumnWidth(0,30);
    tabmain->setColumnWidth(1,90);
    tabmain->setColumnWidth(2,20);
    tabmain->setColumnWidth(3,230);
    tabmain->setColumnWidth(4,50);
    tabmain->setColumnWidth(5,40);
    tabmain->setColumnWidth(6,100);
    tabmain->setColumnWidth(7,100);
    tabmain->setColumnWidth(8,50);
    tabmain->setColumnWidth(9,0);
    tabmain->setColumnWidth(10,0);
    tabmain->setColumnWidth(11,0);
    tabmain->setRowCount(1);
    
    mainwidget->setCurrentIndex(1);
    
    opendocID = "";
    opendocSource = "";
    
    QMenu* btnprintmenu = new QMenu( this );
    Q_CHECK_PTR( btnprintmenu );

    QAction* print_preview = new QAction( tr("&Print pre&view"), this );
	connect(print_preview , SIGNAL(triggered()), this, SLOT(printpreview()));
	btnprintmenu->addAction(print_preview);
    QAction* print = new QAction( tr("&Print document"), this );
	connect(print , SIGNAL(triggered()), this, SLOT(print())); 
	btnprintmenu->addAction(print);
    QAction* printesr = new QAction( tr("Paying-in &slip"), this );
	connect(printesr , SIGNAL(triggered()), this, SLOT(printesr())); 
	btnprintmenu->addAction(printesr);		
	btnprint->setMenu(btnprintmenu);
	
	vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }
    
    connect(btnclose, SIGNAL(released()), this, SLOT(close()));
    connect(btnsearchaddr, SIGNAL(released()), this, SLOT(selectaddress()));
    connect(cmbdoc, SIGNAL(activated(int)), this, SLOT(selecteddocument()));
}
//
void doceditfrm::closeEvent( QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void doceditfrm::readdoctab()
{
    cmbdoc->clear();
    filename.clear();
    doccount.clear();
    docdef.clear();
    
    QString qstr = "SELECT name, filename, count, users FROM doctab ORDER BY ID;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		int tmpid;
		while(query.next())
		{
		    tmpid = query.value(0).toString().section(" ", 0, 0).toInt()-1;
		    if(query.value(3).toString().contains(username+" [11]"))
				cmbdoc->addItem(docnames[tmpid]);
		    else
				cmbdoc->addItem("*" + docnames[tmpid]);
		    docdef << query.value(0).toString();
		    filename << query.value(1).toString();
		    doccount << query.value(2).toString();
		}
    }
}
//
void doceditfrm::selecteddocument()
{
	QDate date = boxdate->date();
	bool ok;
	if(txtdoccount->text().mid(2).toInt(&ok, 10)<20000000)
	{
		if(cmbdoc->currentText().mid(0,1)!="*")
		{
			txtdoccount->setText(docprefix+date.toString("MMyy")+doccount[cmbdoc->currentIndex()]);
			switch(cmbdoc->currentIndex()) {
			case 0:
				docfile = "of"+txtdoccount->text()+".dvi"; 
				break;
			case 1:
				docfile = "oc"+txtdoccount->text()+".dvi"; 
				break;	    
			case 2:
				docfile = "dn"+txtdoccount->text()+".dvi"; 
				break;
			case 3:
				docfile = "bi"+txtdoccount->text()+".dvi"; 
				break;    
	    	}
		    btnnew->setEnabled(TRUE);
		    btnsave->setEnabled(TRUE);
		    btnprint->setEnabled(TRUE);
		    btncomplete->setEnabled(TRUE);
		    //tabmain->setReadOnly(FALSE);
		}
		else
		{
		    btnnew->setEnabled(FALSE);
		    btnsave->setEnabled(FALSE);
		    btnprint->setEnabled(FALSE);
		    btncomplete->setEnabled(FALSE);
		    //tabmain->setReadOnly(TRUE);
		    QMessageBox::information(0,"Error...",tr("You are not authorized to provide the selected document"));
		}
	}
	else
	{
		switch(cmbdoc->currentIndex()) 
		{
		case 0:
			docfile = "of"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi"; 
			break;
		case 1:
			docfile = "oc"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi";
			break;	    
		case 2:
			docfile = "dn"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi"; 
			break;
		case 3:
			docfile = "bi"+date.toString("ddMMyyyy")+txtdoccount->text().mid(2)+".dvi"; 
			break;    
		}      
	}
}
//
void doceditfrm::opendocfromid(QString source, QString dbID)
{
	
}
//
void doceditfrm::calc_tot()
{
	
}
void doceditfrm::print()
{
	
}
//
void doceditfrm::printpreview()
{
	
}
//
void doceditfrm::printesr()
{
	
}
//
void doceditfrm::initvat()
{
    vatlist.clear();
    vatamount.clear();
    QStringList tmplist;
    QString connstr = "SELECT col1 FROM taxtab ORDER BY ID;";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		while(query.next())
		{
		    vatlist << query.value(0).toString();
		    vatamount << "0.00";
		}
    }
}
//
void doceditfrm::loadmaincfg()
{
    QString connstr = QString("SELECT value FROM `maincfgtab` WHERE `var` = 'docpref' OR `var` = 'banktnr' OR `var` = 'firmanschrift' ORDER BY var;");
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		query.next();
		tnr = query.value(0).toString();	    
		query.next();
		docprefix = query.value(0).toString();
		query.next();
		companyaddress = query.value(0).toString();	    
    }
}
//
void doceditfrm::selectaddress()
{
    addrselectfrm *safrm = new addrselectfrm;
    safrm->init();
    if(safrm->exec())
    {
       QString answer = safrm->getadress();
       boxdiscount->setText(safrm->getrabatt());
       QStringList fields = answer.split(":#:");
       boxaddress->setText(fields[0].replace("<BR>", "\n"));
       lblID->setText(fields[1]);
    }
}

