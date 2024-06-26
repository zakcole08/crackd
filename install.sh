#!/bin/bash

PROGRAM_NAME="crackd"
CONFIG_FILE="crackd.cnf"

if [[ ! -d /etc/$PROGRAM_NAME ]]; then
        sudo mkdir /etc/$PROGRAM_NAME
fi

if [[ ! -f /etc/$PROGRAM_NAME ]]; then
        sudo cp $PROGRAM_NAME /etc/$PROGRAM_NAME
        sudo chmod +x /etc/$PROGRAM_NAME/$PROGRAM_NAME
fi

if [[ ! -f /etc/$PROGRAM_NAME/$CONFIG_FILE ]]; then
    sudo touch /etc/$PROGRAM_NAME/$CONFIG_FILE
        echo "TEXT_EDITOR=vim" | tee /etc/$PROGRAM_NAME/$CONFIG_FILE
fi

sudo grep -Fxq "export PATH=/etc/crackd:\$PATH" "$HOME/.bashrc"
if [[ $? -ne 0 ]]; then
        sudo echo "export PATH=/etc/crackd:\$PATH" >> ~/.bashrc
fi

sudo grep -Fxq "alias vim=crackd" "$HOME/.bashrc"
if [[ $? -ne 0 ]]; then
    sudo echo "alias vim=crackd" >> ~/.bashrc        # Probably want to make this optional
fi

exec bash
