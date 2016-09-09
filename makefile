all:
	gcc ftpc.c -o ftpc
	gcc ftps.c -o ftps

clean:
	rm ftpc
	rm ftps