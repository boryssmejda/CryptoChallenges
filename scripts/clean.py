import project_paths as pp
import os
import shutil


def delete_if_exists(FOLDER_PATH: str) -> None:
    if os.path.exists(FOLDER_PATH) and os.path.isdir(FOLDER_PATH):
        shutil.rmtree(FOLDER_PATH)
        print(f"Deleted successfully: {FOLDER_PATH}")
    else:
        print(f"{FOLDER_PATH} does not exist")


if __name__ == "__main__":
    delete_if_exists(pp.INSTALL_DIR)
    delete_if_exists(pp.BUILD_DIR)
