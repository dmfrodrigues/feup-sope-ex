RM=rm -f
LATEX=latexmk -synctex=1 -interaction=nonstopmode --shell-escape -pdf -quiet -silent

all: exams/SOPE_exams.pdf

test: FORCE
	make -C tp test
	make -C exams test

FORCE:

%.pdf: %.tex
ifeq ($(VERSION),)
	cd $(<D) && $(LATEX) $(<F)
else
	cd $(<D) && (echo "$(VERSION)" > VERSION) && $(LATEX) $(<F) && $(RM) VERSION
endif

clean:
	git clean -dfX
