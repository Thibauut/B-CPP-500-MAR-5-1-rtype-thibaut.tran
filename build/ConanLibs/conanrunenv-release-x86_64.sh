script_folder="/home/maokoro/Bureau/Epitech/Tek3/B-CPP-500-MAR-5-1-rtype-maori.dino/build/ConanLibs"
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


export LD_LIBRARY_PATH="/home/maokoro/.conan2/p/b/sfml888f9897b2697/p/lib:/home/maokoro/.conan2/p/b/boost311955bc4ab84/p/lib:$LD_LIBRARY_PATH"
export DYLD_LIBRARY_PATH="/home/maokoro/.conan2/p/b/sfml888f9897b2697/p/lib:/home/maokoro/.conan2/p/b/boost311955bc4ab84/p/lib:$DYLD_LIBRARY_PATH"