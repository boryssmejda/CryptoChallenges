"""Module deletes generated folders"""

import argparse
import os
import shutil
import project_paths as pp

def delete_if_exists(folder_path: str) -> None:
    """
    Deletes given folder, provided that it exists.

        Parameters:
            folder_path (str): Absolute path to the directory to be deleted

        Returns:
            None
    """
    if os.path.exists(folder_path) and os.path.isdir(folder_path):
        shutil.rmtree(folder_path)
        print(f"Deleted successfully: {folder_path}")
    else:
        print(f"{folder_path} does not exist")


if __name__ == "__main__":
    PARSER = argparse.ArgumentParser()
    PARSER.add_argument("folder-to-be-deleted", choices=['build', 'install', 'env', 'all'],
                        help="Choose folder to be deleted,"
                        "'all' deletes build, install and venv at once")
    ARGS = PARSER.parse_args()

    FOLDER_TO_BE_DELETED = vars(ARGS)['folder-to-be-deleted']

    if FOLDER_TO_BE_DELETED == 'all':
        delete_if_exists(pp.INSTALL_DIR)
        delete_if_exists(pp.BUILD_DIR)
        delete_if_exists(pp.VENV_FOLDER_LOCATION)
    elif FOLDER_TO_BE_DELETED == "build":
        delete_if_exists(pp.BUILD_DIR)
    elif FOLDER_TO_BE_DELETED == "install":
        delete_if_exists(pp.INSTALL_DIR)
    elif FOLDER_TO_BE_DELETED == "env":
        delete_if_exists(pp.VENV_FOLDER_LOCATION)
