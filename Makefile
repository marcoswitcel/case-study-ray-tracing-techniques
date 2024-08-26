
run:
	g++ src/main.cpp -o target/main
	cd target && ./main --scene ../sample/basic_luminosity.scene_definition basic_luminosity.ppm
