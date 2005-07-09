#!/usr/bin/perl -w

use File::Basename;

# Hack to find out kalyptusdir
my $here = `pwd`; chomp $here;
my $kdomdir = substr($here, 0, index($here, "kdom")); 
my $kalyptusdir = $kdomdir . "/../kdebindings/kalyptus";
$kdomdir .= "kdom";

my $outdir = $kdomdir . "/generate.pl.tmpdir";
my $finaloutdir = $kdomdir;

my $finalname = "data/generateddata.cc";
my $finalInterfacename = "ecma/EcmaInterface.h";

## Note: outdir and finaloutdir should NOT be the same dir!

if (! -d $outdir) { mkdir $outdir; }


# Need to cd to kalyptus's directory so that perl finds Ast.pm etc.
chdir "$kalyptusdir" or die "Couldn't go to $kalyptusdir (edit script to change dir)\n";

# Find out which header files we need to parse
my %excludes = ( );
my %excludeDirs = ( "svg" => 0, "parser" => 0, "data" => 0,
                    "ecma" => 0, "scripts" => 0, "test" => 0, "backends" => 0,
					"catalog" => 0, "xinclude" => 0, "kxmllint" => 0, "xpointer" => 0 );

# List headers, and exclude the ones listed above
my @headers = ();
my $incdir=$here."/";
opendir (INCS, $incdir) or die "Couldn't find $incdir";

# Maximum 3-dirs recursive like kdom/events/impl/
my @content = grep !/^\.\.?$/, readdir INCS;
foreach $filename (@content) {
	$entry = $incdir . $filename;

	if (-d $entry && !defined $excludeDirs{$filename}) { 
		opendir (INCS2, $entry) or die "Couldn't find $incdir";
		my @content2 = grep !/^\.\.?$/, readdir INCS2;

		foreach $filename2 (@content2) {
		    $entry = $incdir . $filename . "/" . $filename2;	

			if (-d $entry && !defined $excludeDirs{$filename2}) { 
				opendir (INCS3, $entry) or die "Couldn't find $incdir";
				my @content3 = grep !/^\.\.?$/, readdir INCS3;

				foreach $filename3 (@content3) {
		    		$entry = $incdir . $filename . "/" . $filename2 . "/" . $filename3;	
			        push(@headers, $entry)
    			      if ( !defined $excludes{$filename3} # Not excluded
				      && $filename3 =~ /\.h$/ ); # Not a backup file etc. Only headers.
				}
				closedir INCS3;
			}
		
	        push(@headers, $entry)
    	      if ( !defined $excludes{$filename2} # Not excluded
		      && $filename2 =~ /\.h$/ ); # Not a backup file etc. Only headers.
		}
		closedir INCS2;
	}

    if ( ( -e $entry or -l $entry )         # A real file or a symlink
        && ( ! -d _ ) )                     # Not a symlink to a dir though
    {
        push(@headers, $entry)
          if ( !defined $excludes{$filename} # Not excluded
	      && $filename =~ /\.h$/ ); # Not a backup file etc. Only headers.
    }
}
closedir INCS;

# Launch kalyptus
system "perl -I$kdomdir/scripts kalyptus -fKDOMECMA --name=kdom --outputdir=$outdir @headers";
my $exit = $? >> 8;
exit $exit if ($exit);

system "cp -f $outdir/generateddata.cc $finaloutdir/$finalname";
system "cp -f $outdir/EcmaInterface.h $finaloutdir/$finalInterfacename";

# Delete outdir
system "rm -rf $outdir";
