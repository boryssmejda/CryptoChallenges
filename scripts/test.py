"""Test module runs ctest on the project with given configuration"""

import sys
import os
import subprocess
import project_paths as pp

if __name__ == "__main__":
    assert (len(sys.argv) == 2), "No build type given! Aborting ..."

    CONFIGURATION = sys.argv[1]
    if CONFIGURATION not in ['Release', 'Debug']:
        raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

    try:
        os.chdir(pp.BUILD_DIR)
    except OSError:
        print(f"Can't change the cwd to: {pp.BUILD_DIR}")

    CMAKE_COMMAND = ['ctest', '--build-config', CONFIGURATION]
    subprocess.run(CMAKE_COMMAND, check=True)
