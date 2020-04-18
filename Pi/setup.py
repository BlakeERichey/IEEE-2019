from setuptools import setup, find_packages

setup(name='victor',
      version='0.0.1',
      packages=find_packages(),
      description='V.I.C.T.O.R.',
      author = 'Blake Richey',
      author_email='blake.e.richey@gmail.com',
      install_requires=[
        # "opencv-python>=4.1.2.30",
        "scipy>=1.4.1",
        "matplotlib>=3.1",
        "pyserial>=3.4",
        "scikit-image>=0.15.0",
        "scikit-learn>=0.22.1"
      ],)