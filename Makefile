# Define the link target.
linkTarget = a.out

HOME = /home/runner/HoseoSDL

SRC_DIR := $(HOME)/src
INC_DIR := $(HOME)/include
OBJ_DIR := $(HOME)/build
BIN_DIR := $(HOME)/bin
SDL_INC := $(HOME)/3rdParty/SDL/include
SDL_LIB := $(HOME)/3rdParty/SDL/lib/x86_64-linux-gnu


EXE := $(BIN_DIR)/a.out
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP -I$(INC_DIR) -I$(SDL_INC) 
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm
SDL_LIBS := -L$(SDL_LIB)/libSDL2_2.0.so -lSDL2 -L$(SDL_LIB)/libSDL2_image-2.0.so $(SDL_LIB)/libSDL2_image.a -lpng -ljpeg -ltiff -lwebp -L $(SDL_LIB)/libSDL2_gfx.so $(SDL_LIB)/libSDL2_gfx.a

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(SDL_LIBS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)

run: $(EXE)
	$(EXE)