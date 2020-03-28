paralel:
	nvcc src/paralel_dijkstra.cu -o paralel_dijkstra
	./paralel_dijkstra

serial:
	g++ src/serial_dijkstra.cpp -o serial_dijkstra
	./serial_dijkstra