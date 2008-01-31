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
//
QString lastdatatab;
QStringList stockrightslist, tabnamelist, colslist, tabtyplist;
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
       
    QString connstr = QString("SELECT * FROM datatabs WHERE users LIKE '%%1 [1%';").arg(username);
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
	connect(btndelete, SIGNAL(released()), this, SLOT(delstockentry()));
	connect(btnprint, SIGNAL(released()), this, SLOT(print()));
    connect(maintable, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenudata()));
    connect(maintree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contmenustock()));
    connect(btnsearch, SIGNAL(released()), this, SLOT(searchentries()));
    connect(txtsearch, SIGNAL(returnPressed()), this, SLOT(searchentries()));    
    connect(btnclear, SIGNAL(released()), this, SLOT(clearsearch()));
}
//
void datafrm::closeEvent(QCloseEvent* ce )
{
	vars v;
	v.savegeo(this->objectName(), this->isMaximized(), this->x(), this->y(), this->width(), this->height());
	ce->accept();
}
//
void datafrm::checkrights()
{
    if(lbluser->text() == "Administrator" || stockrightslist[cmbdata->currentIndex()]=="[11]")
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
		btnedit->setEnabled(FALSE);
		btndelete->setEnabled(FALSE);
		btntransfer->setEnabled(FALSE);
    }
}

