# Rebuilds the bouncer application into an executable named "bouncer".  
# (This should be the default rule.)
all:	
	g++ main.c `pkg-config --cflags --libs libavutil libavformat libavcodec libswscale` -o bouncer

# Removes the bouncer application, all .o files, all movie files, and all 
# .mpff files from the directory.
clean:	
	rm *.o *.mpff *.mp4;

# Uses ffmpeg to assemble the 300 frames of the movie into an .mp4 movie 
# named "movie.mp4".
movie:	
	ffmpeg -r 25 -i frame%03d.mpff movie.mp4