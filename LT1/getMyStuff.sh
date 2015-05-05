#!/bin/bash
echo "User ID: "
id -u
echo "Primary group ID: "
id -g
echo "The names of all groups you belong to: "
id -Gn
echo "The absolute path of the bash shell: "
whereis bash
echo "The absolute path of your home directory: "
echo $HOME
echo "Your PATH environment variable: "
echo $PATH
