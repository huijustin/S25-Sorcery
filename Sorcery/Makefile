# Makefile for Sorcery

# Compiler and flags
CXX = g++-14
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla
LDFLAGS = -lX11

# Executable name
EXEC = sorcery

# Source files
OBJECTS = \
    main.o \
    Ability.o \
    ActivatedAbility.o \
    ascii_graphics.o \
    Board.o \
    BuffEffect.o \
    Card.o \
    CardFactory.o \
    DamageEffect.o \
    DarkRitual.o \
    Deck.o \
    Enchantment.o \
    EnrageEnchantment.o \
    GameEngine.o \
    GiantStrengthEnchantment.o \
    Graveyard.o \
    GraphicsView.o \
    Hand.o \
    HasteEnchantment.o \
    MagicFatigueEnchantment.o \
    Minion.o \
    Player.o \
    Ritual.o \
    SilenceEnchantment.o \
    Spell.o \
    SummonEffect.o \
    TextView.o \
    Window.o

DEPENDS = ${OBJECTS:.o=.d}

# Default target
${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} -o ${EXEC} ${OBJECTS} ${LDFLAGS}

# Include dependency files
-include ${DEPENDS}

# Phony targets
.PHONY: clean

# Clean up build files
clean:
	rm -f ${EXEC} ${OBJECTS} ${DEPENDS}
