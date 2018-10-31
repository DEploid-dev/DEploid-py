#import subprocess
#import platform
import os
import os.path
#from warnings import warn

from setuptools import setup, Extension
#from setuptools.command.build_ext import build_ext as _build_ext


#CONDA_PREFIX = os.getenv("MSP_CONDA_PREFIX", None)
#IS_WINDOWS = platform.system() == "Windows"

libdir = "DEploid/src/"
includes = [libdir]

lasso_dir = "lasso/"
random_dir = "random/"
gzstream_dir = "gzstream/"
codeCogs_dir = "codeCogs/"

source_files = [
    "dEploidIO.cpp", "panel.cpp", "variantIndex.cpp", "txtReader.cpp",
    "vcfReader.cpp", "ibd.cpp", "updateHap.cpp", "mcmc.cpp", "utility.cpp",
    os.path.join(lasso_dir,"dEploidLasso.cpp"),
    os.path.join(lasso_dir, "lasso.cpp"),
    os.path.join(random_dir, "fastfunc.cpp"),
    os.path.join(random_dir, "mersenne_twister.cpp"),
    os.path.join(random_dir, "random_generator.cpp"),
    os.path.join(gzstream_dir, "gzstream.cpp")
]


dEploid_module = Extension(
    'dEploid',
    sources=["dEploid-py.cpp"] + [os.path.join(libdir, f) for f in source_files],
    extra_compile_args=['-std=c++0x', '-lz'],
    undef_macros=["NDEBUG"],
    define_macros = [("DDEPLOIDVERSION","todo"), ("DLASSOVERSION","todo"), ("DCOMPILEDATE","todo"), ("DVERSION", "todo")],
    include_dirs=["DEploid/"] + includes
)

setup(
    name="dEploid",
    description="dEploid CPP module",
    author="Joe Zhu",
    author_email="joe.zhu@bdi.ox.ac.uk",
    url="https://github.com/DEploid-dev/DEploid-py",
    ext_modules=[dEploid_module])

