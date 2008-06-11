#include <QSqlDatabase>
#include <QSqlQuery>
#include <QHeaderView>
#include <QMessageBox>
#include <QComboBox>
#include <QTableWidget>
#include <QCloseEvent>
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTextStream>
#include <QMenu>
#include <QSqlError>
//
#include "datafrm.h"
#include "vars.h"
#include "dataeditfrm.h"
#include "printfrm.h"
#include "dataimpexpfrm.h"
//
QString lastdatatab;
QStringList stockrightslist, tabnamelist, colslist, tabtyplist;
extern int uid;
extern QString username, templatefolder;
//
datafrm::datafrm( QWidget * parent, Qt::WFlags f) 
	: QWidget(parent, f)
{
	setupUi(this);
}
//
void datafrm::init()
{
	
    lastdatatab = "";

    //Liste leeren
    stockrightslist.clear();
    tabnamelist.clear();
    colslist.clear();
    tabtyplist.clear();
    
    QHeaderView *tvh = maintable->verticalHeader();
    tvh->setOffset(0);

	maintree->setColumnCount(0);

    lbluser->setText(username);    	     
       
    QString connstr = QString("SELECT * FROM datatables WHERE users LIKE '%%1 [1%';").arg(username);
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		progbar->setMaximum(query.size()-1);
		progbar->setValue(0);
		int i = 0;
		while(query.next())
		{
		    progbar->setValue(++i);
		    tabnamelist.append(query.value(1).toString());
		    cmbdata->addItem(query.value(2).toString());
		    stockrightslist.append(query.value(3).toString().section(username, 1, 1).section(" ", 1, 1));
		    colslist.append(query.value(4).toString());
		    tabtyplist.append(query.value(5).toString());
		}
    }

    vars v;
    QStringList sgeo = v.loadgeo(this->objectName());
    if(sgeo.size() > 0	)
    {
	    if(sgeo[0] == "1")
			this->setWindowState(this->windowState() ^ Qt::WindowMaximized);
	    this->setGeometry(sgeo[1].toInt(), sgeo[2].toInt(), sgeo[3].toInt(), sgeo[4].toInt());
    }
    
    maintree->header()->setClickable(FALSE);
    maintree->header()->setMovable(FALSE);
    
    btnsave->setEnabled(FALSE);
    btnnew->setEnabled(FALSE);
    btnedit->setEnabled(FALSE);
    btndelete->setEnabled(FALSE);
    btnprint->setEnabled(FALSE);
    
	connect(cmbdata, SIGNAL(activated(int)), this, SLOT(changecmb()));
	connect(btnsave, SIGNAL(released()), this, SLOT(savetable()));
	connect(maintable, SIGNAL(cellChanged(int, int)), this, SLOT(navtable()));
	connect(btnnew, SIGNAL(released()), this, SLOT(newstockentry()));
	connect(btnedit, SIGNAL(released()), this, SLOT(editstockentry()));
	connect(maintree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int) ), this, SLOT(editstockentry()));
	connect(btndelete, SIGNAL(released()), this, SLOT(delstockentry()));
	connect(btnprint, SIGNAL(released()), this, SLOT(print()));
    connect(maintable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenudata()));
    connect(maintree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenustock()));
    connect(btnsearch, SIGNAL(released()), this, SLOT(searchentries()));
    connect(txtsearch, SIGNAL(returnPressed()), this, SLOT(searchentries()));    
    connect(btnclear, SIGNAL(released()), this, SLOT(clearsearch()));
    connect(btntransfer, SIGNAL(released()), this, SLOT(impexp()));
}
//
void datafrm::closeEvent(QCloseEvent* ce )
{
	QSqlDatabase::database().rollback();
	vars v;
	v.unlocktable(lastdatatab);
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void datafrm::checkrights()
{
    if(uid == 0 || stockrightslist[cmbdata->currentIndex()]=="[11]")
    {
		btntransfer->setEnabled(TRUE);
		if(tabtyplist[cmbdata->currentIndex()]=="stock")
		{
		    btnsave->setEnabled(FALSE);
		    btnnew->setEnabled(TRUE);
		    btnedit->setEnabled(TRUE);
		    btndelete->setEnabled(TRUE);
		    btnprint->setEnabled(TRUE);
		}
		else
		{
		    btnsave->setEnabled(TRUE);
		    btnnew->setEnabled(FALSE);
		    btnedit->setEnabled(FALSE);
		    btndelete->setEnabled(FALSE);
		    btnprint->setEnabled(FALSE);
		}
    }
    else
    {
		btnsave->setEnabled(FALSE);
		btnnew->setEnabled(FALSE);
		btnedit->setEnabled(TRUE);
		btndelete->setEnabled(FALSE);
		btntransfer->setEnabled(FALSE);
    }
}

void datafrm::changecmb()
{
	disconnect(cmbdata, SIGNAL(activated(int)), this, SLOT(changecmb()));
    btnprint->setEnabled(FALSE);
    if(cmbdata->currentText() != lastdatatab)
    {
    	QSqlDatabase::database().rollback();
    	
	    int updatecount = 0;
	    QString updatestr = "";
	    QTableWidgetItem *item = new QTableWidgetItem;
	    do{
	    	item = maintable->item(updatecount, maintable->columnCount()-1);
	    	if(item!=0)
		    	updatestr = item->text();
			updatecount++;
	    }while(updatestr == "" && updatecount < maintable->rowCount()-1);
	    if(updatestr != "")
	    {
			int answ=QMessageBox::warning(this, tr("Save changes..."), tr("Save changes?"), QMessageBox::Yes, QMessageBox::No);
			if(answ == QMessageBox::Yes)
			{
			    int newselection = cmbdata->currentIndex();
			    cmbdata->setCurrentIndex(tabnamelist.lastIndexOf(lastdatatab));
			    savetable();
			    cmbdata->setCurrentIndex(newselection);
			}
	    }
    	vars v;
    	v.unlocktable(lastdatatab);
		if(tabtyplist[cmbdata->currentIndex()]=="stock")
		{
		    checkrights();
		    loadstock();
		}
		else
		{
		    checkrights();	    
		    loaddata();
		}
    }
	connect(cmbdata, SIGNAL(activated(int)), this, SLOT(changecmb()));
}
//
void datafrm::loadstock()
{
    mainwidget->setCurrentIndex(0);
    
    maintable->setRowCount(0);
    maintable->setColumnCount(0);
    
    maintree->clear();
    maintree->setColumnCount(0);
   
    QStringList cols = colslist[cmbdata->currentIndex()].split("#");
    
    maintree->setColumnCount(6);
    maintree->headerItem()->setText(0, "");
    maintree->headerItem()->setText(1, "");
    maintree->headerItem()->setText(2, cols[0].section(":", 0, 0));
    maintree->headerItem()->setText(3, cols[1].section(":", 0, 0));
    maintree->headerItem()->setText(4, "");
    maintree->headerItem()->setText(5, "");
	maintree->header()->setResizeMode(0, QHeaderView::Fixed);
	maintree->header()->setResizeMode(1, QHeaderView::Fixed);
	maintree->setColumnWidth(0, 50);
    maintree->hideColumn(1);
	maintree->setColumnWidth(2, 150);
    maintree->hideColumn(4);
    maintree->hideColumn(5);

    QString connstr = "SELECT * FROM " +tabnamelist[cmbdata->currentIndex()]+" ORDER BY col1;";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		int i;
		int countrow = 0;
		progbar->setMaximum(query.size());
		while(query.next())
		{
		    QTreeWidgetItem *item = new QTreeWidgetItem(maintree);
		    item->setText(1, query.value(0).toString());
		    item->setText(2, query.value(1).toString());
		    item->setText(3, query.value(2).toString().section("\n", 0, 0));
		    item->setText(4, query.value(2).toString());
		    if(query.value(2).toString().contains("\n")>0)
		    {
				QTreeWidgetItem *item2 = new QTreeWidgetItem(item, item);
				item2->setText(1, "2");
				item2->setText(2, "---");
				item2->setText(3, query.value(2).toString().section("\n", 1));
		    }
	    
		    QTreeWidgetItem *childitem;   
		    for(i=3;i<7;i++)
		    {
				childitem = new QTreeWidgetItem(item);
				childitem->setText(1, QString("%1").arg(i, 0, 10));
				childitem->setText(2, cols[i-1].section(":", 0, 0));
				childitem->setText(3, query.value(i).toString().section("\n", 0, 0));
		    }
	    
		    //Load Sellprice
		    childitem = new QTreeWidgetItem(item);
		    childitem->setText(1, QString("%1").arg(8, 0, 10));
		    childitem->setText(2, cols[7].section(":", 0, 0));
		    childitem->setText(3, query.value(8).toString().section("\n", 0, 0));
	    
		    //Load Suppliers
		    childitem = new QTreeWidgetItem(item);
		    childitem->setText(2, cols[6].section(":", 0, 0));
		    QStringList lines = query.value(9).toString().split(":##:");
		    for(i=0;i<lines.count()-1;i++)
		    {
				QTreeWidgetItem *child = new QTreeWidgetItem(childitem);
				child->setText(2, lines[i].section(":#:", 0, 0).section(";", 0, 0));
				child->setText(3, lines[i].section(":#:", 2, 2));
		    }
	    
		    QString tmpstr = "";
		    for(i=0;i<=cols.count();i++)
		    {
				tmpstr += query.value(i).toString()+":|:";
		    }
		    item->setText(5, tmpstr);
		    progbar->setValue(++countrow);
		}
    }	
    lastdatatab = tabnamelist[cmbdata->currentIndex()];
}
//
void datafrm::loaddata()
{
    mainwidget->setCurrentIndex(1);
    maintable->setRowCount(0);
    maintable->setColumnCount(0);
       
    bool ok;
    QStringList cols = colslist[cmbdata->currentIndex()].split("#");
    int colcount;
    QTableWidgetItem *id_item = new QTableWidgetItem;
	maintable->setColumnCount(cols.count()+2);
    id_item->setText("ID");
    maintable->setHorizontalHeaderItem(0, id_item);
    for(colcount=1;colcount<=cols.count();colcount++)
    {
    	QTableWidgetItem *item = new QTableWidgetItem;
		item->setText(cols[colcount-1].section(":", 0, 0));
		maintable->setHorizontalHeaderItem(colcount, item);
		maintable->setColumnWidth(colcount, cols[colcount-1].section(":", 1, 1).toInt(&ok, 10));
    }
    QTableWidgetItem *new_item = new QTableWidgetItem;
	new_item->setText("new");
	maintable->setHorizontalHeaderItem(maintable->columnCount()-1, new_item);
    maintable->setColumnWidth(0,0);
    maintable->setColumnWidth(maintable->columnCount()-1, 0);

	vars v;
	QString qstr;
	QString userlock = v.checklockstate(tabnamelist[cmbdata->currentIndex()], "");
	if(userlock != "")
	{
		this->setWindowTitle(QString("Stock / Datatables ( Locked by User: %1 )").arg(userlock));
		btnsave->setEnabled(FALSE);
		qstr = QString("SELECT * FROM %1 ORDER BY col1;").arg(tabnamelist[cmbdata->currentIndex()]);
	}
	else
	{
		this->setWindowTitle(QString("Stock / Datatables"));
		qstr = QString("SELECT * FROM %1 ORDER BY col1 FOR UPDATE;").arg(tabnamelist[cmbdata->currentIndex()]);
		v.locktable(tabnamelist[cmbdata->currentIndex()]);
	}
	QSqlDatabase::database().transaction();

    QSqlQuery query(qstr);
    if(query.isActive())
    {
		progbar->setMaximum(query.size());
		maintable->setRowCount(query.size());
		int i;
		int countrow = 0;
		while(query.next())
		{
		    for(i=0;i<maintable->columnCount()-1;i++)
		    {
		    	QTableWidgetItem *item = new QTableWidgetItem;
   				item->setText(query.value(i).toString());
				maintable->setItem(countrow, i, item);
	    	}
   	    	QTableWidgetItem *item = new QTableWidgetItem;
	    	item->setText("");
		    maintable->setItem(countrow, maintable->columnCount()-1, item);
		    progbar->setValue(++countrow);
		}
		
		if(stockrightslist[cmbdata->currentIndex()]=="[11]")
		{
			QTableWidgetItem *item = new QTableWidgetItem;
		    maintable->setRowCount(maintable->rowCount()+1);
		    item->setText("xn");
		    maintable->setItem(maintable->rowCount()-1, maintable->columnCount()-1, item);
		}
    }		
    lastdatatab = tabnamelist[cmbdata->currentIndex()];
}
//
void datafrm::savetable()
{
    int i;
    QString colwidth = "UPDATE `datatables` SET `cols`='";
    QTableWidgetItem *item = new QTableWidgetItem;
    for(i=0;i<maintable->columnCount()-2;i++)
    {
    	item = maintable->horizontalHeaderItem(i+1);
		colwidth += QString("%1:%2#").arg(item->text()).arg(maintable->columnWidth(i+1), 0, 10);
   	}
    colwidth = colwidth.leftJustified(colwidth.length()-1 , '.', TRUE );
    colwidth += QString("' WHERE `name`='%1';").arg(tabnamelist[cmbdata->currentIndex()]);
    QSqlQuery query(colwidth);
    colslist[cmbdata->currentIndex()] = colwidth.section("'", 1, 1).section("'", 0, 0);
    
    progbar->setMaximum(maintable->rowCount()-1);
    progbar->setValue(0);
    for(i=0;i<maintable->rowCount();i++)
    {
    	item = maintable->item(i, maintable->columnCount()-1);
		if (item->text()=="u")
		{
		    QString connstr = "UPDATE `"+tabnamelist[cmbdata->currentIndex()]+ "` SET ";
		    int isave;
		    for(isave=1;isave<maintable->columnCount()-1;isave++)
		    {
		    	item = maintable->item(i, isave);
				connstr += QString("`col%1` = '%2', ").arg(isave,0,10).arg(item->text());	
	    	}
		    connstr.truncate(connstr.length()-3);
		    connstr += "' WHERE `ID` = '";
		    item = maintable->item(i, 0);
		    connstr += item->text();
		    connstr += "' LIMIT 1;";
		    QSqlQuery query(connstr);
		    query.exec();
		}
		else if (item->text()=="n")
		{
		    QString connstr1 = "INSERT INTO `"+tabnamelist[cmbdata->currentIndex()]+"` ( `ID` , ";
		    int isave;
		    for(isave=1;isave<maintable->columnCount()-1;isave++)
				connstr1 += QString("`col%1`, ").arg(isave,0,10);
		    connstr1.truncate(connstr1.length()-2);
		    connstr1 += ")VALUES('',";
		    for(isave=1;isave<maintable->columnCount()-1;isave++)
		    {
				item = maintable->item(i, isave);
				if(item!=0)
					connstr1 += "'"+item->text()+"', ";
				else
					connstr1 += "'', ";
			}
		    connstr1.truncate(connstr1.length()-2);
   		    //item = maintable->item(i, 0);
		    //connstr1 += item->text();
		    connstr1 += ");";
		    QSqlQuery query1(connstr1);
		   
		    QString connstr2 = "SELECT ID FROM "+tabnamelist[cmbdata->currentIndex()]+" WHERE ";
		    for(isave=1;isave<maintable->columnCount()-1;isave++)
		    {
		    	item = maintable->item(i, isave);
		    	if(item!=0)
					connstr2 += QString("`col%1` = '%2' AND ").arg(isave,0,10).arg(item->text());
				else
					connstr2 += QString("`col%1` = '' AND ").arg(isave,0,10);
	    	}
		    connstr2.truncate(connstr2.length()-5);
		    connstr2 += ";";
		    QSqlQuery query2(connstr2);
		    query2.next();
		    
		    QTableWidgetItem *id_item = new QTableWidgetItem;
		    id_item->setText(query2.value(0).toString());
		    maintable->setItem(i, 0, id_item);
		    
		    QTableWidgetItem *new_item = new QTableWidgetItem;
   		    new_item->setText("");
		    maintable->setItem(i, maintable->columnCount()-1, new_item);
		}
		progbar->setValue(progbar->maximum());
		QSqlDatabase::database().commit(); //Close open transaction and for save
		QSqlDatabase::database().transaction(); //Start a new one
	}
}
//
void datafrm::navtable()
{
    QTableWidgetItem *item = new QTableWidgetItem;
    item = maintable->item(maintable->currentRow(), maintable->columnCount()-1);
    if(item!=0)
    {
	    if(item->text()=="")
			item->setText("u");
	    else if (item->text()=="xn")
			item->setText("n");
	    if(maintable->currentRow() == maintable->rowCount()-1)
	    {
			maintable->insertRow(maintable->rowCount());
			QTableWidgetItem *newitem = new QTableWidgetItem;
			newitem->setText("xn");
			maintable->setItem(maintable->rowCount()-1, maintable->columnCount()-1, newitem);
	    }
    }
}
//
void datafrm::newstockentry()
{
    dataeditfrm *estock = new dataeditfrm;
    estock->init();
    estock->lbldatatab->setText(tabnamelist[cmbdata->currentIndex()]);
    if(estock->exec())
		loadstock();    
}
//
void datafrm::editstockentry()
{
    QTreeWidgetItem *tmpitem = maintree->currentItem();
    if(tmpitem != 0)
    {
		while(tmpitem->parent() != 0)
		    tmpitem = tmpitem->parent();
		dataeditfrm *estock = new dataeditfrm;
		estock->init();
		estock->loadentry(tabnamelist[cmbdata->currentIndex()]+"_"+tmpitem->text(1));
		if(uid == 0 || stockrightslist[cmbdata->currentIndex()]=="[11]")
			estock->btnok->setEnabled(TRUE);
		else
    		estock->btnok->setEnabled(FALSE);
		if(estock->exec())
		    loadstock();
    }
}
//
void datafrm::delstockentry()
{
    QTreeWidgetItem* item =  maintree->currentItem();
    if(item!=0)
    {    
		int r=QMessageBox::information(this, tr("Delete entry..."), tr("Delete entry %1?").arg(item->text(2)), QMessageBox::Yes, QMessageBox::No);
		if(r == QMessageBox::Yes)
		{
		    QSqlQuery query;
		    query.prepare(QString("DELETE FROM %1 WHERE `ID` = :ID;").arg(tabnamelist[cmbdata->currentIndex()]));
		    query.bindValue(":ID", item->text(1));
		    query.exec();
		    loadstock();
		}
    }    
}
//
void datafrm::print()
{
    printfrm *pfrm = new printfrm;
    pfrm->rdbtn_2->setEnabled(FALSE);
    pfrm->rdbtn_4->setEnabled(FALSE);
    if(pfrm->exec())
    {
		if(pfrm->rdbtn_1->isChecked())
		    this->writetexfile(0);
		else if(pfrm->rdbtn_2->isChecked())
		    this->writetexfile(1);
		else if(pfrm->rdbtn_3->isChecked())
		    this->writetexfile(2);
		else if(pfrm->rdbtn_4->isChecked())
		    this->writetexfile(3);
    }        
}
//
void datafrm::writetexfile(int type)
{
    int i;
    QStringList cols = colslist[cmbdata->currentIndex()].split("#");
    QString tabhead = cols[0].section(":", 0, 0) + " & " + cols[1].section(":", 0, 0) + " & " + cols[2].section(":", 0, 0) + " & " + cols[3].section(":", 0, 0) + " & " + cols[4].section(":", 0, 0) + " & " + cols[5].section(":", 0, 0) + " & " + cols[6].section(":", 0, 0) + " & " + cols[8].section(":", 0, 0) + " & " + cols[19].section(":", 0, 0);
    
    QString tabcontent = "";
    QTreeWidgetItem* item = maintree->topLevelItem(0);
    
    switch(type)
    {
	    case 0:
		for(i=0;i<maintree->topLevelItemCount();i++)
		{
		    if(i>0)
				item = maintree->topLevelItem(i);
		    cols = item->text(5).split(":|:");
		    tabcontent += cols[1].replace("_", "\\_") + " & " + cols[2].replace("&", "") + " & " + cols[3] + " & " + cols[4] + " & " + cols[5] + " & " + cols[6] + " & " + cols[8] + " & " +cols[9].section(":#:", 0, 0)+" - "+cols[9].section(":#:", 2, 2)+ " & "+ cols[20] +" \\\\ \n";
		}
		break;
	    case 1:
		break;
	    case 2:
		for(i=0;i<maintree->topLevelItemCount();i++)
		{
		    if(i>0)
				item = maintree->topLevelItem(i);
		    if(item->isSelected())
		    {
				cols = item->text(5).split(":|:");
				tabcontent += cols[1].replace("_", "\\_") + " & " + cols[2].replace("&", "") + " & " + cols[3] + " & " + cols[4] + " & " + cols[5] + " & " + cols[6] + " & " + cols[8] + " & " +cols[9].section(":#:", 0, 0)+" - "+cols[9].section(":#:", 2, 2)+ " & "+ cols[20] +" \\\\ \n";
		    }
		}
		break;
	    case 3:
		break;
    }
   
	QString templatestr = loadtemplatedata();

	QTime now = QTime::currentTime();
	QDate today = QDate::currentDate();
    QFile output(QDir::homePath()+"/.first4/tmp/"+username+"-"+today.toString("yyyyMMdd")+now.toString("hhmmsszzz")+".tex");

	if ( output.open( QIODevice::WriteOnly ) )
	{
	    QTextStream outstream( &output );
	    templatestr = templatestr.replace("+++DATE+++", today.toString("dd. MMMM yyyy"));
	    templatestr = templatestr.replace("+++PAGE+++", tr("Page:"));
		templatestr = templatestr.replace("+++STOCKNAME+++", cmbdata->currentText().replace("_", "\\_"));
		templatestr = templatestr.replace("+++TABHEAD+++", tabhead);
		templatestr = templatestr.replace("+++TABCONTENT+++", tabcontent.replace("#",""));
		outstream << templatestr << "\n";
	    output.close();
	} else {
	    QMessageBox::critical(0,"Error...",tr("Can't write ouputfile!"));
	}
	    
    vars v;
    QString tool = v.get_tool("TEX2DVI");
	    
    //converting text to dvi
	QStringList args;
    args <<  "-output-directory="+QDir::homePath()+"/.first4/tmp/" << output.fileName();
    QProcess *procdvi = new QProcess( this );
    procdvi->start(tool, args);
    if(procdvi->exitCode()!=0)
		QMessageBox::critical(0,"Error...", tr("Error during convertion from TEXT to DVI!"));

	tool = v.get_tool("DVIVIEWER");
	args.clear();
    args <<  QDir::homePath()+"/.first4/tmp/"+output.fileName().replace(".tex", ".dvi");
    QProcess *procshow = new QProcess( this );
    procshow->start(tool, args);
    if(procshow->exitCode()!=0)
		QMessageBox::critical(0,"Error...", tr("Can't show DVI file."));
	
}
void datafrm::contmenudata()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );

    QAction* del_row = new QAction( tr("Delete &Row"), this );
	connect(del_row , SIGNAL(triggered()), this, SLOT(removerow()));
	contextMenu->addAction(del_row);
		
    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}

