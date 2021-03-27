"""Builds and configures the project"""

import argparse
import platform
import subprocess
import project_paths as pp

def get_generator() -> str:
    generators = {
        'Windows': 'Visual Studio 16 2019',
        'Linux': 'Ninja Multi-Config',
        'Darwin': 'Xcode'
    }
    return generators[platform.system()]

def build_target(BUILD_CONFIGURATION: str, TARGET_NAME: str) -> None:
    assert (BUILD_CONFIGURATION in ["Debug", "Release"]), "Unknown build configuration!"

    BUILD_COMMAND = ['cmake', '--build', pp.BUILD_DIR,
                         '--config', BUILD_CONFIGURATION,
                         '--target', TARGET_NAME]

    CommandExecutor.execute_command(BUILD_COMMAND)

class CommandExecutor:
    @staticmethod
    def execute_command(COMMAND) -> None:
        subprocess.run(COMMAND, check=True)

class CMakeConfigurationCommandBuilder:
    def __init__(self):
        generator = get_generator()
        self.cmake_command = ["cmake",
                               "-G", generator,
                               "-S", pp.PROJECT_ROOT,
                               "-B", pp.BUILD_DIR,
                               "-D", f"OPENSSL_ROOT_DIR={pp.PROJECT_ROOT}/deps/OpenSSL/lib",
                               "-D", f"CMAKE_PREFIX_PATH={pp.PROJECT_ROOT}/deps",
                               "-D", f"CMAKE_INSTALL_PREFIX={pp.INSTALL_DIR}"]

        self.SHOULD_BUILD_TESTS = None
        self.SHOULD_CREATE_CODE_COVERAGE = None
        self.SHOULD_USE_VALGRIND = None

    def shouldBuildWithUnitTests(self, SHOULD_BUILD_TESTS: bool):
        self.SHOULD_BUILD_TESTS = SHOULD_BUILD_TESTS
        return self

    def shouldUseValgrind(self, SHOULD_USE_VALGRIND: bool):
        self.SHOULD_USE_VALGRIND = SHOULD_USE_VALGRIND
        return self

    def shouldBuildWithCodeCoverage(self, SHOULD_CREATE_CODE_COVERAGE: bool):
        self.SHOULD_CREATE_CODE_COVERAGE = SHOULD_CREATE_CODE_COVERAGE
        return self

    def build(self):
        assert (self.SHOULD_BUILD_TESTS is not None), "SHOULD_BUILD_TESTS not set!"
        assert (self.SHOULD_CREATE_CODE_COVERAGE is not None), "SHOULD_CREATE_CODE_COVERAGE not set!"
        assert (self.SHOULD_USE_VALGRIND is not None), "SHOULD_USE_VALGRIND not set!"

        self.cmake_command += ["-D", f"RUN_UT_VALGRIND={self.SHOULD_USE_VALGRIND}"]
        self.cmake_command += ["-D", f"ENABLE_COVERAGE={self.SHOULD_CREATE_CODE_COVERAGE}"]
        self.cmake_command += ["-D", f"BUILD_TESTS={self.SHOULD_BUILD_TESTS}"]

        return self.cmake_command

class CryptoLibBuild:
    def __init__(self, CONFIGURATION: str):
        if CONFIGURATION not in ['Release', 'Debug']:
            raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

        self.BUILD_CONFIGURATION = CONFIGURATION
        self.TARGET_NAME = "cryptoLib"
        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        CMAKE_COMMAND = CMakeConfigurationCommandBuilder() \
                        .shouldBuildWithCodeCoverage(False) \
                        .shouldBuildWithUnitTests(False) \
                        .shouldUseValgrind(False) \
                        .build()

        CommandExecutor.execute_command(CMAKE_COMMAND)

    def build(self):
        build_target(self.BUILD_CONFIGURATION, self.TARGET_NAME)

class UnitTestBuild:
    def __init__(self, CONFIGURATION: str):
        if CONFIGURATION not in ['Release', 'Debug']:
            raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

        self.BUILD_CONFIGURATION = CONFIGURATION
        self.TARGET_NAME = "ut"
        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        CMAKE_COMMAND = CMakeConfigurationCommandBuilder() \
                        .shouldBuildWithUnitTests(True) \
                        .shouldUseValgrind(False) \
                        .shouldBuildWithCodeCoverage(False) \
                        .build()

        CommandExecutor.execute_command(CMAKE_COMMAND)

    def build(self):
        build_target(self.BUILD_CONFIGURATION, self.TARGET_NAME)

class CodeCoverageBuild:
    def __init__(self):
        self.BUILD_CONFIGURATION = "Debug"
        self.TARGET_NAME = "ut_coverage"
        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        CMAKE_COMMAND = CMakeConfigurationCommandBuilder() \
                        .shouldBuildWithUnitTests(True) \
                        .shouldUseValgrind(False) \
                        .shouldBuildWithCodeCoverage(True) \
                        .build()

        CommandExecutor.execute_command(CMAKE_COMMAND)

    def build(self):
        build_target(self.BUILD_CONFIGURATION, self.TARGET_NAME)

class UnitTestBuildWithValgrind:
    def __init__(self):
        self.BUILD_CONFIGURATION = "Debug"
        self.TARGET_NAME = "ut_valgrind"
        self.configure_cmake()
        self.build()

    def configure_cmake(self):
        CMAKE_COMMAND = CMakeConfigurationCommandBuilder() \
                        .shouldBuildWithUnitTests(True) \
                        .shouldUseValgrind(True) \
                        .shouldBuildWithCodeCoverage(False) \
                        .build()

        CommandExecutor.execute_command(CMAKE_COMMAND)

    def build(self):
        build_target(self.BUILD_CONFIGURATION, self.TARGET_NAME)

if __name__ == "__main__":
    PARSER = argparse.ArgumentParser()
    PARSER.add_argument("build_target", choices=['crypto_debug', 'crypto_release',
                                                 'ut_debug', 'ut_release',
                                                 'ut_coverage', 'ut_valgrind',
                                                 'static_analysis'])
    ARGS = PARSER.parse_args()

    BUILD_TARGET = vars(ARGS)['build_target']

    if BUILD_TARGET == 'crypto_debug':
        CRYPTO_LIB_BUILD_DEBUG = CryptoLibBuild(CONFIGURATION="Debug")
    elif BUILD_TARGET == 'crypto_release':
        CRYPTO_LIB_BUILD_RELEASE = CryptoLibBuild(CONFIGURATION="Release")
    elif BUILD_TARGET == 'ut_debug':
        UNIT_TEST_BUILD_DEBUG = UnitTestBuild(CONFIGURATION="Debug")
    elif BUILD_TARGET == 'ut_release':
        UNIT_TEST_BUILD_RELEASE = UnitTestBuild(CONFIGURATION="Release")
    elif BUILD_TARGET == 'ut_coverage':
        CODE_COVERAGE_BUILD = CodeCoverageBuild()
    elif BUILD_TARGET == 'ut_valgrind':
        UT_VALGRIND_BUILD = UnitTestBuildWithValgrind()


"""
* You should always run configure cmake as first!

What options you want to have:
1) Build crypto library -> run.py [crypto_debug,crypto_release]
2) Build and run ut -> this would force also to build 1) -> run.py [ut_debug, ut_release]
3) Build and run ut together with code coverage analysis -> run.py [ut_coverage] // debug configuration
4) Build and run ut together with valgrind check -> run.py [ut_valgrind] // build would be as debug configuration
5) Run static analysis tool like clang-tidy -> run.py clang_tidy
"""
