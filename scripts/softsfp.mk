SOFTSFP_INC = $(SOFTSFP_HOME)/include
SOFTSFP_SRC = $(SOFTSFP_HOME)/src
SOFTSFP_BUILD_DIR =$(SOFTSFP_HOME)/build
SOFTSFP_OBJS = $(addprefix $(SOFTSFP_BUILD_DIR)/, $(addsuffix .o, $(basename \
	$(notdir $(shell find $(SOFTSFP_SRC) -name "*.c" -o -name "*.cc")))))

SOFTSFP_ARCHIVE = $(SOFTSFP_BUILD_DIR)/softsfp.a

CC = clang
CXX = clang++

FLAGS = -I$(SOFTSFP_INC) -O2 -Wall -g
CFLAGS = -std=c99 $(FLAGS)
CXXFLAGS = -std=c++11 $(FLAGS)

.PHONY: softsfp_archive softsfp_clean

softsfp_archive: $(SOFTSFP_ARCHIVE)

$(SOFTSFP_ARCHIVE): $(SOFTSFP_OBJS) | $(SOFTSFP_BUILD_DIR)
	$(AR) -rcs $@ $^

$(SOFTSFP_BUILD_DIR)/%.o: $(SOFTSFP_SRC)/%.cc | $(SOFTSFP_BUILD_DIR)
	$(CXX) -o $@ $(CXXFLAGS) -c $^

$(SOFTSFP_BUILD_DIR)/%.o: $(SOFTSFP_SRC)/%.c | $(SOFTSFP_BUILD_DIR)
	$(CC) -o $@ $(CFLAGS) -c $^

$(SOFTSFP_BUILD_DIR):
	mkdir -p $@

softsfp_clean:
	-rm -rf $(SOFTSFP_BUILD_DIR)
