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
#include "chipcard.h"

#include <chipcard3/chipcard3.h>
#include <chipcard3/client/card.h>
#include <chipcard3/client/client.h>
#include <chipcard3/client/cards/geldkarte.h>
#include <chipcard3/client/cards/geldkarte_values.h>

#include <QtCore>
#include <QtGui>
#include <QtSql>

ChipCard *chipcard_instance = NULL;
ChipCard::ChipCard( QWidget *parent ) : QWidget( parent ) {
	setupUi( this );
	chipcard_instance = this;

	connect( btnPay, SIGNAL( clicked() ), this, SLOT( pay() ) );

	QDesktopWidget *desktop = qApp->desktop();
	const QRect rect = desktop->availableGeometry( desktop->primaryScreen() );
	int left = ( rect.width() - width() ) / 2;
	int top = ( rect.height() - height() ) / 2;
	setGeometry( left, top, width(), height() );

	reloadCustomer();
	reloadProducts();
}

ChipCard::~ChipCard() {}

void ChipCard::closeEvent( QCloseEvent *e ) {

	chipcard_instance = NULL;
	e->accept();
}

void ChipCard::pay() {

	if ( initCard() )
		;
	else {
		deinitCard( lcCard, lcClient, lcClientRes );
	}

	rv = LC_GeldKarte_ExtendCard( lcCard );
	if ( rv ) {
		QMessageBox::warning( this, "First4 - Payment", QObject::tr( "Could not extend card as money card ( %1 )." ).arg( rv ) );
		deinitCard( lcCard, lcClient, lcClientRes );
		return;
	}

	lcClientRes = LC_Card_Open( lcCard );
	if ( lcClientRes != LC_Client_ResultOk ) {
		errorMsg( lcCard, lcClientRes );
		deinitCard( lcCard, lcClient, lcClientRes );
		return;
	}

	lcClientRes = LC_Client_Stop( lcClient );
	if ( lcClientRes != LC_Client_ResultOk ) {
		errorMsg( lcCard, lcClientRes );
		deinitCard( lcCard, lcClient, lcClientRes );
		return;
	}

	lcGeldkarteValues = LC_GeldKarte_Values_new();
	lcClientRes = LC_GeldKarte_ReadValues( lcCard, lcGeldkarteValues );
	if ( lcClientRes != LC_Client_ResultOk ) {
		errorMsg( lcCard, lcClientRes );
		deinitCard( lcCard, lcClient, lcClientRes );
		return;
	}

	double loaded = ( double )LC_GeldKarte_Values_GetLoaded( lcGeldkarteValues ) / 100.00;
	double maxTransfer = ( double )LC_GeldKarte_Values_GetMaxXfer( lcGeldkarteValues ) / 100.00;
	
	// Standardwert für den Verkaufspreis bzw. Einkaufspreis
	double buy = 0.00;
	
	/* TODO		Code zum Zahlen mit Karte

		Aus der Datenbank die Produktbeschreibungen holen
		QString productDescription = QString( "" );
		QString name = QString( "" );
		QString connStr = QString( "SELECT * FROM data1;" );
		QSqlQuery query( constr );
		
		int fieldNo = query.record().indexOf( "price" );
	
		if ( query.isActive() ) {
			while ( query.next() ) {
				QString name = query.value( fieldNo ).toString();
			}
		}
	
		Aus der Datenbank den Betrag des Produktes holen
		double buy;
	*/
	
	if( buy <= 0.00 ) {
		QMessageBox::warning( this, tr( "First4 - Payment" ), tr( "The productprice is zero." ) );
		deinitCard( lcCard, lcClient, lcClientRes );
		return;
	}
	
	
	if( buy > maxTransfer ) {
		QMessageBox::warning( this, tr( "First4 - Payment" ), tr( "The productprice is too big, you must sell with creditcard.\n\nThe max. transfer on this card is %1 EUR." ).arg( maxTransfer ) );
		deinitCard( lcCard, lcClient, lcClientRes );
		return;
	}
	
	if( loaded < buy )
		QMessageBox::warning( this, tr( "First4 - Payment" ), tr( "The card have no enougth money on chip.\n\nAvailable money on card are: %1 EUR" ).arg( loaded ) );
			

	deinitCard( lcCard, lcClient, lcClientRes );
}

