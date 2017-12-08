SRC_DIR := ./src
INC_DIRS := ./include
BUILD_DIR := ./build

INC_FLAGS := $(addprefix -I,$(INC_DIRS))
CPPFLAGS := -std=c++11 -g $(INC_FLAGS) -O2 -MMD -MP

SRCS := $(shell cd $(SRC_DIR); find . -name "*.cpp")
OBJS := $(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(SRCS)))
DEPS := $(OBJS:.o=.d)

render: $(OBJS)
	g++ $(CPPFLAGS) $(OBJS) -o $@ $(LUA_LIBS);

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@ $(LUA_LIBS)

clean:
	rm -r $(BUILD_DIR)
	rm ./render

.PHONY: clean all

-include $(DEPS)
