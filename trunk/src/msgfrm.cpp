#include <QtCore>
#include <QCloseEvent>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QMenu>
//
#include "msgfrm.h"
#include "vars.h"
#include "printfrm.h"
#include "msgeditfrm.h"
//
extern int uid;
extern QString username, fullname, templatefolder;
//
msgfrm::msgfrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void msgfrm::init()
{
	lbluser->setText(username);
	
	treeindex->hideColumn(1);
	treeindex->hideColumn(2);
	treeindex->hideColumn(3);
    treeindex->header()->setClickable(FALSE);
    treeindex->header()->setResizeMode(QHeaderView::Fixed);	
	
	connect(btnclose, SIGNAL(released()), this, SLOT(close()));
	connect(treeindex, SIGNAL(itemClicked(QTreeWidgetItem* , int)), this, SLOT(loadmsg()));
	connect(btnnew, SIGNAL(released()), this, SLOT(newmsg()));
	connect(btnedit, SIGNAL(released()), this, SLOT(editmsg()));
	connect(btndelete, SIGNAL(released()), this, SLOT(deletemsg()));
	connect(btnprint, SIGNAL(released()), this, SLOT(print()));
	connect(btncomplete, SIGNAL(released()), this, SLOT(completeitems()));
	connect(treemain, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenu()));
	
    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
        if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
   	}
   	
   	loadmsgcfg();
   	treeindex->setCurrentItem(treeindex->topLevelItem(0));
	loadmsg();
}
//
void msgfrm::closeEvent(QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void msgfrm::loadmsgcfg()
{
    int i;
    progbar->setMaximum(4);
    QString qstr = "SELECT ID, name, users FROM msgcfgtab ORDER BY ID ASC;";
    QSqlQuery query(qstr);
    if(query.isActive())
    {
		QTreeWidgetItem *item = treeindex->topLevelItem(0);
		item->setText(2, "per");
		item->setText(3, "11");
		for(i=1;i<5;i++)
		{
			item = new QTreeWidgetItem;
			item = treeindex->topLevelItem(i);
		    query.next();
		    item->setText(2, query.value(1).toString());
		    item->setText(3, query.value(2).toString().section(username+" [", 1, 1).section("]", 0, 0));
		    progbar->setValue(i+1);
		}
    }	
}
//
void msgfrm::loadmsg()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    initmainlistview(indexitem->text(2));
    
    if(indexitem->text(3) == "10" || indexitem->text(3) == "11" || uid == 0)
    {
		if(indexitem->text(3) == "11" || uid == 0)
		{
		    btnnew->setEnabled(TRUE);
		    btnedit->setEnabled(TRUE);
		    btndelete->setEnabled(TRUE);
		    btncomplete->setEnabled(TRUE);
		}
		else
		{
		    btnnew->setEnabled(FALSE);
		    btndelete->setEnabled(FALSE);
		    btncomplete->setEnabled(FALSE);
		}

		QString connstr = QString("SELECT ID, typ, user, date, msgtext, data1, data2, data3, data4, data5 FROM msgtab WHERE `typ` = '%1' ORDER BY ID DESC;").arg(indexitem->text(2));
		QSqlQuery query(connstr);
		if(query.isActive())
		{
		    progbar->setMaximum(query.size());
		    while(query.next())
		    {
				progbar->setValue(query.at()+1);
				QTreeWidgetItem *item = new QTreeWidgetItem(treemain);
				item->setText(0, query.value(0).toString());
				item->setCheckState(1, Qt::Unchecked);
				//item->setText(1, query.value(1).toString()); ///////////////////////test
				item->setText(2, query.value(2).toString());
				QString s = query.value(3).toString();
				item->setText(4, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				item->setText(5, query.value(4).toString());
				item->setText(6, query.value(5).toString());
				if(indexitem->text(2)=="ord" || indexitem->text(2)=="iem")
				    item->setText(6, item->text(6).section(" (", 0, 0));
				item->setText(7, query.value(6).toString());
				item->setText(8, query.value(7).toString());
				item->setText(9, query.value(8).toString());
				if(indexitem->text(2)=="ord")
				{
				    s = item->text(8);
				    item->setText(8, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				    s = item->text(9);
				    item->setText(9, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				}
				if(indexitem->text(2)=="iem")
				{
				    s = item->text(8);
				    item->setText(8, s.section("-", 2, 2) + "." + s.section("-", 1, 1) + "." + s.section("-", 0, 0));
				}
				item->setText(10, query.value(9).toString());
		    }
		}
    }
}
//
void msgfrm::initmainlistview(QString type)
{
    treemain->clear();
    treemain->setColumnCount(11);

    int i;
    for(i=0;i<treemain->columnCount();i++)
    	treemain->showColumn(i);

    treemain->header()->setClickable(FALSE);
    
    treemain->headerItem()->setText(0, tr("ID"));
    treemain->headerItem()->setText(1, "");
    treemain->headerItem()->setIcon(1, QIcon(QString::fromUtf8(":/button_ok_small.png")));
    treemain->headerItem()->setText(2, tr("type"));
    treemain->headerItem()->setText(3, tr("user"));
    treemain->headerItem()->setText(4, tr("Date"));

    treemain->hideColumn(0);
	treemain->setColumnWidth(1, 35);
    treemain->hideColumn(2);
    treemain->hideColumn(3);
    treemain->setColumnWidth(4, 100);
    
    if(type=="per")
    {
    	treemain->headerItem()->setText(5, tr("Info"));
    	treemain->setColumnWidth(5, 580);
		treemain->hideColumn(6);
		treemain->hideColumn(7);
		treemain->hideColumn(8);
		treemain->hideColumn(9);
		treemain->hideColumn(10);
    }
    else if(type=="gen")
    {
    	treemain->headerItem()->setText(5, tr("Info"));
    	treemain->setColumnWidth(5, 580);
		treemain->hideColumn(6);
		treemain->hideColumn(7);
		treemain->hideColumn(8);
		treemain->hideColumn(9);
		treemain->hideColumn(10);
    }
    else if(type=="sto")
    {
    	treemain->headerItem()->setText(5, tr("info"));
    	treemain->headerItem()->setText(6, tr("Label"));
    	treemain->headerItem()->setText(7, tr("Description"));
    	treemain->headerItem()->setText(8, tr("Stock"));
    	treemain->headerItem()->setText(9, tr("Min. quantity"));
    	treemain->headerItem()->setText(10, tr("Supplier"));
    	
    	treemain->hideColumn(5);
    	treemain->setColumnWidth(6, 100);
    	treemain->setColumnWidth(7, 300);
    	treemain->setColumnWidth(8, 75);
    	treemain->setColumnWidth(9, 75);
    	treemain->setColumnWidth(10, 100);
    }
    else if(type=="ord")
    {
		treemain->headerItem()->setText(5, tr("info"));
    	treemain->headerItem()->setText(6, tr("Client"));
    	treemain->headerItem()->setText(7, tr("Order.-Nr."));
    	treemain->headerItem()->setText(8, tr("Date of entry"));
    	treemain->headerItem()->setText(9, tr("Complete until"));
    	treemain->headerItem()->setText(10, tr("data"));
		
		treemain->hideColumn(5);
	   	treemain->setColumnWidth(6, 200);
    	treemain->setColumnWidth(7, 100);
    	treemain->setColumnWidth(8, 100);
    	treemain->setColumnWidth(9, 100);
		treemain->hideColumn(10);
    }
    else
    {
		treemain->headerItem()->setText(5, tr("info"));
    	treemain->headerItem()->setText(6, tr("Client"));
    	treemain->headerItem()->setText(7, tr("Ref-Nr."));
    	treemain->headerItem()->setText(8, tr("Last payment"));
    	treemain->headerItem()->setText(9, tr("Amount"));
    	treemain->headerItem()->setText(10, tr("data"));
		
		treemain->hideColumn(5);
	   	treemain->setColumnWidth(6, 200);
    	treemain->setColumnWidth(7, 100);
    	treemain->setColumnWidth(8, 100);
    	treemain->setColumnWidth(9, 100);
		treemain->hideColumn(10);
    }
}
//
void msgfrm::newmsg()
{
    QTreeWidgetItem *item = treeindex->currentItem();
	if(item == 0)
		item = treeindex->topLevelItem(0);
    if(item!=0)
    {
		msgeditfrm *emsg = new msgeditfrm;
		emsg->init(item->text(2));
		emsg->setWindowTitle(tr("New Entry..."));
		emsg->chknew->setChecked(TRUE);
		int r = emsg->exec();
		if(r)
	    	loadmsg();
    }
}
//
void msgfrm::editmsg()
{
    QTreeWidgetItem *indexitem = treeindex->currentItem();
    QTreeWidgetItem *item = treemain->currentItem();
    if(item!=0)
    {
		msgeditfrm *emsg = new msgeditfrm;
		emsg->init(indexitem->text(2));
		emsg->setWindowTitle(tr("Edit entry..."));
		emsg->loadentry(item->text(0));
		if(!btnnew->isEnabled())
			emsg->btnaccept->setEnabled(FALSE);
		int r = emsg->exec();
		if(r)
	    	loadmsg();
    }
}
//
void msgfrm::deletemsg()
{
    QTreeWidgetItem* item =  treemain->currentItem();
    if(item!=0)
    {
		int r=QMessageBox::information(this, tr("Delete entry..."), tr("Delete entry?"), QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{
	    	QString connstr = QString("DELETE FROM `msgtab` WHERE `ID` = '%2';").arg(item->text(0));
		    QSqlQuery query(connstr);
	    	treemain->takeTopLevelItem(treemain->indexOfTopLevelItem(item));
		}
    }
}
//
void msgfrm::contmenu()
{

    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    QAction* editmsg = new QAction( tr("&Edit Message"), this );
	connect(editmsg , SIGNAL(triggered()), this, SLOT(editmsg()));
	contextMenu->addAction(editmsg);
    QAction* deletemesg = new QAction( tr("&Delete Message"), this );
	connect(deletemesg , SIGNAL(triggered()), this, SLOT(deletemsg()));
	
	QTreeWidgetItem *indexitem = treeindex->currentItem();
	if(indexitem->text(3) == "11" || uid == 0)
		contextMenu->addAction(deletemesg);
		
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void msgfrm::completeitems()
{
    int i;
    if(treemain->topLevelItemCount() > 0)
    {
		int r=QMessageBox::information(this, tr("Complete entry..."), tr("Complete entry"),QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{	
	    	QString qstr = "DELETE FROM `msgtab` WHERE ";
		    for(i=0;i<treemain->topLevelItemCount();i++)
	    	{
	    		QTreeWidgetItem *item = treemain->topLevelItem(0);
				if(	item->checkState(1) == Qt::Checked)
			    	qstr += QString("`ID` = '%1' OR ").arg(item->text(0));
	    	}
	    	qstr = qstr.leftJustified(qstr.length()-3, '.', TRUE);
		    QSqlQuery query(qstr);
	    	loadmsg();
		}
    }
}
//
void msgfrm::print()
{
    printfrm *pfrm = new printfrm;
    if(pfrm->exec())
    {
		if(pfrm->rdbtn_1->isChecked())
	    	printalllist();
		else if(pfrm->rdbtn_2->isChecked())
	    	printall();
		else if(pfrm->rdbtn_3->isChecked())
	    	printsellist();
		else if(pfrm->rdbtn_4->isChecked())
	    	printsel();
    }
}
//
void msgfrm::printalllist()
{/*
    if(mainlistview->childCount()>0)
    {
	int i, ii, iii, zeilen;
	
	progfrm *pfrm = new progfrm;
	pfrm->setFixedSize(pfrm->width(), pfrm->height());
	pfrm->setGeometry(300, 300, pfrm->width(), pfrm->height());
	pfrm->lblinfo->setText(tr("Document will be created..."));
	pfrm->progbar->setTotalSteps(mainlistview->childCount());
	pfrm->show();
	
	QFile file(docfolder+"/"+"~msgtmpprint.kud");
	if(file.open( IO_WriteOnly ) )
	{
	    QTextStream stream( &file );	
	    stream << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
	    stream << "<!DOCTYPE KugarData [\n    <!ATTLIST KugarData\n        Template CDATA #REQUIRED>\n]>\n";
	    stream << "<KugarData Template=\""<< templatefolder ;
	    
	    QListViewItem *indexitem = indexview->currentItem();
	    if(indexitem->text(1)=="per")
		stream << "msgeigenelist.kut";
	    else if(indexitem->text(1)=="gen")
		stream << "msgallgemeinlist.kut";
	    else if(indexitem->text(1)=="sto")
		stream << "msglagerlist.kut";
	    else if(indexitem->text(1)=="ord")
		stream << "msgauftraglist.kut";
	    else
		stream << "msgeinauslist.kut";
	    stream << "\">\n";
	    
	    stream << "<Field level=\"0\" Art=\"" << indexitem->text(0) << "\"/>\n";
    
	    stream << "<Field level=\"1\" ";
	    for(i=0;i<mainlistview->columns();i++)
	    {
		stream << "col" << QString("%1").arg(i, 0, 10) << "=\"" << mainlistview->columnText(i) << "\" ";
	    }
	    stream << "/>\n";
	    
	    QListViewItem* item = mainlistview->firstChild();
	    for(i=0;i<mainlistview->childCount();i++)
	    {
		pfrm->progbar->setProgress(i+1);
		if(i>0)
		    item = item->itemBelow();
		
		zeilen = 0;
		for(ii=0; ii<mainlistview->columns();ii++)
		{
		    if(item->text(ii).contains("\n")>zeilen)
			zeilen = item->text(ii).contains("\n");
		}
		
		for(iii=0; iii<=zeilen;iii++)
		{
		    stream << "<Field level=\"2\" ";
		    for(ii=0; ii<mainlistview->columns();ii++)
		    {
			stream << "col" << QString("%1").arg(ii, 0, 10) << "=\"" << item->text(ii).section("\n", iii, iii) << "\" ";
		    }
		    stream << "/>\n";
		}
	    }
	    stream << "<!--created by first-->\n</KugarData>";
	    file.close();
	    system("kugar "+ docfolder+"/"+"~msgtmpprint.kud --print");
	}
	else
	{
	    QMessageBox::critical(0,"Error...",tr("File cannot be written.\n\nExamine please path and authorization!"));
	}
	pfrm->close();	
    }*/
}
//
void msgfrm::printall()
{/*
    if(mainlistview->childCount()>0)
    {
	int i, ii;
	
	progfrm *pfrm = new progfrm;
	pfrm->setFixedSize(pfrm->width(), pfrm->height());
	pfrm->setGeometry(300, 300, pfrm->width(), pfrm->height());
	pfrm->lblinfo->setText(tr("Document will be written..."));
	pfrm->progbar->setTotalSteps(mainlistview->childCount());
	pfrm->show();	
	
	QListViewItem* item = mainlistview->firstChild();
	for(i=0;i<mainlistview->childCount();i++)
	{
	    QFile file(docfolder+"/"+"~msgtmpprint_"+QString("%1").arg(i, 0, 10)+".kud");
	    if(file.open( IO_WriteOnly ) )
	    {
		pfrm->progbar->setProgress(i+1);
		if(i>0)
		    item = item->itemBelow();
		QTextStream stream( &file );	
		stream << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
		stream << "<!DOCTYPE KugarData [\n    <!ATTLIST KugarData\n        Template CDATA #REQUIRED>\n]>\n";
		stream << "<KugarData Template=\""<< templatefolder ;
		
		QListViewItem *indexitem = indexview->currentItem();
		if(indexitem->text(1)=="per")
		    stream << "msgeigeneeinzel.kut";
		else if(indexitem->text(1)=="gen")
		    stream << "msgallgemeineinzel.kut";
		else if(indexitem->text(1)=="sto")
		    stream << "msglagereinzel.kut";
		else if(indexitem->text(1)=="ord")
		    stream << "msgauftrageinzel.kut";
		else
		    stream << "msgeinauseinzel.kut";
		stream << "\">\n";
		
		stream << "<Field level=\"0\" Art=\"" << indexitem->text(0) << "\"/>\n";
		
		stream << "<Field level=\"1\" ";		
		for(ii=0;ii<mainlistview->columns();ii++)
		{
		    stream << "col" << QString("%1").arg(i, 0, 10) << "=\"" << mainlistview->columnText(i) << "\" ";
		}
		stream << "/>\n";
		
		stream << "<Field level=\"2\" ";
		for(ii=0; ii<mainlistview->columns();ii++)
		{
		    stream << "col" << QString("%1").arg(ii, 0, 10) << "=\"" << item->text(ii) << "\" ";
		}
		stream << "/>\n<!--created by first-->\n</KugarData>";
		file.close();
		system("kugar "+ docfolder+"/"+"~msgtmpprint_"+QString("%1").arg(i, 0, 10)+".kud --print");
	    }
	    else
	    {
		QMessageBox::critical(0,"Error...",tr("File cannot be written.\n\nExamine please path and authorization!"));
	    }
	}
	pfrm->close();
    }*/
}
//
void msgfrm::printsellist()
{/*
    if(mainlistview->childCount()>0)
    {
	int i, ii, iii, zeilen;
	
	progfrm *pfrm = new progfrm;
	pfrm->setFixedSize(pfrm->width(), pfrm->height());
	pfrm->setGeometry(300, 300, pfrm->width(), pfrm->height());
	pfrm->lblinfo->setText(tr("Document will be written..."));
	pfrm->progbar->setTotalSteps(mainlistview->childCount());
	pfrm->show();
	
	QFile file(docfolder+"/"+"~msgtmpprint.kud");
	if(file.open( IO_WriteOnly ) )
	{
	    QTextStream stream( &file );	
	    stream << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
	    stream << "<!DOCTYPE KugarData [\n    <!ATTLIST KugarData\n        Template CDATA #REQUIRED>\n]>\n";
	    stream << "<KugarData Template=\""<< templatefolder ;
	    
	    QListViewItem *indexitem = indexview->currentItem();
	    if(indexitem->text(1)=="per")
		stream << "msgeigenelist.kut";
	    else if(indexitem->text(1)=="gen")
		stream << "msgallgemeinlist.kut";
	    else if(indexitem->text(1)=="sto")
		stream << "msglagerlist.kut";
	    else if(indexitem->text(1)=="ord")
		stream << "msgauftraglist.kut";
	    else
		stream << "msgeinauslist.kut";
	    stream << "\">\n";
	    
	    stream << "<Field level=\"0\" Art=\"" << indexitem->text(0) << "\"/>\n";
    
	    stream << "<Field level=\"1\" ";
	    for(i=0;i<mainlistview->columns();i++)
	    {
		stream << "col" << QString("%1").arg(i, 0, 10) << "=\"" << mainlistview->columnText(i) << "\" ";
	    }
	    stream << "/>\n";
	    
	    QListViewItem* item = mainlistview->firstChild();
	    for(i=0;i<mainlistview->childCount();i++)
	    {
		pfrm->progbar->setProgress(i+1);
		if(i>0)
		    item = item->itemBelow();
		
		if(item->isSelected())
		{
		    zeilen = 0;
		    for(ii=0; ii<mainlistview->columns();ii++)
		    {
			if(item->text(ii).contains("\n")>zeilen)
			    zeilen = item->text(ii).contains("\n");
		    }
		
		    for(iii=0; iii<=zeilen;iii++)
		    {
			stream << "<Field level=\"2\" ";
			for(ii=0; ii<mainlistview->columns();ii++)
			{
			    stream << "col" << QString("%1").arg(ii, 0, 10) << "=\"" << item->text(ii).section("\n", iii, iii) << "\" ";
			}
			stream << "/>\n";
		    }
		}
	    }
	    stream << "<!--created by first-->\n</KugarData>";
	    file.close();
	    system("kugar "+ docfolder+"/"+"~msgtmpprint.kud --print");
	}
	else
	{
	    QMessageBox::critical(0,"Error...",tr("File cannot be written.\n\nExamine please path and authorization!"));
	}
	pfrm->close();	
    }*/
}
//
void msgfrm::printsel()
{/*
    if(mainlistview->childCount()>0)
    {
	int i, ii;
	
	progfrm *pfrm = new progfrm;
	pfrm->setFixedSize(pfrm->width(), pfrm->height());
	pfrm->setGeometry(300, 300, pfrm->width(), pfrm->height());
	pfrm->lblinfo->setText(tr("Document will be written..."));
	pfrm->progbar->setTotalSteps(mainlistview->childCount());
	pfrm->show();	
	
	QListViewItem* item = mainlistview->firstChild();
	for(i=0;i<mainlistview->childCount();i++)
	{
	    pfrm->progbar->setProgress(i+1);
	    if(i>0)
		item = item->itemBelow();	    
	    if(item->isSelected())
	    {
		QFile file(docfolder+"/"+"~msgtmpprint_"+QString("%1").arg(i, 0, 10)+".kud");
		if(file.open( IO_WriteOnly ) )
		{
		    QTextStream stream( &file );	
		    stream << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
		    stream << "<!DOCTYPE KugarData [\n    <!ATTLIST KugarData\n        Template CDATA #REQUIRED>\n]>\n";
		    stream << "<KugarData Template=\""<< templatefolder ;
		
		    QListViewItem *indexitem = indexview->currentItem();
		    if(indexitem->text(1)=="per")
			stream << "msgeigeneeinzel.kut";
		    else if(indexitem->text(1)=="gen")
			stream << "msgallgemeineinzel.kut";
		    else if(indexitem->text(1)=="sto")
			stream << "msglagereinzel.kut";
		    else if(indexitem->text(1)=="ord")
			stream << "msgauftrageinzel.kut";
		    else
			stream << "msgeinauseinzel.kut";
		    stream << "\">\n";
		
		    stream << "<Field level=\"0\" Art=\"" << indexitem->text(0) << "\"/>\n";
		
		    stream << "<Field level=\"1\" ";		
		    for(ii=0;ii<mainlistview->columns();ii++)
		    {
			stream << "col" << QString("%1").arg(i, 0, 10) << "=\"" << mainlistview->columnText(i) << "\" ";
		    }
		    stream << "/>\n";
		
		    stream << "<Field level=\"2\" ";
		    for(ii=0; ii<mainlistview->columns();ii++)
		    {
			stream << "col" << QString("%1").arg(ii, 0, 10) << "=\"" << item->text(ii) << "\" ";
		    }
		    stream << "/>\n<!--created by first-->\n</KugarData>";
		    file.close();
		    system("kugar "+ docfolder+"/"+"~msgtmpprint_"+QString("%1").arg(i, 0, 10)+".kud --print");
		}
		else
		{
		    QMessageBox::critical(0,"Error...",tr("File cannot be written.\n\nExamine please path and authorization!"));
		}
	    }
	}
	pfrm->close();
    }*/
}
