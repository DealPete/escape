SOURCE = *.cpp
LIBS = -lsfml-system -lsfml-window -lsfml-graphics

all: source images/pass.png

images/pass.png: images/pass.svg
	convert -size 100x100 -background none images/pass.svg images/pass.png

source:
	c++ -o escape $(LIBS) $(SOURCE) -std=c++11

debug:
	c++ -o escape $(LIBS) $(SOURCE) -std=c++11 -g

clean:
	$(RM) escape
