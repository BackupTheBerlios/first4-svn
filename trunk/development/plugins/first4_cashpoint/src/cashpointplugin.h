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
#ifndef CASHPOINTPLUGIN_H
#define CASHPOINTPLUGIN_H

#include <QtCore>
#include <QtGui>

#include <plugininterface.h>

class CashpointPlugin : public QObject, public First4PluginInterface {
	Q_OBJECT
	Q_INTERFACES( First4PluginInterface )

	public:
		QIcon img() const;
		QString pluginName() const;
		QString pluginVersion() const;
		QDialog *dialog() const;
		QWidget *newToolBoxWidget() const;

		int toolBoxIndex() const;
		bool showWindow( QDialog *dialog ) const;
		bool showWindow( QWidget *widget ) const;
		void setenv(QStringList parameters) const;

	private:
		QWidget *widget() const;

	private slots:
		void showWidget();
};

#endif //CASHPOINTPLUGIN_H
