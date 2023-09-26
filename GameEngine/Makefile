# Nom du compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -Wextra -std=c++11

# Nom du fichier exécutable
TARGET = myEngine

# Liste des fichiers source
SOURCES = GameEngine.cpp

# Liste des fichiers objets générés à partir des fichiers source
OBJECTS = $(SOURCES:.cpp=.o)

# Règle pour la cible principale (le fichier exécutable)
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Règle générique pour la compilation des fichiers source en fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJECTS) $(TARGET)

# Règle pour clean et recompile
re: clean $(TARGET)
