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

#include <QtGui>
#include <QtCore>

#include "docscanner.h"
#include "docscannerplugin.h"

QIcon DocScannerPlugin::img() const {
	return QIcon( ":/docscanner.png" );
}

QString DocScannerPlugin::pluginName() const {

	return QString( tr( "Dokumentenscanner" ) );
}

QString DocScannerPlugin::pluginVersion() const {

	return QString( "0.0.1" );
}

QDialog *DocScannerPlugin::dialog() const {

	return NULL;
}

QWidget *DocScannerPlugin::widget() const {

	if ( !docscanner_instance ) {
		docscanner_instance = new DocScanner();
	
	} else {
		return docscanner_instance;
	}

	return docscanner_instance;
}

void DocScannerPlugin::showWidget() {
	showWindow( widget() );
}

QWidget *DocScannerPlugin::newToolBoxWidget() const {

	QWidget *window = new QWidget();
	QGridLayout *layout = new QGridLayout;
	QPushButton *btn = new QPushButton( tr( "Scan documents" ) );
	btn->setFlat( true );
	
	connect( btn, SIGNAL( clicked() ), this, SLOT( showWidget() ) );
	
	layout->addWidget( btn, 0, 0 );

	window->setLayout( layout );
	return window;
}

int DocScannerPlugin::toolBoxIndex() const {

	return -1;
}

bool DocScannerPlugin::showWindow( QDialog *dialog ) const {

	if ( dialog->exec() == QDialog::Accepted ) {
		delete dialog;
		return true;

	} else {
		delete dialog;
		return false;
	}
}

bool DocScannerPlugin::showWindow( QWidget *widget ) const {

	widget->show();
	return true;
}

Q_EXPORT_PLUGIN2( docscannerplugin, DocScannerPlugin )
