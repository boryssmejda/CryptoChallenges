"""Install module runs cmake --install command to create library package"""

import sys
import subprocess
import project_paths as pp

if __name__ == "__main__":
    assert (len(sys.argv) == 2), "No build type given! Aborting ..."

    CONFIGURATION = sys.argv[1]
    if CONFIGURATION not in ['Release', 'Debug']:
        raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

    CMAKE_COMMAND = ['cmake', '--install', pp.BUILD_DIR, '--config', CONFIGURATION]
    subprocess.run(CMAKE_COMMAND, check=True)
