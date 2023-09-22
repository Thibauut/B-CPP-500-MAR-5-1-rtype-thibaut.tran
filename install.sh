#!/bin/sh
# Déterminer le système d'exploitation
os=$(uname)

# Vérifier si le système d'exploitation est Linux
if [ "$os" = "Linux" ]; then
    # Installer les dépendances nécessaires sur Linux
    sudo apt-get install libvorbis-dev libogg-dev
    sudo apt-get install libopenal-dev
    sudo apt-get install libflac-dev
    sudo apt-get install libfreetype6-dev
fi

rm -rf ./build/ && mkdir -p build && cmake -S . -B ./build/

# cmake -B . -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake

# git submodule add https://github.com/SFML/SFML.git libs/SFML




# #!/bin/sh
# mkdir -p build && cmake -S . -B ./build/ && make -C ./build/

# # cmake -B . -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake

# # git submodule add https://github.com/SFML/SFML.git libs/SFML