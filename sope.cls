\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{sope}
\LoadClass[a4paper]{book}
% Margins
\RequirePackage[top=35mm,bottom=35mm,left=25mm,right=25mm]{geometry}
% Tables with colored cells
\RequirePackage[table]{xcolor}%
% Encodings (to render letters with diacritics and special characters)
\RequirePackage[utf8]{inputenc}
\RequirePackage[T1]{fontenc}

\RequirePackage{basiclistings}

% Tables with diagonal slashes
\RequirePackage{diagbox}
% Directory trees
\RequirePackage{dirtree}
% Math stuff
\RequirePackage[mathscr]{euscript}
\RequirePackage{amsmath,amssymb}
\RequirePackage{mathtools}
\RequirePackage[inline]{enumitem}
\RequirePackage[binary-units=true]{siunitx} %SI units

% Answer separator
\newcommand\ansseparator{\noindent\hfil\rule{0.5\textwidth}{.4pt}\hfil}

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
% Sections
\makeatletter
\renewcommand\thesection{\thechapter\ifnum\c@section>\z@ -P\arabic{section}\fi}
\renewcommand\thesubsection{\thesection-\arabic{subsection}}
\renewcommand\thesubsubsection{\thesubsection\alph{subsubsection}}
\makeatother

\makeatletter
\renewcommand{\l@chapter}{\bfseries\@dottedtocline{0}{0em}{2.5em}}
\renewcommand{\l@section}{\normalfont\@dottedtocline{1}{1em}{3.7em}}
\renewcommand{\l@subsection}{\normalfont\@dottedtocline{2}{2em}{4.5em}}
\renewcommand{\l@subsubsection}{\normalfont\@dottedtocline{3}{3em}{4.5em}}
\makeatother

\RequirePackage{titlesec}
\newcommand{\sectionbreak}{\clearpage}
\titleformat{\chapter}[display]
  {\normalfont\bfseries}{}{0pt}{\Huge}

% Alias
\setcounter{secnumdepth}{-2}
\newcommand\exam[1]{\chapter{#1}}
\newcommand\exampart[1]{\section{#1}}
\newcommand\question[1]{\subsection{#1}}
\newcommand\questionitem[1]{\subsubsection{#1}}
