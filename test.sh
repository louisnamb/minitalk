#!/bin/bash
random_string=$(openssl rand -base64 $1)
pid=$(ps | grep "\.\/server" | awk '{print $1}')
./client $pid "$random_string"
