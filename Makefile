
run:
	g++ src/main.cpp -o target/main
	cd target && ./main --scene ../sample/basic.scene_definition
