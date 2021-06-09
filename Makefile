all:
	@make --ignore-errors clean
	@make --ignore-errors install
	@make build
clean:
	@rm plGE
	@rm deb/*.deb
install:
	@sudo apt install libx11-dev
build:
	@g++ src/app.cpp -o plGE -lX11 -pthread
build-discord-rpc:
	@cd src/load-discord-rpc/
	@make
run:
	@make all
	@./plGE
deb-pkg:
	@make --ignore-errors clean
	@g++ src/app.cpp -o deb/plGE_1.0-1_amd64/usr/bin/plGE -lX11 -pthread
	@pkg src/load-discord-rpc -t latest-linux-x64 -o deb/plGE_1.0-1_amd64/usr/bin/plGEldrpc
	@dpkg-deb --build --root-owner-group deb/plGE_1.0-1_amd64/