# Variáveis
CXX = g++
CXXFLAGS = -Iinclude -g
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/tp1.out

# Regra padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $^ -o $@

# Regra para criar os arquivos objeto
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para limpar arquivos compilados
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/tp1.out

# Regra para depurar o Makefile
print-%  : ; @echo $* = $($*)

