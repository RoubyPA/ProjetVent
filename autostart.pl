#! /usr/bin/perl
#
# \file    autostart
# \brief   Projet vent
#          Perl 5
# \date    2016
# \author  Rouby Pierre-Antoine
#
use strict ;
use warnings ;
use File::Copy qw/copy/ ;

my $hostRPI       = '/etc/hostname' ;
my $hostUSB       = '/home/iris/USB/data/hostname' ;
my $dataBaseRPI   = '/home/iris/ProjetVent/local.sqlite' ;
my $dataBaseUSB   = '/home/iris/USB/data/local.sqlite' ;

# Verification de l'existence du fichier
print ("$hostRPI don't exists !\n")       and exit(-1) if not -e $hostRPI ;
print ("$dataBaseRPI don't exists !\n")   and exit(-1) if not -e $dataBaseRPI ;

# Copie du fichier
copy( $hostRPI, $hostUSB )          or die "Copy failed: $!" ;
copy( $dataBaseRPI, $dataBaseUSB )  or die "Copy failed: $!" ;

print("Done !\n") ;

exit(0) ;
