TARGETS = input.cpp text.cpp intro.cpp main.cpp
INCLUDES = -I*.hpp
LIBS = -lsfml-system -lsfml-window -lsfml-graphics

all: $(TARGETS)
	c++ -o escape $(INCLUDES) $(LIBS) $(TARGETS)

clean:
	$(RM) escape
