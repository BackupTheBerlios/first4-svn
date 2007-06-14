-- MySQL dump 10.10
--
-- Host: localhost    Database: first4
-- ------------------------------------------------------
-- Server version	5.0.24a-Debian_9ubuntu0.1-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `accounttab`
--

DROP TABLE IF EXISTS `accounttab`;
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

--
-- Dumping data for table `accounttab`
--


/*!40000 ALTER TABLE `accounttab` DISABLE KEYS */;
LOCK TABLES `accounttab` WRITE;
INSERT INTO `accounttab` VALUES (1,'ietab','Incomes / Expenditures','','','','','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `accounttab` ENABLE KEYS */;

--
-- Table structure for table `adrtabs`
--

DROP TABLE IF EXISTS `adrtabs`;
CREATE TABLE `adrtabs` (
  `ID` int(10) unsigned NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `users` text NOT NULL,
  `idcounter` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Table structure for table `datatabs`
--

DROP TABLE IF EXISTS `datatabs`;
CREATE TABLE `datatabs` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `users` text NOT NULL,
  `cols` text NOT NULL,
  `tabtyp` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `datatabs`
--


/*!40000 ALTER TABLE `datatabs` DISABLE KEYS */;
LOCK TABLES `datatabs` WRITE;
INSERT INTO `datatabs` VALUES (1,'vattab','MwSt.-Werte','','Tax:70#Comments:200','vattab');
UNLOCK TABLES;
/*!40000 ALTER TABLE `datatabs` ENABLE KEYS */;

--
-- Table structure for table `docdrafts`
--

DROP TABLE IF EXISTS `docdrafts`;
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

--
-- Table structure for table `docpositions`
--

DROP TABLE IF EXISTS `docpositions`;
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

--
-- Table structure for table `docs`
--

DROP TABLE IF EXISTS `docs`;
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

--
-- Table structure for table `doctab`
--

DROP TABLE IF EXISTS `doctab`;
CREATE TABLE `doctab` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `filename` text NOT NULL,
  `count` text NOT NULL,
  `users` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `doctab`
--


/*!40000 ALTER TABLE `doctab` DISABLE KEYS */;
LOCK TABLES `doctab` WRITE;
INSERT INTO `doctab` VALUES (1,'1 offer','','0001',''),(2,'2 orderconf','','0001',''),(3,'3 deliverynote','/','0001',''),(4,'4 bill','','0002','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `doctab` ENABLE KEYS */;

--
-- Table structure for table `invcfgtab`
--

DROP TABLE IF EXISTS `invcfgtab`;
CREATE TABLE `invcfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `USERS` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `invcfgtab`
--


/*!40000 ALTER TABLE `invcfgtab` DISABLE KEYS */;
LOCK TABLES `invcfgtab` WRITE;
INSERT INTO `invcfgtab` VALUES (1,'');
UNLOCK TABLES;
/*!40000 ALTER TABLE `invcfgtab` ENABLE KEYS */;

--
-- Table structure for table `invtab`
--

DROP TABLE IF EXISTS `invtab`;
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

--
-- Table structure for table `maincfgtab`
--

DROP TABLE IF EXISTS `maincfgtab`;
CREATE TABLE `maincfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `var` text NOT NULL,
  `value` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `maincfgtab`
--


/*!40000 ALTER TABLE `maincfgtab` DISABLE KEYS */;
LOCK TABLES `maincfgtab` WRITE;
INSERT INTO `maincfgtab` VALUES (1,'docfolder',''),(2,'templatefolder',''),(3,'dbversion','1.4.0-20070412'),(4,'company',''),(5,'companyaddress',''),(6,'bankname',''),(7,'bankaddress',''),(8,'bankblz',''),(9,'bankaccountnr',''),(10,'banktnr',''),(11,'docpref',''),(12,'DoG','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `maincfgtab` ENABLE KEYS */;

--
-- Table structure for table `msgcfgtab`
--

DROP TABLE IF EXISTS `msgcfgtab`;
CREATE TABLE `msgcfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `name` text NOT NULL,
  `description` text NOT NULL,
  `users` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `msgcfgtab`
--


/*!40000 ALTER TABLE `msgcfgtab` DISABLE KEYS */;
LOCK TABLES `msgcfgtab` WRITE;
INSERT INTO `msgcfgtab` VALUES (1,'gen','1 general',''),(2,'sto','2 stock',''),(3,'ord','3 order',''),(4,'iem','4 incexp','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `msgcfgtab` ENABLE KEYS */;

--
-- Table structure for table `orderscfgtab`
--

DROP TABLE IF EXISTS `orderscfgtab`;
CREATE TABLE `orderscfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `USERS` text NOT NULL,
  `COUNTER` int(11) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `orderscfgtab`
--


/*!40000 ALTER TABLE `orderscfgtab` DISABLE KEYS */;
LOCK TABLES `orderscfgtab` WRITE;
INSERT INTO `orderscfgtab` VALUES (1,'',5020);
UNLOCK TABLES;
/*!40000 ALTER TABLE `orderscfgtab` ENABLE KEYS */;

--
-- Table structure for table `orderstab`
--

DROP TABLE IF EXISTS `orderstab`;
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

--
-- Table structure for table `procedurearchiv`
--

DROP TABLE IF EXISTS `procedurearchiv`;
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

--
-- Table structure for table `procedurecfgtab`
--

DROP TABLE IF EXISTS `procedurecfgtab`;
CREATE TABLE `procedurecfgtab` (
  `ID` int(11) NOT NULL auto_increment,
  `users` text NOT NULL,
  `auftrid` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `procedurecfgtab`
--


/*!40000 ALTER TABLE `procedurecfgtab` DISABLE KEYS */;
LOCK TABLES `procedurecfgtab` WRITE;
INSERT INTO `procedurecfgtab` VALUES (1,'','0');
UNLOCK TABLES;
/*!40000 ALTER TABLE `procedurecfgtab` ENABLE KEYS */;

--
-- Table structure for table `procedureorders`
--

DROP TABLE IF EXISTS `procedureorders`;
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

--
-- Table structure for table `proceduretab`
--

DROP TABLE IF EXISTS `proceduretab`;
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

--
-- Table structure for table `proceduretasks`
--

DROP TABLE IF EXISTS `proceduretasks`;
CREATE TABLE `proceduretasks` (
  `ID` int(11) NOT NULL auto_increment,
  `PROC_ID` text,
  `STATE` int(11) default NULL,
  `TASK` text,
  `DATE` text,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Table structure for table `userstab`
--

DROP TABLE IF EXISTS `userstab`;
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

--
-- Dumping data for table `userstab`
--


/*!40000 ALTER TABLE `userstab` DISABLE KEYS */;
LOCK TABLES `userstab` WRITE;
INSERT INTO `userstab` VALUES (11,'Administrator','','Administrator','','','0000-00-00','','','','0','','','','','','','','','','','','','','','','','','','','','','','','','','','','');
UNLOCK TABLES;
/*!40000 ALTER TABLE `userstab` ENABLE KEYS */;

--
-- Table structure for table `vattab`
--

DROP TABLE IF EXISTS `vattab`;
CREATE TABLE `vattab` (
  `ID` int(11) NOT NULL auto_increment,
  `col1` text NOT NULL,
  `col2` text NOT NULL,
  PRIMARY KEY  (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vattab`
--


/*!40000 ALTER TABLE `vattab` DISABLE KEYS */;
LOCK TABLES `vattab` WRITE;
INSERT INTO `vattab` VALUES (1,'7.6','Normaler MwSt.-Satz'),(2,'2.4','Reduzierter MwSt.-Satz'),(3,'0.0','Keine MwSt.');
UNLOCK TABLES;
/*!40000 ALTER TABLE `vattab` ENABLE KEYS */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

