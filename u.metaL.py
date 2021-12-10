## @file
## @brief meta: embedded programming language / OS

from metaL import *

p = Project(
    title='''embedded programming language / OS''',
    about='''
* targets on embedded devices & IoT
* inspired by FORTH, Erlang (and Smalltalk ?)
* made as simple as can be for learning purposes
''') \
    | Cpp() \
    | Skelex()

p.sync()
