script_folder="/Users/thibaut/Documents/B-CPP-500-MAR-5-1-rtype-maori.dino/bonus/Pong/build/ConanLibs"
echo "echo Restoring environment" > "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
for v in LD_LIBRARY_PATH DYLD_LIBRARY_PATH
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "$script_folder/deactivate_conanrunenv-release-x86_64.sh"
    fi
done


export LD_LIBRARY_PATH="/Users/thibaut/.conan2/p/b/sfml55efd878c5bfd/p/lib:/Users/thibaut/.conan2/p/b/booste645d7d84ab77/p/lib:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="/Users/thibaut/.conan2/p/b/sfml55efd878c5bfd/p/lib:/Users/thibaut/.conan2/p/b/booste645d7d84ab77/p/lib:$DYLD_LIBRARY_PATH"