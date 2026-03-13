init-third-party:
	git submodule update --init --recursive

build-calculator:
	cmake -B build .
	cmake --build build

build-with-tests:
	cmake -B build -DBUILD_TESTS=ON
	cmake --build build
