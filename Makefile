all:
	make --ignore-errors clean
	make --ignore-errors install
	make build
clean:
	rm plGE
install:
	sudo apt install libx11-dev
build:
	g++ src/app.cpp -o plGE -lX11
run:
	make all
	./plGE
