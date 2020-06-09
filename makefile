all:

test: tp01 tp02 tp03 tp04

tp%: FORCE
	make -C $@ test

FORCE:
