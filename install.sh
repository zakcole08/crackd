#!/bin/bash

PROGRAM_NAME="crackd"
CONFIG_FILE="crackd.cnf"

if [[ ! -d /etc/$PROGRAM_NAME ]]; then
	mkdir /etc/$PROGRAM_NAME
fi

if [[ ! -f /etc/$PROGRAM_NAME ]]; then
	cp $PROGRAM_NAME /etc/$PROGRAM_NAME
	chmod +x /etc/$PROGRAM_NAME/$PROGRAM_NAME
fi

if [[ ! -f /etc/$PROGRAM_NAME/$CONFIG_FILE ]]; then
	echo "TEXT_EDITOR=vim" >> /etc/$PROGRAM_NAME/$CONFIG_FILE
fi

grep -Fxq "export PATH=/etc/crackd:\$PATH" "/etc/$PROGRAM_NAME/$CONFIG_FILE"
if [[ $? -eq 1 ]]; then
	echo "export PATH=/etc/crackd:\$PATH" >> ~/.bashrc
fi

exec ~/.bashrc