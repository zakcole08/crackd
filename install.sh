#!/bin/bash

PROGRAM_NAME="crackd"
CONFIG_FILE="crackd.cnf"

if [[ ! -d /etc/$PROGRAM_NAME ]]; then
	sudo mkdir /etc/$PROGRAM_NAME
fi

if [[ ! -f /etc/$PROGRAM_NAME ]]; then
	cp $PROGRAM_NAME /etc/$PROGRAM_NAME
	sudo chmod +x /etc/$PROGRAM_NAME/$PROGRAM_NAME
fi

if [[ ! -f /etc/$PROGRAM_NAME/$CONFIG_FILE ]]; then
	sudo echo "TEXT_EDITOR=vim" >> /etc/$PROGRAM_NAME/$CONFIG_FILE
fi

sudo grep -Fxq "export PATH=/etc/crackd:\$PATH" "/etc/$PROGRAM_NAME/$CONFIG_FILE"
if [[ $? -ne 0 ]]; then
	sudo echo "export PATH=/etc/crackd:\$PATH" >> ~/.bashrc
fi

sudo exec ~/.bashrc