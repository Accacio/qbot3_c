

test_qbot: test_qbot.c qbot.h
	gcc $^ -ldl -lncursesw -o $@ 

test: test_qbot
	./test_qbot

clean:
	rm -rf test_qbot
