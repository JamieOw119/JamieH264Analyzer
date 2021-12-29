CC 	= g++
objs = obj/SimpleH264Analyzer.o obj/stream.o obj/NALUnit.o
arg = ./bin/test.h264

bin/SimpleH264Analyzer: ${objs}
	$(CC) -o bin/SimpleH264Analyzer $(objs)

obj/SimpleH264Analyzer.o: src/SimpleH264Analyzer.cpp include/stream.h
	$(CC) -o obj/SimpleH264Analyzer.o -c src/SimpleH264Analyzer.cpp -I include

obj/stream.o: src/stream.cpp include/stream.h
	$(CC) -o obj/stream.o -c src/stream.cpp -I include

obj/NALUnit.o: src/NALUnit.cpp include/NALUnit.h
	$(CC) -o obj/NALUnit.o -c src/NALUnit.cpp -I include

run:
	./bin/SimpleH264Analyzer $(arg)

clean:
	rm -rf $(objs) bin/SimpleH264Analyzer