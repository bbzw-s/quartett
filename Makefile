
.PHONY : build
build:
	mkdir build
	cd build &&\
	cmake ..&&\
	cmake --build .

.PHONY : run
run:
	./build/quartett


.PHONY : clean
clean:
	rm -rf ./build
