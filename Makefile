filename=main

all: 
	$(MAKE) -C test
	$(MAKE) -C tex

test:
	$(MAKE) -C test

pdf:
	$(MAKE) -C tex

clean:
	$(MAKE) clean -C tex 
	$(MAKE) clean -C test