$ENV{'TEXINPUTS'}='..:' . $ENV{'TEXINPUTS'};
system("../get-commit-info.sh > COMMIT.tex");