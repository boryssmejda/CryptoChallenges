import project_paths as pp
import os
import shutil
import sys


def delete_if_exists(FOLDER_PATH: str) -> None:
    if os.path.exists(FOLDER_PATH) and os.path.isdir(FOLDER_PATH):
        shutil.rmtree(FOLDER_PATH)
        print(f"Deleted successfully: {FOLDER_PATH}")
    else:
        print(f"{FOLDER_PATH} does not exist")


if __name__ == "__main__":

    AVAILABLE_CONFIGURATIONS = ["all", "build", "install", "venv"]

    if len(sys.argv) == 2:
        configuration = sys.argv[1]
    else:
        configuration = "build"

    assert(configuration in AVAILABLE_CONFIGURATIONS), "Incorrect configuration! Aborting...."

    if configuration == "all":
        delete_if_exists(pp.INSTALL_DIR)
        delete_if_exists(pp.BUILD_DIR)
        delete_if_exists(pp.VENV_FOLDER_LOCATION)
    elif configuration == "build":
        delete_if_exists(pp.BUILD_DIR)
    elif configuration == "install":
        delete_if_exists(pp.INSTALL_DIR)
    elif configuration == "venv":
        delete_if_exists(pp.VENV_FOLDER_LOCATION)
