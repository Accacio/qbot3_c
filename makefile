all: test_qbot test_qbot_video

test_qbot: test_qbot.c qbot.h
	gcc $^ -ldl -lncursesw -o $@ 

test_qbot_video: test_qbot_video.c  qbot.h qbot_video.h
	gcc $^ -ldl -ljpeg -lncursesw -o $@ 

test: test_qbot
	./test_qbot
video: test_qbot_video
	./test_qbot_video

clean:
	rm -rf test_qbot
	rm -rf test_qbot_video

.PHONY: all
