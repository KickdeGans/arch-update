make:
	gcc -o arch-update src/main.c

install:
	sudo cp arch-update /bin/arch-update