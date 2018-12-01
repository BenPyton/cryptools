EXEC = aes
CXX = g++
CXX_FLAGS = -Wall -O2 -s
SRC_DIR = ./src
TMP_DIR = ./tmp
BIN_DIR = ./bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(TMP_DIR)/%.o,$(SOURCES))

all: $(EXEC)

# surement linker avec -pie
$(EXEC): prepare $(OBJECTS)
	@echo "Linking...";
	@$(CXX) -s -static -static-libgcc -static-libstdc++ -o $(BIN_DIR)/$(EXEC) $(OBJECTS);
	@echo "Done.";
	
$(TMP_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compile $<";
	@$(CXX) -fPIC -c $(CXX_FLAGS) $< -o $@;

prepare:
	@echo "Preparing...";

	@# Preparing obj directory
	@if [ ! -d $(TMP_DIR) ];\
	then\
		echo "Created: $(TMP_DIR)";\
		mkdir $(TMP_DIR);\
	fi;

	@# Preparing bin directory
	@if [ ! -d $(BIN_DIR) ];\
	then\
		echo "Created: $(BIN_DIR)";\
		mkdir $(BIN_DIR);\
	fi;
	

fresh: clean prepare $(EXEC)

clean:
	@echo "Cleaning...";
	@rm -fr $(TMP_DIR) $(BIN_DIR);
