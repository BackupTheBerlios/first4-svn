#!/usr/bin/perl  

#
# first4server Script
#
# Description: 
#
# This first4-Serverscript checks if there are some pending procedures (orders)
# or incomes who must completed until the actual date. If some entries will be
# found a message will be created.
#
# Version: 0.0.1
#

use strict;
use DBI;

############################################################
### Configuration ##########################################
############################################################

### Database settings

my @db = ('first4:first4pwd:localhost:first4dbTEST:3306','first4:first4pwd:localhost:first4dbPROD:3306');

### Log-Settings
my $logfile = "/var/log/first4server.log";

############################################################
### There is no need to change something after this line ###
############################################################


### Initializing
  open(STDOUT, ">> $logfile") or die "Failed to dup STDOUT: $!";
  open(STDERR, ">&STDOUT") or die "Failed to re-direct STDERR to '$logfile': $!";
  my $now_string = localtime;
  printf("\nStart check-process at '%s'.\n", $now_string);

### Create DB-connection

  my $tmpstr;
  foreach $tmpstr (@db)
  {
     my @dbstring = split(":", $tmpstr);
     my $database = @dbstring[3];
     my $hostname = @dbstring[2];
     my $port = @dbstring[4];
     my $user = @dbstring[0];
     my $password = @dbstring[1];

     my $dsn = "DBI:mysql:database=$database;host=$hostname;port=$port";
     my $dbh = DBI->connect($dsn, $user, $password);
     printf("Setting up DB connection for database '%s' on host '%s'.\n", $database, $hostname);

     ### set acutal date
     (my $day, my $month, my $year) = (localtime)[3,4,5];
     $year += 1900;
     my $date = $year."-".$month."-".$day;

     ### check procedures
     print "*Checking procedures";
     my $query_procedures = $dbh->prepare(sprintf("SELECT ID, status, completed, client, description, date, orderid, priority, contactperson, resp_person, complete_until FROM procedures WHERE `complete_until` < '%s';", $date));
     $query_procedures->execute();
     while (my $ref = $query_procedures->fetchrow_hashref()) {
  	my $query1 = $dbh->prepare(sprintf("SELECT * FROM messages WHERE `data2`='%s' AND `data3`='%s' AND `data4`='%s';", $ref->{'orderid'}, $ref->{'date'}, $ref->{'complete_until'}));
	if($query1->execute() == 0) {
     	   my $query2 = $dbh->prepare(sprintf("INSERT INTO `messages` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'ord', '', '%s', '', '%s', '%s', '%s', '%s', '');", $date, $ref->{'client'}, $ref->{'orderid'}, $ref->{'date'}, $ref->{'complete_until'}));
	   $query2->execute();
	}
        print ".";
      }
      $query_procedures->finish();
      print "finished.\n";

      ### check incomes and expenditures
      print "*Checking incomes and expenditures";
      my $query_incexp = $dbh->prepare(sprintf("SELECT state, ID, date, refnr, address, code, description, amount FROM incexp WHERE `type`='inc' AND `date` < '%s';", $date));
      $query_incexp->execute();
      while (my $ref = $query_incexp->fetchrow_hashref()) {
  	 my $query1 = $dbh->prepare(sprintf("SELECT * FROM messages WHERE `data2`='%s' AND `data3`='%s' AND `data4`='%s';", $ref->{'refnr'}, $ref->{'date'}, $ref->{'amount'}));
	 if($query1->execute() == 0) {
  	    my $query2 = $dbh->prepare(sprintf("INSERT INTO `messages` (`ID`, `typ`, `user`, `date`, `msgtext`, `data1`, `data2`, `data3`, `data4`, `data5`) VALUES (NULL, 'iem', '', '%s', '', '%s', '%s', '%s', '%s', '');", $date, $ref->{'address'}, $ref->{'refnr'}, $ref->{'date'}, $ref->{'amount'}));
	    $query2->execute();
	 }
	 print ".";
      }
      $query_procedures->finish();
      print "finished.\n";

      printf("Closing DB connection for database '%s' on host '%s'.\n", $database, $hostname);
  }
  $now_string = localtime;
  printf("Finished check-process at '%s'.\n", $now_string);
