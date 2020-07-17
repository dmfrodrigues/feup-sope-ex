all:

test:
	find . -name "*.sh" -exec chmod u+x {} \;
	./p01.sh
	./p02.sh
	./p03.sh
	./p04.sh
	cd p05/ab/a && ./p05_a_compile.sh
	cd p05/ab/b && ./p05_b_compile.sh
	cd p05/c    && ./p05_c_compile.sh
	./p08.sh