void ChipCard::reloadCustomer() {

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

void ChipCard::reloadProducts() {}	

bool ChipCard::initCard() {

	QMessageBox::information( this, tr( "First4 - Payment" ), tr( "Please insert a moneycard, and press Ok." ) );

	lcCard = 0;
	lcClient = LC_Client_new( "First4 - Payment", "0.0.1" );
	lcClientRes = LC_Client_Init( lcClient );

	if ( lcClientRes != LC_Client_ResultOk ) {
		errorMsg( lcCard, lcClientRes );
		deinitCard( lcCard, lcClient, lcClientRes );
		return false;
	}

	lcClientRes = LC_Client_Start( lcClient );
	if ( lcClientRes != LC_Client_ResultOk ) {
		errorMsg( lcCard, lcClientRes );
		deinitCard( lcCard, lcClient, lcClientRes );
		return false;
	}

	lcClientRes = LC_Client_GetNextCard( lcClient, &lcCard, 20 );
	if ( lcClientRes != LC_Client_ResultOk ) {
		QMessageBox::critical( this, tr( "First4 - Payment" ), tr( "No card found." ) );
		errorMsg( lcCard, lcClientRes );
		LC_Client_Stop( lcClient );
		deinitCard( lcCard, lcClient, lcClientRes );
		return false;
	}

	return true;
}

bool ChipCard::deinitCard( LC_CARD *card, LC_CLIENT * cl, LC_CLIENT_RESULT res ) {
	
	res = LC_Card_Close( card );
	if ( res == LC_Client_ResultOk ) {
		LC_Client_ReleaseCard( cl, card );
		LC_Card_free( card );
		LC_Client_free( cl );
		QMessageBox::information( this, tr( "First4 - Payment" ), tr( "You can now remove the card from reader." ) );
		return true;
	}

	LC_Client_ReleaseCard( cl, card );
	LC_Card_free( card );
	LC_Client_free( cl );
	return false;
}


void ChipCard::errorMsg( LC_CARD *card, LC_CLIENT_RESULT res ) {
	QString s, lr, lt;

	switch ( res ) {

		case LC_Client_ResultOk:
			s = "Ok.";

			break;

		case LC_Client_ResultWait:
			s = "Timeout.";

			break;

		case LC_Client_ResultIpcError:
			s = "IPC error.";

			break;

		case LC_Client_ResultCmdError:
			s = "Command error.";

			break;

		case LC_Client_ResultDataError:
			s = "Data error.";

			break;

		case LC_Client_ResultAborted:
			s = "Aborted.";

			break;

		case LC_Client_ResultInvalid:
			s = "Invalid argument to command.";

			break;

		case LC_Client_ResultInternal:
			s = "Internal error.";

			break;

		case LC_Client_ResultGeneric:
			s = "Generic error.";

			break;

		default:
			s = "Unknown error.";

			break;
	}

	if ( res == LC_Client_ResultCmdError ) {
		int sw1;
		int sw2;

		sw1 = LC_Card_GetLastSW1( card );
		sw2 = LC_Card_GetLastSW2( card );
		lr = LC_Card_GetLastResult( card );
		lt = LC_Card_GetLastText( card );

		//if ( sw1 != -1 && sw2 != -1 )
		QMessageBox::critical( this, tr( "First4 - Payment" ), tr( "Last card command result: SW1 = %1, SW2 = %2\nResult: %3\nText: %4\n\nError: %5" ).arg( QString("%1").arg( sw1 ), QString("%1").arg( sw2 ), lr, lt, s ) );
	}
	
	QMessageBox::critical( this, tr( "First4 - Payment" ), tr( "Error: %1" ).arg( s ) );
}
