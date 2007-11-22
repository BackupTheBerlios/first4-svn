CREATE TABLE `accounttab` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `accountnr` text NOT NULL,
  `bank` text NOT NULL,
  `blz` text NOT NULL,
  `currency` text NOT NULL,
  `users` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `adrtabs` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `users` text NOT NULL,
  `idcounter` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `datatabs` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `users` text NOT NULL,
  `cols` text NOT NULL,
  `tabtyp` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `docdrafts` (
  `ID` int(11) NOT NULL auto_increment,
  `doctyp` text NOT NULL,
  `date` text NOT NULL,
  `client` text NOT NULL,
  `comments` text NOT NULL,
  `amount` text NOT NULL,
  `discount` text NOT NULL,
  `docID` text NOT NULL,
  `salutation` text NOT NULL,
  `introduction` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `docpositions` (
  `ID` int(11) NOT NULL auto_increment,
  `DOCID` text NOT NULL,
  `STOCK` text NOT NULL,
  `STOCK_ID` text NOT NULL,
  `DOC_POSITION` int(11) NOT NULL default '0',
  `LABEL` text NOT NULL,
  `DESCRIPTION` text NOT NULL,
  `QUANTITY` float NOT NULL default '0',
  `UNIT` text NOT NULL,
  `PRICE` float NOT NULL default '0',
  `VAT` float NOT NULL default '0',
  `TYPE` char(10) default NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `docs` (
  `ID` int(11) NOT NULL auto_increment,
  `doctyp` text NOT NULL,
  `date` text NOT NULL,
  `client` text NOT NULL,
  `comments` text NOT NULL,
  `amount` text NOT NULL,
  `discount` text NOT NULL,
  `docID` text NOT NULL,
  `salutation` text NOT NULL,
  `introduction` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


CREATE TABLE `doctab` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `filename` text NOT NULL,
  `count` text NOT NULL,
  `users` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `doctab` WRITE;
INSERT INTO `doctab` VALUES (1,'1 offer','','0001',''),(2,'2 orderconf','','0001',''),(3,'3 deliverynote','/','0001',''),(4,'4 bill','','0002','');
UNLOCK TABLES;

CREATE TABLE `invcfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `USERS` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `invcfgtab` WRITE;
INSERT INTO `invcfgtab` VALUES (1,'');
UNLOCK TABLES;

CREATE TABLE `invtab` (
  `ID` int(11) NOT NULL auto_increment,
  `NAME` text NOT NULL,
  `DATATABLE` text NOT NULL,
  `TABLENAME` text NOT NULL,
  `DATE` text NOT NULL,
  `USERS` text NOT NULL,
  `FINISHED` text NOT NULL,
  `COMMENTS` text,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `maincfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `var` text NOT NULL,
  `value` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `maincfgtab` WRITE;
INSERT INTO `maincfgtab` VALUES (1,'docfolder',''),(2,'templatefolder',''),(3,'dbversion','1.4.0-20070412'),(4,'company',''),(5,'companyaddress',''),(6,'bankname',''),(7,'bankaddress',''),(8,'bankblz',''),(9,'bankaccountnr',''),(10,'banktnr',''),(11,'docpref',''),(12,'DoG','');
UNLOCK TABLES;

CREATE TABLE `msgcfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `users` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `msgcfgtab` WRITE;
INSERT INTO `msgcfgtab` VALUES (1,'gen','1 general',''),(2,'sto','2 stock',''),(3,'ord','3 order',''),(4,'iem','4 incexp','');
UNLOCK TABLES;

CREATE TABLE `orderscfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `USERS` text NOT NULL,
  `COUNTER` int(11) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `orderscfgtab` WRITE;
INSERT INTO `orderscfgtab` VALUES (1,'',5000);
UNLOCK TABLES;

CREATE TABLE `orderstab` (
  `ID` int(11) NOT NULL auto_increment,
  `STATUS` int(11) NOT NULL default '0',
  `ORDERED_BY` text NOT NULL,
  `FOR_ORDER` int(11) NOT NULL default '0',
  `STOCK` text NOT NULL,
  `DATE1` date NOT NULL default '0000-00-00',
  `DATE2` date NOT NULL default '0000-00-00',
  `DATE3` date NOT NULL default '0000-00-00',
  `DEF` text NOT NULL,
  `DESCRIPTION` text NOT NULL,
  `QUANTITY` int(11) NOT NULL default '0',
  `SUPPLIER` text NOT NULL,
  `PRICE` text NOT NULL,
  `COMMENTS` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `procedurearchiv` (
  `ID` int(11) NOT NULL auto_increment,
  `status` text NOT NULL,
  `completed` text NOT NULL,
  `priority` text NOT NULL,
  `date` date NOT NULL default '0000-00-00',
  `client` text NOT NULL,
  `contactperson` text NOT NULL,
  `orderid` text NOT NULL,
  `description` text NOT NULL,
  `resp_person` text NOT NULL,
  `complete_until` date NOT NULL default '0000-00-00',
  `tasks` text NOT NULL,
  `orders` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `procedurecfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `users` text NOT NULL,
  `auftrid` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

LOCK TABLES `procedurecfgtab` WRITE;
INSERT INTO `procedurecfgtab` VALUES (1,'','0');
UNLOCK TABLES;

CREATE TABLE `procedureorders` (
  `ID` int(11) NOT NULL auto_increment,
  `PROC_ID` text NOT NULL,
  `STOCK` text NOT NULL,
  `STOCK_ID` text NOT NULL,
  `STATE` char(1) NOT NULL default '0',
  `LABEL` text NOT NULL,
  `DESCRIPTION` text NOT NULL,
  `QUANTITY` float NOT NULL default '0',
  `UNIT` text NOT NULL,
  `PRICE` float NOT NULL default '0',
  `VAT` float NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `proceduretab` (
  `ID` int(11) NOT NULL auto_increment,
  `status` text NOT NULL,
  `completed` text NOT NULL,
  `priority` text NOT NULL,
  `date` date NOT NULL default '0000-00-00',
  `client` text NOT NULL,
  `contactperson` text NOT NULL,
  `orderid` text NOT NULL,
  `description` text NOT NULL,
  `resp_person` text NOT NULL,
  `complete_until` date NOT NULL default '0000-00-00',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `proceduretasks` (
  `ID` int(11) NOT NULL auto_increment,
  `PROC_ID` text,
  `STATE` int(11) default NULL,
  `TASK` text,
  `DATE` text,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

CREATE TABLE `userstab` (
  `ID` int(11) NOT NULL auto_increment,
  `username` text character set latin1 NOT NULL,
  `userpass` text character set latin1 NOT NULL,
  `fullname` text character set latin1 NOT NULL,
  `firstname` text character set latin1 NOT NULL,
  `lastname` text character set latin1 NOT NULL,
  `dob` date NOT NULL default '0000-00-00',
  `p_street` text character set latin1 NOT NULL,
  `p_zip` text character set latin1 NOT NULL,
  `p_location` text character set latin1 NOT NULL,
  `p_country` text character set latin1 NOT NULL,
  `b_street` text character set latin1 NOT NULL,
  `b_zip` text character set latin1 NOT NULL,
  `b_location` text character set latin1 NOT NULL,
  `b_country` text character set latin1 NOT NULL,
  `profession` text character set latin1 NOT NULL,
  `org_unit` text character set latin1 NOT NULL,
  `position` text character set latin1 NOT NULL,
  `emp_type` text character set latin1 NOT NULL,
  `p_tel` text character set latin1 NOT NULL,
  `p_fax` text character set latin1 NOT NULL,
  `p_mobile` text character set latin1 NOT NULL,
  `p_pager` text character set latin1 NOT NULL,
  `p_ip` text character set latin1 NOT NULL,
  `email1` text character set latin1 NOT NULL,
  `email2` text character set latin1 NOT NULL,
  `email3` text character set latin1 NOT NULL,
  `p_web` text character set latin1 NOT NULL,
  `b_tel` text character set latin1 NOT NULL,
  `b_teldir` text character set latin1 NOT NULL,
  `b_fax` text character set latin1 NOT NULL,
  `b_mobile` text character set latin1 NOT NULL,
  `b_pager` text character set latin1 NOT NULL,
  `b_ip` text character set latin1 NOT NULL,
  `email4` text character set latin1 NOT NULL,
  `email5` text character set latin1 NOT NULL,
  `email6` text character set latin1 NOT NULL,
  `notes` text character set latin1 NOT NULL,
  `emp_grade` text character set latin1 NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

LOCK TABLES `userstab` WRITE;
INSERT INTO `userstab` VALUES (11,'Administrator','','Administrator','','','0000-00-00','','','','0','','','','','','','','','','','','','','','','','','','','','','','','','','','','');
UNLOCK TABLES;

CREATE TABLE `vattab` (
  `ID` int(11) NOT NULL auto_increment,
  `col1` text NOT NULL,
  `col2` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;