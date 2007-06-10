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

#ifndef CHIPCARD_H
#define CHIPCARD_H

#include "ui_chipcardbase.h"

#include <chipcard/chipcard.h>
#include <chipcard/client/card.h>
#include <chipcard/client/client.h>
#include <chipcard/client/cards/geldkarte.h>

#include <QtCore>
#include <QtGui>

class ChipCard;
extern ChipCard *chipcard_instance;

class ChipCard : public QWidget, public Ui::UiChipCardBase
{
	Q_OBJECT

	public:
		ChipCard( QWidget *parent = 0L );
		~ChipCard();

		static ChipCard *instance() { return chipcard_instance;	}

	private slots:
		void pay();
		void reloadCustomer();
		void reloadProducts();
		void errorMsg ( LC_CARD *card, LC_CLIENT_RESULT res );

	private:
		bool initCard();
		bool deinitCard( LC_CARD *card, LC_CLIENT *cl, LC_CLIENT_RESULT res );

		LC_CLIENT *lcClient;
		LC_CLIENT_RESULT lcClientRes;
		LC_CARD *lcCard;
		LC_GELDKARTE_VALUES *lcGeldkarteValues;

		int rv;

	protected:
		void closeEvent( QCloseEvent *e );
};
#endif //CHIPCARD_H
