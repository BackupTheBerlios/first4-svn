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

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	
	scanRect = rect;
	scanTeft = left;
	scanTop = top;
	
	setGeometry( left, top, width(), height() );

	reloadCustomer();
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
	scanWidget = new QDialog( 0 );
	
	QVBoxLayout *wlayout = new QVBoxLayout( scanWidget );
	QHBoxLayout *btn_layout = new QHBoxLayout;

	QFrame *separator = new QFrame( scanWidget );
	separator->setFrameShape( QFrame::HLine );
	separator->setFrameShadow( QFrame::Sunken );
	
	QApplication::restoreOverrideCursor();
	
	sanew = new SaneWidget( scanWidget );

	if ( sanew->openDevice( device ) == FALSE ) {
		QString dev = sanew->selectDevice( NULL );

		if ( sanew->openDevice( dev ) == FALSE ) {
			QErrorMessage *err = new QErrorMessage( this );
			err->showMessage( QString( "Opening the selected scanner failed!" ) );
			delete( scanWidget );			
			delete( sanew );
			scanWidget = NULL;
			sanew = NULL;
			return;
		}
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
	
	QApplication::setOverrideCursor( Qt::WaitCursor );
	qApp->processEvents();

	wlayout->setMargin( 2 );
	wlayout->setSpacing( 2 );
	wlayout->addWidget( sanew );
	wlayout->addWidget( separator );
	wlayout->addLayout( btn_layout );

	scanWidget->setGeometry( scanTeft, scanTop, width(), height() );
	scanWidget->show();
	QApplication::restoreOverrideCursor();
#endif
}


void DocScanner::scanStart() {
#ifdef Q_OS_WIN32
	// WINDOWS
#else
	if ( progressDialog == NULL ) {
		progressDialog = new QProgressDialog( NULL );
	}

	progressDialog->setMaximum( PROGRESS_MAX );
	progressDialog->setMinimum( PROGRESS_MIN );

	if( sanew ) {
		connect( progressDialog, SIGNAL( canceled() ), sanew, SLOT( scanCancel() ) );
		connect( sanew, SIGNAL( scanProgress( int ) ), progressDialog, SLOT( setValue( int ) ) );
	}

	progressDialog->show();
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
	// FIXME: Stretch image
	if( !pix.isNull() )
		labelPixmap->setPixmap( pix );
#endif
}

void DocScanner::reloadCustomer() {

	cbxCustomer->clear();
	QString connstr = QString( "SELECT * FROM adrtabs;" );

	QSqlQuery query( connstr );
	int fieldNo = query.record().indexOf( "name" );

	if ( query.isActive() ) {
		while ( query.next() ) {
			QString name = query.value( fieldNo ).toString();
			cbxCustomer->addItem( name );
		}
	}
}
