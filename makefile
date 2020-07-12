RM=rm -f
LATEX=latexmk -synctex=1 -interaction=nonstopmode --shell-escape -pdf

all: exams/SOPE_exams.pdf

test: tp01 tp02 tp03 tp04 tp05 tp06 tp07 exams

tp%: FORCE
	make -C $@ test

exams: FORCE
	make -C $@ test

FORCE:

%.pdf: %.tex
ifeq ($(VERSION),)
	cd $(<D) && $(LATEX) $(<F)
else
	cd $(<D) && (echo "$(VERSION)" > VERSION) && $(LATEX) $(<F) && $(RM) VERSION
endif

clean:
	git clean -dfX
