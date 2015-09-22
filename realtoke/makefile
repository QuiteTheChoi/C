All: tokenizer.c
	gcc -o tokenizer tokenizer.c

debug:
	gcc -g -o tokenizer tokenizer.c
	gdb ./tokenizer	
run:
	./tokenizer ""	
	./tokenizer " "	
	./tokenizer "  "	
	./tokenizer "0"	
	./tokenizer " 0   "	
	./tokenizer ".01"
	./tokenizer "."
	./tokenizer "(.]"
	./tokenizer "hello world"
	./tokenizer "(hello world);"
	./tokenizer " 0 0 0 0001 0x2213"
	./tokenizer "qwerty123456-+======<><><>< > > > > > 				0tuy       "
	./tokenizer "abc123 123 0x123ttt 07123zz123 1.23e10123e-10"
	./tokenizer "    \"hello world   \" 21312 asd 0x1 123 /*hello this is to be ignored*/ but this shou...12312 xxx 0x123adabnm //I think I can test this > now?"

clean:
	rm -rf *.o tokenizer