void datafrm::contmenustock()
{
    QMenu* contextMenu = new QMenu( this );
    Q_CHECK_PTR( contextMenu );
    
    QAction* edit_entry = new QAction( tr("&Edit entry"), this );
	connect(edit_entry , SIGNAL(triggered()), this, SLOT(editstockentry()));
	contextMenu->addAction(edit_entry);
	
	if(uid == 0 || stockrightslist[cmbdata->currentIndex()]=="[11]")
    {
	    QAction* del_entry = new QAction( tr("&Delete entry"), this );
		connect(del_entry , SIGNAL(triggered()), this, SLOT(delstockentry()));
		contextMenu->addAction(del_entry);
	}

    contextMenu->exec( QCursor::pos() );
    delete contextMenu;
}
//
void datafrm::removerow()
{
    int i;
    for (i=0;i<maintable->rowCount()-1;i++)
    {
    	QTableWidgetItem *item = maintable->item(i, 0);
		if(item->isSelected())
		{
		    QString connstr = "DELETE FROM "+tabnamelist[cmbdata->currentIndex()]+" WHERE `ID`='"+item->text()+"' LIMIT 1;";
		    QSqlQuery query(connstr);
		    query.exec();
			maintable->removeRow(item->row());
		}
    }
    lastdatatab = "";
    //loaddata();
    
    if(maintable->rowCount() == 0)
    	maintable->setRowCount(1);
}
//
void datafrm::searchentries()
{
    if(tabtyplist[cmbdata->currentIndex()]=="stock")
		searchstock();
    else
		searchdata();
}
//
void datafrm::searchdata()
{
    maintable->setRowCount(0);
    int itemp;
    QString connstr = "SELECT * FROM "+tabnamelist[cmbdata->currentIndex()]+" WHERE";
    for (itemp=1;itemp<maintable->columnCount()-1;itemp++)
		connstr += QString(" col%1 LIKE '%%2%' OR").arg(itemp,0,10).arg(txtsearch->text());
    connstr += "DER BY col1;";
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		progbar->setMaximum(query.size());
		maintable->setRowCount(query.size());
		int i;
		int countrow = 0;
		while(query.next())
		{
		    for(i=0;i<maintable->columnCount()-1;i++)
		    {
		    	QTableWidgetItem *item = new QTableWidgetItem;
   				item->setText(query.value(i).toString());
				maintable->setItem(countrow, i, item);
	    	}
   	    	QTableWidgetItem *item = new QTableWidgetItem;
	    	item->setText("");
		    maintable->setItem(countrow, maintable->columnCount()-1, item);
		    progbar->setValue(++countrow);
		}
		
		if(stockrightslist[cmbdata->currentIndex()]=="[11]")
		{
			QTableWidgetItem *item = new QTableWidgetItem;
		    maintable->setRowCount(maintable->rowCount()+1);
		    item->setText("xn");
		    maintable->setItem(maintable->rowCount()-1, maintable->columnCount()-1, item);
		}  
    }		
    lastdatatab = tabnamelist[cmbdata->currentIndex()];
}
//
void datafrm::searchstock()
{
    maintree->clear();
    QStringList cols = colslist[cmbdata->currentIndex()].split("#");
    QString connstr = QString("SELECT * FROM " +tabnamelist[cmbdata->currentIndex()]+" WHERE `col1` LIKE '%%1%' OR `col2` LIKE '%%2%' ORDER BY col1;").arg(txtsearch->text()).arg(txtsearch->text());
    QSqlQuery query(connstr);
    if(query.isActive())
    {
		int i;
		int countrow = 0;
		progbar->setMaximum(query.size());
		while(query.next())
		{
		    QTreeWidgetItem *item = new QTreeWidgetItem(maintree);
		    item->setText(1, query.value(0).toString());
		    item->setText(2, query.value(1).toString());
		    item->setText(3, query.value(2).toString().section("\n", 0, 0));
		    item->setText(4, query.value(2).toString());
		    if(query.value(2).toString().contains("\n")>0)
		    {
				QTreeWidgetItem *item2 = new QTreeWidgetItem(item, item);
				item2->setText(1, "2");
				item2->setText(2, "---");
				item2->setText(3, query.value(2).toString().section("\n", 1));
		    }
	    
		    QTreeWidgetItem *childitem;   
		    for(i=3;i<7;i++)
		    {
				childitem = new QTreeWidgetItem(item);
				childitem->setText(1, QString("%1").arg(i, 0, 10));
				childitem->setText(2, cols[i-1].section(":", 0, 0));
				childitem->setText(3, query.value(i).toString().section("\n", 0, 0));
		    }
	    
		    //Load Sellprice
		    childitem = new QTreeWidgetItem(item);
		    childitem->setText(1, QString("%1").arg(8, 0, 10));
		    childitem->setText(2, cols[7].section(":", 0, 0));
		    childitem->setText(3, query.value(8).toString().section("\n", 0, 0));
	    
		    //Load Suppliers
		    childitem = new QTreeWidgetItem(item);
		    childitem->setText(2, cols[6].section(":", 0, 0));
		    QStringList lines = query.value(9).toString().split(":##:");
		    for(i=0;i<lines.count()-1;i++)
		    {
				QTreeWidgetItem *child = new QTreeWidgetItem(childitem);
				child->setText(2, lines[i].section(":#:", 0, 0).section(";", 0, 0));
				child->setText(3, lines[i].section(":#:", 2, 2));
		    }
	    
		    QString tmpstr = "";
		    for(i=0;i<=cols.count();i++)
		    {
				tmpstr += query.value(i).toString()+":|:";
		    }
		    item->setText(5, tmpstr);
		    progbar->setValue(++countrow);
	    }
	}    
	lastdatatab = tabnamelist[cmbdata->currentIndex()];    
}
//
void datafrm::clearsearch()
{
    txtsearch->setText("");
    if(tabtyplist[cmbdata->currentIndex()]=="stock")
		loadstock();
    else
		loaddata();
}
//
void datafrm::impexp()
{
    dataimpexpfrm *dataimpexp = new dataimpexpfrm;
    dataimpexp->init();
    if(dataimpexp->exec())
    {
		lastdatatab = "";
		changecmb();
	}
}
//
QString datafrm::loadtemplatedata()
{
	QString answ;
	QSqlQuery query("SELECT data FROM templates WHERE `name`='sys_stocklist';");
	if ( query.isActive())
	{
		query.next();
		answ = query.value(0).toString();
	}
	else
	{
		QSqlError qerror = query.lastError();
		QMessageBox::warning ( 0, tr ( "Can't load template..." ), qerror.text() );
	}
	return answ;
}
