import project_paths as pp
import platform
import sys
import subprocess

def get_generator():
    generators = {
        'Windows': 'Visual Studio 16 2019',
        'Linux': 'Ninja Multi-Config',
        'Darwin': 'Xcode'
    }
    return generators[platform.system()]


if __name__ == "__main__":

    PLATFORM_GENERATOR = get_generator()
    cmake_command = ["cmake",
                    "-G", PLATFORM_GENERATOR,
                    "-S", pp.PROJECT_ROOT,
                    "-B", pp.BUILD_DIR,
                    "-D", f"CMAKE_INSTALL_PREFIX={pp.INSTALL_DIR}",
                    "-D", "BUILD_TESTS=ON"]

    subprocess.run(cmake_command)
