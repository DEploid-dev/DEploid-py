demo.cpython-36m-x86_64-linux-gnu.so: dEploid-py.cpp
	python setup.py build_ext -i

dist: dEploid-py.cpp MANIFEST.in
	python setup.py build sdist

clean:
	rm -fR build *.so

