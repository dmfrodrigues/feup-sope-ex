all:

test: tp01 tp02 tp03

tp%: FORCE
	make -C $@ test

FORCE:
