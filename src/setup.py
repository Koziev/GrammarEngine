from setuptools import setup, Extension

setup(
    name='Solarix',
    version='0.0.1',
    packages=['pyparser',],
    license='Creative Commons Attribution-Noncommercial-Share Alike license',
    long_description=open('README.txt').read(),
    author = 'Ilya Koziev',
    author_email = 'inkoziev@gmail.com',
    url = 'http://solarix.ru',
    include_package_data=True,
    #data_files=[('pyparser', ['pyparser.pyd', 'libdesr.dll', 'sqlite.dll', 'msvcp140.dll', 'vcruntime140.dll']),],
    classifiers=[
        # Trove classifiers
        # The full list is here: https://pypi.python.org/pypi?%3Aaction=list_classifiers
        'Development Status :: 3 - Alpha',
    ]    
)
