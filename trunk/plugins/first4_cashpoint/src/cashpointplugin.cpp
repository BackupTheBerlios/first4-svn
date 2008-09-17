/*
*   Copyright (C) 2008 by Orlando Procopio <orlando@procopio.ch>
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
//
#include <QtGui>
#include <QtCore>
#include <QtSql>
//
#include "cashpoint_main.h"
#include "cashpointplugin.h"
//
QString username, fullname, firstver;
//
QIcon CashpointPlugin::img() const {
	return QIcon( ":/kcalc.png" );
}

QString CashpointPlugin::pluginName() const {

	return QString( tr( "first4 Cashpoint" ) );
}

QString CashpointPlugin::pluginVersion() const {

	return QString( "0.0.1" );
}

QDialog *CashpointPlugin::dialog() const {

	return NULL;
}

QWidget *CashpointPlugin::widget() const {

	if ( !cashpoint_instance ) {
		cashpoint_instance = new CashPoint();
	
	} else {
		return cashpoint_instance;
	}

	return cashpoint_instance;
}

void CashpointPlugin::showWidget() {
	QStringList parameters = (QStringList() << "username" << "fullname" << "firstver");
	cashpoint_instance->init(parameters);
	showWindow( widget() );
} 

QWidget *CashpointPlugin::newToolBoxWidget() const {

	QWidget *window = new QWidget();
	QGridLayout *layout = new QGridLayout;
	QPushButton *btn = new QPushButton( tr( "Cashpoint" ) );
	btn->setFlat( true );
	btn->setIcon(QIcon(img()));
	btn->setAutoFillBackground(true);
	btn->setGeometry(QRect(9, 9, 253, 26));
	
	connect( btn, SIGNAL( clicked() ), this, SLOT( showWidget() ) );
	
	layout->setAlignment(Qt::AlignTop);
	layout->addWidget( btn, 0, 0 );
	window->setLayout( layout );
	return window;
}

int CashpointPlugin::toolBoxIndex() const {

	return -1;
}

bool CashpointPlugin::showWindow( QDialog *dialog ) const {

	if ( dialog->exec() == QDialog::Accepted ) {
		delete dialog;
		return true;

	} else {
		delete dialog;
		return false;
	}
}

bool CashpointPlugin::showWindow( QWidget *widget ) const {

	widget->show();
	return true;
}

Q_EXPORT_PLUGIN2(first4_cashpoint, CashpointPlugin )
