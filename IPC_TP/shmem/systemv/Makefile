target: main_producer main_consumer

main_producer: main_producer.o helper.o
	gcc main_producer.o helper.o -o main_producer

main_consumer: main_consumer.o helper.o
	gcc main_consumer.o helper.o -o main_consumer

main_producer.o: main_producer.c
	gcc -c main_producer.c

main_consumer.o : main_consumer.c
	gcc -c main_consumer.c

helper.o: helper.c
	gcc -c helper.c

clean:
	rm *.o main_consumer main_producer