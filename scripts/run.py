"""Builds and configures the project"""

import argparse
import platform
import sys
import subprocess
import project_paths as pp

def get_generator() -> str:
    generators = {
        'Windows': 'Visual Studio 16 2019',
        'Linux': 'Ninja Multi-Config',
        'Darwin': 'Xcode'
    }
    return generators[platform.system()]

class CryptoLibBuild:
    def __init__(self, CONFIGURATION:str):
        if CONFIGURATION not in ['Release', 'Debug']:
            raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

        self.BUILD_CONFIGURATION = CONFIGURATION

        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        generator = get_generator()
        cmake_command = ["cmake",
                     "-G", generator,
                     "-S", pp.PROJECT_ROOT,
                     "-B", pp.BUILD_DIR,
                     "-D", f"CMAKE_INSTALL_PREFIX={pp.INSTALL_DIR}"]

        subprocess.run(cmake_command, check=True)

    def build(self):
        CMAKE_COMMAND = ['cmake', '--build', pp.BUILD_DIR,
                         '--config', self.BUILD_CONFIGURATION,
                         '--target', 'cryptoLib']

        subprocess.run(CMAKE_COMMAND, check=True)

class UnitTestBuild:
    def __init__(self, CONFIGURATION: str):
        if CONFIGURATION not in ['Release', 'Debug']:
            raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

        self.BUILD_CONFIGURATION = CONFIGURATION

        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        generator = get_generator()
        cmake_command = ["cmake",
                     "-G", generator,
                     "-S", pp.PROJECT_ROOT,
                     "-B", pp.BUILD_DIR,
                     "-D", f"CMAKE_INSTALL_PREFIX={pp.INSTALL_DIR}",
                     "-D", "BUILD_TESTS=ON"]

        subprocess.run(cmake_command, check=True)

    def build(self):
        CMAKE_COMMAND = ['cmake', '--build', pp.BUILD_DIR, '--config', self.BUILD_CONFIGURATION, '--target', 'ut']
        subprocess.run(CMAKE_COMMAND, check=True)

class CodeCoverageBuild:
    def __init__(self):
        self.BUILD_CONFIGURATION = "Debug"

        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        generator = get_generator()
        cmake_command = ["cmake",
                     "-G", generator,
                     "-S", pp.PROJECT_ROOT,
                     "-B", pp.BUILD_DIR,
                     "-D", f"CMAKE_INSTALL_PREFIX={pp.INSTALL_DIR}",
                     "-D", "BUILD_TESTS=ON",
                     "-D", "ENABLE_COVERAGE=ON"]

        subprocess.run(cmake_command, check=True)

    def build(self):
        CMAKE_COMMAND = ['cmake', '--build', pp.BUILD_DIR, '--config', self.BUILD_CONFIGURATION, '--target', 'ut_coverage']
        subprocess.run(CMAKE_COMMAND, check=True)

if __name__ == "__main__":
    PARSER = argparse.ArgumentParser()
    PARSER.add_argument("build_target", choices=['crypto_debug', 'crypto_release', 'ut_debug', 'ut_release',
        'ut_coverage', 'ut_valgrind', 'static_analysis'
    ])
    ARGS = PARSER.parse_args()

    BUILD_TARGET = vars(ARGS)['build_target']

    if BUILD_TARGET == 'crypto_debug':
        cryptoLibBuildDebug = CryptoLibBuild(CONFIGURATION="Debug")
    elif BUILD_TARGET == 'crypto_release':
        cryptoLibBuildRelease = CryptoLibBuild(CONFIGURATION="Release")
    elif BUILD_TARGET == 'ut_debug':
        unitTestBuildDebug = UnitTestBuild(CONFIGURATION="Debug")
    elif BUILD_TARGET == 'ut_release':
        unitTestBuildRelease = UnitTestBuild(CONFIGURATION="Release")
    elif BUILD_TARGET == 'ut_coverage':
        codeCoverageBuild = CodeCoverageBuild()
    elif BUILD_TARGET == 'ut_valgrind':
        pass


"""
* You should always run configure cmake as first!

What options you want to have:
1) Build crypto library -> run.py [crypto_debug,crypto_release]
2) Build and run ut -> this would force also to build 1) -> run.py [ut_debug, ut_release]
3) Build and run ut together with code coverage analysis -> run.py [ut_coverage] // debug configuration
4) Build and run ut together with valgrind check -> run.py [ut_valgrind] // build would be as debug configuration
5) Run static analysis tool like clang-tidy -> run.py clang_tidy
"""