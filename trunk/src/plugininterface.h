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

#ifndef __FIRST4_PLUGININTERFACE_H__
#define __FIRST4_PLUGININTERFACE_H__

// QtCore Classes
class QIcon;
class QString;
class QWidget;
class QDialog;
class QPushButton;

/**
* @author Alexander Saal <alex.saal@gmx.de>
* @date 2007/03/05
* @version 1.4.x
* @since 1.4.x
*/
class First4PluginInterface
{
	Q_CLASSINFO("Author", "Alexander Saal")
	Q_CLASSINFO("EMAIL", "alex.saal@gmx.de")
	Q_CLASSINFO("URL", "http://chmaster.freeforge.net")

	public:
		/**
		* Konstrukor First4PluginInterface
		*/
		virtual ~First4PluginInterface() {}

		/**
		* Rückgabe des Icons
		*
		* @return	Icon was fr das Plugin definiert wurde
		*/
		virtual QIcon img() const = 0;

		/**
		* Rckgabe des Pluginnamens
		*
		* @return	Pluginname
		*
		* @code
		* QString Pluginname() {
		*	return "Mein erstes Plugin";
		* }
		* @endcode
		*/
		virtual QString pluginName() const = 0;

		/**
		* Rckgabe der Pluginversion
		*
		* @return	Pluginversion
		*
		* @code
		* QString pluginVersion() {
		*	return "1.4.0.0";
		* }
		* @endcode
		*/
		virtual QString pluginVersion() const = 0;

		/**
		* Rückgabe des QDialoges\n\n
		* Es muss ein "return NULL;" erfolgen wenn kein QDialog existiert oder angegeben wurde.\n
		* Es kann nur eine von beiden Funktionen benutzt werden.\n
		*
		* @return	QDialog
		*
		* @code
		* QDialog *dialog() {
		*	return NULL;
		* }
		* @endcode
		*/
		virtual QDialog *dialog() const = 0;

		/**
		* Rückgabe des QWidgets\n\n
		* Es muss ein "return NULL;" erfolgen wenn kein QWidget existiert oder angegeben wurde.\n
		* Es kann nur eine von beiden Funktionen benutzt werden.\n
		*
		* @return	QWidget
		*
		* @code
		* QWidget *widget() {
		*	return NULL;
		* }
		* @endcode
		*/
		virtual QWidget *widget() const = 0;

		/**
		* Rückgabe eines QPushButtons mit Text
		*
		* @return	QPushButton
		*
		* @code
		* QPushButton *button( QWidget *widget ) {
		*	return new QPushButton( widget );
		* }
		* 
		* QPushButton *button() {
		*	return new QPushButton();
		* }
		* @endcode
		*/
		virtual QPushButton *button( QWidget *widget ) const = 0;
		virtual QPushButton *button() const = 0;

		/**
		* Rückgabe eines QWidgets
		*
		* @return	QWidget
		*
		* @code
		* QWidget *newToolBoxWidget() {
		*	return new QWidget();
		* }
		* @endcode
		*/
		virtual QWidget *newToolBoxWidget() const = 0;

		/**
		* Rückgabe des ToolBoxIndexes, ist gleich zusetzen mit den ToolBarPages
		*
		* @return	index 
		*
		* @code
		* int toolBoxIndex() {
		*	return 0;
		* }
		* @endcode
		*/
		virtual int toolBoxIndex() const = 0;

		/**
		* Anzeigen des QDialoges
		*
		* @return	war oder falsch (hängt vom übergebenen Parameter ab)
		*
		* @code
		* bool showWindow( QDialog *dialog ) {
		*	dialog->exec();
		*	delete dialog;
		* }
		* @endcode
		*/
		virtual bool showWindow( QDialog *dialog ) const = 0;

		/**
		* Anzeigen des QWidgets
		*
		* @return	war oder falsch (hängt vom übergebenen Parameter ab)
		*
		* @code
		* bool showWindow( QWidget *widget ) {
		*	widget->show();
		*	delete widget;
		* }
		* @endcode
		*/
		virtual bool showWindow( QWidget *widget ) const = 0;
};

Q_DECLARE_INTERFACE( First4PluginInterface, "first4.First4PluginInterface/1.4.x" )

#endif // __FIRST4_PLUGININTERFACE_H__
