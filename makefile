

test_qbot: test_qbot.c 
	gcc $^ -ldl -lncursesw -o $@ 

test: test_qbot
	./test_qbot

clean:
	rm -rf test_qbot
