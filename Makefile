demo.cpython-36m-x86_64-linux-gnu.so: dEploid-py.cpp
	python3 setup.py build_ext -i


clean:
	rm -fR build *.so

