target: mkfifo fifoReader fifoWriter simplepipe pipewithprocesses twowaypipe 

mkfifo: mkfifo.o
	gcc mkfifo.o -o mkfifo
fifoReader: fifoReader.o
	gcc fifoReader.o -o fifoReader
fifoWriter: fifoWriter.o
	gcc fifoWriter.o -o fifoWriter
pipewithprocesses: pipewithprocesses.o
	gcc pipewithprocesses.o -o pipewithprocesses
twowaypipe: twowaypipe.o
	gcc twowaypipe.o -o twowaypipe
simplepipe: simplepipe.o
	gcc simplepipe.o -o simplepipe
mkfifo.o: mkfifo.c
	gcc -c mkfifo.c
fifoReader.o: fifoReader.c
	gcc -c fifoReader.c
fifoWriter.o: fifoWriter.c
	gcc -c fifoWriter.c
simplepipe.o: simplepipe.c
	gcc -c simplepipe.c
twowaypipe.o: twowaypipe.c
	gcc -c twowaypipe.c
pipewithprocesses.o: pipewithprocesses.c
	gcc -c pipewithprocesses.c
clean:
	rm *.o mkfifo fifoReader fifoWriter simplepipe twowaypipe pipewithprocesses tejas sum