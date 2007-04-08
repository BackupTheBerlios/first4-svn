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

#include <QtCore>
#include <QtXml>

#include "chipcard.h"

ChipCard *chipcard_instance = NULL;
ChipCard::ChipCard( QWidget *parent ) : QWidget( parent ) {
	setupUi( this );
	chipcard_instance = this;

	//connect ( btnSearch, SIGNAL ( clicked() ), this, SLOT ( slotSearch() ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry( left, top, width(), height() );
}

ChipCard::~ChipCard() {}

void ChipCard::closeEvent( QCloseEvent *e ) {
	chipcard_instance = NULL;
}

void ChipCard::pay() {}
