all:LSH_var LSH MinHash_Similarity Jsim 

LSH: characteristic_matrix.o minhash_signature.o LSH.cpp
	g++ -std=c++11 -O3 -o  LSH LSH.cpp  minhash_signature.o characteristic_matrix.o

LSH_var: characteristic_matrix.o minhash_signature.o LSH_var.cpp
	g++ -std=c++11 -O3 -o  LSH_var LSH_var.cpp  minhash_signature.o characteristic_matrix.o

MinHash_Similarity: characteristic_matrix.o minhash_signature.o minHash_Similarity.cpp
	g++ -std=c++11 -O3 -o  MinHash_Similarity minHash_Similarity.cpp  minhash_signature.o characteristic_matrix.o

Jsim: characteristic_matrix.o Jsim.cpp
	g++ -std=c++11 -O3 -o Jsim Jsim.cpp  characteristic_matrix.o

minhash_signature.o: minhash_signature.cpp
		g++ -std=c++11 -c minhash_signature.cpp

characteristic_matrix.o: characteristic_matrix.cpp
	g++ -std=c++11 -c characteristic_matrix.cpp

clean:
	rm *.o
	rm *.exe
