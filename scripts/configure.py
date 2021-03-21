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

def configure_cmake() -> None:
    generator = get_generator()
    cmake_command = ["cmake",
                     "-G", generator,
                     "-S", pp.PROJECT_ROOT,
                     "-B", pp.BUILD_DIR,
                     "-D", f"CMAKE_INSTALL_PREFIX={pp.INSTALL_DIR}",
                     "-D", "BUILD_TESTS=ON",
                     "-D", "ENABLE_COVERAGE=ON"]

    subprocess.run(cmake_command, check=True)


if __name__ == "__main__":

    configure_cmake()

# build
# ut_build
# ut_coverage

# build -> no flags
# ut_build -> BUILD_TESTS=ON
# ut_coverage -> BUILD_TESTS=ON ENABLE_COVERAGE=ON
# ut_valgrind
