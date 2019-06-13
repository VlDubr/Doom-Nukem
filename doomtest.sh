for ((i = 1; i < 100; i++))
do
	./doom &
	sleep 2
	pkill doom
done