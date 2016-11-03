OPT = -O0 -g -std=c++11
SRC_FOLDER = .
LIB = -lfltk -lfltk_gl -lGL -lGLU -lglut

FILES = Main.cpp

DEPFILES = draw.cpp \
           form.cpp \
           Frame_1.cpp

SRC = $(addprefix $(SRC_FOLDER)/, $(FILES))
DEP_SRC = $(addprefix $(SRC_FOLDER)/, $(DEPFILES))

EXES = $(addsuffix .exe, $(basename $(FILES)))
DEPS = $(addsuffix .o, $(basename $(DEPFILES)))

all : $(DEPS)
all : $(EXES)


%.o: $(SRC_FOLDER)/%.cpp
	$(CXX) $(OPT) -c -o $@ $<

%.exe: $(SRC_FOLDER)/%.cpp
	$(CXX) $(OPT) -o $@ $(DEPS) $< $(LIB)

clean:
	rm -f $(DEPS)

cleanall: clean
	rm -f $(EXES)

