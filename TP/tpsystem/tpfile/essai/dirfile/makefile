COMPILER = g++ -c -I../include/

$(nom).run: $(nom).o file2.o
	g++ -s -o $(nom).run $(nom).o -L. -lSys
$(nom).o: $(nom).cxx
	$(COMPILER) $(nom).cxx
libSys.a: file2.cxx ../include/
	$(COMPILER) file2.cxx; ar -cqs libSys.a file2.o; rm file2.o
clean:
	rm *.o $(nom).run