void datafrm::changecmb()
{
    btnprint->setEnabled(FALSE);
    if(cmbdata->currentText() != lastdatatab)
    {
		if(tabtyplist[cmbdata->currentIndex()]=="stock")
		{
		    checkrights();
		    loadstock();
		}
		else
		{
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
				int answ=QMessageBox::warning(this, tr("Save changes..."), tr("Save changes?"),QMessageBox::Yes, QMessageBox::No);
				if(answ == QMessageBox::Yes)
				{
				    QString newselection = cmbdata->currentText();
				    cmbdata->setEditText(lastdatatab);
				    savetable();
				    cmbdata->setEditText(newselection);
				}
		    }
		    checkrights();	    
		    loaddata();
		}
    }
}
//
void datafrm::loadstock()
{
    mainwidget->setCurrentIndex(0);
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
    lastdatatab = cmbdata->currentText();
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
	    
    QString connstr = "SELECT * FROM " +tabnamelist[cmbdata->currentIndex()]+" ORDER BY col1;";
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
    lastdatatab = cmbdata->currentText();
}
//
void datafrm::savetable()
{
    int i;
    QString colwidth = "UPDATE `datatabs` SET `cols`='";
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
		    this->loaddata();
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
		progbar->setValue(i);
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
		if(estock->exec())
		    loadstock();
		else
			QSqlDatabase::database().rollback();
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
	    
    //converting text to dvi
	QStringList args;
    args <<  "-output-directory="+QDir::homePath()+"/.first4/tmp/" << output.fileName();
    QProcess *procdvi = new QProcess( this );
    procdvi->start("latex", args);
    if(procdvi->exitCode()!=0)
		QMessageBox::critical(0,"Error...", tr("Error during convertion from TEXT to DVI!"));

	args.clear();
    args <<  QDir::homePath()+"/.first4/tmp/"+output.fileName().replace(".tex", ".dvi");
    QProcess *procshow = new QProcess( this );
    procshow->start("kdvi", args);
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
    QAction* del_entry = new QAction( tr("&Delete entry"), this );
	connect(del_entry , SIGNAL(triggered()), this, SLOT(delstockentry()));
	contextMenu->addAction(del_entry);
			
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
		}
    }    
    lastdatatab = "";
    loaddata();
    
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
    lastdatatab = cmbdata->currentText();
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
	lastdatatab = cmbdata->currentText();    
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
{/*
    stockimpexpfrm *simpexp = new stockimpexpfrm;
    simpexp->setFixedSize(simpexp->width(), simpexp->height());  
    if(tabtyplist[cmbdata->currentItem()]!="stock")
    {
	simpexp->rdbtn_3->setEnabled(FALSE);
	simpexp->rdbtn_4->setEnabled(FALSE);
    }
    if(simpexp->exec())
    {
	QString filestr;
	if(simpexp->rdbtn_1->isChecked())
	{
	    filestr = QFileDialog::getSaveFileName("", tr("CSV-File (*.csv)"), this, tr("Save File as...") );
	    if(filestr.mid(filestr.length()-4).lower() != ".csv")
		filestr += ".csv";
	    if(filestr!="")
		stockfrm::expdata(filestr, simpexp->rdbtnsel->isChecked());
	}
	else if(simpexp->rdbtn_2->isChecked())
	{
	    filestr = QFileDialog::getOpenFileName("", tr("CSV-File (*.csv)"), this, tr("Open File...") );
	    if(filestr!="")
		stockfrm::impdata(filestr);
	}
	else if(simpexp->rdbtn_3->isChecked())
	{
	    filestr = QFileDialog::getSaveFileName("", tr("Stock-File (*.fst)"), this, tr("Save File as...") );
	    if(filestr.mid(filestr.length()-4).lower() != ".fst")
		filestr += ".fst";
	    if(filestr!="")	    
		stockfrm::expstock(filestr, simpexp->rdbtnsel->isChecked());
	}
	else if(simpexp->rdbtn_4->isChecked())
	{
	    filestr = QFileDialog::getOpenFileName("", tr("Stock-File (*.fst)"), this, tr("Open File...") );
	    if(filestr!="")
		stockfrm::impstock(filestr);
	}
    }*/
}
//
void datafrm::expstock(QString filestr, bool selection)
{/*
    int i, ichild;
    
    progfrm *pfrm = new progfrm;
    pfrm->setFixedSize(pfrm->width(), pfrm->height());
    pfrm->setGeometry(300, 300, pfrm->width(), pfrm->height());
    pfrm->lblinfo->setText(tr("Stock will be exported..."));
    pfrm->progbar->setTotalSteps(mainlistview->childCount());
    pfrm->show();        
    
    if(!selection)
    {
	QFile file(filestr);
	if(file.open(IO_WriteOnly))	    
	{
	    QTextStream stream(&file);
	    stream << "<first-" << firstver << ">\n";
	    QListViewItem *item = mainlistview->firstChild();
	    if(item!=0)
	    {
		for(i=0;i<mainlistview->childCount();i++)
		{
		    if(i>0)
			    item = item->itemBelow();
		    stream << "\"" << item->text(2) << "\";";
		    stream << "\"" << item->text(4).replace("\n",",") << "\";";
		    QListViewItem *child = item->firstChild();
		    if(child!=0)
		    {
			for(ichild=0;ichild<item->childCount();ichild++)
			{
			    if(ichild>0)
				child = child->itemBelow();
			    if(child->text(2)!="")
				stream << "\"" << child->text(3) << "\";";
			}
		    }
		    stream << item->text(5) << "\n";
		    pfrm->progbar->setProgress(i+1);
		}
		
	    }
	}
	file.close();
    }
    else
    {
	QFile file(filestr);
	if(file.open(IO_WriteOnly))	    
	{
	    QTextStream stream(&file);
	    stream << "<first-" << firstver << ">\n";
	    QListViewItem *item = mainlistview->firstChild();
	    if(item!=0)
	    {
		for(i=0;i<mainlistview->childCount();i++)
		{
		    if(i>0)
			item = item->itemBelow();		    
		    if(mainlistview->isSelected(item))
		    {
			stream << "\"" << item->text(2) << "\";";
			stream << "\"" << item->text(4).replace("\n",",") << "\";";
			QListViewItem *child = item->firstChild();
			if(child!=0)
			{
			    for(ichild=0;ichild<item->childCount();ichild++)
			    {
				if(ichild>0)
				    child = child->itemBelow();
				if(child->text(2)!="")
				    stream << "\"" << child->text(3) << "\";";
			    }
			}
			stream << item->text(5) << "\n";
		    }
		    pfrm->progbar->setProgress(i+1);
		}
	    }
	}
	file.close();
    }
    pfrm->close();*/
}
//
void datafrm::impstock(QString filestr)
{/*
    int i, ii;
    stockimpprevfrm *impprev = new stockimpprevfrm;
    impprev->maintable->setNumRows(0);
    impprev->maintable->setNumCols(0);
    
    impprev->cmbtable->clear();
    for(i=0;i<tabtyplist.count();i++)
    {
	if(tabtyplist[i]=="stock")
	{
	    impprev->cmbtable->insertItem(cmbdata->text(i), -1);
	    impprev->cmbtabname->insertItem(tabnamelist[i], -1);
	}
    }
    QString connstr = "SELECT * FROM `datatabs` WHERE `tabart`= 'Lager';";
    QSqlQuery query(connstr);
    query.next();
    QStringList cols = QStringList::split("", query.value(4).toString());
    impprev->maintable->setNumCols(cols.count());
    QHeader *thh = impprev->maintable->horizontalHeader();
    for(i=0;i<cols.count();i++)
    {
	thh->setLabel(i, cols[i].section(";", 0, 0));
	impprev->maintable->setColumnWidth(i, cols[i].section(";", 1, 1).toInt());
    }
    
    QFile file(filestr);
    if(file.open( IO_ReadOnly ) )
    {
	QTextStream stream( &file );
	QString line;
	line = stream.readLine(); // line of text excluding '\n'
	while(!stream.atEnd())
	{
	    line = stream.readLine(); // line of text excluding '\n'
	    QStringList cells = QStringList::split(";", line);
	    impprev->maintable->insertRows(impprev->maintable->numRows(), 1);
	    for(i=0;i<cells.count();i++)
	    {
		impprev->maintable->setText(impprev->maintable->numRows()-1, i, cells[i].replace("\"", ""));
	    }
	}
	file.close();
	if(impprev->exec())
	{
	    for(i=0;i<impprev->maintable->numRows();i++)
	    {
		QString connstr = "INSERT INTO `"+impprev->cmbtabname->text(impprev->cmbtable->currentItem())+"` (`ID`, `col1`, `col2`, `col3`, `col4`, `col5`, `col6`, `col7`, `col8`, `col9`, `col10`, `col11`, `col12`, `col13`, `col14`, `col15`, `col16`, `col17`, `col18`, `col19`, `col20`) VALUES (NULL, ";
		for(ii=0;ii<impprev->maintable->numCols();ii++)
		{
		    connstr += "'" + impprev->maintable->text(i, ii) +"', ";
		}
		connstr = connstr.left(connstr.length()-2);
		connstr += ");";
		QSqlQuery query(connstr);
	    }
	}
    }
    else
    {
	QMessageBox::critical(0,"Error...", tr("Error during reading of the File!"));
    }*/
}
//
void datafrm::expdata(QString filestr, bool selection)
{/*
    int row, col;    
    
    progfrm *pfrm = new progfrm;
    pfrm->setFixedSize(pfrm->width(), pfrm->height());
    pfrm->setGeometry(300, 300, pfrm->width(), pfrm->height());
    pfrm->lblinfo->setText(tr("Date will be exported..."));
    pfrm->progbar->setTotalSteps(maintable->numRows());
    pfrm->show();    
    
    if(!selection)
    {
	QFile file(filestr);
	if(file.open(IO_WriteOnly))
	{  
	    QTextStream stream(&file);
	    for(row=0;row<maintable->numRows();row++)
	    {
		for(col=1;col<maintable->numCols()-1;col++)
		{
		    stream << "\"" << maintable->text(row, col) << "\"";
		    if(col < maintable->numCols()-2)
			stream << ";";
		}
		stream << "\n";
		pfrm->progbar->setProgress(row+1);
	    }
	    file.close();    
	}
	else
	{
	    QMessageBox::critical(0,"Export...",tr("Error during writting of the File!"));
	}
    }
    else
    {
	QFile file(filestr);
	if(file.open(IO_WriteOnly))
	{  
	    QTextStream stream(&file);
	    for(row=0;row<maintable->numRows();row++)
	    {
		if(maintable->isRowSelected(row))
		{
		    for(col=1;col<maintable->numCols()-1;col++)
		    {
			stream << maintable->text(row, col);
			if(col < maintable->numCols()-2)
			    stream << ";";
		    }
		    stream << "\n";
		}
		pfrm->progbar->setProgress(row+1);
	    }
	    file.close();    
	}
	else
	{
	    QMessageBox::critical(0,"Export...",tr("Error during writting of the File!"));
	}	    
    }
    pfrm->close();*/
}
//
void datafrm::impdata(QString filestr)
{/*
    int i, ii;
    stockimpprevfrm *impprev = new stockimpprevfrm;
    impprev->maintable->setNumRows(0);
    impprev->maintable->setNumCols(0);
    
    impprev->cmbtable->clear();
    for(i=0;i<tabtyplist.count();i++)
    {
	if(tabtyplist[i]!="Lager")
	{
	    impprev->cmbtable->insertItem(cmbdata->text(i), -1);
	    impprev->cmbtabname->insertItem(tabnamelist[i], -1);
	}
    }
    
    QFile file(filestr);
    if(file.open( IO_ReadOnly ) )
    {
	QTextStream stream( &file );
	QString line;
	
	
	line = stream.readLine(); // erste zeile auslesen um anzahl spalten zu ermitteln
	QStringList cells = QStringList::split(";", line);
	impprev->maintable->setNumCols(cells.count());
	impprev->maintable->insertRows(impprev->maintable->numRows(), 1);
	for(i=0;i<cells.count();i++)
	{
	    impprev->maintable->setText(impprev->maintable->numRows()-1, i, cells[i].replace("\"", ""));
	}
	
	while(!stream.atEnd())
	{
	    line = stream.readLine(); // line of text excluding '\n'
	    cells = QStringList::split(";", line);
	    impprev->maintable->insertRows(impprev->maintable->numRows(), 1);
	    for(i=0;i<cells.count();i++)
	    {
		impprev->maintable->setText(impprev->maintable->numRows()-1, i, cells[i].replace("\"", ""));
	    }
	}
	file.close();
	
	if(impprev->exec())
	{
	    for(i=0;i<impprev->maintable->numRows();i++)
	    {
		QString connstr = "INSERT INTO `"+impprev->cmbtabname->text(impprev->cmbtable->currentItem())+"` (";
		QString colstr = "SHOW FIELDS FROM `"+impprev->cmbtabname->text(impprev->cmbtable->currentItem())+"`";
		QSqlQuery colquery(colstr);
		while(colquery.next())
		{
		    connstr += "`"+colquery.value(0).toString() + "`, ";
		}
		connstr = connstr.left(connstr.length()-2);
		connstr += ") VALUES ('', ";
		for(ii=0;ii<colquery.size();ii++)
		{
		    if(ii<impprev->maintable->numCols())
			connstr += "'" + impprev->maintable->text(i, ii) +"', ";
		}
		connstr = connstr.left(connstr.length()-2);
		connstr += ");";
		QSqlQuery query(connstr);
	    }
	}
    }
    else
    {
	QMessageBox::critical(0,"Error...", tr("Error during reading of the File!"));
    }*/
}
//
QString datafrm::loadtemplatedata()
{
	QString answ;
	QSqlQuery query("SELECT data FROM templatestab WHERE `name`='sys_stocklist';");
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
