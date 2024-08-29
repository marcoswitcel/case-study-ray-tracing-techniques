
build:
	g++ -std=c++17 src/main.cpp -o target/main

run: build
	cd target && ./main --scene ../sample/basic_luminosity_specular.scene_definition basic_luminosity_specular.ppm
