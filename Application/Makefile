CC 	= g++
objs = obj/SimpleH264Analyzer.o obj/Stream.o obj/NALUnit.o \
	obj/Configuration.o obj/Utils.o obj/SeqParamSet.o obj/PicParamSet.o \
	obj/I_slice.o obj/SliceHeader.o obj/Macroblock.o
#deps = include/global.h
deps = 
target = bin/SimpleH264Analyzer

arg = ./bin/test.h264
log = ./trace.txt

$(target): $(objs)
	$(CC) -o bin/SimpleH264Analyzer $(objs)

obj/SimpleH264Analyzer.o: src/SimpleH264Analyzer.cpp $(deps)
	$(CC) -o obj/SimpleH264Analyzer.o -c $^ -I include	

obj/Stream.o: src/Stream.cpp $(deps)
	$(CC) -o obj/Stream.o -c $^ -I include

obj/NALUnit.o: src/NALUnit.cpp $(deps)
	$(CC) -o obj/NALUnit.o  -c $^ -I include

obj/Configuration.o: src/Configuration.cpp $(deps)
	$(CC) -o obj/Configuration.o -c $^ -I include

obj/Utils.o: src/Utils.cpp $(deps)
	$(CC) -o obj/Utils.o -c $^ -I include

obj/SeqParamSet.o: src/SeqParamSet.cpp $(deps)
	$(CC) -o obj/SeqParamSet.o -c $^ -I include

obj/PicParamSet.o: src/PicParamSet.cpp $(deps)
	$(CC) -o obj/PicParamSet.o -c $^ -I include

obj/I_slice.o: src/I_slice.cpp $(deps)
	$(CC) -o obj/I_slice.o -c $^ -I include
	
obj/SliceHeader.o: src/SliceHeader.cpp $(deps)
	$(CC) -o obj/SliceHeader.o -c $^ -I include

obj/Macroblock.o: src/Macroblock.cpp $(deps)
	$(CC) -o obj/Macroblock.o -c $^ -I include

run:
	./$(target) $(arg)

.PHONY:clean
clean:
	rm -rf $(objs) bin/SimpleH264Analyzer $(log)