
make build

cd target
for file in $(ls ../sample)
do 
  ./main --scene "../sample/$file" "$file.ppm"
done
