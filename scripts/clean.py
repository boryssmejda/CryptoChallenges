import argparse
import os
import project_paths as pp
import shutil
import sys


def delete_if_exists(FOLDER_PATH: str) -> None:
    if os.path.exists(FOLDER_PATH) and os.path.isdir(FOLDER_PATH):
        shutil.rmtree(FOLDER_PATH)
        print(f"Deleted successfully: {FOLDER_PATH}")
    else:
        print(f"{FOLDER_PATH} does not exist")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("folder-to-be-deleted", choices=['build', 'install', 'env', 'all'],
        help="Choose folder to be deleted, 'all' deletes build, install and venv at once")
    args = parser.parse_args()

    folder_to_be_deleted = vars(args)['folder-to-be-deleted']

    if folder_to_be_deleted == 'all':
        delete_if_exists(pp.INSTALL_DIR)
        delete_if_exists(pp.BUILD_DIR)
        delete_if_exists(pp.VENV_FOLDER_LOCATION)
    elif folder_to_be_deleted == "build":
        delete_if_exists(pp.BUILD_DIR)
    elif folder_to_be_deleted == "install":
        delete_if_exists(pp.INSTALL_DIR)
    elif folder_to_be_deleted == "env":
        delete_if_exists(pp.VENV_FOLDER_LOCATION)
