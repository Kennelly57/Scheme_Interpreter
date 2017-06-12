#!/bin/bash

exec valgrind --dsymutil=yes --leak-check=full --show-leak-kinds=all -v --track-origins=yes ./parser
