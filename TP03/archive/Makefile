.PHONY: clean

md5:	coll_finder/libcoll.a md5.o main.o
	g++ coll_finder/*.o md5.o main.o -o md5

coll_finder/libcoll.a:
	cd coll_finder && $(MAKE)

clean:
	rm -f md5
	rm -f *.o
	cd coll_finder && $(MAKE) clean
