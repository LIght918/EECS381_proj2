CC = g++
LD = g++

CFLAGS = -c -pedantic-errors -std=c++11 -Wall -g
LFLAGS = -pedantic -Wall -g

OBJS = p2_main.o Record.o Collection.o p2_globals.o String.o Utility.o
PROG = p2exe

SDEMO1 = sdemo1exe
SDEMO2 = sdemo2exe
SDEMO3 = sdemo3exe
SDEMO4 = sdemo4exe
OCdemo = ocdemoexe

default: $(PROG)
sdemo1: $(SDEMO1)
sdemo2: $(SDEMO2)
sdemo3: $(SDEMO3)
sdemo4: $(SDEMO4)
OCdemo: $(OCdemo)

comptest: 
		g++ -pedantic -Wall -g p2_main.o Record.o Collection.o p2_globals.o String.o Utility.o -o p2exeo

stest:  test.o String.o Utility.o
	$(LD) $(LFLAGS) -fno-elide-constructors test.o String.o Utility.o -o testexe

test: $(PROG)
	./p2exe <test_files/errors_in.txt >test_output/errors_out
	diff test_output/errors_out test_output/errors_out.txt
	./p2exe <test_files/typeahead_in.txt >test_output/typeahead_out
	diff test_output/typeahead_out test_output/typeahead_out.txt
	./p2exe <test_files/normal_in.txt >test_output/normal_out
	diff test_output/savefile1.txt  savefile1.txt
	diff test_output/normal_out test_output/normal_out.txt

$(SDEMO1): String_demo1.o String.o Utility.o
	$(LD) $(LFLAGS) String_demo1.o String.o Utility.o -o $(SDEMO1)
	./sdemo1exe >test_output/sdemo1.txt <test_files/sdemo1.in
	diff test_output/sdemo1.txt test_output/sdemo1.out

$(SDEMO2): String_demo2.o String.o Utility.o
	$(LD) $(LFLAGS) String_demo2.o String.o Utility.o -o $(SDEMO2)
	./sdemo2exe >test_output/sdemo2.txt <test_files/sdemo2.in
	diff test_output/sdemo2.txt test_output/sdemo2.out

$(SDEMO3): String_demo3.o String.o Utility.o
	$(LD) $(LFLAGS) -fno-elide-constructors String_demo3.o String.o Utility.o -o $(SDEMO3)
	./sdemo3exe >test_output/sdemo3.txt 
	diff test_output/sdemo3.txt test_output/sdemo3a.out

$(SDEMO4): String_demo4.o String.o Utility.o
	$(LD) $(LFLAGS) String_demo4.o String.o Utility.o -o $(SDEMO4)
	./sdemo4exe >test_output/sdemo4.txt 
	diff test_output/sdemo4.txt test_output/sdemo4.out

$(OCdemo): Ordered_list_demo.o Utility.o p2_globals.o Ordered_list.h
	$(LD) $(LFLAGS) Ordered_list_demo.o Utility.o p2_globals.o -o $(OCdemo)
	./$(OCdemo) >test_output/OCdemo.txt <test_files/OCdemo.in
	diff test_output/OCdemo.txt test_output/OCdemo.out

String_demo1.o: test_files/String_demo1.cpp String.h Utility.h
	$(CC) $(CFLAGS) test_files/String_demo1.cpp

String_demo2.o: test_files/String_demo2.cpp String.h Utility.h
	$(CC) $(CFLAGS) test_files/String_demo2.cpp

String_demo3.o: test_files/String_demo3.cpp String.h Utility.h
	$(CC) $(CFLAGS) test_files/String_demo3.cpp

String_demo4.o: test_files/String_demo4.cpp String.h Utility.h
	$(CC) $(CFLAGS) test_files/String_demo4.cpp

Ordered_list_demo.o: test_files/Ordered_list_demo.cpp String.h Utility.h Ordered_list.h
	$(CC) $(CFLAGS) test_files/Ordered_list_demo.cpp

$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

p2_main.o: p2_main.cpp Ordered_list.h p2_globals.h Record.h String.h Utility.h
	$(CC) $(CFLAGS) p2_main.cpp

Record.o: Record.cpp Record.h String.h Utility.h
	$(CC) $(CFLAGS) Record.cpp

Collection.o: Collection.cpp Collection.h Ordered_list.h p2_globals.h String.h Utility.h
	$(CC) $(CFLAGS) Collection.cpp

p2_globals.o: p2_globals.cpp p2_globals.h
	$(CC) $(CFLAGS) p2_globals.cpp

String.o: String.cpp String.h Utility.h
	$(CC) $(CFLAGS) String.cpp

Utility.o: Utility.cpp Utility.h String.h
	$(CC) $(CFLAGS) Utility.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe

