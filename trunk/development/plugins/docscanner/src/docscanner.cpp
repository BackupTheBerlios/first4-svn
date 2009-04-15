/*
*   Copyright (C) 2007 by Alexander Saal <alex.saal@gmx.de>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or (at
*   your option) any later version.
*
*   This program is distributed in the hope that it will be useful, but
*   WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software Foundation,
*   Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "docscanner.h"

#include <QtCore>
#include <QtGui>
#include <QtSql>

#ifdef Q_OS_WIN32
	#include <Twain.h>
#else
	#include <sane_widget.h>
#endif

DocScanner *docscanner_instance = NULL;
DocScanner::DocScanner( QWidget *parent ) : QWidget( parent )
{
	setupUi( this );
	docscanner_instance = this;

	connect( btnScan, SIGNAL( clicked() ), this, SLOT( scann() ) );
	connect( cbxAddressbook, SIGNAL( currentIndexChanged( QString ) ), this, SLOT( reloadCustomer( QString ) ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	
	scanRect = rect;
	scanLeft = left;
	scanTop = top;
	
	setGeometry( left, top, width(), height() );
	
	reloadAddressBook();
	checkDatabaseVersion();
}

DocScanner::~DocScanner() {}

void DocScanner::closeEvent( QCloseEvent *e ) {

	docscanner_instance = NULL;
	e->accept();
}

void DocScanner::scann() {

#ifdef Q_OS_WIN32
	// WINDOWS
#else
	QApplication::setOverrideCursor( Qt::WaitCursor );
	qApp->processEvents();
	
	progressDialog = NULL;
	QString device( "" );
	
	// Scanning dialog
	scanWidget = new QWidget( 0 );
	
	QVBoxLayout *wlayout = new QVBoxLayout( scanWidget );
	QHBoxLayout *btn_layout = new QHBoxLayout;

	QFrame *separator = new QFrame( scanWidget );
	separator->setFrameShape( QFrame::HLine );
	separator->setFrameShadow( QFrame::Sunken );
	
	sanew = new SaneWidget( scanWidget );
	
	if ( sanew->openDevice( device ) == FALSE ) {
		QString dev = sanew->selectDevice( NULL );

		if ( sanew->openDevice( dev ) == FALSE ) {
			QErrorMessage *err = new QErrorMessage( this );
			err->showMessage( QString( "Opening the selected scanner failed!" ) );
			
			if( scanWidget != NULL ) {
				delete( scanWidget );
				scanWidget = NULL;
			}

			if( sanew != NULL ) {
				delete( sanew );
				sanew = NULL;
			}

			return;
		}

		scanWidget->setWindowTitle( tr( "Scanwidget ... " ) + dev );
	}
	

	connect( sanew, SIGNAL( scanStart() ), this, SLOT( scanStart() ) );
	connect( sanew, SIGNAL( scanFaild() ), this, SLOT( scanFailed() ) );
	connect( sanew, SIGNAL( scanDone() ), this, SLOT( scanEnd() ) );
	connect( sanew, SIGNAL( imageReady() ), this, SLOT( imageReady() ) );

	sanew->setIconColorMode( QIcon( ":/color.png" ) );
	sanew->setIconGrayMode( QIcon( ":/gray.png" ) );
	sanew->setIconBWMode( QIcon( ":/black_white.png" ) );
	sanew->setIconPreview( QIcon( ":/eye.png" ) );
	sanew->setIconFinal( QIcon( ":/filesave.png" ) );
	sanew->setIconZoomIn( QIcon( ":/viewmag+.png" ) );
	sanew->setIconZoomOut( QIcon( ":/viewmag-.png" ) );
	sanew->setIconZoomSel( QIcon( ":/viewmagfit.png" ) );
	sanew->setIconZoomFit( QIcon( ":/view_fit_window.png" ) );
	
	wlayout->setMargin( 2 );
	wlayout->setSpacing( 2 );
	wlayout->addWidget( sanew );
	wlayout->addWidget( separator );
	wlayout->addLayout( btn_layout );

	scanWidget->setGeometry( scanLeft + 100, scanTop + 100, width(), height() );
	scanWidget->show();
	QApplication::restoreOverrideCursor();
#endif
}


void DocScanner::scanStart() {
#ifdef Q_OS_WIN32
	// WINDOWS
#else
	QApplication::setOverrideCursor( Qt::WaitCursor );

	if ( progressDialog == NULL ) {
		progressDialog = new QProgressDialog( NULL );
	}

	progressDialog->setWindowTitle( tr( "Scanning document ..." ) );
	progressDialog->setCancelButtonText( tr( "Cancel" ) );
	progressDialog->setMaximum( PROGRESS_MAX );
	progressDialog->setMinimum( PROGRESS_MIN );

	if( sanew ) {
		connect( progressDialog, SIGNAL( canceled() ), sanew, SLOT( scanCancel() ) );
		connect( sanew, SIGNAL( scanProgress( int ) ), progressDialog, SLOT( setValue( int ) ) );
	}

	progressDialog->show();

	QApplication::restoreOverrideCursor();
#endif
}

void DocScanner::scanEnd() {
#ifdef Q_OS_WIN32
	// WINDOWS
#else
	if ( progressDialog != NULL ) {
		delete( progressDialog );
		progressDialog = NULL;
	}
#endif
}

void DocScanner::scanFailed() {
	
#ifdef Q_OS_WIN32
	// WINDOWS
#else
	if ( progressDialog != NULL )	{
		delete( progressDialog );
		progressDialog = NULL;
	}
	
	QMessageBox mb( "SaneWidget",

	                "Scanning failed!\n",
	                QMessageBox::Critical,
	                QMessageBox::Ok | QMessageBox::Default,
	                QMessageBox::NoButton,
	                QMessageBox::NoButton );
	mb.exec();
#endif
}

void DocScanner::imageReady() {

#ifdef Q_OS_WIN32
	// WINDOWS
#else
	QPixmap pix = QPixmap::fromImage( *( sanew->getFinalImage() ) );

	if( !pix.isNull() ) {
		// Close scanwidget
		scanWidget->close();

		// Work with object "pix"
		if( rBtnSaveImageFile->isChecked() ) {			
			// save image as file			
						
			// some information:
			// 1.	username
// 			// 2.	documet dirctory (select from database)
			// 3.	but last not least, save image to the correct user
			
			QString userName = QString( cbxCustomer->currentText() );	
			if( userName.isEmpty() )  return;
				
			QString sqlDocQuery = QString( "SELECT value FROM maincfgtab WHERE var LIKE '%docfolder%';" );
			QString docFolder = QString( "" );
			
			QSqlQuery docQuery( sqlDocQuery );

			int fieldNo = docQuery.record().indexOf( "value" );
			
			if( fieldNo <= -1 ) {
				QMessageBox::critical( this, tr( "DocScanner Plugin" ), tr( "The index of column 'value' from 'maincfgtab' table is not correct, abort!" ) );
				return;
			}
						
			bool isActive = docQuery.isActive();

			if ( isActive ) {
				while ( docQuery.next() ) {
					docFolder = docQuery.value( fieldNo ).toString();
				}
			}

			if( docFolder.isEmpty() ) {
				QMessageBox::critical( this, tr( "DocScanner Plugin" ), tr( "No document folder availabel!" ) );
				return;
			}
			
			// FIXME: set the correct sql statement for insert image (blob) or image as file to the correct costumner
			QString sqlImgQuery = QString( "" );
			QSqlQuery imgQuery( sqlImgQuery );
			if( imgQuery.exec() )
				return;
			

		} else if ( rBtnSaveImageBlob->isChecked() ) {
			// save image as blob into database .... more memory in database is needed
		}
	}
#endif
}

void DocScanner::reloadAddressBook() {

	addressBook.clear();
	cbxAddressbook->clear();
	cbxAddressbook->addItem( "" );

	QString connstr = QString( "SELECT * FROM adrtabs;" );

	QSqlQuery query( connstr );
	int fieldNoName = query.record().indexOf( "name" );
	int fieldNoDesc = query.record().indexOf( "description" );

	if ( query.isActive() ) {
		while ( query.next() ) {
			QString name = query.value( fieldNoName ).toString();
			QString desc = query.value( fieldNoDesc ).toString();
			
			cbxAddressbook->addItem( desc );
			addressBook[ name ] = desc;
		}
	}
}

void DocScanner::reloadCustomer( QString desc ) {
	
	if( desc.isEmpty() || desc.isNull() ) {
		cbxCustomer->clear();
		return;
	}

	cbxCustomer->clear();

	QMap<QString, QString>::const_iterator c_it = addressBook.begin();	
	while( c_it != addressBook.end() ) {		
		if( c_it.value() == desc ) {
			QString connstr = QString( "SELECT * FROM " + QString( c_it.key() ) );
			
			QSqlQuery query( connstr );
			int fieldNoLastName = query.record().indexOf( "lastname" );
			int fieldNoFirstName = query.record().indexOf( "firstname" );
			int fieldNoCompany = query.record().indexOf( "company" );

			if ( query.isActive() ) {
				while ( query.next() ) {
					QString lastname = query.value( fieldNoLastName ).toString();
					QString firstname = query.value( fieldNoFirstName ).toString();
					QString company = query.value( fieldNoCompany ).toString();
					
					if( firstname.isEmpty() || firstname.isNull() && lastname.isEmpty() || lastname.isNull() && company.isEmpty() || company.isNull() ) {
						QMessageBox::critical( this, tr( "DocScanner Plugin" ), tr( "No customer availabel!" ) );
						return;
					}
					else if( lastname.isEmpty() || lastname.isNull() && company.isEmpty() || company.isNull() )
						cbxCustomer->addItem( firstname );

					else if( firstname.isEmpty() || firstname.isNull() && company.isEmpty() || company.isNull() )
						cbxCustomer->addItem( lastname );

					else if( !firstname.isEmpty() || !firstname.isNull() && !lastname.isEmpty() || !lastname.isNull() && !company.isEmpty() || !company.isNull())
						cbxCustomer->addItem( company + " - " + lastname + ", " + firstname);

					else if( !company.isEmpty() || !company.isNull() )
						cbxCustomer->addItem( company );

					else if( company.isEmpty() || company.isNull() )
						cbxCustomer->addItem( company );
				}
			}
			
			
		}
		++c_it;
	}	
}

void DocScanner::checkDatabaseVersion() {

	QString connstr = QString( "SELECT value FROM maincfgtab WHERE var = 'dbversion';" );

	QSqlQuery query( connstr );
	if ( query.isActive() ) {
		while ( query.next() ) {
			QString value = query.value( query.record().indexOf( "value" ) ).toString();		

			int mainV = value.split( "." ).value( 0 ).toInt();
			int secondV = value.split( "." ).value( 1 ).toInt();
			int thirdV = value.split( "." ).value( 2 ).toInt();
			int buildDate = value.split( "-" ).value( 1 ).toInt();
		}
	}
}
