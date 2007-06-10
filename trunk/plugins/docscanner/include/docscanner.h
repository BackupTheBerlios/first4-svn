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

#ifndef DOCSCANNER_H
#define DOCSCANNER_H

#include "ui_docscannerbase.h"

#include <QtCore>
#include <QtGui>

#ifdef Q_OS_WIN32
	#include <Twain.h>
#else
	#include <sane_widget.h>
#endif


class DocScanner;
extern DocScanner *docscanner_instance;

class DocScanner : public QWidget, public Ui::UiDocScannerBase
{
	Q_OBJECT

	public:
		DocScanner( QWidget *parent = 0L );
		~DocScanner();

		static DocScanner *instance() { return docscanner_instance;	}

	private slots:
		void scann();
		void reloadCustomer();
		
		void scanStart();
		void scanEnd();
		void scanFailed();
		void imageReady();

	private:
#ifdef Q_OS_WIN32
		// Twain *tw;
#else
		SaneWidget *sanew;
#endif
		QProgressDialog *progressDialog;
		QDialog *scanWidget;

		QRect scanRect;
		int scanTeft;
		int scanTop;

	protected:
		void closeEvent( QCloseEvent *e );
};
#endif //DOCSCANNER_H
