import project_paths as pp
import sys
import subprocess


if __name__ == "__main__":
    assert (len(sys.argv) == 2), "No build type given! Aborting ..."

    CONFIGURATION = sys.argv[1]
    if CONFIGURATION not in ['Release', 'Debug']:
        raise ValueError(f"Unknown Configuration: {CONFIGURATION}")

    cmake_command = ['cmake', '--build', pp.BUILD_DIR,
                            '--parallel', '4',
                            '--config', CONFIGURATION,]
    subprocess.run(cmake_command)
