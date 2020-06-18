LATEX=latexmk -synctex=1 -interaction=nonstopmode -pdf

all: exams/SOPE_exams.pdf

test: tp01 tp02 tp03 tp04 tp05 tp06 tp07 exams

tp%: FORCE
	make -C $@ test

exams: FORCE
	make -C $@ test

FORCE:

%.pdf: %.tex
	cd $(<D) && $(LATEX) $(<F)

clean:
	git clean -dfX
