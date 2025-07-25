# Makefile for Sorcery

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
LDFLAGS = -lX11

# Executable name
TARGET = sorcery

# Source files
SRCS = \
    main.cc \
    Ability.cc \
    ActivatedAbility.cc \
    ascii_graphics.cc \
    Board.cc \
    BuffEffect.cc \
    Card.cc \
    CardFactory.cc \
    DamageEffect.cc \
    DarkRitual.cc \
    Deck.cc \
    Enchantment.cc \
    EnrageEnchantment.cc \
    GameEngine.cc \
    GiantStrengthEnchantment.cc \
    Graveyard.cc \
    GraphicView.cc \
    Hand.cc \
    HasteEnchantment.cc \
    MagicFatigueEnchantment.cc \
    Minion.cc \
    Player.cc \
    Ritual.cc \
    SilenceEnchantment.cc \
    Spell.cc \
    SummonEffect.cc \
    TextView.cc \
    Window.cc

# Object files
OBJS = $(SRCS:.cc=.o)

# Phony targets
.PHONY: all clean

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile source files into object files
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
	