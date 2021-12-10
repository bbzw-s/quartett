
.PHONY : setup
setup: clean
	mkdir build
	cd build &&\
	cmake ..

.PHONY : build
build:
	cd build &&\
	cmake --build .

.PHONY : run
run: build
	./build/quartett


.PHONY : clean
clean:
	rm -rf ./build
