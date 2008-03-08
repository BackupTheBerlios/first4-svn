%define name first4
%define version 1.3.93
%define release 1

Summary: first4 QT-Based ERP Solution
Name: first4
Version: 1.3.93
Release: 1
Source: %{name}-%{version}.tar.gz
Vendor: procopio.ch
URL: http://www.procopio.ch/
License: GPL
Group: Productivity/Office
Prefix: %{_prefix}
BuildRequires: libqt4-sql 
BuildRoot	: %{_tmppath}/%{name}-%{version}-%{release}-builtroot


%description
first4 is a QT4-based free ERP-Solution using MySQL.

%prep
%setup -q

%build
qmake
make

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p %{buildroot}/opt/first4/bin
mkdir -p %{buildroot}/opt/first4/translations
cp bin/first4 %{buildroot}/opt/first4/bin/first4
cp resources/images/logo.png %{buildroot}/opt/first4/bin/logo.png
cp resources/translations/*.qm %{buildroot}/opt/first4/translations/

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/opt/first4/bin/first4
/opt/first4/bin/logo.png
/opt/first4/translations/*.qm

%changelog
* Fri Mar 7 2008 Orlando Procopio <orlando@procopio.ch>
- First draft of the spec file
