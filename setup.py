# import subprocess
# import platform
import os
import os.path
import datetime

# from warnings import warn

from setuptools import setup, Extension
# from setuptools.command.build_ext import build_ext as _build_ext


now = datetime.datetime.now()


# CONDA_PREFIX = os.getenv("MSP_CONDA_PREFIX", None)
# IS_WINDOWS = platform.system() == "Windows"

libdir = "lib/src/"
includes = [libdir]

lasso_dir = "lasso/"
random_dir = "random/"
gzstream_dir = "gzstream/"
codeCogs_dir = "codeCogs/"
dbg_dir = "debug/"
export_dir = "export/"

source_files = [
    "dEploidIO.cpp", "panel.cpp", "variantIndex.cpp", "txtReader.cpp",
    "vcfReader.cpp", "ibd.cpp", "updateHap.cpp", "mcmc.cpp", "utility.cpp",
    os.path.join(lasso_dir, "dEploidLasso.cpp"),
    os.path.join(lasso_dir, "lasso.cpp"),
    os.path.join(lasso_dir, "lassoDBG.cpp"),
    os.path.join(random_dir, "fastfunc.cpp"),
    os.path.join(random_dir, "mersenne_twister.cpp"),
    os.path.join(random_dir, "random_generator.cpp"),
    os.path.join(gzstream_dir, "gzstream.cpp"),
    os.path.join(dbg_dir, "mcmcDebug.cpp"),
    os.path.join(dbg_dir, "vcfReaderDebug.cpp"),
    os.path.join(export_dir, "dEploidIOExport.cpp"),
    os.path.join(export_dir, "dEploidIOExportPosteriorProb.cpp"),
    os.path.join(export_dir, "writeMcmcRelated.cpp")
]

compileData = str("\"") + now.strftime("%Y-%m-%d") + str("\"")


def get_v(obj_dir):
    cwd = os.getcwd()
    os.chdir(obj_dir)
    ret = str("\"") + os.popen(
        "git show HEAD | head -1 | sed -e \"s/commit //g\" | cat").read(
        ).strip("\n") + str("\"")
    os.chdir(cwd)
    return ret


dEploid_v = get_v("lib/")
lasso_v = get_v("lib/DEploid-Lasso-lib")


_dEploid_module = Extension(
    '_dEploid',
    sources=["dEploid-py.cpp"] + [
        os.path.join(libdir, f) for f in source_files],
    extra_compile_args=['-std=c++0x'],
    extra_link_args=['-lz'],
    undef_macros=["NDEBUG"],
    define_macros=[("VERSION", "\"python\""), ("DEPLOIDVERSION", dEploid_v),
                   ("LASSOVERSION", lasso_v), ("COMPILEDATE", compileData)],
    include_dirs=["lib/"] + includes
)

setup(
    name="dEploid",
    packages=['dEploid'],
    description="dEploid CPP module",
    author="Joe Zhu",
    version="0.6.0.1",
    author_email="joe.zhu@bdi.ox.ac.uk",
    url="https://github.com/DEploid-dev/DEploid-py",
    ext_modules=[_dEploid_module],
    keywords=["deconvolution", "mixed infection"],
    license="GNU GPLv3+",
    platforms=["POSIX"],
    classifiers=[
        "Programming Language :: C++",
        "Programming Language :: C",
        "Programming Language :: Python",
        "Development Status :: 2 - Pre-Alpha",
        "Environment :: Other Environment",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: GNU General Public License v3 or later (GPLv3+)",
        "Operating System :: POSIX",
        "Operating System :: MacOS :: MacOS X",
        "Operating System :: Microsoft :: Windows",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Bio-Informatics",
    ],
)
