src = $(wildcard ./*.c)

bin = binaryfile
all: $(bin)

$(bin): $(src)
	gcc $(src) -o $(bin)
clean:
	rm -rf $(bin)
rebuild:clean $(bin)