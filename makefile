PNGS = images/green-hat.png images/red-hat.png images/dark-blue-hat.png images/med-blue-hat.png
SOURCE = main.cpp intro.cpp maze.cpp draw.cpp men.cpp random.cpp state.cpp writer.cpp
LIBS = -lsfml-system -lsfml-window -lsfml-graphics

all: source images/pass.png $(PNGS)

images/pass.png: images/pass.svg
	convert -size 100x100 -background none images/pass.svg images/pass.png

images/%.png: images/%.svg
	convert -size 1280x960 -background none $< $@

source:
	c++ -o escape $(LIBS) $(SOURCE) -std=c++11

debug:
	c++ -o escape $(LIBS) $(SOURCE) -std=c++11 -g

clean:
	$(RM) escape images/*.png
