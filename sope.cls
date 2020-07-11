\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{sope}
\LoadClass[a4paper]{book}
% Margins
\RequirePackage[top=35mm,bottom=35mm,left=25mm,right=25mm]{geometry}
% Tables with colored cells
\RequirePackage[table]{xcolor}%
% Graphics and images
\RequirePackage{tikz}
\RequirePackage{tikz-qtree}
\usetikzlibrary{automata, positioning, arrows}
% Encodings (to render letters with diacritics and special characters)
\RequirePackage[utf8]{inputenc}
% Hyperreferences
\RequirePackage{hyperref}
% Source code
\RequirePackage{listings}
\renewcommand{\lstlistingname}{File}
\lstset{
    basicstyle=\ttfamily,
    frame=tb, % draw frame at top and bottom of the code
    tabsize=4, % tab space width
    numbers=left, % display line numbers on the left
    commentstyle=\color{green}, % comment color
    keywordstyle=\color{blue}, % keyword color
    stringstyle=\color{red} % string color
}
% Tables with bold rows
\RequirePackage{tabularx}
\newcommand\setrow[1]{\gdef\rowmac{#1}#1\ignorespaces}
\newcommand\clearrow{\global\let\rowmac\relax}
\clearrow
% Tables that can span across multiple pages
\RequirePackage{longtable}
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
% Definitions, theorems, remarks,...
\RequirePackage{amsthm}
\newtheorem{definition}{Definition}[section]
\newtheorem{theorem}{Theorem}[section]
\newtheorem{corollary}{Corollary}[theorem]
\newtheorem{lemma}[theorem]{Lemma}
\renewcommand\qedsymbol{$\blacksquare$}
\theoremstyle{remark}
\newtheorem*{remark}{Remark}
% Answer separator
\newcommand\ansseparator{\noindent\hfil\rule{0.5\textwidth}{.4pt}\hfil}
% Copyright page
\newenvironment{secondpage}{
    \clearpage\null\vfill
    \thispagestyle{empty}
    \begin{minipage}[b]{0.9\textwidth}
        \footnotesize\raggedright
        \setlength{\parskip}{0.5\baselineskip}
}{
    \end{minipage}
    \vspace*{2\baselineskip}
}
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
\setcounter{secnumdepth}{1}
\newcommand\exam[1]{\chapter{#1}}
\newcommand\exampart[1]{\section{#1}}
\newcommand\question[1]{\subsection{#1}}
\newcommand\questionitem[1]{\subsubsection{#1}}
