\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{sope}
\LoadClass[a4paper]{book}
% Margins
\RequirePackage[top=35mm,bottom=35mm,left=25mm,right=25mm]{geometry}
% Some work
\def\title#1{\gdef\@title{#1}\gdef\@@title{#1}}
\def\author#1{\gdef\@author{#1}\gdef\@@author{#1}}
\let\@@title\@empty
\let\@@author\@empty
% Headers and footers
\RequirePackage{fancyhdr}
\pagestyle{fancy}
\fancyhf{}
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}
\fancyhead[RE, LO]{\textit{\leftmark}}
\fancyhead[LE, RO]{\thepage}
\fancyfoot[LE, RO]{\ifx\@@author\@empty\else\@@author\fi}



\RequirePackage{exam}
\RequirePackage{basiclistings}
% Tables with colored cells
\RequirePackage[table]{xcolor}%
% Encodings (to render letters with diacritics and special characters)
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}
% Math stuff
\RequirePackage[mathscr]{euscript}
\RequirePackage{amsmath,amssymb}
\RequirePackage{mathtools}
\RequirePackage[inline]{enumitem}
\RequirePackage[binary-units=true]{siunitx} %SI units

