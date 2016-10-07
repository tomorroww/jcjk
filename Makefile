COMPILER	:= g++

buildtype	:= debug

BASE_FLAGS	:= -Wall -Wextra -Wno-unused-parameter -Wconversion
C++FLAGS	:= $(BASE_FLAGS) `pkg-config --cflags opencv` -std=c++14
DEBUG_FLAGS	:= -g3 -O0 -DDEBUG
RELEASE_FLAGS	:= -O0 -DNDEBUG

LIBS		:= `pkg-config --libs opencv`

SOURCES_DIR	:= .
SOURCES		:= $(wildcard $(SOURCES_DIR)/*.cpp)

OBJ_DIR		:= ./obj
OBJECTS		:= $(addprefix $(OBJ_DIR)/$(buildtype)/, $(subst ./,,$(patsubst %.cpp,%.o,$(SOURCES))))

DEP_DIR		:= ./obj
DEPENDS		:= $(addprefix $(DEP_DIR)/$(buildtype)/, $(subst ./,,$(patsubst %.cpp,%.d,$(SOURCES))))

TARGET_DIR	:= ./bin
TARGET		:= $(TARGET_DIR)/$(buildtype)/object_detection


ifeq ($(buildtype), debug)
	CFLAGS += $(DEBUG_FLAGS)
else ifeq ($(buildtype), release)
	CFLAGS += $(RELEASE_FLAGS)
else
	$(echo buildtype must be debug or release)
	$(exit 1)
endif


all : $(TARGET)

run : $(TARGET)
	$(TARGET)

-include $(DEPENDS)


$(TARGET) : $(OBJECTS)
	@[ -d `dirname $@` ] || mkdir -p `dirname $@`
	$(COMPILER) $(OBJECTS) $(C++FLAGS) $(INCLUDE) $(LIBS_DIR) $(LIBS) -o $(TARGET)


$(OBJ_DIR)/$(buildtype)/%.o : $(SOURCES_DIR)/%.cpp Makefile
	@[ -d `dirname $@` ] || mkdir -p `dirname $@`
	$(COMPILER) -c -MMD -MP $< $(C++FLAGS) $(INCLUDE) -o $@ 

clean :
	rm -f -r $(TARGET) $(OBJECTS) $(DEPENDS) $(TARGET_DIR) $(OBJ_DIR)

