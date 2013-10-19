all:
	g++ main.cc -o main
run:
	./main 1000 > tmp
clean:
	rm main tmp
