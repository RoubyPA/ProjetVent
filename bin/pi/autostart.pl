#! /usr/bin/perl
#
# File      autostart
# Brief     Projet vent
#           Perl 5
# Date      2016
# Author :  Rouby Pierre-Antoine
#
use strict ;
use warnings ;
use File::Copy qw/copy/ ;

my $hostRPI       = '/etc/hostname' ;
my $hostUSB       = '/home/pi/USB/data/hostname' ;
my $dataBaseRPI   = '/home/pi/ProjetVent/data/local.sqlite' ;
my $dataBaseUSB   = '/home/pi/USB/data/local.sqlite' ;

# Verification de l'existence du fichier
print ("$hostRPI don't exists !\n")       and exit(-1) if not -e $hostRPI ;
print ("$dataBaseRPI don't exists !\n")   and exit(-1) if not -e $dataBaseRPI ;

# Copie du fichier
copy( $hostRPI, $hostUSB )          or die "Copy failed: $!" ;
copy( $dataBaseRPI, $dataBaseUSB )  or die "Copy failed: $!" ;

print("Done !\n") ;

exit(0) ;
