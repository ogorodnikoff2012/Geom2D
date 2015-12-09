#!/usr/bin/env python3

from sys import *

for filename in stdin:
    name = filename[:-1]
    print("\chapter{" + name.replace("_", "\_") + "}")
    print("\inputminted{c++}{" + name + "}")
    print()
