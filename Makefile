all:
	g++ src/app.cpp -o plGE -lX11
clean:
	rm plGE | hex