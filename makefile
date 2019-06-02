TARGETS = escape.cpp
INCLUDES =
LIBS = -lsfml-system -lsfml-window 

all: $(TARGETS)
	c++ -o escape $(INCLUDES) $(LIBS) $(TARGETS)

clean:
	$(RM) escape
