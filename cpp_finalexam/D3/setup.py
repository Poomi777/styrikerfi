from distutils.core import setup, Extension

digit_module = Extension('digit_module',sources = ['digit_module.cpp'])
setup(name = 'DigitModule',version='1.0',description = 'This is a dumb module',ext_modules = [digit_module])
