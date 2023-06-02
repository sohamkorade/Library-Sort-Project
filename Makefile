all: gentests sort
	mkdir -p testcases
gentests: gentests.cpp
	g++ -o gentests gentests.cpp -Ofast
sort: sort.cpp
	g++ -o sort sort.cpp -Ofast
clean:
	rm -f gentests sort
	rm -rf testcases