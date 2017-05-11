#!/usr/bin/perl

# This perl script generates reverse mapping of TrueType fonts
# used to handle ETO_GLYPH_INDEX flag in text rendering
# It's meant to be lauched with a .ttf file as argument.
# Reverse mapping will add the reverse mapping directly inside
# the "inc/font_mapping.h" header.
#
# libfont-ttf-perl (Debian/Ubunutu package)

use strict;
use Font::TTF::Font;
use File::Basename;
use File::Temp qw/ tempfile tempdir /;
use File::Copy;

# Recover the mapping header file
my $map_header = dirname($0) . '/../inc/font_mapping.h';

# Open and parse the TTF font to recover cmap tables
# and other information
my $f = Font::TTF::Font->open($ARGV[0]);
my $c = $f->{'cmap'}->read->find_ms;
my $p = $f->{'post'}->read;
my @rev = $f->{'cmap'}->reverse;
my $num = $f->{'maxp'}->read->{'numGlyphs'};
my $name = $f->{'name'}->read->find_name(4);

# Open the header file
open my $header, $map_header or die "Could not open $map_header: $!";

# Create some temporary file
my $tmp = new File::Temp( UNLINK => 0 );

my $table_var_name = $name;
$table_var_name =~ s/[^\w]/_/g;
$table_var_name = 'emf2svg_fm_' . lc($table_var_name);

# Read the header file line by line, and rewrite those line in the temporary file
while(my $line = <$header>) {
    # if we hit this marker, we add the new reverse mapping structure
    # corresponding to the font we just used
    if( $line eq "// Mappings Collection END\n"){
        print $tmp "{\"$name\", $num, $table_var_name},\n";
    }
    if( $line eq "// Mappings Table END\n"){
	print $tmp "\nuint32_t ${table_var_name}\[\] = {\n";
        for (my $i = 0; $i < $num; $i++)
        {
            my ($pname) = $p->{'VAL'}[$i];
            my ($uid) = $rev[$i];
            if ($uid) {
                printf $tmp ("0x%04X,", $uid);
            } else {
                printf $tmp ("0x%04X,", 0);
            }
            if ($i % 10 == 9){
                printf $tmp ("\n");
            } else {
                printf $tmp (" ");
            }
        }
        print $tmp "};\n"
    }
    print $tmp "$line";
}

close $header;
close $tmp;

# Replace the old header file with the new one
move($tmp->filename, $map_header);
exit 0;
