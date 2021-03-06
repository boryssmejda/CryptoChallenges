import os

SCRIPTS_LOCATION = os.getcwd() # PROJECT_ROOT/scripts/
PROJECT_ROOT = os.path.dirname(SCRIPTS_LOCATION)
BUILD_DIR = os.path.join(PROJECT_ROOT, "build")
INSTALL_DIR = os.path.join(PROJECT_ROOT, "install")

CONAN_FOLDER_LOCATION = os.path.join(PROJECT_ROOT, "conan")
CONANFILE_DESKTOP_LOCATION = os.path.join(CONAN_FOLDER_LOCATION, "conanfiles", "conanfile.txt")

CONAN_PROFILES_ROOT = os.path.join(CONAN_FOLDER_LOCATION, "profiles")
CONAN_PROFILE_LOCATION_LINUX = os.path.join(CONAN_PROFILES_ROOT, "conan-profile-linux.txt")

VENV_FOLDER_LOCATION = os.path.join(PROJECT_ROOT, "env")
VENV_ACTIVATE_LOCATION = os.path.join(VENV_FOLDER_LOCATION, "bin", "activate")

def print_project_paths():
    print(f"SCRIPTS_LOCATION: {SCRIPTS_LOCATION}")
    print(f"PROJECT_ROOT: {PROJECT_ROOT}")
    print(f"BUILD_DIR: {BUILD_DIR}")
    print(f"INSTALL_DIR: {INSTALL_DIR}")

    print(f"CONAN_FOLDER_LOCATION: {CONAN_FOLDER_LOCATION}")
    print(f"CONANFILE_DESKTOP_LOCATION: {CONANFILE_DESKTOP_LOCATION}")

    print(f"CONAN_PROFILES_ROOT: {CONAN_PROFILES_ROOT}")
    print(f"CONAN_PROFILE_LOCATION_LINUX: {CONAN_PROFILE_LOCATION_LINUX}")

    print(f"VENV_FOLDER_LOCATION: {VENV_FOLDER_LOCATION}")


if __name__ == "__main__":
    print_project_paths()